dnl $Id$
dnl config.m4 for extension king_uuid

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(king_uuid, for king_uuid support,
dnl Make sure that the comment is aligned:
dnl [  --with-king_uuid             Include king_uuid support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(king_uuid, whether to enable king_uuid support,
dnl Make sure that the comment is aligned:
[  --enable-king_uuid           Enable king_uuid support])

if test "$PHP_KING_UUID" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-king_uuid -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/king_uuid.h"  # you most likely want to change this
  dnl if test -r $PHP_KING_UUID/$SEARCH_FOR; then # path given as parameter
  dnl   KING_UUID_DIR=$PHP_KING_UUID
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for king_uuid files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       KING_UUID_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$KING_UUID_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the king_uuid distribution])
  dnl fi

  dnl # --with-king_uuid -> add include path
  dnl PHP_ADD_INCLUDE($KING_UUID_DIR/include)

  dnl # --with-king_uuid -> check for lib and symbol presence
  dnl LIBNAME=king_uuid # you may want to change this
  dnl LIBSYMBOL=king_uuid # you most likely want to change this

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $KING_UUID_DIR/$PHP_LIBDIR, KING_UUID_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_KING_UUIDLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong king_uuid lib version or lib not found])
  dnl ],[
  dnl   -L$KING_UUID_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(KING_UUID_SHARED_LIBADD)

  PHP_NEW_EXTENSION(king_uuid, king_uuid.c, $ext_shared)
fi
