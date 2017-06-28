#include "stage.h"

/**
	@file P/ECE ヒトフデ ステージ部分
*/

#include <piece.h>
#include <stdlib.h>
#include <ctype.h>
#include "zurapce/zurapce.h"

int errno;

static PIECE_BMP s_blank;
static PIECE_BMP s_panel;
static PIECE_BMP s_cursor;
static PIECE_BMP s_check;
extern BYTE blank[];
extern BYTE panel[];
extern BYTE cursor[];
extern BYTE check[];

#define MAX_WIDTH	(14)
#define MAX_HEIGHT	(9)
#define PANEL_W		(8)
#define PANEL_H		(8)
#define BASE

static int width = MAX_WIDTH;	///< ステージの幅
static int height = MAX_HEIGHT;	///< ステージの高さ

static int table[ MAX_WIDTH ][ MAX_HEIGHT ];
static int m_panel_animation;

enum MODE {
	MODE_FREE,
	MODE_CHECK,
	MODE_REVERSE,
	MODE_SWEEP,
	MODE_RESULT,
	MODE_MAX,
};
typedef enum MODE MODE;

enum DIR {
	DIR_NONE,
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_MAX,
};
typedef enum DIR DIR;

DIR reverse_direction[ DIR_MAX ] = {
	DIR_NONE,
	DIR_DOWN,
	DIR_UP,
	DIR_RIGHT,
	DIR_LEFT,
};

struct CURSOR {
	MODE mode;
	unsigned int animation;
	int x;
	int y;
	DIR direction[ ( MAX_WIDTH + 2 ) * ( MAX_HEIGHT + 2 ) ];
	BOOL checked[ MAX_WIDTH + 2 ][ MAX_HEIGHT + 2 ];
} m_cursor;

int Base_X()
{
	return ( DISP_X - ( width + 2 ) * PANEL_W ) / 2;
}

int Base_Y()
{
	return ( DISP_Y - ( height + 2 ) * PANEL_H ) / 2;
}

BOOL IsClear()
{
	int x, y;
	
	for( y = 0; y < height; y++ )
		for( x = 0; x < width; x++ )
			if( table[0][y] != table[x][y] )
				return FALSE;
	
	return TRUE;
}

BOOL IsRetry()
{
	if( m_cursor.mode == MODE_RESULT && !IsClear() )
		if( pcePadGet() & ( TRG_A | TRG_B |TRG_C ) )
			return TRUE;
	return FALSE;
}

BOOL IsEnd()
{
	if( pcePadGet() & TRG_D )
		return TRUE;

	switch( m_cursor.mode )
	{
	case MODE_FREE:
		return( pcePadGet() & TRG_B );
	case MODE_RESULT:
		return( IsClear() && ( pcePadGet() & ( TRG_A | TRG_B |TRG_C ) ) );
	default:
		break;
	}
	return FALSE;
}

void InitCursor()
{
	int x, y;

	m_cursor.mode = MODE_FREE;
	m_cursor.animation = 0;
	for( x = 0; x < ( MAX_WIDTH + 2 ) * ( MAX_HEIGHT + 2 ); x++ )
		m_cursor.direction[x] = DIR_NONE;
	for( y = 0; y < MAX_HEIGHT + 2; y++ )
		for( x = 0; x < MAX_WIDTH + 2; x++ )
			m_cursor.checked[x][y] = FALSE;
}

void InitImage()
{
	draw_GetPieceBmp( &s_blank, blank );
	draw_GetPieceBmp( &s_panel, panel );
	draw_GetPieceBmp( &s_cursor, cursor );
	draw_GetPieceBmp( &s_check, check );
}

void InitStage( char* data )
{
	int x, y;

	while( !isdigit( *data ) )	data++;
	width = atoi( data );
	while( isdigit( *data ) )	data++;
	while( !isdigit( *data ) )	data++;
	height = atoi( data );
	while( isdigit( *data ) )	data++;
	for( y = 0; y < height; y++ )
	{
		for( x = 0; x < width; x++ )
		{
			while( !isdigit( *data ) )	data++;
			table[x][y] = *data++ - '0';
		}
	}
	
	m_cursor.x = m_cursor.y = 1;
	InitCursor();
}

void FreeCursor()
{
	if( pcePadGet() & TRG_UP )
	{
		if( m_cursor.y > 0 )
		{
			m_cursor.y--;
		}
	}
	else if( pcePadGet() & TRG_DN )
	{
		if( m_cursor.y < height + 2 - 1 )
		{
			m_cursor.y++;
		}
	}
	else if( pcePadGet() & TRG_LF )
	{
		if( m_cursor.x > 0 )
		{
			m_cursor.x--;
		}
	}
	else if( pcePadGet() & TRG_RI )
	{
		if( m_cursor.x < width + 2 - 1 )
		{
			m_cursor.x++;
		}
	}
	else if( pcePadGet() & TRG_A )
	{
		m_cursor.mode = MODE_CHECK;
		m_cursor.checked[ m_cursor.x ][ m_cursor.y ] = TRUE;
	}
}

void Check( DIR direction )
{
	int x = m_cursor.x, y = m_cursor.y;
	int i;
	
	switch( direction )
	{
	case DIR_UP:
		y--;
		break;
	case DIR_DOWN:
		y++;
		break;
	case DIR_LEFT:
		x--;
		break;
	case DIR_RIGHT:
		x++;
		break;
	default:
		break;
	}
	for( i = 0; m_cursor.direction[ i ] != DIR_NONE; i++ );
	
	if( m_cursor.checked[ x ][ y ] )
	{
		if( m_cursor.direction[ i - 1 ] == reverse_direction[ direction ] )
		{
			m_cursor.direction[ i - 1 ] = DIR_NONE;
			m_cursor.checked[ m_cursor.x ][ m_cursor.y ] = FALSE;
			m_cursor.x = x;
			m_cursor.y = y;
		}
	}
	else
	{
		m_cursor.direction[ i ] = direction;
		m_cursor.checked[ x ][ y ] = TRUE;
		m_cursor.x = x;
		m_cursor.y = y;
	}
}

void CheckCursor()
{
	if( pcePadGet() & TRG_UP )
	{
		if( m_cursor.y > 0 )
		{
			Check( DIR_UP );
		}
	}
	else if( pcePadGet() & TRG_DN )
	{
		if( m_cursor.y < height + 2 - 1 )
		{
			Check( DIR_DOWN );
		}
	}
	else if( pcePadGet() & TRG_LF )
	{
		if( m_cursor.x > 0 )
		{
			Check( DIR_LEFT );
		}
	}
	else if( pcePadGet() & TRG_RI )
	{
		if( m_cursor.x < width + 2 - 1 )
		{
			Check( DIR_RIGHT );
		}
	}
	else if( pcePadGet() & TRG_A )
	{
		m_cursor.mode = MODE_REVERSE;
		m_panel_animation = 0;
	}
	else if( pcePadGet() & TRG_B )
	{
		InitCursor();
	}
}

void UpdateStage()
{
	int x, y;

	switch( m_cursor.mode )
	{
	case MODE_FREE:
		FreeCursor();
		break;
	case MODE_CHECK:
		CheckCursor();
		break;
	case MODE_REVERSE:
		if( m_panel_animation >= 8 )
		{
			for( y = 0; y < height; y++ )
				for( x = 0; x < width; x++ )
					if( m_cursor.checked[ x + 1 ][ y + 1 ] )
						table[ x ][ y ] ^= 1;
			m_cursor.mode = MODE_SWEEP;
			m_panel_animation = 0;
		}
		break;
	case MODE_SWEEP:
		if( m_panel_animation >= width + 5 )
		{
			m_cursor.mode = MODE_RESULT;
		}
		break;
	case MODE_RESULT:
		break;
	default:
		break;
	}
}

void DrawPanel()
{
	int animation[2][8] = {
		{ 0, 2, 4, 6, 7, 5, 3, 1 },
		{ 1, 3, 5, 7, 6, 4, 2, 0 },
	};
	int x, y, sx, sy, i;

	for( y = 0; y < height + 2; y++ )
		for( x = 0; x < width + 2; x++ )
			draw_DrawPieceBmp( &s_blank, PANEL_W * x + Base_X(), PANEL_H * y + Base_Y(),
								0, 0, PANEL_W, PANEL_H, DRW_NOMAL );

	for( y = 0; y < height; y++ )
	{
		for( x = 0; x < width; x++ )
		{
			sx = 0;
			sy = table[x][y] * 8;
			switch( m_cursor.mode )
			{
			case MODE_REVERSE:
				if( m_cursor.checked[ x + 1 ][ y + 1 ] )
				{
					sx = animation[ table[x][y] ][ m_panel_animation ] / 2 * 8;
					sy = animation[ table[x][y] ][ m_panel_animation ] % 2 * 8;
				}
				break;
			case MODE_SWEEP:
			case MODE_RESULT:
				for( i = 0; i < width && table[x][y] == table[i][y]; i++ );
				if( i >= width )
				{
					sx = ( table[x][y]? m_panel_animation - x : ( m_panel_animation - ( width - x ) ) ) * PANEL_W;
					if( sx < 0 )		sx = 0;
					if( sx > PANEL_W * 4 )	sx = PANEL_W * 4;
				}
				break;
			default:
				break;
			}
			draw_DrawPieceBmp( &s_panel, PANEL_W * ( x + 1 ) + Base_X(), PANEL_H * ( y + 1 ) + Base_Y(),
								sx, sy, PANEL_W, PANEL_H, DRW_NOMAL );
		}
	}
}

void DrawCursor()
{
	int x = m_cursor.x, y = m_cursor.y;
	int i;
	int color = ( m_cursor.animation % 2 )? 3 : 0;

	switch( m_cursor.mode )
	{
	case MODE_FREE:
	case MODE_REVERSE:
	case MODE_SWEEP:
	case MODE_RESULT:
		draw_DrawPieceBmp( &s_cursor, PANEL_W * x + Base_X() - 4, PANEL_H * y + Base_Y() - 4,
							( m_cursor.animation % 8 ) / 2 * 16, 0, 16, 16,
							DRW_CLR( color, COLOR_MASK ) );
		break;
	case MODE_CHECK:
		for( i = 0; m_cursor.direction[ i ] != DIR_NONE; i++ );
		for( ; i >= 0; i-- )
		{
			DIR src_direction = ( i > 0 )? m_cursor.direction[ i - 1 ] : DIR_NONE;
			DIR dst_direction = m_cursor.direction[ i ];
		
			draw_DrawPieceBmp( &s_check, PANEL_W * x + Base_X(), PANEL_H * y + Base_Y(),
								PANEL_W * src_direction, PANEL_H * dst_direction, PANEL_W, PANEL_H,
								DRW_CLR( color, COLOR_MASK ) );
			switch( src_direction )
			{
			case DIR_UP:
				y++;
				break;
			case DIR_DOWN:
				y--;
				break;
			case DIR_LEFT:
				x++;
				break;
			case DIR_RIGHT:
				x--;
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}

void DrawStage()
{
	pceLCDPaint( 0, 0, 0, DISP_X, DISP_Y );
	DrawPanel();
	DrawCursor();
	if( m_cursor.mode == MODE_RESULT )
	{
		pceFontSetType( 0 );
		pceFontSetPos( 44, 39 );
		if( IsClear() )
		{
			draw_FontPutStrColor( "ク", 0, 3 );
			draw_FontPutStrColor( "リ", 3, 0 );
			draw_FontPutStrColor( "ア", 0, 3 );
			draw_FontPutStrColor( "ー", 3, 0 );
		}
		else
		{
			draw_FontPutStrColor( "リ", 0, 3 );
			draw_FontPutStrColor( "ト", 3, 0 );
			draw_FontPutStrColor( "ラ", 0, 3 );
			draw_FontPutStrColor( "イ", 3, 0 );
		}
	}
	m_cursor.animation++;
	m_panel_animation++;
	LCDUpdate = TRUE;
}

