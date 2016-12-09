--TEST--
kupynaXXX_kmac
--SKIPIF--
<?php if (!extension_loaded('kupyna')) die('skip'); ?>
--FILE--
<?php
$vec = '';
$key = '';
for ($i=0; $i<256; ++$i) $vec .= chr($i);
for ($i=0; $i<64; ++$i)  $key .= chr(0xFF);

echo kupyna256_kmac($key, $vec), PHP_EOL;
echo kupyna384_kmac($key, $vec), PHP_EOL;
echo kupyna512_kmac($key, $vec), PHP_EOL;
?>
--EXPECT--
a0b5d5bcf95d75a809b05a018874b434194b618435c7fd0901d1d234b5e6b0db
5a27925090d579ea756f57c4318b0bfea639a95798dbe2915c7aefb90f082bbea49b423a73e304ac410b9ef6aefe5409
1ae8a63bfbdeb4f4b0e739827ca2bc6a87f7a7e92187d926d19b9bcf4d59d78fb9a0d05a14c0ee0c9a113a681b7c8c6515c960d302af2db5ddcfe9b248c4cd8a
