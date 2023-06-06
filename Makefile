# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/16 18:53:13 by nimai             #+#    #+#              #
#    Updated: 2023/06/06 18:06:59 by nimai            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#

LIBS		:=  
LIBS_TARGET	:= 
INCS		:= inc
SRC_DIR		:= src
SRCS		:= \
				main.c \
				errors.c

SRCS		:= $(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR	:= .build
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d)

CC			:= cc
CFLAGS		:= -g3 -Wall -Wextra -Werror
CPPFLAGS	:= $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS		:= $(addprefix -L,$(dir $(LIBS_TARGET))) 
LDLIBS		:= $(addprefix -l,$(LIBS))

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#

RM			:= rm -f
RF			:= rm -rf
DIR_DUP		= mkdir -p $(@D)

#------------------------------------------------#
#   ASCII ART                                    #
#------------------------------------------------#
CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m

define	ART
$(YELLOW)
       /^-^\         /^-----^\\
      / o o \        V  o o  V
     /   ▼   \        |  ▽  |
     V \ ∧ / V         \ Q / 
       / - \\           / - \\
      /    | ========= |    \\
(    /     |   philo   |     \\     )
 ===/___) || ========= || (___\\====$(CLR_RMV)
endef
export	ART

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	$(info CREATED $(NAME))
	@echo "$$ART"

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)
	$(RF) $(BUILD_DIR)

re:
	$(MAKE) fclean
	$(MAKE) all

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: all clean fclean re
.SILENT: