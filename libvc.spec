# RPM spec file for Red Hat Linux
# rename this file to libvc.spec before doing a make dist if you want
# the resultant tar.gz for creating Red Hat RPMs.
# $Id: libvc.spec_rh,v 1.2 2003/05/15 04:59:41 ahsu Exp $
Summary: A vCard library.
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
BuildRoot: %{_tmppath}/%{name}-buildroot

%description
This vCard library was written using flex and bison. The library
handles scanning a vCard file, parsing the vCard file into a data
storage structure, manipulating the data storage structure, and
writing back to file. It was originally written for rolo, but has
been split-off as a generic library for general use.

%prep
%setup -q

%build
./configure --libdir=/usr/lib --includedir=/usr/include --mandir=/usr/share/man
make

%install
rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%{_libdir}/libvc.a
%{_includedir}/vc.h
%{_mandir}/man3/vc.3*
%doc AUTHORS COPYING ChangeLog INSTALL NEWS README THANKS
