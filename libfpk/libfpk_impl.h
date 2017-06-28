/*
	* libfpk -- using FPK archive on P/ECE
	* 	By Yui N., 2003.
	* http://www.autch.net/
*/

// yui: 2005.07.19: �����p�錾�͂�����ֈړ�

#ifndef LIBFPK_IMPL_H
#define LIBFPK_IMPL_H

#include "libfpk.h"


//int pceFileReadPos(FILEACC *pfa, unsigned char *buf, int pos, int size);
//��{{2005/06/12 Naoyuki Sawa}}
// int pceFileReadPos(HFPK hFpk, unsigned char *buf, int pos, int size);
// yui: 2005.07.03 ���͂� P/ECE �W�� pceFileReadPos() �ł͂Ȃ��̂ŉ���
int fpkFileReadPos(HFPK hFpk, unsigned char *buf, int pos, int size);

/*{{2005/06/12 Naoyuki Sawa*/
int fpkStrCaseCmp(const char* s1, const char* s2);
int fpkFileNameCRC(const char* fname); /* 16bit */
/*}}2005/06/12 Naoyuki Sawa*/

// ############################################################################
// ## ���k���\�b�h
// ############################################################################

#ifndef LIBFPK_NO_LZSS
void hitodeLZSSDecode(HFPK hFpk, int ofs, int size, BYTE* dst);
#endif

#ifndef LIBFPK_NO_LZF
DWORD lzfDecompress(HFPK hFpk, DWORD dwOffset, int dwSourceSize, BYTE* pDst, int dwDestSize);
#endif

#ifndef LIBFPK_NO_ZLIB
DWORD zlibDecode(HFPK hFpk, DWORD dwOffset, DWORD dwSourceSize, BYTE *pOutBuff);
#endif

// inflate �֌W�͂�₱�����̂� .h ���c��

#endif /* !LIBFPK_IMPL_H */
