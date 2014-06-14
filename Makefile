NAME		=	gilbOS.img

CC			=	gcc

LDFLAGS		=	--oformat=binary -Ttext 1000 -melf_i386

CFLAGS		=	-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -Wall -Wextra -Werror -nostartfiles -nodefaultlibs -I./kernel/includes -O3

BOOT_SRCS	=	boot/gilbOS_boot.s


KERNEL_SRCS	=	kernel.c \
				screen_output.c \
				gdt.c

KERNEL_CCS	=	$(addprefix kernel/, $(KERNEL_SRCS))

KERNEL_OBJS	=	$(KERNEL_CCS:.c=.o)


FUN_SRCS	=	stdfuns.c

FUN_CCS		=	$(addprefix kernel/functions/, $(FUN_SRCS))

FUN_OBJS	=	$(FUN_CCS:.c=.o)


all: $(NAME)

$(NAME): kernel_cc boot_cc
	cat kernel.bin >> boot.bin
	dd if=boot.bin count=4096 of=gilbOS.img conv=sync

kernel_cc: $(KERNEL_OBJS) $(FUN_OBJS)
	ld $(LDFLAGS) $^ -o kernel.bin

boot_cc: $(BOOT_SRCS)
	nasm -f bin $(BOOT_SRCS) -o boot.bin

clean:
	rm -f $(NAME) boot.bin kernel.bin $(KERNEL_OBJS) $(FUN_OBJS)

re: clean all
