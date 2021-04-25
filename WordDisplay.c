#include "WordDisplay.h"

//文字列表示の初期化
void WordDisplay_init(struct WordDisplay* input_WordDisplay, const char* input_word,
	int input_x, int input_y)
{
	//初期設定
	//引数から文字列とそれを表示する位置を設定する
	input_WordDisplay->word = input_word;

	//画像の初期化
	input_WordDisplay->object.CH = NULL;

	//文字列のセット
	WordDisplay_SetWord(input_WordDisplay, input_word);

	//位置のセット
	WordDisplay_SetPosition(input_WordDisplay, input_x, input_y);
}

//文字列のセット
void WordDisplay_SetWord(struct WordDisplay* input_WordDisplay, const char* input_word)
{
	//引数から文字列とそれを表示する位置を設定する
	input_WordDisplay->word = input_word;
	input_WordDisplay->length = strlen(input_WordDisplay->word);//入力された文字列の長さをカウント

	//もし既にオブジェクトの文字列が動的確保されていたら、解放
	if (input_WordDisplay->object.CH != NULL)
	{
		free(input_WordDisplay->object.CH);
	}
	else
	{
		//当てはまらない場合、何もせずに次へ
	}

	//オブジェクトの用意
	//オブジェクトの横幅を文字数分にする
	Object_init(&input_WordDisplay->object, input_WordDisplay->length, 1,
		input_WordDisplay->object.position_x, input_WordDisplay->object.position_y);

	//文字列をオブジェクトにコピー
	for (int i = 0; i < input_WordDisplay->length; i++)
	{
		input_WordDisplay->object.CH[i].Char.UnicodeChar = input_WordDisplay->word[i];
		input_WordDisplay->object.CH[i].Attributes = 15 + (0 << 4);
	}
}

//文字列表示の移動
void WordDisplay_SetPosition(struct WordDisplay* input_WordDisplay, int input_x, int input_y)
{
	//オブジェクトに反映する
	Object_SetPosition(&input_WordDisplay->object, input_x, input_y);
}

//文字列の色の設定
void WordDisplay_SetColor(struct WordDisplay* input_WordDisplay,
	int font_color, int background_color)
{
	//オブジェクトに反映する
	Object_SetColor(&input_WordDisplay->object, font_color, background_color);
}

//文字列の描画
void WordDisplay_draw(struct WordDisplay* input_WordDisplay)
{
	//オブジェクトの描画
	Object_draw(&input_WordDisplay->object);
}