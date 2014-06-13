#ifndef SCREEN_H
# define SCREEN_H

# define VIDEO_RAM			0xb8000
# define SCREEN_MEM_SIZE	4000

void				scroll_up(int n);
void				putchar(char c);
void				putstr(char *s);

#endif
