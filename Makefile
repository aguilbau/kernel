NAME		=	gilbOS.img

CC			=	gcc

LDFLAGS		=	--oformat=binary -Ttext 1000 -melf_i386

CFLAGS		=	-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -Wall -Wextra -Werror -nostartfiles -nodefaultlibs -I./kernel/includes -O3

BOOT_SRCS	=	boot/gilbOS_boot.s

KERNEL_SRCS	=	kernel.c \
				screen_output.c

KERNEL_CCS	=	$(addprefix kernel/, $(KERNEL_SRCS))

OBJS = $(KERNEL_CCS:.c=.o)

all: $(NAME)

$(NAME): kernel_cc boot_cc
	cat kernel.bin >> boot.bin
	dd if=boot.bin count=4096 of=gilbOS.img conv=sync

kernel_cc: $(OBJS)
	ld $(LDFLAGS) $^ -o kernel.bin

boot_cc: $(BOOT_SRCS)
	nasm -f bin $(BOOT_SRCS) -o boot.bin

