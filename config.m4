dnl $Id$
dnl config.m4 for extension tinycdb

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(tinycdb, for tinycdb support,
dnl Make sure that the comment is aligned:
dnl [  --with-tinycdb             Include tinycdb support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(tinycdb, whether to enable tinycdb support,
Make sure that the comment is aligned:
[  --enable-tinycdb           Enable tinycdb support])

TINYCDB_FILES="tinycdb.c vendor/tinycdb/cdb_init.c vendor/tinycdb/cdb_find.c vendor/tinycdb/cdb_findnext.c \
  vendor/tinycdb/cdb_seq.c vendor/tinycdb/cdb_seek.c \
  vendor/tinycdb/cdb_unpack.c \
  vendor/tinycdb/cdb_make_add.c vendor/tinycdb/cdb_make_put.c vendor/tinycdb/cdb_make.c vendor/tinycdb/cdb_hash.c"

if test "$PHP_TINYCDB" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-tinycdb -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/tinycdb.h"  # you most likely want to change this
  dnl if test -r $PHP_TINYCDB/$SEARCH_FOR; then # path given as parameter
  dnl   TINYCDB_DIR=$PHP_TINYCDB
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for tinycdb files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       TINYCDB_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$TINYCDB_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the tinycdb distribution])
  dnl fi

  dnl # --with-tinycdb -> add include path
  dnl PHP_ADD_INCLUDE($TINYCDB_DIR/include)

  dnl # --with-tinycdb -> check for lib and symbol presence
  dnl LIBNAME=tinycdb # you may want to change this
  dnl LIBSYMBOL=tinycdb # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $TINYCDB_DIR/$PHP_LIBDIR, TINYCDB_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_TINYCDBLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong tinycdb lib version or lib not found])
  dnl ],[
  dnl   -L$TINYCDB_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(TINYCDB_SHARED_LIBADD)

  PHP_SUBST(TINYCDB_SHARED_LIBADD)

  PHP_NEW_EXTENSION(tinycdb, ${TINYCDB_FILES}, $ext_shared)
  PHP_ADD_BUILD_DIR([$ext_builddir/vendor/tinycdb])

fi
