NAME	=	gilbOS.img

SRCS	=	boot/gilbOS_boot.s

all: $(NAME)

$(NAME):
		nasm -f bin $(SRCS) -o $(NAME)

clean:
		/bin/rm -f $(NAME)

re: clean all
