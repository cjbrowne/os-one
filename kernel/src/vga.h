#ifndef VGA_H
#define VGA_H

#include "common.h"
void vga_putc(char c);
void vga_clear_screen(void);
void vga_print(char* str);

// VGA literals
#define VGA_COLOR_BLACK 0
#define VGA_COLOR_WHITE 15

// ASCII literals (TODO: move these into their own header file)
#define ASCII_SPACE 0x20
#define ASCII_BACKSPACE 0x08
#define ASCII_TAB 0x09


#endif
