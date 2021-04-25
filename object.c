#include "object.h"
#include "DrawManager.h"

//オブジェクトの初期化
void Object_init(struct Object* input_Object, int input_width, int input_height, int input_x, int input_y)
{
	//初期設定
	//引数からその物体の位置と大きさを設定する
	input_Object->width = input_width;//横幅
	input_Object->height = input_height;//縦幅
	input_Object->position_x = input_x;//位置(左右)
	input_Object->position_y = input_y;//位置(上下)

	//画像に使う文字列の用意
	//物体の横幅×縦幅分の文字変数を用意する
	input_Object->CH =
		(CHAR_INFO*)malloc(sizeof(CHAR_INFO) * input_Object->width * input_Object->height);//動的確保

	for (int y = 0; y < input_Object->height; y++)//バッファの中身の初期化
	{
		for (int x = 0; x < input_Object->width; x++)
		{
			//文字色と背景色
			input_Object->CH[y * (int)input_Object->width + x].Attributes = 0 + (15 << 4);

			//文字
			input_Object->CH[y * (int)input_Object->width + x].Char.UnicodeChar = ' ';//スペース(空白)
		}
	}
}

void Object_end(struct Object* input_Object)//オブジェクトの終了処理
{
	//動的確保したら開放する
	if (input_Object->CH != NULL)
	{
		free(input_Object->CH);
	}
}

//オブジェクトの移動
void Object_SetPosition(struct Object* input_Object, int input_x, int input_y)
{
	//引数で指定した位置に物体の位置を書き換える
	input_Object->position_x = input_x;
	input_Object->position_y = input_y;
}

//オブジェクトの色の設定
void Object_SetColor(struct Object* input_Object, int font_color, int background_color)
{
	for (int i = 0; i < input_Object->height; i++)
	{
		for (int j = 0; j < input_Object->width; j++)
		{
			input_Object->CH[i].Attributes = font_color + (0 << background_color);
		}
	}
}

//オブジェクトの描画
void Object_draw(struct Object* input_Object)
{
	struct DrawManager* pDrawManager = GetActiveDrawManager();//コンソールと描画機能を取得

	for (int i = 0; i < input_Object->height; i++)
	{
		//画面の外に描くと壊れるよ
		if (input_Object->position_y + i >= 0 && input_Object->position_y + i < pDrawManager->screen_height)
		{
			for (int j = 0; j < input_Object->width; j++)
			{
				//画面の外に描くと壊れるよ
				if (input_Object->position_x + j >= 0 && input_Object->position_x + j < pDrawManager->screen_width)
				{
					//文字色と背景色
					pDrawManager->screen_buffer[(input_Object->position_y + i) * pDrawManager->screen_width + (input_Object->position_x + j)].Attributes = input_Object->CH[input_Object->width * i + j].Attributes;

					//文字
					pDrawManager->screen_buffer[(input_Object->position_y + i) * pDrawManager->screen_width + (input_Object->position_x + j)].Char.UnicodeChar = input_Object->CH[input_Object->width * i + j].Char.UnicodeChar;
				}
			}
		}
	}

	/*
	通常、コンソールのアプリケーションでは、
	表示したいもの毎に画面にprinntfを実行する為、
	画面がチカチカしたり、
	画面内の位置によって変化の反映に時間差が生まれたりする。

	あらかじめ画面の他に画面のサイズと同じ大きさの文字列を用意しておき、
	そこに表示したいものを、あらかじめ全て書き出してから、
	画面に出せば、ちらつきや時間差がなくなる。

	このObject_Drawでは、
	DrawManagerという構造体に持たせた画面サイズ分の文字列screen_bufferに
	表示して欲しいものを登録する作業をしている。
	*/
}