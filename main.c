#include <stdio.h>

#include "DrawManager.h"
#include "time.h"
#include "object.h"
#include "NumberDisyplay.h"
#include "WordDisplay.h"
#include "common.h"

void main (void)
{
	//���͑ҋ@�e�X�g
	rewind(stdin);
	getchar();

	DrawManager_init();
	time_init();

	//�R���\�[�����
	struct DrawManager* pDrawManager = GetActiveDrawManager();

	//�e�X�g�p�̕���A�̏���
	struct Object A;
	Object_init(&A, 2, 2, 5, 5);

	//�e�X�g�p�̕����̏���
	struct WordDisplay wd;
	WordDisplay_init(&wd, "FIGHT", 3, 3);
	
	//A�ɒ��g������
	for (int i = 0; i < 4; i++)
	{
		A.CH[i].Attributes = 1 + (2 << 4);
		A.CH[i].Char.UnicodeChar = 'A';
	}

	BOOL left = FALSE;//A�����Ɉړ����邩

	while(1)
	{
		//��ʂ̃N���A
		DrawManager_clear();
		
		//A�̕\��
		Object_draw(&A);

		//A�̉E�ړ�
		if (left == FALSE)
		{
			Object_SetPosition(&A, (A.position_x + 1), A.position_y);

			//�E�[�Ɍ������獶��
			if ((A.position_x + A.width) >= pDrawManager->screen_width)
			{
				left = TRUE;
			}
		}

		//A�̍��ړ�
		if (left)
		{
			Object_SetPosition(&A, (A.position_x - 1), A.position_y);

			//���[�Ɍ�������E��
			if (A.position_x <= 0)
			{
				left = FALSE;
			}
		}

		//������\���̃e�X�g
		WordDisplay_draw(&wd);

		//FPS�\��
		time_draw();

		//��ʂ̕\��
		DrawManager_present();

		//�����̕\���e�X�g
		SetCursorPosition(0, 2);
		printf("����ɂ��́I");

		//FPS�ێ�
		time_update();
	}
}