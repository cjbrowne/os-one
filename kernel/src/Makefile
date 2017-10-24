SOURCES=boot.o main.o
CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS=-Tlink.ld
ASFLAGS=-f elf64

all: $(SOURCES) link

clean:
	rm *.o osone

link:
	ld $(LDFLAGS) -o osone $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
