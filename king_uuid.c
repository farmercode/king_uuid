/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
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

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_king_uuid.h"
#include <zend_API.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <zend_hash.h>

/* If you declare any globals in php_king_uuid.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(king_uuid)
*/

/* True global resources - no need for thread safety here */
static int le_king_uuid;

static HashTable inner_time_count;

/* {{{ king_uuid_functions[]
 *
 * Every user visible function must have an entry in king_uuid_functions[].
 */
const zend_function_entry king_uuid_functions[] = {
	PHP_FE(confirm_king_uuid_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(ku_get_uuid, NULL)
	PHP_FE_END	/* Must be the last line in king_uuid_functions[] */
};
/* }}} */

/* {{{ king_uuid_module_entry
 */
zend_module_entry king_uuid_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"king_uuid",
	king_uuid_functions,
	PHP_MINIT(king_uuid),
	PHP_MSHUTDOWN(king_uuid),
	PHP_RINIT(king_uuid),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(king_uuid),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(king_uuid),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_KING_UUID_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_KING_UUID
ZEND_GET_MODULE(king_uuid)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("king_uuid.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_king_uuid_globals, king_uuid_globals)
    STD_PHP_INI_ENTRY("king_uuid.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_king_uuid_globals, king_uuid_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_king_uuid_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_king_uuid_init_globals(zend_king_uuid_globals *king_uuid_globals)
{
	king_uuid_globals->global_value = 0;
	king_uuid_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(king_uuid)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	zend_hash_init(&inner_time_count,1024,NULL,ZVAL_PTR_DTOR,0);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(king_uuid)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	//释放内存
	zend_hash_destroy(&inner_time_count);
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(king_uuid)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(king_uuid)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(king_uuid)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "king_uuid support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_king_uuid_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_king_uuid_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "king_uuid", arg);
	RETURN_STRINGL(strg, len, 0);
}

/**
 * 获得一个当前服务器的唯一id
 */
PHP_FUNCTION(ku_get_uuid)
{
	int pid =0;
	int count = 0;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l",&pid) == FAILURE){
		return;
	}

	if(pid <= 0 ){
		pid = (int)getpid();
	}
	int64_t ku_uuid;
	int64_t ku_tmp_time;
	struct timeval tv;
	//获得当前时间
	gettimeofday(&tv,NULL);
	ku_tmp_time = tv.tv_sec*1000+tv.tv_usec/1000;
#ifdef  USE_KING_UUID_DEBUG
	php_printf("input args:%d\n",pid);
	php_printf("micro time:%lld\n",ku_tmp_time);
#endif
	count = get_current_time_count(ku_tmp_time);
	ku_uuid = (int64_t)count;
	ku_uuid |= ku_tmp_time << 13;
	ku_uuid |= pid << 54;
#ifdef USE_KING_UUID_DEBUG
	php_printf("uuid:%lld\n",ku_uuid);
#endif

	RETURN_LONG(ku_uuid);
}

int get_current_time_count(int64_t current_time)
{
	int *current_num;
	zval key;
	ZVAL_LONG(&key,current_time);
	//将数字变量转化为字符串
	convert_to_string(&key);
	char *key_string = key.value.str.val;
	uint key_len = key.value.str.len;
	ulong hash_value;
	hash_value = zend_get_hash_value(key.value.str.val,key.value.str.len);
	if(zend_hash_quick_exists(&inner_time_count,key.value.str.val,key.value.str.len,hash_value)){
		if(zend_hash_quick_find(&inner_time_count,key_string,key_len,hash_value,(void **)&current_num) == FAILURE){
			return 0;
		}
		*current_num++;
		zend_hash_quick_update(&inner_time_count,key_string,key_len,hash_value,(void *)current_num,sizeof(int),NULL);
	}else{
		*current_num = 1;
		zend_hash_quick_add(&inner_time_count,key_string,key_len,hash_value,(void *)current_num,sizeof(int),NULL);
	}
	return *current_num;
}

/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
