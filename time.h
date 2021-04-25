#pragma once
#include <Windows.h>
#include "NumberDisyplay.h"

//時間関係の情報を記録する自作構造体
typedef struct time_info
{
	float MIN_FREAM_TIME;//ループ処理が一周毎に掛ける時間の目標
	
	float frameTime;//時間の計測を始めてから経過した時間

	LARGE_INTEGER start_time;//計測開始時刻
	LARGE_INTEGER end_time;//現在時刻
	LARGE_INTEGER frequence_time;//周波数(命令を処理する速さ)

	float fps;//1秒毎のループ処理が行われた回数

	struct NumberDisplay fps_display;
};

void time_init(void);//時間関係の情報を初期化
void time_update(void);//fpsを安定させる処理
void time_draw(void);//fpsの表示(デバッグ用)

/*
LARGE_INTEGERは巨大なint型変数
*/