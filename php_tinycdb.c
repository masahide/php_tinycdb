
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <fcntl.h>

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_php_tinycdb.h"
#include "tinycdb/cdb.h"

ZEND_DECLARE_MODULE_GLOBALS(php_tinycdb)

#define CDBNAME_MAX_LEN  	(1 << 8)

typedef struct { 
	char cdbname[CDBNAME_MAX_LEN];
	struct cdb data;
} tinycdb_storage;

/* True global resources - no need for thread safety here */
static int le_php_tinycdb;
static tinycdb_storage shm_storage;

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
    //STD_PHP_INI_ENTRY("php_tinycdb.global_value",        "42", PHP_INI_ALL, OnUpdateLong,   global_value, zend_php_tinycdb_globals, php_tinycdb_globals)
    //STD_PHP_INI_ENTRY("php_tinycdb.global_string",   "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_php_tinycdb_globals, php_tinycdb_globals)
    STD_PHP_INI_ENTRY("php_tinycdb.init_dbname", "sample.cdb", PHP_INI_ALL, OnUpdateString, init_dbname, zend_php_tinycdb_globals, php_tinycdb_globals)
PHP_INI_END()
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */


/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string cdb_get(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(cdb_get)
{
	char *key = NULL;
	int key_len, len;
	unsigned vlen, vpos;
	char *val;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key, &key_len) == FAILURE) {
		return;
	}
	if (cdb_find(&shm_storage.data, key, key_len) > 0) { /* if search successeful */
		vpos = cdb_datapos(&shm_storage.data); /* position of data in a file */
		vlen = cdb_datalen(&shm_storage.data); /* length of data */
		val = emalloc(vlen+1); /* allocate memory */
		val[vlen]=0;
		cdb_read(&shm_storage.data, val, vlen, vpos); /* read the value into buffer */
		ZVAL_STRINGL(return_value, val, vlen,0);
	}
}
/* }}} */


/* {{{ php_php_tinycdb_init_globals
 */
static void php_php_tinycdb_init_globals(zend_php_tinycdb_globals *php_tinycdb_globals)
{
	//php_tinycdb_globals->global_value = 0;
	//php_tinycdb_globals->global_string = NULL;
	php_tinycdb_globals->init_dbname = "sample.cdb";
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(php_tinycdb)
{
	REGISTER_INI_ENTRIES();
	int	fd;
	fd = shm_open(PHP_TINYCDB_G(init_dbname), O_RDWR, 0666);
	if (fd < 0 || cdb_init(&shm_storage.data, fd) != 0) {
		return FAILURE; 
	}

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(php_tinycdb)
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
PHP_RINIT_FUNCTION(php_tinycdb)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(php_tinycdb)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(php_tinycdb)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "php_tinycdb support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ php_tinycdb_functions[]
 *
 * Every user visible function must have an entry in php_tinycdb_functions[].
 */
const zend_function_entry php_tinycdb_functions[] = {
	PHP_FE(cdb_get,	NULL)		/* For testing */
	PHP_FE_END	/* Must be the last line in php_tinycdb_functions[] */
};
/* }}} */

/* {{{ php_tinycdb_module_entry
 */
zend_module_entry php_tinycdb_module_entry = {
	STANDARD_MODULE_HEADER,
	"php_tinycdb",
	php_tinycdb_functions,
	PHP_MINIT(php_tinycdb),
	PHP_MSHUTDOWN(php_tinycdb),
	PHP_RINIT(php_tinycdb),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(php_tinycdb),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(php_tinycdb),
	PHP_PHP_TINYCDB_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PHP_TINYCDB
ZEND_GET_MODULE(php_tinycdb)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
