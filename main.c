/**
	@file P/ECE ヒトフデ メイン
*/

#include <piece.h>
#include "zurapce/zurapce.h"
#include "libfpk/libfpk.h"

#include "stage.h"

#define FPK_ENTRY_MAX (1024)

static HFPK s_hfpk;
static FPKENTRY s_fpk_entry[ FPK_ENTRY_MAX ];

#define LAUNCH_NUM ( ( DISP_Y - 10 ) / 6 )
static int s_question_amount;
static int s_question_index = 0;
static int s_question_offset = 0;

static char* s_data;

enum MODE {
	MODE_LAUNCH,
	MODE_GAME,
	MODE_MAX,
};
typedef enum MODE MODE;
static MODE s_mode = MODE_LAUNCH;

/// 問題選択
void UpdateLaunch()
{
	if( pcePadGet() & TRG_UP )
	{
		s_question_index = ( s_question_index + s_question_amount - 1 ) % s_question_amount;
		if( s_question_index == s_question_amount - 1 && s_question_amount > LAUNCH_NUM )
		{
			s_question_offset = s_question_amount - LAUNCH_NUM;
		}
		else if( s_question_index < s_question_offset )
		{
			s_question_offset = s_question_index;
		}
	}
	else if( pcePadGet() & TRG_DN )
	{
		s_question_index = ( s_question_index + 1 ) % s_question_amount;
		if( s_question_index == 0 )
		{
			s_question_offset = 0;
		}
		else if( s_question_offset + LAUNCH_NUM <= s_question_index )
		{
			s_question_offset++;
		}
	}
	else if( pcePadGet() & ( TRG_A | TRG_C ) )
	{
		pceHeapFree( s_data );
		s_data = (char*)fpkExtractToBuffer( s_hfpk, &s_fpk_entry[ s_question_index ] );
		InitStage( s_data );
		s_mode = MODE_GAME;
	}
	else if( pcePadGet() & TRG_D )
	{
		pceAppReqExit( 0 );
	}
}


/// 問題選択描画
void DrawLaunch()
{
	int i;
	int* select = (int*)( vBuff + ( ( s_question_index - s_question_offset ) * 6 + 10 ) * DISP_X );

	pceLCDPaint( 0, 0, 0, DISP_X, DISP_Y );
	
	pceLCDPaint( 2, 0, 0, DISP_X, 10 );
	pceFontSetType( 0 );
	pceFontSetPos( 0, 0 );
	pceFontSetTxColor( 0 );
	pceFontSetBkColor( FC_SPRITE );
	pceFontPutStr( "P/ECEヒトフデ\n" );
	
	pceFontSetType( 2 );
	pceFontSetTxColor( 3 );
	pceFontSetBkColor( 0 );
	for( i = s_question_offset; i < s_question_offset + LAUNCH_NUM; i++ )
		pceFontPrintf( "%s\n", s_fpk_entry[i].szFileName );
	
	for( i = 0; i < DISP_X * 6 / sizeof(int); i++ )
		*select++ ^= 0x03030303; // 選択部分の反転

	LCDUpdate = TRUE;
}

/// 初期化
void pceAppInit( void )
{
	int i;

	app_Init( 100 );

	InitImage();
	if( ( s_hfpk = fpkOpenArchive( "hitofude.fpk" ) ) != NULL )
	{
		s_question_amount = s_hfpk->fpkHeader.dwFilesAmount;
		if( s_question_amount > FPK_ENTRY_MAX )
			s_question_amount = FPK_ENTRY_MAX;
		for( i = 0; i < s_question_amount; i++ )
			fpkGetFileInfoN( s_hfpk, i, &s_fpk_entry[i] );
	}
}

/// メイン
void pceAppProc( int cnt )
{
	if( s_hfpk == NULL || s_question_amount == 0 )
		pceAppReqExit( 0 );

	switch( s_mode )
	{
	case MODE_LAUNCH:
		UpdateLaunch();
		DrawLaunch();
		break;
	case MODE_GAME:
		if( IsEnd() )
		{
			s_mode = MODE_LAUNCH;
		}
		UpdateStage();
		if( IsRetry() )
		{
			InitStage( s_data );
		}
		DrawStage();
		break;
	default:
		break;
	}
	draw_LCDTrans();
}

/// 終了
void pceAppExit( void )
{
	fpkCloseArchive( s_hfpk );
	app_Exit();
}

