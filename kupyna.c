#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdint.h>
#include <main/php.h>
#include <Zend/zend.h>
#include <ext/hash/php_hash.h>
#include <ext/standard/info.h>
#include <ext/standard/md5.h>
#include "php_kupyna.h"
#include "kupyna256.h"
#include "kupyna512.h"
#include "kupyna_kmac.h"

#if PHP_VERSION_ID >= 80000
#define TSRMLS_CC
#endif

static void hash_kupyna256_init(
	void* context
#if PHP_VERSION_ID >= 80100
	, ZEND_ATTRIBUTE_UNUSED HashTable* args
#endif
)
{
	size_t offset               = (((size_t)context + 15) & ~0x0F) - (size_t)context;
	struct kupyna256_ctx_t* ctx = (struct kupyna256_ctx_t*)((char*)context + offset);
	kupyna256_init(ctx);
}

static void hash_kupyna384_init(
	void* context
#if PHP_VERSION_ID >= 80100
	, ZEND_ATTRIBUTE_UNUSED HashTable* args
#endif
)
{
	size_t offset               = (((size_t)context + 15) & ~0x0F) - (size_t)context;
	struct kupyna512_ctx_t* ctx = (struct kupyna512_ctx_t*)((char*)context + offset);
	kupyna384_init(ctx);
}

static void hash_kupyna512_init(
	void* context
#if PHP_VERSION_ID >= 80100
	, ZEND_ATTRIBUTE_UNUSED HashTable* args
#endif
)
{
	size_t offset               = (((size_t)context + 15) & ~0x0F) - (size_t)context;
	struct kupyna512_ctx_t* ctx = (struct kupyna512_ctx_t*)((char*)context + offset);
	kupyna512_init(ctx);
}

static void hash_kupyna256_update(
	void* context,
	const unsigned char* buf,
#if PHP_VERSION_ID >= 70400
	size_t count
#else
	unsigned int count
#endif
)
{
	size_t offset               = (((size_t)context + 15) & ~0x0F) - (size_t)context;
	struct kupyna256_ctx_t* ctx = (struct kupyna256_ctx_t*)((char*)context + offset);
	kupyna256_update(ctx, buf, count);
}

static void hash_kupyna384_update(
	void* context,
	const unsigned char* buf,
#if PHP_VERSION_ID >= 70400
	size_t count
#else
	unsigned int count
#endif
)
{
	size_t offset               = (((size_t)context + 15) & ~0x0F) - (size_t)context;
	struct kupyna512_ctx_t* ctx = (struct kupyna512_ctx_t*)((char*)context + offset);
	kupyna384_update(ctx, buf, count);
}

static void hash_kupyna512_update(
	void* context,
	const unsigned char* buf,
#if PHP_VERSION_ID >= 70400
	size_t count
#else
	unsigned int count
#endif
)
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
#if PHP_VERSION_ID >= 80000
	"kupyna256",
#endif
	hash_kupyna256_init,
	hash_kupyna256_update,
	hash_kupyna256_final,
#if PHP_VERSION_ID >= 50300
	(php_hash_copy_func_t)php_hash_copy,
#endif
#if PHP_VERSION_ID >= 80000
	NULL,
	NULL,
	NULL,
#endif
	32,
	64,
	(sizeof(struct kupyna256_ctx_t) + 15)
#if PHP_VERSION_ID >= 70400
	, 1
#endif
};

const php_hash_ops kupyna384_hash_ops = {
#if PHP_VERSION_ID >= 80000
	"kupyna384",
#endif
	hash_kupyna384_init,
	hash_kupyna384_update,
	hash_kupyna384_final,
#if PHP_VERSION_ID >= 50300
	(php_hash_copy_func_t)php_hash_copy,
#endif
#if PHP_VERSION_ID >= 80000
	NULL,
	NULL,
	NULL,
#endif
	48,
	128,
	(sizeof(struct kupyna512_ctx_t) + 15)
#if PHP_VERSION_ID >= 70400
	, 1
#endif
};

const php_hash_ops kupyna512_hash_ops = {
#if PHP_VERSION_ID >= 80000
	"kupyna512",
#endif
	hash_kupyna512_init,
	hash_kupyna512_update,
	hash_kupyna512_final,
#if PHP_VERSION_ID >= 50300
	(php_hash_copy_func_t)php_hash_copy,
#endif
#if PHP_VERSION_ID >= 80000
	NULL,
	NULL,
	NULL,
#endif
	64,
	128,
	(sizeof(struct kupyna512_ctx_t) + 15)
#if PHP_VERSION_ID >= 70400
	, 1
#endif
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

static PHP_FUNCTION(kupyna256_kmac)
{
	char* key;
	char* data;
#if PHP_MAJOR_VERSION < 7
	int key_len;
	int data_len;
#else
	size_t key_len;
	size_t data_len;
#endif

	uint8_t mac[32];
	char result[65];

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &key, &key_len, &data, &data_len)) {
		RETURN_NULL();
	}

	if (key_len < 32) {
		struct kupyna256_ctx_t ctx;
		kupyna256_init(&ctx);
		kupyna256_update(&ctx, (uint8_t*)key, key_len);
		kupyna256_final(&ctx, mac);
		kupyna256_kmac(mac, (const uint8_t*)data, (size_t)data_len, mac);
	}
	else {
		kupyna256_kmac((const uint8_t*)key, (const uint8_t*)data, (size_t)data_len, mac);
	}

	make_digest_ex(result, mac, 32);
#if PHP_MAJOR_VERSION < 7
	RETURN_STRINGL(result, 64, 1);
#else
	RETURN_STRINGL(result, 64);
#endif
}

static PHP_FUNCTION(kupyna384_kmac)
{
	char* key;
	char* data;
#if PHP_MAJOR_VERSION < 7
	int key_len;
	int data_len;
#else
	size_t key_len;
	size_t data_len;
#endif

	uint8_t mac[48];
	char result[97];

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &key, &key_len, &data, &data_len)) {
		RETURN_NULL();
	}

	if (key_len < 48) {
		struct kupyna512_ctx_t ctx;
		kupyna384_init(&ctx);
		kupyna384_update(&ctx, (uint8_t*)key, key_len);
		kupyna384_final(&ctx, mac);
		kupyna384_kmac(mac, (const uint8_t*)data, (size_t)data_len, mac);
	}
	else {
		kupyna384_kmac((const uint8_t*)key, (const uint8_t*)data, (size_t)data_len, mac);
	}

	make_digest_ex(result, mac, 48);
#if PHP_MAJOR_VERSION < 7
	RETURN_STRINGL(result, 96, 1);
#else
	RETURN_STRINGL(result, 96);
#endif
}

static PHP_FUNCTION(kupyna512_kmac)
{
	char* key;
	char* data;
#if PHP_MAJOR_VERSION < 7
	int key_len;
	int data_len;
#else
	size_t key_len;
	size_t data_len;
#endif

	uint8_t mac[64];
	char result[129];

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &key, &key_len, &data, &data_len)) {
		RETURN_NULL();
	}

	if (key_len < 64) {
		struct kupyna512_ctx_t ctx;
		kupyna512_init(&ctx);
		kupyna512_update(&ctx, (uint8_t*)key, key_len);
		kupyna512_final(&ctx, mac);
		kupyna512_kmac(mac, (const uint8_t*)data, (size_t)data_len, mac);
	}
	else {
		kupyna512_kmac((const uint8_t*)key, (const uint8_t*)data, (size_t)data_len, mac);
	}

	make_digest_ex(result, mac, 64);
#if PHP_MAJOR_VERSION < 7
	RETURN_STRINGL(result, 128, 1);
#else
	RETURN_STRINGL(result, 128);
#endif
}

ZEND_BEGIN_ARG_INFO(arginfo_kmac, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

static const zend_function_entry kupyna_functions[] = {
	PHP_FE(kupyna256_kmac, arginfo_kmac)
	PHP_FE(kupyna384_kmac, arginfo_kmac)
	PHP_FE(kupyna512_kmac, arginfo_kmac)
	PHP_FE_END
};

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
	kupyna_functions,
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
