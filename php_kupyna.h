#ifndef PHP_KUPYNA_H
#define PHP_KUPYNA_H

#include <main/php.h>
#include <ext/hash/php_hash.h>

#define PHP_KUPYNA_EXTNAME  "kupyna"
#define PHP_KUPYNA_EXTVER   "0.2"

#ifndef ZEND_MOD_END
#define ZEND_MOD_END { NULL, NULL, NULL, 0 }
#endif

#if defined(__GNUC__) && __GNUC__ >= 4
#	define KUPYNA_VISIBILITY_HIDDEN __attribute__((visibility("hidden")))
#else
#	define KUPYNA_VISIBILITY_HIDDEN
#endif


ZEND_DLEXPORT extern const php_hash_ops kupyna256_hash_ops;
ZEND_DLEXPORT extern const php_hash_ops kupyna512_hash_ops;

#ifdef COMPILE_DL_KUPYNA
KUPYNA_VISIBILITY_HIDDEN
#endif
extern zend_module_entry kupyna_module_entry;

#define phpext_kupyna_ptr &kupyna_module_entry

#endif /* PHP_KUPYNA_H */
