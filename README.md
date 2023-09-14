# php-kupyna

[![Build and Test](https://github.com/sjinks/php-kupyna/actions/workflows/test.yml/badge.svg)](https://github.com/sjinks/php-kupyna/actions/workflows/test.yml)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=sjinks_php-kupyna&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=sjinks_php-kupyna)

DSTU 7564:2014 (Kupyna) Hash Function Implementation for PHP.

Tested with PHP 5.4, 5.5, 5.6, 7.0, 7.1, 7.2, 7.3, 7.4, 8.0, 8.1, 8.2, and nightly (8.3 as of writing)

## Introduction

This extension provides the implementation of DSTU 7564:2014 256-, 384-, and 512-bit hash functions to use with PHP [hash](http://php.net/hash) extension.

The extension registers three hashes:
  * `kupyna-256` (DSTU 7564:2014 256 bit hash function);
  * `kupyna-384` (DSTU 7564:2014 384 bit hash function);
  * `kupyna-512` (DSTU 7564:2014 512 bit hash function);

These hashes can be used with any function from PHP `hash` extension.

The extension also makes these functions available:
  * `string kupyna256_kmac(string $key, string $data)`
  * `string kupyna384_kmac(string $key, string $data)`
  * `string kupyna512_kmac(string $key, string $data)`

These functions return KMAC code (like HMAC, but computed differently) using the 256/384/512-bit key `$key` over the message `$data`.
If the key size is less than 256/384/512 bits, the key is hashed with the respective `kupynaXXX` function, and the returned result (which will be of the required size) is used as the key. If the key is longer than required, it will be truncated.

## Installing/Configuring

```bash
phpize
./configure
make
sudo make install
```

There are no configuration directives defined in `php.ini`.

## Usage Example

**Hash calculation:**

```php
$data = '012345678901234567890123456789012345678901234567890123456789012';
echo hash('kupyna256', $data), PHP_EOL;
echo hash('kupyna384', $data), PHP_EOL;
echo hash('kupyna512', $data), PHP_EOL;
```

**HMAC calculation:**

```php
$data = 'Very secret data';
$key  = 'password';
echo hash_hmac('kupyna512', $data, $key);
```
