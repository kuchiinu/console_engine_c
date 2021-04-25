#pragma once
#include <Windows.h>

#define SCREEN_WIDTH (20)
#define SCREEN_HEIGHT (20)

#define FONT_WIDTH (20)
#define FONT_HEIGHT (20)

//�R���\�[���Ɖ�ʕ\���Ɋւ������܂Ƃ߂�����\����
typedef struct DrawManager
{
	HANDLE handle;//�R���\�[���E�B���h�E�̏������ϐ�

	CONSOLE_FONT_INFOEX font_config;//�t�H���g�֌W�̏������ϐ�

	CHAR_INFO* screen_buffer;//��ʂɕ\�����镶����

	CONSOLE_CURSOR_INFO cursor_Info;//�J�[�\���֌W�̏������ϐ�

	int screen_width;//�R���\�[���E�B���h�E�̉���
	int screen_height;//�R���\�[���E�B���h�E�̏c��
	int font_width;//�t�H���g�̉���
	int font_height;//�t�H���g�̏c��;
};

/*
CHAR_INFO�͕����F�Ɣw�i�F�̏���ǉ��o��������char�^�ϐ�
*/

void DrawManager_init(void);//�R���\�[���ƕ`��@�\�̏�����
void DrawManager_end(void);//�R���\�[���ƕ`��@�\�̏I������
void DrawManager_clear(void);//�o�b�t�@�̃��Z�b�g
void DrawManager_present(void);//�o�b�t�@����ʂ֕\��

struct DrawManager* GetActiveDrawManager(void);//�R���\�[���ƕ`��@�\���擾