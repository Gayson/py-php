#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_vehicle.h"

zend_class_entry *fooclass_ce;
zend_object_handlers foo_ce_handlers;

/*static zend_function_entry fooclass_method[] =*/
/*{*/
/*{ NULL, NULL, NULL }*/
/*};*/

PHP_MINIT_FUNCTION(vehicle)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "FooClass", NULL);
	fooclass_ce = zend_register_internal_class(&ce);

	memcpy(&foo_ce_handlers, zend_get_std_object_handlers(), sizeof(foo_ce_handlers));

	return SUCCESS;
}
