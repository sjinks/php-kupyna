--TEST--
hash_algos()
--SKIPIF--
<?php if (!extension_loaded('kupyna')) die('skip'); ?>
--FILE--
<?php
var_dump(in_array('kupyna256', hash_algos()));
var_dump(in_array('kupyna384', hash_algos()));
var_dump(in_array('kupyna512', hash_algos()));
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
