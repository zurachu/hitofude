#include "wave.h"

#include <string.h>

void wav_GetPieceWave(PCEWAVEINFO* pWav, BYTE* pData)
{
	memcpy( pWav, pData + 8, sizeof(PCEWAVEINFO) );
	pWav->pData = pData + 8 + sizeof(PCEWAVEINFO);
}

