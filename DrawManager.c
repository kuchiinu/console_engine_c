#include "DrawManager.h"
#include <stdlib.h>

struct DrawManager draw;

//�R���\�[���ƕ`��@�\�̏�����
void DrawManager_init(void)
{
	//�����ݒ�̐��l�𔽉f
	draw.screen_width = SCREEN_WIDTH;
	draw.screen_height = SCREEN_HEIGHT;
	draw.font_width = FONT_WIDTH;
	draw.font_height = FONT_HEIGHT;

	draw.handle = GetStdHandle(STD_OUTPUT_HANDLE);//�ϐ��Ɍ��ݑ��삵�Ă���R���\�[���̏���n��

	//�t�H���g�ݒ�
	draw.font_config.cbSize = sizeof(draw.font_config);
	draw.font_config.nFont = 0;
	draw.font_config.dwFontSize.X = draw.font_width;//�t�H���g�̉���
	draw.font_config.dwFontSize.Y = draw.font_height;//�t�H���g�̏c��
	draw.font_config.FontFamily = FF_DONTCARE;
	draw.font_config.FontWeight = FW_NORMAL;

	SetCurrentConsoleFontEx(draw.handle, FALSE, &draw.font_config);//�t�H���g�̐ݒ�𔽉f

	/*
	�ϐ�������������ł́A�݌v�}������������Ȃ̂Ɠ����B
	���݂̃R���\�[���E�B���h�E�ɔ��f���Ă�����K�v������B
	*/

	/*
	�R���\�[���Ɍ��炸�A�����̐ݒ���������Ƃɂ́A
	���ڐݒ��������^�C�v��
	�ݒ�̃Z�b�g(�݌v�})������Ă��甽�f����^�C�v�̓������A
	�Ɖ��ƂȂ��o���Ă����Ɨǂ�����
	*/

	//�J�[�\���ݒ�
	draw.cursor_Info.dwSize = 1;
	draw.cursor_Info.bVisible = FALSE;//�J�[�\����\�������Ȃ�
	SetConsoleCursorInfo(draw.handle, &draw.cursor_Info);

	COORD coord = { 0,0 };
	SetConsoleScreenBufferSize(draw.handle, coord);
	SMALL_RECT m_rectWindow = { 0, 0, 1, 1 };
	SetConsoleWindowInfo(draw.handle, TRUE, &m_rectWindow);

	//�o�b�t�@��ʂ̃T�C�Y
	coord.X = (short)draw.screen_width;//��ʂ̉���
	coord.Y = (short)draw.screen_height;//��ʂ̏c��
	SetConsoleScreenBufferSize(draw.handle, coord);
	SetConsoleActiveScreenBuffer(draw.handle);

	//�E�B���h�E�T�C�Y
	SMALL_RECT rect_w = { 0, 0, (short)draw.screen_width - 1, (short)draw.screen_height - 1 };//�E�B���h�E�T�C�Y��ݒ�
	SetConsoleWindowInfo(draw.handle, TRUE, &rect_w);//�E�B���h�E�T�C�Y�̐ݒ�𔽉f

	//�o�b�t�@�̗p��
	//��ʂ̉����~�c�����̕����ϐ���p�ӂ���
	draw.screen_buffer = (CHAR_INFO*)malloc(sizeof(CHAR_INFO) * draw.screen_width * draw.screen_height);//���I�m��

	/*
	�����ł̃o�b�t�@�́A��ʑS�̂ɕ\�����镶����̎��B
	�R���\�[����ł́A�S�ĕ����ŕ\�������̂ŁA
	��ʑS�̂���̕�����Ƒ�������B
	*/

	/*
	�ϐ��̔z���p�ӂ��鎞�ɁA�󋵂ɂ���ĕK�v�ȕϐ��̐����ω�����ꍇ������B
	���̏ꍇ�ɂ́A�z��̑傫�����v���O�����̒��Ŏ��R�ɐݒ�o����u���I�m�ہv���g���B
	�u���I�m�ہv���g���ۂɂ́A�|�C���^�ϐ��Ŕz��̓��ꕨ��p�ӂ���B
	����Ō����΁A��ʂ̃T�C�Y�ɂ���āA�K�v��CHAR_INFO�ϐ��̐����ω�����̂ŁA
	����ɍ��킹�āA�z��̃T�C�Y��ς���B
	*/

	/*
	���I�m�ۂ����z�񂪕s�v�ɂȂ�����J������B
	����u���邮�炢�Ȃ�A�]���̎����Ȃ�������Ȃ����A
	��������I�m�ۂ��s����ꍇ�́A�������������Ȃǂ̃G���[���o�鎖������B
	*/

	//�o�b�t�@�̏�����(�����`�悳��Ă��Ȃ���Ԃ̕������p�ӂ��Ă���)
	for (int y = 0; y < draw.screen_height; y++)//�o�b�t�@�̒��g�̏�����
	{
		for (int x = 0; x < draw.screen_width; x++)
		{
			//�����F�Ɣw�i�F
			draw.screen_buffer[y * (int)draw.screen_width + x].Attributes = 15 + (0 << 4);

			//����
			draw.screen_buffer[y * (int)draw.screen_width + x].Char.UnicodeChar = ' ';//�X�y�[�X(��)

			/*
			�������F��\���Ă���B
			15�����ŁA0�����B
			CHAR_INFO�̒��ɂ���Attribute�́A�����F�Ɣw�i�F��8���̓�i���ŋL�^���Ă���B
			������4�����w�i�F�A�E����4���������F��\�����Ă���ׁA
			�w�i�F�ł���0�̐������u<<4�v�ō����փr�b�g�ړ������Ă�����B
			*/

			/*
			�ǂ̐������ǂ̐F��\���̂��킩��ɂ����̂ŁA
			�{����#define��enum���g���āA
			�uWHITE�v�Ɠ��͂��邾����0���w��ł���悤�ɂ��Ă�����Ɨǂ�
			*/
		}
	}

	//�}�E�X�A�L�[�{�[�h�̓��͂ŏ������~�߂Ȃ�
	HANDLE handle_In = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(handle_In, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}

//�R���\�[���ƕ`��@�\�̏I������
void DrawManager_end(void)
{
	//���I�m�ۂ�����J������
	if (draw.screen_buffer != NULL)
	{
		free(draw.screen_buffer);
	}
}

//�o�b�t�@�̃��Z�b�g
void DrawManager_clear(void)
{
	for (int y = 0; y < draw.screen_height; y++)//�o�b�t�@�̒��g�̏�����
	{
		for (int x = 0; x < draw.screen_width; x++)
		{
			//�����F�Ɣw�i�F
			draw.screen_buffer[y * (int)draw.screen_width + x].Attributes = 15 + (0 << 4);

			//����
			draw.screen_buffer[y * (int)draw.screen_width + x].Char.UnicodeChar = ' ';//�X�y�[�X(��)
		}
	}

	/*
	���̏u�Ԃɕ\��������ʂ�p�ӂ���ׂɁA
	��x���̉�ʂ������������܂�Ă��Ȃ���Ԃփ��Z�b�g�����ƁB
	�����͈Ⴆ�ǉ�����\������v���O�����ł́A�K����鎖�ɂȂ�͂��B
	*/
}

//�o�b�t�@����ʂ֕\��
void DrawManager_present(void)
{
	COORD size = { (short)draw.screen_width, (short)draw.screen_height };//�T�C�Y

	COORD coord = { 0,0 };//�������݂��J�n����ʒu
	SMALL_RECT rect = { coord.X, coord.Y, size.X, size.Y };//�������މӏ�����`�Ŏw��
	WriteConsoleOutput(draw.handle, draw.screen_buffer, size, coord, &rect);
}

//�R���\�[���ƕ`��@�\���擾
struct DrawManager* GetActiveDrawManager(void)
{
	return &draw;
}