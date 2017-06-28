#include "draw.h"

#include <string.h>

BYTE* vBuff;
BOOL LCDUpdate;

static DRAW_OBJECT dObj;

void draw_Init()
{
	vBuff = pceHeapAlloc( DISP_X * DISP_Y );
	memset( vBuff, 0, DISP_X * DISP_Y );
	pceLCDSetBuffer( vBuff );

	LCDUpdate = TRUE;
}

void draw_GetPieceBmp( PIECE_BMP* pBmp, BYTE* pData )
{
	memcpy( &pBmp->header, pData, sizeof(PBMP_FILEHEADER) );
	pBmp->buf = pData + sizeof(PBMP_FILEHEADER);
	pBmp->mask = pBmp->buf + ( pBmp->header.w * pBmp->header.h * pBmp->header.bpp >> 3 );
}

void draw_DrawPieceBmp( PIECE_BMP *pBmp, int dx, int dy, int sx, int sy, int w, int h, int param )
{
	pceLCDSetObject( &dObj, pBmp, dx, dy, sx, sy, w, h, param );
	pceLCDDrawObject( dObj );
}

void draw_LCDTrans()
{
	if ( LCDUpdate )
	{
		pceLCDTrans();
		LCDUpdate = FALSE;
	}
}

void draw_FontPutStrColor( char* str, int tx_color, int bk_color )
{
	pceFontSetTxColor( tx_color );
	pceFontSetBkColor( bk_color );
	pceFontPutStr( str );
}

