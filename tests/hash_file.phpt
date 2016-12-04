--TEST--
hash_file()
--SKIPIF--
<?php if (!extension_loaded('kupyna')) die('skip'); ?>
--FILE--
<?php
echo hash_file('kupyna256', dirname(__FILE__) . '/test1.txt'), PHP_EOL;
echo hash_file('kupyna512', dirname(__FILE__) . '/test1.txt'), PHP_EOL;
?>
--EXPECT--
5458da58f28e137100d564c6ea201356ae31c25f001e07e5c13090edd353a18f
9dc29544cd5f184cf5cfe0ccc9ab895c3a7cebff36805eba4468cfe8cb33c68fc57b61ef61d8ac65629eb3291d62bc7efb98aa422b2a2aa9d8fb236634d49aa9
