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

#ifndef PHP_KING_UUID_H
#define PHP_KING_UUID_H

extern zend_module_entry king_uuid_module_entry;
#define phpext_king_uuid_ptr &king_uuid_module_entry

#define PHP_KING_UUID_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_KING_UUID_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_KING_UUID_API __attribute__ ((visibility("default")))
#else
#	define PHP_KING_UUID_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(king_uuid);
PHP_MSHUTDOWN_FUNCTION(king_uuid);
PHP_RINIT_FUNCTION(king_uuid);
PHP_RSHUTDOWN_FUNCTION(king_uuid);
PHP_MINFO_FUNCTION(king_uuid);

PHP_FUNCTION(confirm_king_uuid_compiled);	/* For testing, remove later. */
PHP_FUNCTION(ku_get_uuid);
/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(king_uuid)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(king_uuid)
*/


/* In every utility function you add that needs to use variables 
   in php_king_uuid_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as KING_UUID_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define KING_UUID_G(v) TSRMG(king_uuid_globals_id, zend_king_uuid_globals *, v)
#else
#define KING_UUID_G(v) (king_uuid_globals.v)
#endif

#endif	/* PHP_KING_UUID_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
