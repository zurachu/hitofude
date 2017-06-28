#ifndef H_ZURAPCE_DRAW_
#define H_ZURAPCE_DRAW_

/**
	@file ��ʕ`��֘A
*/

#include <piece.h>

/// �`��o�b�t�@
extern BYTE* vBuff;

/// LCD �X�V�t���O
extern BOOL LCDUpdate;

/**
	��ʊ֌W�̏��������s���܂�.
*/
void draw_Init();

/**
	�f�[�^���� PIECE_BMP ���쐬���܂�.
	@param pBmp 
	@param pData �f�[�^�ւ̃|�C���^
*/
void draw_GetPieceBmp(PIECE_BMP* pBmp, BYTE* pData);

/**
	PIECE_BMP��`�悵�܂�.
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
	LCDUpdate == TRUE �Ȃ� vBuff �̓��e��LCD�ɓ]�����܂�.
*/
void draw_LCDTrans();

/**
	�����F�A�w�i�F���w�肵�ĕ������`�悵�܂�.
	@param str ������
	@param tx_color �����F
	@param bk_color �w�i�F
*/
void draw_FontPutStrColor( char* str, int tx_color, int bk_color );

#endif // H_ZURAPCE_DRAW_

