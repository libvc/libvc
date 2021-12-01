## Process this file with automake to produce Makefile.in
## $Id: Makefile.am,v 1.2 2003/05/12 10:44:07 ahsu Rel $

BUILT_SOURCES = vc_parse.h
AM_YFLAGS = -d
AM_LFLAGS = -i
include_HEADERS = vc.h
lib_LTLIBRARIES = libvc.la
libvc_la_SOURCES = vc.c vc_parse.y vc_scan.l
libvc_la_LDFLAGS = -version-info $(LIBVC_ABI_VERSION)
CLEANFILES = vc_parse.c vc_parse.h vc_scan.c
