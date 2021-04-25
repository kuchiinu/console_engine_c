#include "NumberDisyplay.h"

//�����\���̏�����
void NumberDisplay_init(struct NumberDisplay* input_NumberDisplay, int input_number, int input_x, int input_y)
{
	//�����ݒ�
	//�������琔���Ƃ����\������ʒu��ݒ肷��
	input_NumberDisplay->number = input_number;//����

	//�摜�̏�����
	input_NumberDisplay->object.CH = NULL;

	//�����̃Z�b�g
	NumberDisplay_SetNumber(input_NumberDisplay, input_NumberDisplay->number);

	//�\���ʒu�̃Z�b�g
	NumberDisplay_SetPosition(input_NumberDisplay, input_x, input_y);
}

//�����̃Z�b�g
void NumberDisplay_SetNumber(struct NumberDisplay* input_NumberDisplay, int input_number)
{
	//��������V��������������
	input_NumberDisplay->number = input_number;

	//���������߂�
	int buf = input_NumberDisplay->number;
	int diget = 0;//�������L�^����ϐ�

	//���ʂ�0�ɂȂ�܂ŁA10�ŏ��Z����΁A���̉񐔂Ō���������
	while (buf != 0)
	{
		buf /= 10;
		diget++;
	}

	//�����̋L�^
	input_NumberDisplay->diget = diget;

	//�������ɃI�u�W�F�N�g�̕����񂪓��I�m�ۂ���Ă�����A���
	if (input_NumberDisplay->object.CH != NULL)
	{
		free(input_NumberDisplay->object.CH);
	}
	else
	{
		//���Ă͂܂�Ȃ��ꍇ�A���������Ɏ���
	}

	//�I�u�W�F�N�g�̗p��
	//�I�u�W�F�N�g�̉������������ɂ���
	Object_init(&input_NumberDisplay->object, diget, 1,
		input_NumberDisplay->object.position_x, input_NumberDisplay->object.position_y);

	//�������ꌅ����������
	buf = input_NumberDisplay->number;

	for (int i = 0; i < diget; i++)
	{
		//10�Ŋ������]�肪���̌��̐����ƂȂ�
		input_NumberDisplay->object.CH[diget - 1 - i].Char.UnicodeChar = '0' + (buf % 10);
		input_NumberDisplay->object.CH[diget - 1 - i].Attributes = 15 + (0 << 4);

		//1�̈ʂ������āA���̌���
		buf /= 10;
	}
}

//�����\���̈ړ�
void NumberDisplay_SetPosition(struct NumberDisplay* input_NumberDisplay, int input_x, int input_y)
{
	//�I�u�W�F�N�g�ɔ��f����
	Object_SetPosition(&input_NumberDisplay->object, input_x, input_y);
}

//������̐F�̐ݒ�
void NumberDisplay_SetColor(struct NumberDisplay* input_NumberDisplay,
	int font_color, int background_color)
{
	//�I�u�W�F�N�g�ɔ��f����
	Object_SetColor(&input_NumberDisplay->object, font_color, background_color);
}

//�����̕`��
void NumberDisplay_draw(struct NumberDisplay* input_NumberDisplay)
{
	//�I�u�W�F�N�g�̕`��
	Object_draw(&input_NumberDisplay->object);
}

//�����̎擾
int NumberDisplay_GetDiget(struct NumberDisplay* input_NumberDisplay)
{
	return input_NumberDisplay->diget;
}