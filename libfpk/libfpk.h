/*
	* libfpk -- using FPK archive on P/ECE
	* 	By Yui N., 2003.
	* http://www.autch.net/
*/

// yui: 2005.07.19: こちらには公開する関数のみ残す事にした
//                  実装用関数は→libfpk_impl.h

#ifndef LIBFPK_H
#define LIBFPK_H

#include <piece.h>

// yui: 2005.07.03
// zlib を使いたくないならコメントをはずす！
// ただし変えるとライブラリのリビルドが必要になる！
//#ifndef LIBFPK_NO_ZLIB
//#define LIBFPK_NO_ZLIB
//#endif

// yui: 2005.07.05
// LZSS を使いたくないならコメントをはずす！
// ただし変えるとライブラリのリビルドが必要になる！
//#ifndef LIBFPK_NO_LZSS
//#define LIBFPK_NO_LZSS
//#endif

// yui: 2005.07.19
// LZF を使いたくないならコメントをはずす！
// ただし変えるとライブラリのリビルドが必要になる！
//#ifndef LIBFPK_NO_LZF
//#define LIBFPK_NO_LZF
//#endif

#include "fpk.h"
//#include "pceFileReadPos.h" /*{{2005/06/12 Naoyuki Sawa}}*/

typedef struct
{
	FPKHEADER	fpkHeader;
	FILEACC pfa;
	/*{{2005/06/12 Naoyuki Sawa*/
	unsigned short* crc/*[fpkHeader.dwFilesAmount]*/;
	int sct;                  // セクタ番号
	unsigned char cache[4096];// セクタバッファ
	/*}}2005/06/12 Naoyuki Sawa*/
}FPK, *PFPK;
typedef PFPK HFPK;

HFPK fpkOpenArchive(LPSTR lpszFileName);

// C にも関数オーバーロードがあれば……（ぉ
BOOL fpkGetFileInfoS(HFPK hFpk, LPSTR lpszFileName, FPKENTRY *lpFileEntry);
BOOL fpkGetFileInfoN(HFPK hFpk, DWORD dwFileIndex, FPKENTRY *lpFileEntry);

BYTE *fpkExtractToBuffer(HFPK hFpk, FPKENTRY *fpkEntry);
VOID fpkCloseArchive(HFPK hFpk);

#endif /* !LIBFPK_H */
