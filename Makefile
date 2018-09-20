#* ************************************************************************** */
#*                                                                            */
#*                                                        :::      ::::::::   */
#*   Makefile                                           :+:      :+:    :+:   */
#*                                                    +:+ +:+         +:+     */
#*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
#*                                                +#+#+#+#+#+   +#+           */
#*   Created: 2017/04/18 03:42:42 by jkrause           #+#    #+#             */
#*   Updated: 2018/06/05 18:51:45 by jkrause            ###   ########.fr     */
#*                                                                            */
#* ************************************************************************** */
# ----------------- Version 1.7 --------------------- #

# ------------- Automated Configuration ------------- #
LFLAGS = 
CFLAGS = -g -DDEBUG=1  -fPIC -Wall -Werror -Wextra 
RBTREE_NAME = rbtree
CFLAGS += -I includes
RBTREE_SRC = src/treeops.c \
src/assert.c \
src/algorithm.c \
src/rb_remove.c \
src/main.c \
src/rb_insert.c \
libft-min/ft_strcmp.c \
libft-min/ft_memcpy.c \
libft-min/ft_ltostr_base.c \
libft-min/ft_printf.c \
libft-min/ft_isdigit.c \
libft-min/parse_module.c \
libft-min/ft_bzero.c \
libft-min/module_manager.c \
libft-min/expand_write.c \
libft-min/formati_module.c \
libft-min/expand_pad.c \
libft-min/ft_putstr_fd.c \
libft-min/ft_lstdelone.c \
libft-min/ft_putnbr_fd.c \
libft-min/directbuffer_module.c \
libft-min/ft_putendl_fd.c \
libft-min/ft_memdel.c \
libft-min/string_module.c \
libft-min/bufferwrite_module.c \
libft-min/ft_strlen.c \
libft-min/ft_strsub.c \
libft-min/ft_strnew.c \
libft-min/ft_memalloc.c \
libft-min/asterisks_module.c \
libft-min/ft_strnchr.c \
libft-min/integer_module.c \
libft-min/ft_strncmp.c \
libft-min/ft_putchar_fd.c \
libft-min/get_next_line.c \
libft-min/ft_memset.c \
libft-min/ft_isalpha.c \
libft-min/ft_itoa_base.c \
libft-min/ft_strcat.c \
libft-min/bufferstring_module.c \
libft-min/ft_atoi.c \
libft-min/ft_strchr.c \
libft-min/memorywrite_module.c \

RBTREE_OBJ = $(subst .c,.o, $(RBTREE_SRC))

# ------------------- Targets ----------------------- #

all: $(RBTREE_NAME)

%.o: %.c
	gcc $(CFLAGS) -c $? -o $@

$(RBTREE_NAME): $(RBTREE_OBJ)
	gcc $(LFLAGS) $(RBTREE_OBJ) -o $(RBTREE_NAME)
	@#/bin/rm -f $(RBTREE_NAME)
	@#ar rcs $(RBTREE_NAME) $(RBTREE_OBJ))dnl


re: clean all 

clean:
	/bin/rm -f $(RBTREE_OBJ)

fclean: clean
	/bin/rm -f $(RBTREE_NAME)
