#ifndef SCREEN_H
# define SCREEN_H

# define VIDEO_RAM			0xb8000
# define SCREEN_MEM_SIZE	4000

# define MAX_COLUMNS		80
# define MAX_ROWS			25

extern unsigned char g_cursor_y;

void				scroll_up(void);
void				putchar(char c);
void				putstr(char *s);
void				clear_screen(void);

#endif
