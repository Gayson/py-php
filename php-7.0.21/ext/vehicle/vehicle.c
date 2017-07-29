/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "zend_compile.h"
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_vehicle.h"

static int le_vehicle;


zend_class_entry *foo_ce;
zend_class_entry *foo_child_ce;

PHP_METHOD(Foo, hi)
{
	php_printf("hello from foo\n");
}

PHP_METHOD(Foo, bye)
{
	php_printf("bye from foo\n");
}


ZEND_BEGIN_ARG_INFO(arginfo_arg_val, 0)
ZEND_ARG_PASS_INFO(1)
ZEND_END_ARG_INFO()

PHP_METHOD(Foo, getVal)
{
	zval *pval;
	double d_val;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zd", &pval, &d_val) == FAILURE)
	{
		return;
	}
	/*php_printf("get data\n");*/
	php_printf("type: %d\n", Z_TYPE_P(pval));

	/*val->value.dval = 123;*/

	if (Z_ISREF_P(pval))
	{
		zval *val = Z_REFVAL_P(pval);
		php_printf("inner val type: %d\n", Z_TYPE_P(val));
		switch (Z_TYPE_P(val))
		{
		case IS_DOUBLE:
		{
			php_printf("get double\n");
			double double_val = zval_get_double(val);
			val->value.dval = double_val * 2;
			break;
		}
		case IS_LONG:
		{
			php_printf("get long\n");
			long long_val = zval_get_long(val);
			val->value.lval = long_val * 2;

			break;
		}
		case IS_STRING:
		{
			php_printf("get string\n");
			zend_string *str = zval_get_string(val);
			size_t len = sizeof("foo_str_val");
			memcpy(ZSTR_VAL(str), "foo_str_val", len);
			ZSTR_VAL(str)[len] = '\0'; /*str->val = "foo_str_val";*/ break;

		}
		case IS_NULL:
		{
			php_printf("get_null\n");
			zend_string *str = zend_string_init("nothing", sizeof("nothing") - 1, false);
			php_printf("%s\n", str->val);

			val->value.str = str;
			val->u1.v.type = IS_STRING;
			/*val->value.ref->val;*/
			break;
		}
		default:
		{
			php_printf("get other\n");
			break;
		}
		}
	}
}

PHP_METHOD(FooChild, child)
{
	RETURN_STRING("this is foo child");
}


PHP_METHOD(FooChild, __construct)
{
}


static const zend_function_entry foo_funcs[] =
{
	PHP_ME(Foo, hi, NULL, 0)
	PHP_ME(Foo, bye, NULL, 0)
	PHP_ME(Foo, getVal, arginfo_arg_val, 0)
	/*PHP_ME(Foo, getVal, NULL, 0)*/
	PHP_FE_END
};

static const zend_function_entry foo_child_funcs[] =
{
	PHP_ME(FooChild, child, NULL, 0)
	PHP_FE_END
};


PHP_FUNCTION(say)
{
	zend_string *strg;
	strg = strpprintf(0, "helloworld");
	RETURN_STR(strg);
}

PHP_FUNCTION(my_echo)
{
	char *s;
	size_t len;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &s, &len) == FAILURE)
	{
		return;
	}
	RETURN_STRING(s);
}

PHP_FUNCTION(confirm_vehicle_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	int val;
	zend_string *strg;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "sl", &arg, &arg_len, &val) == FAILURE)
	{
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP. vesion %d", "vehicle", arg, val);

	RETURN_STR(strg);
}


PHP_FUNCTION(other_array_concat)
{
	zval *arr, *prefix, *entry, *prefix_entry, value;
	zend_string *string_key, *result;
	zend_ulong num_key;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "aa", &arr, &prefix) == FAILURE)
	{
		return;
	}

	array_init(return_value);

	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(arr), num_key, string_key, entry)
	{
		if (string_key && zend_hash_exists(Z_ARRVAL_P(prefix), string_key))
		{
			prefix_entry = zend_hash_find(Z_ARRVAL_P(prefix), string_key);
			if (Z_TYPE_P(entry) == IS_STRING && prefix_entry != NULL && Z_TYPE_P(prefix_entry) == IS_STRING)
			{
				result = strpprintf(0, "%s%s", Z_STRVAL_P(prefix_entry), Z_STRVAL_P(entry));
				ZVAL_STR(&value, result);
				add_assoc_zval(return_value, string_key->val, &value);
			}
		}
		else if (string_key == NULL && zend_hash_index_exists(Z_ARRVAL_P(prefix), num_key))
		{
			prefix_entry = zend_hash_index_find(Z_ARRVAL_P(prefix), num_key);
			if (Z_TYPE_P(entry) == IS_STRING && prefix_entry != NULL && Z_TYPE_P(prefix_entry) == IS_STRING)
			{
				result = strpprintf(0, "%s%s", Z_STRVAL_P(prefix_entry), Z_STRVAL_P(entry));
				ZVAL_STR(&value, result);
				add_index_zval(return_value, num_key, &value);
			}
		}
		else if (string_key)
		{
			php_printf("3\n");
			php_printf("%s\n", string_key);
			add_assoc_zval(return_value, string_key->val, entry);
			zval_add_ref(entry);
		}
		else
		{
			php_printf("4\n");
			php_printf("%s\n", string_key);
			add_index_zval(return_value, num_key, entry);
			zval_add_ref(entry);
		}
	}
	ZEND_HASH_FOREACH_END();

}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_vehicle_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_vehicle_init_globals(zend_vehicle_globals *vehicle_globals)
{
    vehicle_globals->global_value = 0;
    vehicle_globals->global_string = NULL;
}
*/
/* }}} */

/*PHP_INI_BEGIN()*/
/*STD_PHP_INI_BOOLEAN("vehicle.use_namespace", "1", PHP_INI_ALL, OnUpdateBool, use_namespace, zend_vehicle_globals, vehicle_globals)*/
/*PHP_INI_END()*/

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(vehicle)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/

	/* my init */
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "Vehicle\\Foo", foo_funcs);

	foo_ce = zend_register_internal_class_ex(&ce, NULL);

	zend_declare_property_long(foo_ce, "long_val", sizeof("long_val") - 1, 0, ZEND_ACC_PUBLIC);

	zend_declare_property_string(foo_ce, "bar", sizeof("bar") - 1, "bar", ZEND_ACC_PUBLIC);

	foo_ce->ce_flags = ZEND_ACC_IMPLICIT_PUBLIC;

	/* FooChild */
	zend_class_entry cec;

	INIT_CLASS_ENTRY(cec, "Vehicle\\FooChild", foo_child_funcs);

	foo_child_ce = zend_register_internal_class_ex(&cec, foo_ce);

	zend_declare_property_long(foo_child_ce, "long_child_val", sizeof("long_child_val") - 1, 0, ZEND_ACC_PUBLIC);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(vehicle)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(vehicle)
{
#if defined(COMPILE_DL_VEHICLE) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(vehicle)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(vehicle)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "vehicle support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ vehicle_functions[]
 *
 * Every user visible function must have an entry in vehicle_functions[].
 */
const zend_function_entry vehicle_functions[] =
{
	PHP_FE(say, NULL)
	PHP_FE(my_echo, NULL)
	PHP_FE(other_array_concat, NULL)
	PHP_FE(confirm_vehicle_compiled,    NULL)       /* For testing, remove later. */
	PHP_FE_END  /* Must be the last line in vehicle_functions[] */
};
/* }}} */

/* {{{ vehicle_module_entry
 */
zend_module_entry vehicle_module_entry =
{
	STANDARD_MODULE_HEADER,
	"vehicle",
	vehicle_functions,
	PHP_MINIT(vehicle),
	PHP_MSHUTDOWN(vehicle),
	PHP_RINIT(vehicle),     /* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(vehicle), /* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(vehicle),
	PHP_VEHICLE_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_VEHICLE
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(vehicle)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
