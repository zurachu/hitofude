#ifndef H_ZURAPCE_EXT_
#define H_ZURAPCE_EXT_

/**
	@file 拡張端子関連
*/

#include <piece.h>

#define P0CFP (*((BYTE *)0x402D0))
#define P0    (*((BYTE *)0x402D1))
#define P0IOC (*((BYTE *)0x402D2))
#define P1CFP (*((BYTE *)0x402D4))
#define P1    (*((BYTE *)0x402D5))
#define P1IOC (*((BYTE *)0x402D6))
#define CFEX  (*((BYTE *)0x402DF))

/**
	拡張端子の入出力を初期化します.
	@param p1 ポート1（拡張端子1）：入力=0／出力=1
	@param p2 ポート2（拡張端子4）：入力=0／出力=1
	@param p3 ポート3（拡張端子6）：入力=0／出力=1
	@param p4 ポート4（拡張端子7）：入力=0／出力=1
	@param p5 ポート5（拡張端子8）：入力=0／出力=1
*/
void ext_Init(BYTE const p1, BYTE const p2, BYTE const p3, BYTE const p4, BYTE const p5);

/**
	拡張端子にデータを出力します.
	@param port 出力先ポート（1～5）
	@param data データ（0／1）
*/
void ext_PortSet(int const port, BYTE const data);

/**
	拡張端子からデータを入力します.
	@param port 入力元ポート（1～5）
	@return データ（0／1）
*/
int ext_PortGet(int const port);

#endif // H_ZURAPCE_EXT_

