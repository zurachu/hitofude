#include "app.h"

#include <piece.h>
#include "draw.h"

void app_Init( int period )
{
	pceLCDDispStop();

	pceAppSetProcPeriod( period );
	draw_Init();

	pceLCDDispStart();
}

void app_Exit()
{
	pceWaveStop( 0 );
}

