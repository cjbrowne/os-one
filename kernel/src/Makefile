SOURCES=boot.o main.o common.o vga.o
CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m64
LDFLAGS=-Tlink.ld -n
ASFLAGS=-f elf64

all: $(SOURCES) link

clean:
	rm *.o osone

link:
	ld $(LDFLAGS) -o osone $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
