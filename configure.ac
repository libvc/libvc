# Process this file with autoconf to produce a configure script.
# $Id: configure.ac,v 1.1 2003/05/10 09:22:20 ahsu Rel $

AC_INIT(libvc, 002, ahsu@users.sf.net)
AM_INIT_AUTOMAKE
AC_PREREQ(2.57)
AC_COPYRIGHT([Copyright (C) 2003  Andrew Hsu])
AC_REVISION($Revision: 1.1 $)
AC_CONFIG_SRCDIR([src/vc.c])

# Checks for programs.
AC_PROG_CC
AC_PROG_LEX
AC_PROG_YACC
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strdup])

AC_CONFIG_FILES([Makefile src/Makefile doc/Makefile])
AC_OUTPUT
