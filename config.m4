dnl $Id$
dnl config.m4 for extension php_tinycdb

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(php_tinycdb, for php_tinycdb support,
dnl Make sure that the comment is aligned:
dnl [  --with-php_tinycdb             Include php_tinycdb support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(php_tinycdb, whether to enable php_tinycdb support,
Make sure that the comment is aligned:
[  --enable-php_tinycdb           Enable php_tinycdb support])

PHP_TINYCDB_FILES="php_tinycdb.c tinycdb/cdb_init.c tinycdb/cdb_find.c tinycdb/cdb_findnext.c \
  tinycdb/cdb_seq.c tinycdb/cdb_seek.c \
  tinycdb/cdb_unpack.c \
  tinycdb/cdb_make_add.c tinycdb/cdb_make_put.c tinycdb/cdb_make.c tinycdb/cdb_hash.c"

if test "$PHP_PHP_TINYCDB" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-php_tinycdb -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/php_tinycdb.h"  # you most likely want to change this
  dnl if test -r $PHP_PHP_TINYCDB/$SEARCH_FOR; then # path given as parameter
  dnl   PHP_TINYCDB_DIR=$PHP_PHP_TINYCDB
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for php_tinycdb files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PHP_TINYCDB_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PHP_TINYCDB_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the php_tinycdb distribution])
  dnl fi

  dnl # --with-php_tinycdb -> add include path
  dnl PHP_ADD_INCLUDE($PHP_TINYCDB_DIR/include)

  dnl # --with-php_tinycdb -> check for lib and symbol presence
  dnl LIBNAME=php_tinycdb # you may want to change this
  dnl LIBSYMBOL=php_tinycdb # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PHP_TINYCDB_DIR/$PHP_LIBDIR, PHP_TINYCDB_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PHP_TINYCDBLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong php_tinycdb lib version or lib not found])
  dnl ],[
  dnl   -L$PHP_TINYCDB_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  PHP_SUBST(PHP_TINYCDB_SHARED_LIBADD)

  PHP_NEW_EXTENSION(php_tinycdb, ${PHP_TINYCDB_FILES}, $ext_shared)
  PHP_ADD_BUILD_DIR([$ext_builddir/tinycdb])
fi
