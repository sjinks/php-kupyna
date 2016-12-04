# php-kupyna [![Build Status](https://travis-ci.org/sjinks/php-kupyna.png?branch=master)](https://travis-ci.org/sjinks/php-kupyna)

DSTU 7564:2014 (Kupyna) Hash Function implementation for PHP.

Tested with PHP 5.4, 5.5, 5.6, 7.0, 7.1

## Introduction

This extension provides implementation of DSTU 7564:2014 256 and 512 bit hash functions to be used with PHP [hash](http://php.net/hash) extension.

The extension does not introduce any new functions; instead, it registers two hashes:
  * `kupyna-256` (DSTU 7564:2014 256 bit hash function);
  * `kupyna-512` (DSTU 7564:2014 512 bit hash function);

These hashes can be used with any function from PHP `hash` extension.

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
echo hash('kupyna512', $data), PHP_EOL;
```

**HMAC calculation:**

```php
$data = 'Very secret data';
$key  = 'password';
echo hash_hmac('kupyna512', $data, $key);
```
