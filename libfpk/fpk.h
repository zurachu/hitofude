/////////////////////////////////////////////
// fpk.h -- extended fpk archive format
/////////////////////////////////////////////

#ifndef FPK_H
#define FPK_H

//  reference: /usr/piece/tools/filepack/�f�R�[�_src/filepack.c
//  original source codes are copyrighted as following:
//    Copyright:  AQUA (Leaf)  since 2001 - Programd by.  Miyakusa Masakazu

#ifndef VOID
typedef void					VOID;
#endif // !VOID

typedef char *				LPSTR;

typedef struct
{
  DWORD dwHeader;                         //  �p�b�N�w�b�_
  DWORD dwFilesAmount;                    //  �t�@�C����
}FPKHEADER;

typedef struct
{
  CHAR  szFileName[16];                   //  �t�@�C�����i�g���q�A'\0'�܂݂�16�����܂Łj
  DWORD dwOffset;                         //  �I�t�Z�b�g�A�h���X
  DWORD dwSize;                           //  �t�@�C���T�C�Y
}FPKENTRY;

// Yui N. �ɂ��g��
// ���ۂ̃R�[�h���ł͂��̌^�͎g��ꂸ�C���̌^�ł��邩�̂悤�� FPKENTRY ���g���B
typedef struct
{
  BYTE szFileName[15];                    // �t�@�C�����i�k�������܂߂� 15 �����܂Łj
  BYTE bCompressed;                       // �g�����k���i��q�j
  DWORD dwOffset;                         // �I�t�Z�b�g�A�h���X�iDWORD ���E�j
  DWORD dwSize;                           // ���k��̃t�@�C���T�C�Y�B���k�O�̃t�@�C���T�C�Y��
                                          // �f�[�^�̐擪 4 bytes �ɖ��ߍ��܂�Ă���B
}FPKENTRY_C;

#define FPK_NO_COMPRESSION    0x00    // 0000 0000

// yui: 2005.07.05
#ifndef LIBFPK_NO_LZSS
#define FPK_LZSS_COMPRESSION  0x80    // 1000 0000
#endif // !LIBFPK_NO_LZSS

#ifndef LIBFPK_NO_ZLIB                // yui: 2005.07.03
#define FPK_ZLIB_COMPRESSION  0xc0    // 1100 0000 /*{{2005/06/23 Naoyuki Sawa}}*/
// yui: 2005.03.21 pva block header
#define PVNSPACK_HEADER 0x1c0258
#endif // !LIBFPK_NO_ZLIB

// yui: 2005.07.03 
#define FPK_LZF_COMPRESSION   0xe0    // 1110 0000


// �g�����k���ɂ���
// --------------------
// ���̃t�@�C�������k����Ă��邩�ۂ��𒲂ׂ�ɂ́C
// bCompressed �̍ŏ�ʃr�b�g�𒲂ׂ邱�Ƃŋ��߂���B
// ����ł͂��̂ق��̃r�b�g�͎g�p���Ȃ��B�����̊g���ɔ��� 0 �ɂ��邱�ƁB

///////////////////////////////////////////////////////////

#endif /* !FPK_H */
