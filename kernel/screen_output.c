#include "screen.h"

unsigned char		g_cursor_x = 0;
unsigned char		g_cursor_y = 0;
unsigned char		g_cursor_attr = 0x0a;

void				scroll_up(unsigned char n)
{
	(void)n;
}

void				putchar(char c)
{
	unsigned char	*video;

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
	if (g_cursor_x > 80)
	{
		g_cursor_y++;
		g_cursor_x = 0;
	}
}

void				putstr(char *s)
{
	while (*s)
		putchar(*s++);
}
