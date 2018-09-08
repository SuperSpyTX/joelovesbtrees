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
divert(-1)

# ------------- Real Configuration ------------------ #
# This is now defined in ./configure.  Please go use that. #

define(MK_NUM_OF_TARGETS, 1)
define(MK_FCLEAN_ON_RE, 0)
define(MK_DEBUG, 0)
define(MK_LIBFT_BUILD, 0)
define(MK_CORRECTION, 0)
define(MK_LITE, 0)

define(MK_RBTREE_NAME, rbtree)
define(MK_RBTREE_SUFFIX, )
define(MK_RBTREE_ISLIB, 0)
define(MK_RBTREE_INCLUDE_DIRS, includes)
define(MK_RBTREE_SRC_DIRS, src ifelse(MK_LIBFT_BUILD, 1, libft, ifelse(MK_LITE, 1, libft-min,  )))
define(MK_RBTREE_DEBUG, 0)
define(MK_RBTREE_LITE, 0)

# ------------ Automated Variables ------------------ #
define(MK_AUTO_ISLINUX, ifelse(esyscmd(uname -s | tr -d '\n'), `Darwin', 0, 1))
define(MK_AUTO_COMPILER,ifelse(MK_AUTO_ISLINUX, 1, clang, gcc))

define(MK_RBTREE_AUTO_SRC_DIR, patsubst(MK_RBTREE_SRC_DIRS,` ',`````,'''''))
pushdef(`MK_RBTREE_AUTO_SRC_DIR', ifelse(MK_RBTREE_SRC_DIRS,.,.,{MK_RBTREE_AUTO_SRC_DIR}))
define(MK_RBTREE_AUTO_SRC, esyscmd(bash -c 'find MK_RBTREE_AUTO_SRC_DIR -type f -name "*.c" | sed -e "s/$/ \\\/g"'))
define(MK_RBTREE_AUTO_SRC_DIR, patsubst(MK_RBTREE_SRC_DIRS,` ',```,'''))
define(MK_RBTREE_AUTO_INCLUDE_DIR, -I patsubst(MK_RBTREE_INCLUDE_DIRS,` ',``` -I '''))

divert(0)
# ------------- Automated Configuration ------------- #
LFLAGS = ifelse(MK_SUFFIX, ".dylib", -dynamiclib, ifelse(MK_SUFFIX, ".so", -shared,))
CFLAGS = ifelse(MK_DEBUG, 1,-g -DDEBUG=1) -fPIC -Wall -Werror -Wextra ifelse(MK_CORRECTION,1, -DCORRECTION=1)
RBTREE_NAME = defn(`MK_RBTREE_NAME')MK_RBTREE_SUFFIX
CFLAGS += MK_RBTREE_AUTO_INCLUDE_DIR
RBTREE_SRC = MK_RBTREE_AUTO_SRC
RBTREE_OBJ = $(subst .c,.o, $(RBTREE_SRC))

# ------------------- Targets ----------------------- #

all: $(RBTREE_NAME)

%.o: %.c
	MK_AUTO_COMPILER $(CFLAGS) -c $? -o $@

$(RBTREE_NAME): $(RBTREE_OBJ)
	MK_AUTO_COMPILER $(LFLAGS) $(RBTREE_OBJ) -o $(RBTREE_NAME)
	@#/bin/rm -f $(RBTREE_NAME)
	@#ar rcs $(RBTREE_NAME) $(RBTREE_OBJ))dnl


re: ifelse(MK_FCLEAN_ON_RE, 1,f)clean all dnl


clean:
	/bin/rm -f $(RBTREE_OBJ)

fclean: clean
	/bin/rm -f $(RBTREE_NAME)
