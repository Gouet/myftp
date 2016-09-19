##
## Makefile for MAKEFILE in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myftp
## 
## Made by Victor Gouet
## Login   <gouet_v@epitech.net>
## 
## Started on  Mon May  2 10:16:12 2016 Victor Gouet
## Last update Fri May 13 21:20:39 2016 Victor Gouet
##

CC		= gcc

RM		= rm -f

NAME		= server

LIBNAME		= libstringLib.a

LIBS		= lib/on_flag_bounded.c \
		  lib/on_flag_reverse.c \
		  lib/on_flag_strings.c \
		  lib/controller_flags.c \
		  lib/on_flag_char.c \
		  lib/on_flags_bits.c \
		  lib/storage.c \
		  lib/counts_size_bytes.c \
		  lib/on_flag_integer.c \
		  lib/on_flags_less.c \

SRCS		= src/main.c \
		  src/server.c \
		  src/client_connection.c \
		  src/server_connection.c \
		  src/command_login.c \
		  src/command_actions.c \
		  src/command_mode.c \
		  src/exec_command.c \
		  src/get_data.c	\
		  src/init_command.c \
		  src/passiv_exec.c \
		  src/get_client_mode.c \

OBJS		= $(SRCS:.c=.o)

OBJSLIB		= $(LIBS:.c=.o)

CFLAGS		= -I./include -Wall -Wextra -W -I ./lib

LDFLAGS		= -L ./ -lstringLib

$(NAME):	$(OBJS) $(OBJSLIB)
		ar rc $(LIBNAME) $(OBJSLIB)
		ranlib $(LIBNAME)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS) 

all:		$(NAME)

clean:
		$(RM) $(OBJS)
		$(RM) $(OBJSLIB)

fclean:		clean
		$(RM) $(NAME)
		$(RM) $(LIBNAME)

re:		fclean all

.PHONY:		all clean fclean re client
