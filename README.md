# php-kupyna [![Build Status](https://travis-ci.org/sjinks/php-kupyna.png?branch=master)](https://travis-ci.org/sjinks/php-kupyna)

DSTU 7564:2014 (Kupyna) Hash Function implementation for PHP.

Tested with PHP 5.4, 5.5, 5.6, 7.0, 7.1, 7.2, 7.3, 7.4, nightly (8.0 as of writing)

## Introduction

This extension provides implementation of DSTU 7564:2014 256 and 512 bit hash functions to be used with PHP [hash](http://php.net/hash) extension.

The extension registers three hashes:
  * `kupyna-256` (DSTU 7564:2014 256 bit hash function);
  * `kupyna-384` (DSTU 7564:2014 384 bit hash function);
  * `kupyna-512` (DSTU 7564:2014 512 bit hash function);

These hashes can be used with any function from PHP `hash` extension.

The extension also makes these functions available:
  * `string kupyna256_kmac(string $key, string $data)`
  * `string kupyna384_kmac(string $key, string $data)`
  * `string kupyna512_kmac(string $key, string $data)`

These functions return KMAC code (like HMAC, but computed differently) using the 256/384/512-bit key $key over the message $data.
If the key size is less than 256/384/612 bits, the key is hashed with the respective `kupynaXXX` function, and the returned result (which will be of the required size) is used as the key. If the key is longer than required, it will be truncated.

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
