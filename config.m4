PHP_ARG_ENABLE(kupyna, whether to enable DSTU 7564:2014 Hash Function, [ --enable-kupyna  Enable DSTU 7564:2014 Hash Function])

if test "$PHP_KUPYNA" = "yes"; then
	PHP_C_BIGENDIAN

	AC_DEFINE([HAVE_KUPYNA], [1], [Whether DSTU 7564:2014 Hash Function is supported])
	PHP_NEW_EXTENSION([kupyna], [kupyna.c kupyna256.c kupyna512.c kupyna_tables.c], $ext_shared)
	PHP_ADD_EXTENSION_DEP([kupyna], [hash])
fi
