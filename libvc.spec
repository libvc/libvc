# RPM spec file for Red Hat Linux
# $Id: libvc.spec,v 1.1 2003/05/16 03:03:13 ahsu Exp $
Summary: A vCard library with headers and static libs
Name: libvc
Version: 002
Release: 1
Source: http://osdn.dl.sourceforge.net/sourceforge/rolo/%{name}-%{version}.tar.gz
License: GPL
URL: http://rolo.sf.net/
Packager: Andrew Hsu <ahsu@users.sf.net>
Distribution: Red Hat Linux
Vendor: Andrew Hsu
Group: Development/Libraries
Prefix: /usr
BuildRoot: %{_tmppath}/%{name}-buildroot

%description
This package contains headers and static libs for developing
applications that access and manipulate vCards. This library was
written using flex and bison. The library handles scanning a vCard
file, parsing the vCard file into a data storage structure,
manipulating the data storage structure, and writing back to file.
It was originally written for rolo, but has been split-off as a
generic library for general use.

%prep
%setup -q

%build
./configure --prefix=/usr --mandir=/usr/share/man
make

%install
rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%{_libdir}/*.a
%{_includedir}/*.h
%{_mandir}/man3/vc.3*
%doc AUTHORS COPYING.LIB ChangeLog INSTALL NEWS README THANKS doc/rfc2426.txt
