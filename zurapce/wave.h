#ifndef H_ZURAPCE_WAVE_
#define H_ZURAPCE_WAVE_

/**
	@file サウンド関連
*/

#include <piece.h>

/**
	データから PCEWAVEINFO を生成します.
	@param pWav 
	@param pData 
*/
void wav_GetPieceWave(PCEWAVEINFO* pWav, BYTE* pData);

#endif // H_ZURAPCE_WAVE_

