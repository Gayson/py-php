dnl $Id$
dnl config.m4 for extension vehicle

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(vehicle, for vehicle support,
dnl Make sure that the comment is aligned:
dnl [  --with-vehicle             Include vehicle support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(vehicle, whether to enable vehicle support,
Make sure that the comment is aligned:
[  --enable-vehicle           Enable vehicle support])

if test "$PHP_VEHICLE" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-vehicle -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/vehicle.h"  # you most likely want to change this
  dnl if test -r $PHP_VEHICLE/$SEARCH_FOR; then # path given as parameter
  dnl   VEHICLE_DIR=$PHP_VEHICLE
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for vehicle files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       VEHICLE_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$VEHICLE_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the vehicle distribution])
  dnl fi

  dnl # --with-vehicle -> add include path
  dnl PHP_ADD_INCLUDE($VEHICLE_DIR/include)

  dnl # --with-vehicle -> check for lib and symbol presence
  dnl LIBNAME=vehicle # you may want to change this
  dnl LIBSYMBOL=vehicle # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $VEHICLE_DIR/$PHP_LIBDIR, VEHICLE_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_VEHICLELIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong vehicle lib version or lib not found])
  dnl ],[
  dnl   -L$VEHICLE_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(VEHICLE_SHARED_LIBADD)

  PHP_NEW_EXTENSION(vehicle, vehicle.c Zend_FooClass.c Zend_MyClass.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
