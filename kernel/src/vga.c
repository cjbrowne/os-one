#include "vga.h"

const short vga_screen_height = 25;
const short vga_screen_width = 80;


unsigned short* video_memory = (unsigned short*) 0xb8000;
unsigned char cursor_x, cursor_y;

static void move_cursor()
{

	const short vga_control_port = 0x3D4;
	const short vga_cmd_set_high = 14;
	const short vga_cmd_set_lo   = 15;
	const short vga_data_port    = 0x3D5;

	u16int cursorLocation = cursor_y * vga_screen_width + cursor_x;
	outb(vga_control_port, vga_cmd_set_high);
	outb(vga_data_port, cursorLocation >> 8);
	outb(vga_control_port, vga_cmd_set_lo);
	outb(vga_data_port, cursorLocation);
}

static void scroll()
{

	const u8int attributeByte = (VGA_COLOR_BLACK << 4) | (VGA_COLOR_WHITE & 0x0F);
	const u16int blank = ASCII_SPACE | (attributeByte << 8);
	if(cursor_y >= vga_screen_height)
	{
		int i;
		int video_memory_size = (vga_screen_height)*(vga_screen_width);
		for(i = 0; i < video_memory_size - vga_screen_width; i++)
		{
			video_memory[i] = video_memory[i+80];
		}

		for(i = video_memory_size - vga_screen_width; i < video_memory_size; i++)
		{
			video_memory[i] = blank;
		}
		cursor_y = vga_screen_height - 1;
	}
}

void vga_putc(char c)
{
	const u8int backColour = VGA_COLOR_BLACK;
	const u8int foreColour = VGA_COLOR_WHITE;
	
	const u8int attributeByte = (backColour << 4) | (foreColour & 0x0F);
	const u16int attribute = attributeByte << 8;
	u16int* location;

	if(c == ASCII_BACKSPACE && cursor_x > 0)
	{
		cursor_x--;
	}
	else if (c == ASCII_TAB)
	{
		cursor_x = (cursor_x + 8) & ~(8-1);
	}
	// carriage return should return the cursor to position 0
	else if (c == '\r')
	{
		cursor_x = 0;
	}
	else if (c == '\n')
	{
		cursor_x = 0;
		cursor_y++;
	}
	else if (c >= ' ')
	{
		location = video_memory + (cursor_y * 80 + cursor_x);
		*location = c | attribute;
		cursor_x++;
	}

	if (cursor_x >= vga_screen_width)
	{
		cursor_x = 0;
		cursor_y++;
	}

	scroll();
	move_cursor();
}

void vga_clear(void)
{
	u8int attributeByte = (VGA_COLOR_BLACK << 4) | (VGA_COLOR_WHITE & 0x0F);
	u16int blank = ASCII_SPACE | (attributeByte << 8);

	int i;
	for(i = 0; i < vga_screen_width * vga_screen_height; i++)
	{
		video_memory[i] = blank;
	}

	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

// no buffer overrun protection? are you serious?
void vga_print(char* str)
{
	int i = 0;
	while(str[i] != 0)
	{
		vga_putc(str[i++]);	
	}
}
