#pragma once
#include <Windows.h>

//��ʂɕ\�����镨�̂̏����Ǘ����鎩��\����
typedef struct Object
{
	//�ʒu(���̂̒��S�ł͂Ȃ��A����[�̈ʒu)
	int position_x;//�ʒu(���E)
	int position_y;//�ʒu(�㉺)

	/*
	position_x�̐��l���傫���قǉE�ցA
	position_y�̐��l���傫���قǉ��֍s���B
	�����̃Q�[���ł͕��̂̈ʒu�͍���[�ł͂Ȃ��A���̂̒��S���w���B
	����͓���B
	*/

	//�傫��
	int width;
	int height;

	//�摜
	CHAR_INFO* CH;
};

void Object_init(struct Object* input_Object, int input_width,
	int input_height, int input_x, int input_y);//�I�u�W�F�N�g�̏�����
void Object_end(struct Object* input_Object);//�I�u�W�F�N�g�̏I������
void Object_SetPosition(struct Object* input_Object, int input_x, int input_y);//�I�u�W�F�N�g�̈ړ�
void Object_SetPosition(struct Object* input_Object, int input_x, int input_y);//�I�u�W�F�N�g�̈ړ�
void Object_SetColor(struct Object* input_Object, int font_color, int background_color);//�I�u�W�F�N�g�̐F�̐ݒ�

void Object_draw(struct Object* input_Object);//�I�u�W�F�N�g�̕`��