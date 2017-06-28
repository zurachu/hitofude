#ifndef H_ZURAPCE_DRAW_
#define H_ZURAPCE_DRAW_

/**
	@file 画面描画関連
*/

#include <piece.h>

/// 描画バッファ
extern BYTE* vBuff;

/// LCD 更新フラグ
extern BOOL LCDUpdate;

/**
	画面関係の初期化を行います.
*/
void draw_Init();

/**
	データから PIECE_BMP を作成します.
	@param pBmp 
	@param pData データへのポインタ
*/
void draw_GetPieceBmp(PIECE_BMP* pBmp, BYTE* pData);

/**
	PIECE_BMPを描画します.
	@param pBmp
	@param dx
	@param dy
	@param sx
	@param sy
	@param w
	@param h
	@param param
*/
void draw_DrawPieceBmp( PIECE_BMP* pBmp, int dx, int dy, int sx, int sy, int w, int h, int param );

/**
	LCDUpdate == TRUE なら vBuff の内容をLCDに転送します.
*/
void draw_LCDTrans();

/**
	文字色、背景色を指定して文字列を描画します.
	@param str 文字列
	@param tx_color 文字色
	@param bk_color 背景色
*/
void draw_FontPutStrColor( char* str, int tx_color, int bk_color );

#endif // H_ZURAPCE_DRAW_

