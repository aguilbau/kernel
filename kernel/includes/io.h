#ifndef IO_H
# define IO_H

# define cli __asm__("cli"::)
# define sti __asm__("sti"::)
# define out(port, value) __asm__("outb %%al, %%dx" :: "a" (port), "d", value)
# define in(port) ({unsigned char _v; __asm__("inb %%dx, %%al" : "=a" (_v) : "d" (port)); _v;})

#endif /* !IO_H */
