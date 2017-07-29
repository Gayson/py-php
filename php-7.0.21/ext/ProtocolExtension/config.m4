dnl $Id$
dnl config.m4 for extension ProtocolExtension

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(ProtocolExtension, for ProtocolExtension support,
dnl Make sure that the comment is aligned:
dnl [  --with-ProtocolExtension             Include ProtocolExtension support])

dnl Otherwise use enable:
AC_MSG_CHECKING([for ProtocolExtension-config])
  PROTOCOLEXTENSION_CONFIG="ProtocolExtension-config"
  if test "$PHP_PROTOCOLEXTENSION" != "yes"; then
    PROTOCOLEXTENSION_PATH=$PHP_PROTOCOLEXTENSION
  else
    PROTOCOLEXTENSION_PATH=`$php_shtool path $PROTOCOLEXTENSION_CONFIG`
  fi
PHP_ARG_ENABLE(ProtocolExtension, whether to enable ProtocolExtension support,
Make sure that the comment is aligned:
[  --enable-ProtocolExtension           Enable ProtocolExtension support])

PHP_ADD_INCLUDE([$PHP_PROTOCOLEXTENSION/src])
PHP_ADD_INCLUDE([$PHP_PROTOCOLEXTENSION/src/protocol])
PHP_ADD_INCLUDE([$PHP_PROTOCOLEXTENSION/src/transport])

PHP_ADD_BUILD_DIR([$ext_builddir/src/])
PHP_ADD_BUILD_DIR([$ext_builddir/transport/])
PHP_ADD_BUILD_DIR([$ext_builddir/protocol/])
if test "$PHP_PROTOCOLEXTENSION" != "no"; then
  PHP_NEW_EXTENSION(ProtocolExtension, ProtocolExtension.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
