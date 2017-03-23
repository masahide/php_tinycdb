
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <fcntl.h>

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_php_tinycdb.h"

ZEND_DECLARE_MODULE_GLOBALS(php_tinycdb)


/* True global resources - no need for thread safety here */
static int le_php_tinycdb;

/* {{{ php_tinycdb_close
 */
void php_tinycdb_close()
{
	if (PHP_TINYCDB_G(fd) != 0){
		cdb_free(&PHP_TINYCDB_G(data));
		PHP_TINYCDB_G(cdb_name)[0] = 0;
		close(PHP_TINYCDB_G(fd));
		PHP_TINYCDB_G(fd) = 0;
	}
}
/* }}} */
/* {{{ PHP_INI
 */

/*
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("php_tinycdb.global_value",        "42", PHP_INI_ALL, OnUpdateLong,   global_value, zend_php_tinycdb_globals, php_tinycdb_globals)
    STD_PHP_INI_ENTRY("php_tinycdb.global_string",   "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_php_tinycdb_globals, php_tinycdb_globals)
PHP_INI_END()
*/
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
	int key_len;
	unsigned vlen, vpos;
	char *val;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key, &key_len) == FAILURE) {
		return;
	}
	if (cdb_find(&PHP_TINYCDB_G(data), key, key_len) > 0) { /* if search successeful */
		vpos = cdb_datapos(&PHP_TINYCDB_G(data)); /* position of data in a file */
		vlen = cdb_datalen(&PHP_TINYCDB_G(data)); /* length of data */
		val = emalloc(vlen+1); /* allocate memory */
		val[vlen]=0;
		cdb_read(&PHP_TINYCDB_G(data), val, vlen, vpos); /* read the value into buffer */
		ZVAL_STRINGL(return_value, val, vlen,0);
	}
}
/* }}} */

/* {{{ proto string cdb_name()
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(cdb_name)
{
	ZVAL_STRING(return_value, PHP_TINYCDB_G(cdb_name), 1);
}
/* }}} */

/* {{{ proto string cdb_load_dbfile(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(cdb_load_dbfile)
{
	char *fname = NULL;
	int fname_len;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &fname, &fname_len) == FAILURE) {
		RETURN_FALSE;
	}

	php_tinycdb_close();

	PHP_TINYCDB_G(fd) = shm_open(fname, O_RDWR, 0666);
	if (PHP_TINYCDB_G(fd) < 0 || cdb_init(&PHP_TINYCDB_G(data), PHP_TINYCDB_G(fd)) != 0) {
		RETURN_FALSE;
	}
	strcpy(PHP_TINYCDB_G(cdb_name), fname);
	//RETURN_STRING(fname,1)
	RETURN_TRUE;
}
/* }}} */


/* {{{ proto string cdb_load_dbfile(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(cdb_close_dbfile)
{
	php_tinycdb_close();
}


/* {{{ php_php_tinycdb_init_globals
 */
static void php_php_tinycdb_init_globals(zend_php_tinycdb_globals *php_tinycdb_globals)
{
	php_tinycdb_globals->cdb_name[0] = 0;
	php_tinycdb_globals->fd = 0;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(php_tinycdb)
{
	//REGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(php_tinycdb)
{
	//UNREGISTER_INI_ENTRIES();
	php_tinycdb_close();
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

	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ php_tinycdb_functions[]
 *
 * Every user visible function must have an entry in php_tinycdb_functions[].
 */
const zend_function_entry php_tinycdb_functions[] = {
	PHP_FE(cdb_get, NULL)
	PHP_FE(cdb_name, NULL)
	PHP_FE(cdb_load_dbfile, NULL)
	PHP_FE(cdb_close_dbfile, NULL)
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
