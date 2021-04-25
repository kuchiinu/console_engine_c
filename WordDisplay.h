#pragma once
#include "Object.h"

//��ʂɕ\�����镶������Ǘ����鎩��\����
typedef struct WordDisplay
{
	const char* word;//������
	int length;//������̒���

	struct Object object;//�\������I�u�W�F�N�g
};

void WordDisplay_init(struct WordDisplay* input_WordDisplay, const char* input_word,
	int input_x, int input_y);//������\���̏�����
void WordDisplay_SetWord(struct WordDisplay* input_WordDisplay, const char* input_word);//������̃Z�b�g
void WordDisplay_SetPosition(struct WordDisplay* input_WordDisplay, int input_x, int input_y);//������\���̈ړ�
void WordDisplay_SetColor(struct WordDisplay* input_WordDisplay,
	int font_color, int background_color);//������̐F�̐ݒ�

void WordDisplay_draw(struct WordDisplay* input_WordDisplay);//������̕`��