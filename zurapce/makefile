# Piece 用 makefile

# 拡張子の定義

.SUFFIXES:
.SUFFIXES:  .o .s .c

# 生成コマンド・オプションのマクロ

CC = pcc33
CFLAGS = -c -g -gp=0x0 -near -O2 -Wall
AS = pcc33
ASFLAGS = -c -g -gp=0x0 -near
LD = lib33
LDFLAGS =

# 生成規則

.c.o:
	$(CC) $(CFLAGS) $<

.s.o:
	$(AS) $(ASFLAGS) $<

# 構成ファイル・生成ファイルのマクロ

LIBNAME = zurapce
OBJS =	app.o file.o draw.o wave.o ext.o

$(LIBNAME).lib : $(OBJS)
	$(LD) $(LDFLAGS) $@ $^

# 依存関係

# クリーンアップ
clean:
	del $(LIBNAME).lib *.o

