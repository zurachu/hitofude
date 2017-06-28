#ifndef H_ZURAPCE_EXT_
#define H_ZURAPCE_EXT_

/**
	@file �g���[�q�֘A
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
	�g���[�q�̓��o�͂����������܂�.
	@param p1 �|�[�g1�i�g���[�q1�j�F����=0�^�o��=1
	@param p2 �|�[�g2�i�g���[�q4�j�F����=0�^�o��=1
	@param p3 �|�[�g3�i�g���[�q6�j�F����=0�^�o��=1
	@param p4 �|�[�g4�i�g���[�q7�j�F����=0�^�o��=1
	@param p5 �|�[�g5�i�g���[�q8�j�F����=0�^�o��=1
*/
void ext_Init(BYTE const p1, BYTE const p2, BYTE const p3, BYTE const p4, BYTE const p5);

/**
	�g���[�q�Ƀf�[�^���o�͂��܂�.
	@param port �o�͐�|�[�g�i1�`5�j
	@param data �f�[�^�i0�^1�j
*/
void ext_PortSet(int const port, BYTE const data);

/**
	�g���[�q����f�[�^����͂��܂�.
	@param port ���͌��|�[�g�i1�`5�j
	@return �f�[�^�i0�^1�j
*/
int ext_PortGet(int const port);

#endif // H_ZURAPCE_EXT_

