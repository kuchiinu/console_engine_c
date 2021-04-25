#include "DrawManager.h"
#include <stdlib.h>

struct DrawManager draw;

//コンソールと描画機能の初期化
void DrawManager_init(void)
{
	//初期設定の数値を反映
	draw.screen_width = SCREEN_WIDTH;
	draw.screen_height = SCREEN_HEIGHT;
	draw.font_width = FONT_WIDTH;
	draw.font_height = FONT_HEIGHT;

	draw.handle = GetStdHandle(STD_OUTPUT_HANDLE);//変数に現在操作しているコンソールの情報を渡す

	//フォント設定
	draw.font_config.cbSize = sizeof(draw.font_config);
	draw.font_config.nFont = 0;
	draw.font_config.dwFontSize.X = draw.font_width;//フォントの横幅
	draw.font_config.dwFontSize.Y = draw.font_height;//フォントの縦幅
	draw.font_config.FontFamily = FF_DONTCARE;
	draw.font_config.FontWeight = FW_NORMAL;

	SetCurrentConsoleFontEx(draw.handle, FALSE, &draw.font_config);//フォントの設定を反映

	/*
	変数を作っただけでは、設計図を作っただけなのと同じ。
	現在のコンソールウィンドウに反映してあげる必要がある。
	*/

	/*
	コンソールに限らず、何かの設定をいじる作業には、
	直接設定をいじるタイプと
	設定のセット(設計図)を作ってから反映するタイプの二つがある、
	と何となく覚えておくと良いかも
	*/

	//カーソル設定
	draw.cursor_Info.dwSize = 1;
	draw.cursor_Info.bVisible = FALSE;//カーソルを表示させない
	SetConsoleCursorInfo(draw.handle, &draw.cursor_Info);

	COORD coord = { 0,0 };
	SetConsoleScreenBufferSize(draw.handle, coord);
	SMALL_RECT m_rectWindow = { 0, 0, 1, 1 };
	SetConsoleWindowInfo(draw.handle, TRUE, &m_rectWindow);

	//バッファ画面のサイズ
	coord.X = (short)draw.screen_width;//画面の横幅
	coord.Y = (short)draw.screen_height;//画面の縦幅
	SetConsoleScreenBufferSize(draw.handle, coord);
	SetConsoleActiveScreenBuffer(draw.handle);

	//ウィンドウサイズ
	SMALL_RECT rect_w = { 0, 0, (short)draw.screen_width - 1, (short)draw.screen_height - 1 };//ウィンドウサイズを設定
	SetConsoleWindowInfo(draw.handle, TRUE, &rect_w);//ウィンドウサイズの設定を反映

	//バッファの用意
	//画面の横幅×縦幅分の文字変数を用意する
	draw.screen_buffer = (CHAR_INFO*)malloc(sizeof(CHAR_INFO) * draw.screen_width * draw.screen_height);//動的確保

	/*
	ここでのバッファは、画面全体に表示する文字列の事。
	コンソール上では、全て文字で表現されるので、
	画面全体を一つの文字列と捉えられる。
	*/

	/*
	変数の配列を用意する時に、状況によって必要な変数の数が変化する場合がある。
	その場合には、配列の大きさをプログラムの中で自由に設定出来る「動的確保」を使う。
	「動的確保」を使う際には、ポインタ変数で配列の入れ物を用意する。
	今回で言えば、画面のサイズによって、必要なCHAR_INFO変数の数が変化するので、
	それに合わせて、配列のサイズを変える。
	*/

	/*
	動的確保した配列が不要になったら開放する。
	一つ放置するぐらいなら、余程の事がない限り問題ないが、
	何回も動的確保が行われる場合は、メモリから溢れるなどのエラーが出る事がある。
	*/

	//バッファの初期化(何も描画されていない状態の文字列を用意しておく)
	for (int y = 0; y < draw.screen_height; y++)//バッファの中身の初期化
	{
		for (int x = 0; x < draw.screen_width; x++)
		{
			//文字色と背景色
			draw.screen_buffer[y * (int)draw.screen_width + x].Attributes = 15 + (0 << 4);

			//文字
			draw.screen_buffer[y * (int)draw.screen_width + x].Char.UnicodeChar = ' ';//スペース(空白)

			/*
			数字が色を表している。
			15が白で、0が黒。
			CHAR_INFOの中にあるAttributeは、文字色と背景色を8桁の二進数で記録している。
			左側の4桁が背景色、右側の4桁が文字色を表現している為、
			背景色である0の数字を「<<4」で左側へビット移動させてあげる。
			*/

			/*
			どの数字がどの色を表すのかわかりにくいので、
			本当は#defineやenumを使って、
			「WHITE」と入力するだけで0を指定できるようにしてあげると良い
			*/
		}
	}

	//マウス、キーボードの入力で処理を止めない
	HANDLE handle_In = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(handle_In, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}

//コンソールと描画機能の終了処理
void DrawManager_end(void)
{
	//動的確保したら開放する
	if (draw.screen_buffer != NULL)
	{
		free(draw.screen_buffer);
	}
}

//バッファのリセット
void DrawManager_clear(void)
{
	for (int y = 0; y < draw.screen_height; y++)//バッファの中身の初期化
	{
		for (int x = 0; x < draw.screen_width; x++)
		{
			//文字色と背景色
			draw.screen_buffer[y * (int)draw.screen_width + x].Attributes = 15 + (0 << 4);

			//文字
			draw.screen_buffer[y * (int)draw.screen_width + x].Char.UnicodeChar = ' ';//スペース(空白)
		}
	}

	/*
	次の瞬間に表示される画面を用意する為に、
	一度今の画面を何も書き込まれていない状態へリセットする作業。
	やり方は違えど何かを表示するプログラムでは、必ずやる事になるはず。
	*/
}

//バッファを画面へ表示
void DrawManager_present(void)
{
	COORD size = { (short)draw.screen_width, (short)draw.screen_height };//サイズ

	COORD coord = { 0,0 };//書き込みを開始する位置
	SMALL_RECT rect = { coord.X, coord.Y, size.X, size.Y };//書き込む箇所を矩形で指定
	WriteConsoleOutput(draw.handle, draw.screen_buffer, size, coord, &rect);
}

//コンソールと描画機能を取得
struct DrawManager* GetActiveDrawManager(void)
{
	return &draw;
}