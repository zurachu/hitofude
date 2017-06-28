# Piece �p makefile

# �g���q�̒�`

.SUFFIXES:
.SUFFIXES:  .o .s .c .bmp

.INTERMEDIATE: cursor.c

# �����R�}���h�E�I�v�V�����̃}�N��

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

# �����K��

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

# �\���t�@�C���E�����t�@�C���̃}�N��

PRGNAME = hitofude
FILENAME = hitofude
ICON = icon.pid
CAPTION = P/ECE�q�g�t�f
OBJS =	main.o stage.o panel.o blank.o cursor.o check.o
LIBS =	zurapce\zurapce.lib libfpk\libfpk.lib

all : $(PRGNAME).srf $(FILENAME).fpk

$(PRGNAME).srf : $(OBJS) $(LIBS)
	$(LD) $(LDFLAGS) -e$@ $^

# �ˑ��֌W

main.o : stage.h
stage.o : stage.h

$(ICON) : icon.bmp
	$(PGD) -i $<

$(FILENAME).fpk : $(wildcard QUESTION/*)
	$(FPK) $(FPKFLAGS) $@ $(sort $^)

# �t���b�V���������݃C���[�W����
pex : $(FILENAME).pex

$(FILENAME).pex : $(PRGNAME).srf $(ICON)
	ppack -e $< -o$@ -n$(CAPTION) -i$(ICON)

# �t���b�V����������
isd : $(FILENAME).pex $(FILENAME).fpk
	isd =w $(FILENAME).pex
	isd =w $(FILENAME).fpk

# �N���[���A�b�v
clean:
	del $(PRGNAME).srf $(FILENAME).pex $(PRGNAME).sym $(PRGNAME).map $(ICON) $(FILENAME).fpk *.o

