#pragma once
#include <Windows.h>
#include "NumberDisyplay.h"

//���Ԋ֌W�̏����L�^���鎩��\����
typedef struct time_info
{
	float MIN_FREAM_TIME;//���[�v������������Ɋ|���鎞�Ԃ̖ڕW
	
	float frameTime;//���Ԃ̌v�����n�߂Ă���o�߂�������

	LARGE_INTEGER start_time;//�v���J�n����
	LARGE_INTEGER end_time;//���ݎ���
	LARGE_INTEGER frequence_time;//���g��(���߂��������鑬��)

	float fps;//1�b���̃��[�v�������s��ꂽ��

	struct NumberDisplay fps_display;
};

void time_init(void);//���Ԋ֌W�̏���������
void time_update(void);//fps�����肳���鏈��
void time_draw(void);//fps�̕\��(�f�o�b�O�p)

/*
LARGE_INTEGER�͋����int�^�ϐ�
*/