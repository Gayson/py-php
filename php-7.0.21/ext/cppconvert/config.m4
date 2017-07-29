dnl $Id$
dnl config.m4 for extension cppconvert

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(cppconvert, for cppconvert support,
dnl Make sure that the comment is aligned:
dnl [  --with-cppconvert             Include cppconvert support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(cppconvert, whether to enable cppconvert support,
Make sure that the comment is aligned:
[  --enable-cppconvert           Enable cppconvert support])

if test "$PHP_CPPCONVERT" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-cppconvert -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/cppconvert.h"  # you most likely want to change this
  dnl if test -r $PHP_CPPCONVERT/$SEARCH_FOR; then # path given as parameter
  dnl   CPPCONVERT_DIR=$PHP_CPPCONVERT
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for cppconvert files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       CPPCONVERT_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$CPPCONVERT_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the cppconvert distribution])
  dnl fi

  dnl # --with-cppconvert -> add include path
  dnl PHP_ADD_INCLUDE($CPPCONVERT_DIR/include)

  dnl # --with-cppconvert -> check for lib and symbol presence
  dnl LIBNAME=cppconvert # you may want to change this
  dnl LIBSYMBOL=cppconvert # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $CPPCONVERT_DIR/$PHP_LIBDIR, CPPCONVERT_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_CPPCONVERTLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong cppconvert lib version or lib not found])
  dnl ],[
  dnl   -L$CPPCONVERT_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(CPPCONVERT_SHARED_LIBADD)
  
  PHP_ADD_INCLUDE([$CPPCONVERT_PATH/src])
  PHP_ADD_INCLUDE([$CPPCONVERT_PATH/src/product])
  PHP_ADD_INCLUDE([$CPPCONVERT_PATH/src/transport])

  PHP_ADD_BUILD_DIR([$CPPCONVERT_PATH/src])
  PHP_ADD_BUILD_DIR([$CPPCONVERT_PATH/src/product])
  PHP_ADD_BUILD_DIR([$CPPCONVERT_PATH/src/transport])

  PHP_NEW_EXTENSION(cppconvert, cppconvert.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
