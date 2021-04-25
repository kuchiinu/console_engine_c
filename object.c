#include "object.h"
#include "DrawManager.h"

//�I�u�W�F�N�g�̏�����
void Object_init(struct Object* input_Object, int input_width, int input_height, int input_x, int input_y)
{
	//�����ݒ�
	//�������炻�̕��̂̈ʒu�Ƒ傫����ݒ肷��
	input_Object->width = input_width;//����
	input_Object->height = input_height;//�c��
	input_Object->position_x = input_x;//�ʒu(���E)
	input_Object->position_y = input_y;//�ʒu(�㉺)

	//�摜�Ɏg��������̗p��
	//���̂̉����~�c�����̕����ϐ���p�ӂ���
	input_Object->CH =
		(CHAR_INFO*)malloc(sizeof(CHAR_INFO) * input_Object->width * input_Object->height);//���I�m��

	for (int y = 0; y < input_Object->height; y++)//�o�b�t�@�̒��g�̏�����
	{
		for (int x = 0; x < input_Object->width; x++)
		{
			//�����F�Ɣw�i�F
			input_Object->CH[y * (int)input_Object->width + x].Attributes = 0 + (15 << 4);

			//����
			input_Object->CH[y * (int)input_Object->width + x].Char.UnicodeChar = ' ';//�X�y�[�X(��)
		}
	}
}

void Object_end(struct Object* input_Object)//�I�u�W�F�N�g�̏I������
{
	//���I�m�ۂ�����J������
	if (input_Object->CH != NULL)
	{
		free(input_Object->CH);
	}
}

//�I�u�W�F�N�g�̈ړ�
void Object_SetPosition(struct Object* input_Object, int input_x, int input_y)
{
	//�����Ŏw�肵���ʒu�ɕ��̂̈ʒu������������
	input_Object->position_x = input_x;
	input_Object->position_y = input_y;
}

//�I�u�W�F�N�g�̐F�̐ݒ�
void Object_SetColor(struct Object* input_Object, int font_color, int background_color)
{
	for (int i = 0; i < input_Object->height; i++)
	{
		for (int j = 0; j < input_Object->width; j++)
		{
			input_Object->CH[i].Attributes = font_color + (0 << background_color);
		}
	}
}

//�I�u�W�F�N�g�̕`��
void Object_draw(struct Object* input_Object)
{
	struct DrawManager* pDrawManager = GetActiveDrawManager();//�R���\�[���ƕ`��@�\���擾

	for (int i = 0; i < input_Object->height; i++)
	{
		//��ʂ̊O�ɕ`���Ɖ����
		if (input_Object->position_y + i >= 0 && input_Object->position_y + i < pDrawManager->screen_height)
		{
			for (int j = 0; j < input_Object->width; j++)
			{
				//��ʂ̊O�ɕ`���Ɖ����
				if (input_Object->position_x + j >= 0 && input_Object->position_x + j < pDrawManager->screen_width)
				{
					//�����F�Ɣw�i�F
					pDrawManager->screen_buffer[(input_Object->position_y + i) * pDrawManager->screen_width + (input_Object->position_x + j)].Attributes = input_Object->CH[input_Object->width * i + j].Attributes;

					//����
					pDrawManager->screen_buffer[(input_Object->position_y + i) * pDrawManager->screen_width + (input_Object->position_x + j)].Char.UnicodeChar = input_Object->CH[input_Object->width * i + j].Char.UnicodeChar;
				}
			}
		}
	}

	/*
	�ʏ�A�R���\�[���̃A�v���P�[�V�����ł́A
	�\�����������̖��ɉ�ʂ�prinntf�����s����ׁA
	��ʂ��`�J�`�J������A
	��ʓ��̈ʒu�ɂ���ĕω��̔��f�Ɏ��ԍ������܂ꂽ�肷��B

	���炩���߉�ʂ̑��ɉ�ʂ̃T�C�Y�Ɠ����傫���̕������p�ӂ��Ă����A
	�����ɕ\�����������̂��A���炩���ߑS�ď����o���Ă���A
	��ʂɏo���΁A������⎞�ԍ����Ȃ��Ȃ�B

	����Object_Draw�ł́A
	DrawManager�Ƃ����\���̂Ɏ���������ʃT�C�Y���̕�����screen_buffer��
	�\�����ė~�������̂�o�^�����Ƃ����Ă���B
	*/
}