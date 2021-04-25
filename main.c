#include <stdio.h>

#include "DrawManager.h"
#include "time.h"
#include "object.h"
#include "NumberDisyplay.h"
#include "WordDisplay.h"
#include "common.h"

void main (void)
{
	//入力待機テスト
	rewind(stdin);
	getchar();

	DrawManager_init();
	time_init();

	//コンソール情報
	struct DrawManager* pDrawManager = GetActiveDrawManager();

	//テスト用の物体Aの準備
	struct Object A;
	Object_init(&A, 2, 2, 5, 5);

	//テスト用の文字の準備
	struct WordDisplay wd;
	WordDisplay_init(&wd, "FIGHT", 3, 3);
	
	//Aに中身を入れる
	for (int i = 0; i < 4; i++)
	{
		A.CH[i].Attributes = 1 + (2 << 4);
		A.CH[i].Char.UnicodeChar = 'A';
	}

	BOOL left = FALSE;//Aが左に移動するか

	while(1)
	{
		//画面のクリア
		DrawManager_clear();
		
		//Aの表示
		Object_draw(&A);

		//Aの右移動
		if (left == FALSE)
		{
			Object_SetPosition(&A, (A.position_x + 1), A.position_y);

			//右端に言ったら左へ
			if ((A.position_x + A.width) >= pDrawManager->screen_width)
			{
				left = TRUE;
			}
		}

		//Aの左移動
		if (left)
		{
			Object_SetPosition(&A, (A.position_x - 1), A.position_y);

			//左端に言ったら右へ
			if (A.position_x <= 0)
			{
				left = FALSE;
			}
		}

		//文字列表示のテスト
		WordDisplay_draw(&wd);

		//FPS表示
		time_draw();

		//画面の表示
		DrawManager_present();

		//文字の表示テスト
		SetCursorPosition(0, 2);
		printf("こんにちは！");

		//FPS維持
		time_update();
	}
}