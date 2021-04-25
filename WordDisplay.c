#include "WordDisplay.h"

//������\���̏�����
void WordDisplay_init(struct WordDisplay* input_WordDisplay, const char* input_word,
	int input_x, int input_y)
{
	//�����ݒ�
	//�������當����Ƃ����\������ʒu��ݒ肷��
	input_WordDisplay->word = input_word;

	//�摜�̏�����
	input_WordDisplay->object.CH = NULL;

	//������̃Z�b�g
	WordDisplay_SetWord(input_WordDisplay, input_word);

	//�ʒu�̃Z�b�g
	WordDisplay_SetPosition(input_WordDisplay, input_x, input_y);
}

//������̃Z�b�g
void WordDisplay_SetWord(struct WordDisplay* input_WordDisplay, const char* input_word)
{
	//�������當����Ƃ����\������ʒu��ݒ肷��
	input_WordDisplay->word = input_word;
	input_WordDisplay->length = strlen(input_WordDisplay->word);//���͂��ꂽ������̒������J�E���g

	//�������ɃI�u�W�F�N�g�̕����񂪓��I�m�ۂ���Ă�����A���
	if (input_WordDisplay->object.CH != NULL)
	{
		free(input_WordDisplay->object.CH);
	}
	else
	{
		//���Ă͂܂�Ȃ��ꍇ�A���������Ɏ���
	}

	//�I�u�W�F�N�g�̗p��
	//�I�u�W�F�N�g�̉����𕶎������ɂ���
	Object_init(&input_WordDisplay->object, input_WordDisplay->length, 1,
		input_WordDisplay->object.position_x, input_WordDisplay->object.position_y);

	//��������I�u�W�F�N�g�ɃR�s�[
	for (int i = 0; i < input_WordDisplay->length; i++)
	{
		input_WordDisplay->object.CH[i].Char.UnicodeChar = input_WordDisplay->word[i];
		input_WordDisplay->object.CH[i].Attributes = 15 + (0 << 4);
	}
}

//������\���̈ړ�
void WordDisplay_SetPosition(struct WordDisplay* input_WordDisplay, int input_x, int input_y)
{
	//�I�u�W�F�N�g�ɔ��f����
	Object_SetPosition(&input_WordDisplay->object, input_x, input_y);
}

//������̐F�̐ݒ�
void WordDisplay_SetColor(struct WordDisplay* input_WordDisplay,
	int font_color, int background_color)
{
	//�I�u�W�F�N�g�ɔ��f����
	Object_SetColor(&input_WordDisplay->object, font_color, background_color);
}

//������̕`��
void WordDisplay_draw(struct WordDisplay* input_WordDisplay)
{
	//�I�u�W�F�N�g�̕`��
	Object_draw(&input_WordDisplay->object);
}