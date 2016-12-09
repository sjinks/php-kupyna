#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <main/php.h>
#include <Zend/zend.h>
#include <ext/hash/php_hash.h>
#include <ext/standard/info.h>
#include "php_kupyna.h"
#include "kupyna256.h"
#include "kupyna512.h"

static void hash_kupyna256_init(void* context)
{
	size_t offset               = (((size_t)context + 15) & ~0x0F) - (size_t)context;
	struct kupyna256_ctx_t* ctx = (struct kupyna256_ctx_t*)((char*)context + offset);
	kupyna256_init(ctx);
}

static void hash_kupyna384_init(void* context)
{
	size_t offset               = (((size_t)context + 15) & ~0x0F) - (size_t)context;
	struct kupyna512_ctx_t* ctx = (struct kupyna512_ctx_t*)((char*)context + offset);
	kupyna384_init(ctx);
}

static void hash_kupyna512_init(void* context)
{
	size_t offset               = (((size_t)context + 15) & ~0x0F) - (size_t)context;
	struct kupyna512_ctx_t* ctx = (struct kupyna512_ctx_t*)((char*)context + offset);
	kupyna512_init(ctx);
}

static void hash_kupyna256_update(void* context, const unsigned char* buf, unsigned int count)
{
	size_t offset               = (((size_t)context + 15) & ~0x0F) - (size_t)context;
	struct kupyna256_ctx_t* ctx = (struct kupyna256_ctx_t*)((char*)context + offset);
	kupyna256_update(ctx, buf, count);
}

static void hash_kupyna384_update(void* context, const unsigned char* buf, unsigned int count)
{
	size_t offset               = (((size_t)context + 15) & ~0x0F) - (size_t)context;
	struct kupyna512_ctx_t* ctx = (struct kupyna512_ctx_t*)((char*)context + offset);
	kupyna384_update(ctx, buf, count);
}

static void hash_kupyna512_update(void* context, const unsigned char* buf, unsigned int count)
{
	size_t offset               = (((size_t)context + 15) & ~0x0F) - (size_t)context;
	struct kupyna512_ctx_t* ctx = (struct kupyna512_ctx_t*)((char*)context + offset);
	kupyna512_update(ctx, buf, count);
}

static void hash_kupyna256_final(unsigned char* digest, void* context)
{
	size_t offset               = (((size_t)context + 15) & ~0x0F) - (size_t)context;
	struct kupyna256_ctx_t* ctx = (struct kupyna256_ctx_t*)((char*)context + offset);
	kupyna256_final(ctx, digest);
}

static void hash_kupyna384_final(unsigned char* digest, void* context)
{
	size_t offset               = (((size_t)context + 15) & ~0x0F) - (size_t)context;
	struct kupyna512_ctx_t* ctx = (struct kupyna512_ctx_t*)((char*)context + offset);
	kupyna384_final(ctx, digest);
}

static void hash_kupyna512_final(unsigned char* digest, void* context)
{
	size_t offset               = (((size_t)context + 15) & ~0x0F) - (size_t)context;
	struct kupyna512_ctx_t* ctx = (struct kupyna512_ctx_t*)((char*)context + offset);
	kupyna512_final(ctx, digest);
}

const php_hash_ops kupyna256_hash_ops = {
	hash_kupyna256_init,
	hash_kupyna256_update,
	hash_kupyna256_final,
#if PHP_VERSION_ID >= 50300
	(php_hash_copy_func_t)php_hash_copy,
#endif
	32,
	64,
	(sizeof(struct kupyna256_ctx_t) + 15)
};

const php_hash_ops kupyna384_hash_ops = {
	hash_kupyna384_init,
	hash_kupyna384_update,
	hash_kupyna384_final,
#if PHP_VERSION_ID >= 50300
	(php_hash_copy_func_t)php_hash_copy,
#endif
	48,
	128,
	(sizeof(struct kupyna512_ctx_t) + 15)
};

const php_hash_ops kupyna512_hash_ops = {
	hash_kupyna512_init,
	hash_kupyna512_update,
	hash_kupyna512_final,
#if PHP_VERSION_ID >= 50300
	(php_hash_copy_func_t)php_hash_copy,
#endif
	64,
	128,
	(sizeof(struct kupyna512_ctx_t) + 15)
};

static PHP_MINIT_FUNCTION(kupyna)
{
	php_hash_register_algo("kupyna256", &kupyna256_hash_ops);
	php_hash_register_algo("kupyna384", &kupyna384_hash_ops);
	php_hash_register_algo("kupyna512", &kupyna512_hash_ops);
	return SUCCESS;
}

static PHP_MINFO_FUNCTION(kupyna)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "DSTU 7564:2014 hash functions", "enabled");
	php_info_print_table_row(2, "Version", PHP_KUPYNA_EXTVER);
	php_info_print_table_end();
}

static
#if ZEND_MODULE_API_NO > 20060613
const
#endif
zend_module_dep kupyna_deps[] = {
	ZEND_MOD_REQUIRED("hash")
	ZEND_MOD_END
};

zend_module_entry kupyna_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	kupyna_deps,
	PHP_KUPYNA_EXTNAME,
	NULL,
	PHP_MINIT(kupyna),
	NULL,
	NULL,
	NULL,
	PHP_MINFO(kupyna),
	PHP_KUPYNA_EXTVER,
	NO_MODULE_GLOBALS,
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_KUPYNA
ZEND_GET_MODULE(kupyna)
#endif
