# RPM spec file for Red Hat Linux
# $Id: libvc.spec,v 1.2 2003/05/16 06:30:38 ahsu Rel $
Summary: Shared library for accessing and manipulating vCard files.
Name: libvc
Version: 003
Release: 1
Source: http://osdn.dl.sourceforge.net/sourceforge/rolo/%{name}-%{version}.tar.gz
License: GPL
URL: http://rolo.sf.net/
Packager: Andrew Hsu <ahsu@users.sf.net>
Distribution: Red Hat Linux
Vendor: Andrew Hsu
Group: System Environment/Libraries
Prefix: /usr
BuildRoot: %{_tmppath}/%{name}-buildroot

%description
The libvc library is a C library for accessing and manipulating
vCard files. This package contains only the shared libraries for
use by applications that need them at run-time.

%package devel
Summary: Static library and header file for vCard development.
Group: Development/Libraries
Requires: libvc = %{version}

%description devel
This package contains headers and static libraries for developing
applications that access and manipulate vCards. The library handles
scanning a vCard file, parsing the vCard file into a data storage
structure, manipulating the data storage structure, and writing
back to file.

Install the libvc-devel package if you want to develop applications
that access or manipulate vCard files.

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
%{_libdir}/*.so.*

%files devel
%defattr(-,root,root)
%{_libdir}/*.a
%{_includedir}/*.h
%{_mandir}/man3/vc.3*
%doc AUTHORS COPYING.LIB ChangeLog INSTALL NEWS README THANKS doc/rfc2426.txt
