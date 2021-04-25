#include "NumberDisyplay.h"

//数字表示の初期化
void NumberDisplay_init(struct NumberDisplay* input_NumberDisplay, int input_number, int input_x, int input_y)
{
	//初期設定
	//引数から数字とそれを表示する位置を設定する
	input_NumberDisplay->number = input_number;//数字

	//画像の初期化
	input_NumberDisplay->object.CH = NULL;

	//数字のセット
	NumberDisplay_SetNumber(input_NumberDisplay, input_NumberDisplay->number);

	//表示位置のセット
	NumberDisplay_SetPosition(input_NumberDisplay, input_x, input_y);
}

//数字のセット
void NumberDisplay_SetNumber(struct NumberDisplay* input_NumberDisplay, int input_number)
{
	//引数から新しい数字を決定
	input_NumberDisplay->number = input_number;

	//桁数を求める
	int buf = input_NumberDisplay->number;
	int diget = 0;//桁数を記録する変数

	//結果が0になるまで、10で除算すれば、その回数で桁数が解る
	while (buf != 0)
	{
		buf /= 10;
		diget++;
	}

	//桁数の記録
	input_NumberDisplay->diget = diget;

	//もし既にオブジェクトの文字列が動的確保されていたら、解放
	if (input_NumberDisplay->object.CH != NULL)
	{
		free(input_NumberDisplay->object.CH);
	}
	else
	{
		//当てはまらない場合、何もせずに次へ
	}

	//オブジェクトの用意
	//オブジェクトの横幅を桁数分にする
	Object_init(&input_NumberDisplay->object, diget, 1,
		input_NumberDisplay->object.position_x, input_NumberDisplay->object.position_y);

	//数字を一桁ずつ分解する
	buf = input_NumberDisplay->number;

	for (int i = 0; i < diget; i++)
	{
		//10で割った余りがその桁の数字となる
		input_NumberDisplay->object.CH[diget - 1 - i].Char.UnicodeChar = '0' + (buf % 10);
		input_NumberDisplay->object.CH[diget - 1 - i].Attributes = 15 + (0 << 4);

		//1の位を消して、次の桁へ
		buf /= 10;
	}
}

//数字表示の移動
void NumberDisplay_SetPosition(struct NumberDisplay* input_NumberDisplay, int input_x, int input_y)
{
	//オブジェクトに反映する
	Object_SetPosition(&input_NumberDisplay->object, input_x, input_y);
}

//文字列の色の設定
void NumberDisplay_SetColor(struct NumberDisplay* input_NumberDisplay,
	int font_color, int background_color)
{
	//オブジェクトに反映する
	Object_SetColor(&input_NumberDisplay->object, font_color, background_color);
}

//数字の描画
void NumberDisplay_draw(struct NumberDisplay* input_NumberDisplay)
{
	//オブジェクトの描画
	Object_draw(&input_NumberDisplay->object);
}

//桁数の取得
int NumberDisplay_GetDiget(struct NumberDisplay* input_NumberDisplay)
{
	return input_NumberDisplay->diget;
}