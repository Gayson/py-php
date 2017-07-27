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

PHP_ARG_ENABLE(ProtocolExtension, whether to enable ProtocolExtension support,
Make sure that the comment is aligned:
[  --enable-ProtocolExtension           Enable ProtocolExtension support])

if test "$PHP_PROTOCOLEXTENSION" != "no"; then
  PHP_NEW_EXTENSION(ProtocolExtension, ProtocolExtension.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
