
#ifndef PHP_PHP_TINYCDB_H
#define PHP_PHP_TINYCDB_H

#include "tinycdb/cdb.h"

extern zend_module_entry php_tinycdb_module_entry;
#define phpext_php_tinycdb_ptr &php_tinycdb_module_entry

#define PHP_PHP_TINYCDB_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_PHP_TINYCDB_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_PHP_TINYCDB_API __attribute__ ((visibility("default")))
#else
#	define PHP_PHP_TINYCDB_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define CDBNAME_MAX_LEN  	(1 << 8)

ZEND_BEGIN_MODULE_GLOBALS(php_tinycdb)
	char cdb_name[CDBNAME_MAX_LEN];
	int fd;
	struct cdb data;
ZEND_END_MODULE_GLOBALS(php_tinycdb)

/* In every utility function you add that needs to use variables 
   in php_php_tinycdb_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as PHP_TINYCDB_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define PHP_TINYCDB_G(v) TSRMG(php_tinycdb_globals_id, zend_php_tinycdb_globals *, v)
#else
#define PHP_TINYCDB_G(v) (php_tinycdb_globals.v)
#endif

#endif	/* PHP_PHP_TINYCDB_H */

