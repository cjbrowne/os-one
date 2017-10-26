#ifndef COMMON_H
#define COMMON_H

typedef unsigned long u64int;
typedef 	 long s64int;
typedef unsigned int u32int;
typedef 	 int s32int;
typedef unsigned short u16int;
typedef		 short s16int;
typedef unsigned char u8int;
typedef 	 char s8int;


void outb(unsigned short port, unsigned char value);
unsigned char inb(unsigned short port);
unsigned short inw(unsigned short port);

#endif
