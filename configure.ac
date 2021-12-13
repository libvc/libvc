# Process this file with autoconf to produce a configure script.
# $Id: configure.ac,v 1.3 2003/06/14 01:54:15 ahsu Rel $

### Versioning
AC_INIT([libvc],[011],[rafael@laboissiere.net])
LIBVC_ABI_VERSION=1:3:1
AC_SUBST(LIBVC_ABI_VERSION)

### Main definitions
AM_INIT_AUTOMAKE
AC_PREREQ([2.71])
AC_COPYRIGHT([Copyright (C) 2003  Andrew Hsu
Copyright (C) 2017, 2019-2021 Rafael Laboissière])
AC_REVISION($Revision: 1.3 $)
AC_CONFIG_SRCDIR([src/vc.c])
AC_CONFIG_MACRO_DIRS([m4])

### Checks for programs.
AC_PROG_CC
AC_PROG_LEX([noyywrap])
AC_PROG_YACC
LT_INIT
AC_CHECK_PROG(have_shunit2,shunit2,yes)
AM_CONDITIONAL([HAVE_SHUNIT2], [test x$have_shunit2 = xyes])

### Checks for header files.
AC_CHECK_INCLUDES_DEFAULT

### Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

### Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strdup strcasecmp])

### Checks for visibility suport
m4_include([m4/visibility.m4])
gl_VISIBILITY

### Output files
AC_CONFIG_FILES([Makefile src/Makefile doc/Makefile test/Makefile])
AC_OUTPUT
