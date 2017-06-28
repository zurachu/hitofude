#include "ext.h"

void ext_Init(BYTE p1, BYTE p2, BYTE p3, BYTE p4, BYTE p5)
{
	CFEX  = (CFEX  & 0xFE) | 0x00;
	P0CFP = (P0CFP & 0x8F) | 0x00;
	P1CFP = (P1CFP & 0xEB) | 0x00;
	P0IOC = (P0IOC & 0x8F) | ((p3 << 6) | (p4 << 5) | (p5 << 4));
	P1IOC = (P1IOC & 0xEB) | ((p1 << 4) | (p2 << 2));
}

void ext_PortSet(int const port, BYTE const data)
{
	switch (port) {
		case 1: P1 = (P1 & 0xEF) | (data << 4); break;
		case 2: P1 = (P1 & 0xFB) | (data << 2); break;
		case 3: P0 = (P0 & 0xBF) | (data << 6); break;
		case 4: P0 = (P0 & 0xDF) | (data << 5); break;
		case 5: P0 = (P0 & 0xEF) | (data << 4); break;
	}
}

int ext_PortGet(int const port)
{
	int ret = 0;
	switch (port) {
		case 1: ret = (P1 >> 4) & 1; break;
		case 2: ret = (P1 >> 2) & 1; break;
		case 3: ret = (P0 >> 6) & 1; break;
		case 4: ret = (P0 >> 5) & 1; break;
		case 5: ret = (P0 >> 4) & 1; break;
	}
	return ret;
}

