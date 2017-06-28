# Piece 用 makefile

# 拡張子の定義

.SUFFIXES:
.SUFFIXES:  .o .s .c .bmp

.INTERMEDIATE: cursor.c

# 生成コマンド・オプションのマクロ

CC = pcc33
CFLAGS = -c -g -gp=0x0 -near -O2 -Wall
AS = pcc33
ASFLAGS = -c -g -gp=0x0 -near
LD = pcc33
LDFLAGS = -g -ls -lm

PGD = pbcc
PGDFLAGS = -h
FPK = par
FPKFLAGS = c -CTr

# 生成規則

%.c : 1BIT\%.bmp
	$(PGD) $(PGDFLAGS) -1 $< .\$@

%.c : 2BIT\%.bmp
	$(PGD) $(PGDFLAGS) -2 $< .\$@

%.c : 2BIT_MASK\%.bmp
	$(PGD) $(PGDFLAGS) -m $< .\$@

.c.o:
	$(CC) $(CFLAGS) $<

.s.o:
	$(AS) $(ASFLAGS) $<

# 構成ファイル・生成ファイルのマクロ

PRGNAME = hitofude
FILENAME = hitofude
ICON = icon.pid
CAPTION = P/ECEヒトフデ
OBJS =	main.o stage.o panel.o blank.o cursor.o check.o
LIBS =	zurapce\zurapce.lib libfpk\libfpk.lib

all : $(PRGNAME).srf $(FILENAME).fpk

$(PRGNAME).srf : $(OBJS) $(LIBS)
	$(LD) $(LDFLAGS) -e$@ $^

# 依存関係

main.o : stage.h
stage.o : stage.h

$(ICON) : icon.bmp
	$(PGD) -i $<

$(FILENAME).fpk : $(wildcard QUESTION/*)
	$(FPK) $(FPKFLAGS) $@ $(sort $^)

# フラッシュ書き込みイメージ生成
pex : $(FILENAME).pex

$(FILENAME).pex : $(PRGNAME).srf $(ICON)
	ppack -e $< -o$@ -n$(CAPTION) -i$(ICON)

# フラッシュ書き込み
isd : $(FILENAME).pex $(FILENAME).fpk
	isd =w $(FILENAME).pex
	isd =w $(FILENAME).fpk

# クリーンアップ
clean:
	del $(PRGNAME).srf $(FILENAME).pex $(PRGNAME).sym $(PRGNAME).map $(ICON) $(FILENAME).fpk *.o

