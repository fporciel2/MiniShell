# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fporciel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 11:38:22 by fporciel          #+#    #+#              #
#    Updated: 2024/03/13 12:27:55 by fporciel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# MiniShell is a simple shell for Debian GNU/Linux.
# Copyright (C) 2024  Federico Porciello
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
# For more information on how to contact me by electronic and paper mail
# please see:
# https://github.com/fporciel2/MiniShell
#

.PHONY: all clean fclean re mem memcheck helgrind thread remem rethread \
	autogit destroy
.DEFAULT_GOAL: all
NAME := minishell
FTURL := https://github.com/fporciel2/1_libft.git
DIR := $(shell pwd)
DFT := $(DIR)/$(shell basename -s .git $(FTURL))
HEADER := $(wildcard $(NAME)*.h) $(wildcard $(DFT)/*.h)
MAIN := $(NAME).c
SRCS := $(filter-out $(NAME), $(wildcard $(NAME)*.c))
OBJS := $(patsubst %.c, %.o, $(SRCS))
LIBFT := $(DFT)/$(wildcard *.a)
LIBMS := $(DIR)/$(addprefix lib, $(NAME)).a
CC := gcc
CSTD := -std=c17 -pedantic-errors
CFLAGS := -Wall -Wextra -Werror
AFLAGS := $(CFLAGS) -fsanitize=address -fno-omit-frame-pointer -g
TFLAGS := $(CFLAGS) -fsanitize=thread -g
COPT := -O3 -march=native -g
INCLUDE := $(addprefix -I, $(DIR) $(DFT))
LDINCLUDE := $(addprefix -L, $(DFT))
LDFLAGS := -lc -lft -lreadline -lncurses -ltinfo
LAFLAGS := $(LDFLAGS) -lasan
LTFLAGS := $(LDFLAGS) -ltsan

all: $(NAME)

$(NAME): $(MAIN) $(LIBFT) $(LIBMS)
	@$(CC) $(CSTD) $(CFLAGS) $(COPT) $(INCLUDE) $(HEADER) $(MAIN) $(LIBMS) \
		$(LIBFT) $(LDINCLUDE) $(LDFLAGS) -o $@

$(LIBFT): $(DFT)
	@if [ ! -e $@ ]; then $(MAKE) -C $(DFT) bonus; fi

$(DFT):
	@if [ ! -e $@ ]; then git clone $(FTURL); fi

$(LIBMS): $(OBJS)
	@ar rcs $@ $(OBJS) $(HEADER)

$(OBJS): $(SRCS) $(HEADER)
	@$(CC) $(CSTD) $(CFLAGS) $(COPT) $(INCLUDE) $(HEADER) $(SRCS) -c

mem: $(MAIN) $(SRCS) $(HEADER) $(LIBFT)
	@$(CC) $(CSTD) $(CFLAGS) $(AFLAGS) $(INCLUDE) $(HEADER) $(MAIN) $(SRCS) \
		$(LIBFT) $(LAFLAGS) -o $(NAME)

thread: $(MAIN) $(SRCS) $(HEADER) $(LIBFT)
	@$(CC) $(CSTD) $(CFLAGS) $(TFLAGS) $(INCLUDE) $(HEADER) $(MAIN) $(SRCS) \
		$(LIBFT) $(LTFLAGS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@rm -f $(LIBMS)
	@rm -f $(NAME).h.gch
	@if [ -e $(DFT) ]; then $(MAKE) -C $(DFT) clean; fi

fclean: clean
	@rm -f $(NAME)

re: fclean all

remem: fclean mem

rethread: fclean thread

destroy: fclean
	@rm -rfd $(DFT)

memcheck: re
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		--verbose ./$(NAME)

helgrind: re
	@valgrind --tool=helgrind ./$(NAME)

autogit: destroy
	@git status
	@echo "\nIs there anything to remove? [y/n]"
	@read answer; if [ $$answer = "y" ]; \
		then git rm $$(git ls-files --deleted); fi
	@git status
	@git add *
	@git status
	@git commit -m "$(shell date)"
	@git status
	@git push

