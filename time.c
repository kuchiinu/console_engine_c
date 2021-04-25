#pragma comment(lib, "winmm.lib")

#include "time.h"
#include "DrawManager.h"
#include "object.h"

struct time_info time;

//���Ԋ֌W�̏���������
void time_init(void)
{
	time.MIN_FREAM_TIME = 1.0f / 60;
	time.frameTime== 0;//���Ԃ̌v�����n�߂Ă���o�߂�������
	time.fps = 0.00f;//1�b���̃��[�v�������s��ꂽ��

	//���g��(���߂��������鑬��)�������Ă��炤
	QueryPerformanceFrequency(&time.frequence_time);

	//�v���J�n�������Z�b�g
	QueryPerformanceCounter(&time.start_time);

	//FPS�\���̏���
	struct DrawManager* pDrawManager = GetActiveDrawManager();//�R���\�[�������擾

	//NumberDisplay_init(&time.fps_display, 0, 0, 0);
}

//fps�����肳���鏈��
void time_update(void)
{
	//���ݎ������v��
	QueryPerformanceCounter(&time.end_time);

	//(���ݎ��� - �O�Ɍv����������) / ���g�� = �o�ߎ���(�b�P��)
	time.frameTime = (float)(time.end_time.QuadPart - time.start_time.QuadPart)
		/ (float)(time.frequence_time.QuadPart);

	//���[�v�����̈�����K�v�ȏ�ɑ����I����Ă��܂����ꍇ
	if (time.frameTime < time.MIN_FREAM_TIME)
	{
		//�o�ߎ��Ԃ��~���b�P�ʂɕϊ�
		DWORD sleepTime = (DWORD)((time.MIN_FREAM_TIME - time.frameTime) * 1000);

		timeBeginPeriod(1);
		Sleep(sleepTime);   //�����ς񂾕��ҋ@����(�ҋ@���Ԃ̓~���b�P�ʂŎw�肷��)
		timeEndPeriod(1);

		//���݂̎��Ԃ��擾
		QueryPerformanceCounter(&time.end_time);

		//FPS
		//(���̎��� - �O�t���[���̎���) / ���g�� = �o�ߎ���(�b�P��)
		time.frameTime = (float)(time.end_time.QuadPart - time.start_time.QuadPart) 
			/ (float)(time.frequence_time.QuadPart);
	}

	//FPS
	time.fps = (time.fps * 0.99f) + (0.01f / time.frameTime);

	// ����ւ�
	time.start_time = time.end_time;
}

//fps�̕\��(�f�o�b�O�p)
void time_draw(void)
{
	NumberDisplay_SetNumber(&time.fps_display, (int)time.fps);
	struct DrawManager* pDrawManager = GetActiveDrawManager();
	NumberDisplay_SetPosition(&time.fps_display,
		pDrawManager->screen_width - 1 - (time.fps_display.diget - 1), pDrawManager->screen_height - 1);
	NumberDisplay_draw(&time.fps_display);
}