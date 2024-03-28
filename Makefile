# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fporciel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 11:38:22 by fporciel          #+#    #+#              #
#    Updated: 2024/03/28 11:40:35 by fporciel         ###   ########.fr        #
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
DIR := $(shell pwd)
HEADER := $(wildcard $(NAME)*.h)
MAIN := $(NAME).c
SRCS := $(filter-out $(MAIN), $(wildcard $(NAME)*.c))
OBJS := $(patsubst %.c, %.o, $(SRCS))
LIBMS := $(DIR)/$(addprefix lib, $(NAME)).a
CC := gcc
CSTD := -std=c17 -pedantic-errors
CFLAGS := -Wall -Wextra -Werror
AFLAGS := $(CFLAGS) -fsanitize=address -fno-omit-frame-pointer -g
TFLAGS := $(CFLAGS) -fsanitize=thread -g
COPT := -O3 -march=native -g
INCLUDE := $(addprefix -I, $(DIR))
LDINCLUDE := $(addprefix -L, $(DIR))
LDFLAGS := -lc -lreadline -lncurses -ltinfo -lminishell
LAFLAGS := $(LDFLAGS) -lasan
LTFLAGS := $(LDFLAGS) -ltsan

all: $(NAME)

$(NAME): $(MAIN) $(LIBMS)
	@$(CC) $(CSTD) $(CFLAGS) $(COPT) $(INCLUDE) $(HEADER) $(MAIN) $(LIBMS) \
		$(LDINCLUDE) $(LDFLAGS) -o $@

$(LIBMS): $(OBJS)
	@ar rcs $@ $(OBJS) $(HEADER)

$(OBJS): $(SRCS) $(HEADER)
	@$(CC) $(CSTD) $(CFLAGS) $(COPT) $(INCLUDE) $(HEADER) $(SRCS) -c

mem: $(MAIN) $(SRCS) $(HEADER) $(LIBFT)
	@$(CC) $(CSTD) $(CFLAGS) $(AFLAGS) $(INCLUDE) $(HEADER) $(MAIN) $(SRCS) \
		$(LIBFT) $(filter-out -l$(NAME), $(LAFLAGS)) -o $(NAME)

thread: $(MAIN) $(SRCS) $(HEADER) $(LIBFT)
	@$(CC) $(CSTD) $(CFLAGS) $(TFLAGS) $(INCLUDE) $(HEADER) $(MAIN) $(SRCS) \
		$(LIBFT) $(filter-out -l$(NAME), $(LTFLAGS)) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@rm -f $(LIBMS)
	@rm -f $(NAME).h.gch

fclean: clean
	@rm -f $(NAME)

re: fclean all

remem: fclean mem

rethread: fclean thread

memcheck: re
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		--verbose ./$(NAME)

helgrind: re
	@valgrind --tool=helgrind ./$(NAME)

autogit: fclean
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

