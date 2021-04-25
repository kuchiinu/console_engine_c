#pragma once
#include "Object.h"

//画面に表示する文字列を管理する自作構造体
typedef struct WordDisplay
{
	const char* word;//文字列
	int length;//文字列の長さ

	struct Object object;//表示するオブジェクト
};

void WordDisplay_init(struct WordDisplay* input_WordDisplay, const char* input_word,
	int input_x, int input_y);//文字列表示の初期化
void WordDisplay_SetWord(struct WordDisplay* input_WordDisplay, const char* input_word);//文字列のセット
void WordDisplay_SetPosition(struct WordDisplay* input_WordDisplay, int input_x, int input_y);//文字列表示の移動
void WordDisplay_SetColor(struct WordDisplay* input_WordDisplay,
	int font_color, int background_color);//文字列の色の設定

void WordDisplay_draw(struct WordDisplay* input_WordDisplay);//文字列の描画