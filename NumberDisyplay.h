#pragma once
#include "object.h"

//��ʂɕ\�����鐔�����Ǘ����鎩��\����
typedef struct NumberDisplay
{
	int number;//����
	int diget;//����

	struct Object object;//�\������I�u�W�F�N�g
};

void NumberDisplay_init(struct NumberDisplay* input_NumberDisplay, int input_number,
	int input_x, int input_y);//�����\���̏�����
void NumberDisplay_SetNumber(struct NumberDisplay* input_NumberDisplay, int input_number);//�����̃Z�b�g
void NumberDisplay_SetPosition(struct NumberDisplay* input_NumberDisplay, int input_x, int input_y);//�����\���̈ړ�
void NumberDisplay_SetColor(struct NumberDisplay* input_NumberDisplay,
	int font_color, int background_color);//������̐F�̐ݒ�

void NumberDisplay_draw(struct NumberDisplay* input_NumberDisplay);//�����̕`��
int NumberDisplay_GetDiget(struct NumberDisplay* input_NumberDisplay);//�����̎擾