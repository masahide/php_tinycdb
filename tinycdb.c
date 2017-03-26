
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <fcntl.h>

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_tinycdb.h"

ZEND_DECLARE_MODULE_GLOBALS(tinycdb)


/* True global resources - no need for thread safety here */
static int le_tinycdb;

/* {{{ tinycdb_close
 */
void tinycdb_close()
{
	if (TINYCDB_G(fd) != 0){
		cdb_free(&TINYCDB_G(data));
		TINYCDB_G(cdb_name)[0] = 0;
		close(TINYCDB_G(fd));
		TINYCDB_G(fd) = 0;
	}
}
/* }}} */
/* {{{ PHP_INI
 */

/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("tinycdb.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_tinycdb_globals, tinycdb_globals)
    STD_PHP_INI_ENTRY("tinycdb.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_tinycdb_globals, tinycdb_globals)
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
	if (cdb_find(&TINYCDB_G(data), key, key_len) > 0) { /* if search successeful */
		vpos = cdb_datapos(&TINYCDB_G(data)); /* position of data in a file */
		vlen = cdb_datalen(&TINYCDB_G(data)); /* length of data */
		val = emalloc(vlen+1); /* allocate memory */
		val[vlen]=0;
		cdb_read(&TINYCDB_G(data), val, vlen, vpos); /* read the value into buffer */
		ZVAL_STRINGL(return_value, val, vlen,0);
	}
}
/* }}} */

/* {{{ proto string cdb_name()
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(cdb_name)
{
	ZVAL_STRING(return_value, TINYCDB_G(cdb_name), 1);
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

	tinycdb_close();

	TINYCDB_G(fd) = shm_open(fname, O_RDWR, 0400);
	if (TINYCDB_G(fd) < 0 || cdb_init(&TINYCDB_G(data), TINYCDB_G(fd)) != 0) {
		RETURN_FALSE;
	}
	strcpy(TINYCDB_G(cdb_name), fname);
	//RETURN_STRING(fname,1)
	RETURN_TRUE;
}
/* }}} */


/* {{{ proto string cdb_load_dbfile(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(cdb_close_dbfile)
{
	tinycdb_close();
}
/* }}} */


/* {{{ php_tinycdb_init_globals
 */
static void php_tinycdb_init_globals(zend_tinycdb_globals *tinycdb_globals)
{
	tinycdb_globals->cdb_name[0] = 0;
	tinycdb_globals->fd = 0;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(tinycdb)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(tinycdb)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	tinycdb_close();
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(tinycdb)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(tinycdb)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(tinycdb)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "tinycdb support", "enabled");
	php_info_print_table_row(2, "Version", PHP_TINYCDB_VERSION);
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ tinycdb_functions[]
 *
 * Every user visible function must have an entry in tinycdb_functions[].
 */
const zend_function_entry tinycdb_functions[] = {
	PHP_FE(cdb_get, NULL)
	PHP_FE(cdb_name, NULL)
	PHP_FE(cdb_load_dbfile, NULL)
	PHP_FE(cdb_close_dbfile, NULL)
	PHP_FE_END	/* Must be the last line in tinycdb_functions[] */
};
/* }}} */

/* {{{ tinycdb_module_entry
 */
zend_module_entry tinycdb_module_entry = {
	STANDARD_MODULE_HEADER,
	"tinycdb",
	tinycdb_functions,
	PHP_MINIT(tinycdb),
	PHP_MSHUTDOWN(tinycdb),
	PHP_RINIT(tinycdb),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(tinycdb),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(tinycdb),
	PHP_TINYCDB_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TINYCDB
ZEND_GET_MODULE(tinycdb)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
