# Process this file with autoconf to produce a configure script.
# $Id: configure.ac,v 1.3 2003/06/14 01:54:15 ahsu Rel $

AC_INIT([libvc],[005],[rafael@laboissiere.net])
LIBVC_ABI_VERSION=0:1:0
AC_SUBST(LIBVC_ABI_VERSION)

AM_INIT_AUTOMAKE
AC_PREREQ(2.59)
AC_COPYRIGHT([Copyright (C) 2003  Andrew Hsu
Copyright (C) 2017 Rafael Laboissiere])
AC_REVISION($Revision: 1.3 $)
AC_CONFIG_SRCDIR([src/vc.c])

# Checks for programs.
AC_PROG_CC
AC_PROG_LEX
AC_PROG_YACC
AC_PROG_LIBTOOL

# Checks for libraries.

AC_CHECK_PROG(have_shunit2,shunit2,yes)
AM_CONDITIONAL([HAVE_SHUNIT2], [test x$have_shunit2 = xyes])
# Checks for header files.
AC_HEADER_STDC

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strdup strcasecmp])

AC_CONFIG_FILES([Makefile src/Makefile doc/Makefile test/Makefile])
AC_OUTPUT
