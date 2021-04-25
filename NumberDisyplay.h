#pragma once
#include "object.h"

//画面に表示する数字を管理する自作構造体
typedef struct NumberDisplay
{
	int number;//数字
	int diget;//桁数

	struct Object object;//表示するオブジェクト
};

void NumberDisplay_init(struct NumberDisplay* input_NumberDisplay, int input_number,
	int input_x, int input_y);//数字表示の初期化
void NumberDisplay_SetNumber(struct NumberDisplay* input_NumberDisplay, int input_number);//数字のセット
void NumberDisplay_SetPosition(struct NumberDisplay* input_NumberDisplay, int input_x, int input_y);//数字表示の移動
void NumberDisplay_SetColor(struct NumberDisplay* input_NumberDisplay,
	int font_color, int background_color);//文字列の色の設定

void NumberDisplay_draw(struct NumberDisplay* input_NumberDisplay);//数字の描画
int NumberDisplay_GetDiget(struct NumberDisplay* input_NumberDisplay);//桁数の取得