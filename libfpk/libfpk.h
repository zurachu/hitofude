/*
	* libfpk -- using FPK archive on P/ECE
	* 	By Yui N., 2003.
	* http://www.autch.net/
*/

// yui: 2005.07.19: ������ɂ͌��J����֐��̂ݎc�����ɂ���
//                  �����p�֐��́�libfpk_impl.h

#ifndef LIBFPK_H
#define LIBFPK_H

#include <piece.h>

// yui: 2005.07.03
// zlib ���g�������Ȃ��Ȃ�R�����g���͂����I
// �������ς���ƃ��C�u�����̃��r���h���K�v�ɂȂ�I
//#ifndef LIBFPK_NO_ZLIB
//#define LIBFPK_NO_ZLIB
//#endif

// yui: 2005.07.05
// LZSS ���g�������Ȃ��Ȃ�R�����g���͂����I
// �������ς���ƃ��C�u�����̃��r���h���K�v�ɂȂ�I
//#ifndef LIBFPK_NO_LZSS
//#define LIBFPK_NO_LZSS
//#endif

// yui: 2005.07.19
// LZF ���g�������Ȃ��Ȃ�R�����g���͂����I
// �������ς���ƃ��C�u�����̃��r���h���K�v�ɂȂ�I
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
	int sct;                  // �Z�N�^�ԍ�
	unsigned char cache[4096];// �Z�N�^�o�b�t�@
	/*}}2005/06/12 Naoyuki Sawa*/
}FPK, *PFPK;
typedef PFPK HFPK;

HFPK fpkOpenArchive(LPSTR lpszFileName);

// C �ɂ��֐��I�[�o�[���[�h������΁c�c�i��
BOOL fpkGetFileInfoS(HFPK hFpk, LPSTR lpszFileName, FPKENTRY *lpFileEntry);
BOOL fpkGetFileInfoN(HFPK hFpk, DWORD dwFileIndex, FPKENTRY *lpFileEntry);

BYTE *fpkExtractToBuffer(HFPK hFpk, FPKENTRY *fpkEntry);
VOID fpkCloseArchive(HFPK hFpk);

#endif /* !LIBFPK_H */
