PHP_ARG_ENABLE(kupyna, whether to enable DSTU 7564:2014 Hash Function, [ --enable-kupyna  Enable DSTU 7564:2014 Hash Function])

if test "$PHP_KUPYNA" = "yes"; then
	PHP_C_BIGENDIAN

	AC_DEFINE([HAVE_KUPYNA], [1], [Whether DSTU 7564:2014 Hash Function is supported])
	PHP_NEW_EXTENSION([kupyna], [kupyna.c kupyna256.c kupyna512.c kupyna_kmac.c kupyna_tables.c], $ext_shared,, [-Wall -std=gnu99 -D_GNU_SOURCE])
	PHP_ADD_EXTENSION_DEP([kupyna], [hash])
fi

PHP_ARG_ENABLE(coverage,  whether to include code coverage symbols,
[  --enable-coverage       Enable code coverage symbols, maintainers only!], no, no)

if test "$PHP_COVERAGE" = "yes"; then
	if test "$GCC" != "yes"; then
		AC_MSG_ERROR([GCC is required for --enable-coverage])
	fi

	case `$php_shtool path $CC` in
		*ccache*[)] gcc_ccache=yes;;
		*[)] gcc_ccache=no;;
	esac

	if test "$gcc_ccache" = "yes" && (test -z "$CCACHE_DISABLE" || test "$CCACHE_DISABLE" != "1"); then
		AC_MSG_ERROR([ccache must be disabled when --enable-coverage option is used. You can disable ccache by setting environment variable CCACHE_DISABLE=1.])
	fi

	changequote({,})
	CFLAGS=`echo "$CFLAGS" | $SED -e 's/-O[0-9s]*//g'`
	CXXFLAGS=`echo "$CXXFLAGS" | $SED -e 's/-O[0-9s]*//g'`
	changequote([,])

	CFLAGS="$CFLAGS -O0 --coverage"
	CXXFLAGS="$CXXFLAGS -O0 --coverage"
	EXTRA_LDFLAGS="$EXTRA_LDFLAGS -precious-files-regex \.gcno\\\$$"

	PHP_ADD_MAKEFILE_FRAGMENT([Makefile.frag.coverage])
fi
