#include "screen.h"

unsigned char		g_cursor_x = 0;
unsigned char		g_cursor_y = 0;
unsigned char		g_cursor_attr = 0x0a;

void				scroll_up(void)
{
	volatile int				i;
	unsigned char	*video = (unsigned char *)VIDEO_RAM + 160;

	i = 0;
	while (i < SCREEN_MEM_SIZE - 160)
	{
		*(video - 160 + i) = *(video + i);
		i++;
	}
	if (g_cursor_y > 0)
		g_cursor_y--;
}

void				clear_screen(void)
{
	unsigned char	*video = (unsigned char *)VIDEO_RAM;

	while (video < (unsigned char *)VIDEO_RAM + SCREEN_MEM_SIZE)
		*video++ = 0;
}

void				putchar(char c)
{
	unsigned char	*video = (unsigned char *)0xb8000;

	if (c == '\n')
	{
		g_cursor_x = 0;
		g_cursor_y++;
	}
	else if (c == '\t')
		g_cursor_x = g_cursor_x + 4;
	else if (c == '\r')
		g_cursor_x = 0;
	else
	{
		video = (unsigned char *)VIDEO_RAM + (g_cursor_x * 2) + (g_cursor_y * 160);
		*video = c;
		*(video + 1) = g_cursor_attr;
		g_cursor_x++;
	}
	if (g_cursor_x >= MAX_COLUMNS)
	{
		g_cursor_y++;
		g_cursor_x = 0;
	}
	if (g_cursor_y >= MAX_ROWS)
	{
		scroll_up();
	}
}

void				putstr(char *s)
{
	while (*s)
		putchar(*s++);
}
