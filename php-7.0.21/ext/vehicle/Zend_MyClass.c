#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_vehicle.h"
// 定义类myclass

zend_class_entry *myclass_ce;

// 定义public方法
ZEND_METHOD(myclass, public_method)
{
	php_printf("我是public类型的方法\n");
}

// 定义构造函数
ZEND_METHOD(myclass, __construct)
{
	php_printf("我是__construct方法\n");
}

// 定义static方法
ZEND_METHOD(myclass, static_method)
{
	php_printf("我是static_method方法\n");
}

PHP_METHOD(myclass, public_method);
PHP_METHOD(myclass, __construct);
PHP_METHOD(myclass, static_method);

static zend_function_entry myclass_method[] =
{
	ZEND_ME(myclass, public_method, NULL, ZEND_ACC_PUBLIC)
	ZEND_ME(myclass, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	ZEND_ME(myclass, static_method, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	{
		NULL, NULL, NULL
	}
};

ZEND_MINIT_FUNCTION(academy_sample_minit)
{
	academy_sample_descriptor = zend_register_list_destructors_ex(php_sample_descriptor_dtor, NULL, PHP_SAMPLE_DESCRIPTOR_RES_NAME, module_number);
	academy_sample_descriptor_persist = zend_register_list_destructors_ex(NULL, php_sample_descriptor_dtor_persistent, PHP_SAMPLE_DESCRIPTOR_RES_NAME, module_number);

	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "myclass", myclass_method);
	myclass_ce = zend_register_internal_class(&ce TSRMLS_CC);

	// 定义类属性
	zend_declare_property_null(myclass_ce, "public_var", strlen("public_var"), ZEND_ACC_PUBLIC TSRMLS_CC);
	// 定义类常量
	zend_declare_class_constant_string(myclass_ce, "CONSTANT_VAR", strlen("CONSTANT_VAR"), "LaravelAcademy" TSRMLS_CC);

	return SUCCESS;
}

#endif
