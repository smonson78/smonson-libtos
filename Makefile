CC=m68k-elf-gcc
AR=m68k-elf-ar

IDIOTIC_GCC_BULLSHIT=--param=min-pagesize=0
STD_CFLAGS=-m68000 -fomit-frame-pointer -fno-builtin -I. -ffreestanding -ffunction-sections $(IDIOTIC_GCC_BULLSHIT)
CFLAGS=-Os -g -Wall $(STD_CFLAGS)

TARGET=libtos.a libtos-dlmalloc.a
TOSLIBS=tos.o aes.o xbios.o aes_window.o gemdos.o
# the linker can't handle these: crtstuff.o crt0.o

all: $(TARGET)

dlmalloc.o: dlmalloc.c
	$(CC) $(CFLAGS) -O3 -DLACKS_SYS_TYPES_H -DHAVE_MORECORE=0 -DNO_MALLOC_STATS -DLACKS_ERRNO_H \
		-DLACKS_TIME_H -DLACKS_STDLIB_H -DLACKS_SYS_MMAN_H -DLACKS_FCNTL_H -DLACKS_UNISTD_H \
		-DLACKS_SYS_PARAM_H -DLACKS_ERRNO_H -DNO_MALLINFO -DMMAP_CLEARS=0 -DNO_MALLOC_STATS \
		-DDEFAULT_TRIM_THRESHOLD=131072 -DNO_SEGMENT_TRAVERSAL -DHAVE_MREMAP=0 -g -c -o $@ $^

clean:
	$(RM) $(TARGET) *.o
	$(RM) *~

libtos.a: $(TOSLIBS) libc.o
	$(AR) -crs $@ $^

libtos-dlmalloc.a: $(TOSLIBS) dlmalloc.o libc.o
	$(AR) -crs $@ $^