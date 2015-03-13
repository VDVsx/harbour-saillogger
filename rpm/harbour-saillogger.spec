Name:       harbour-saillogger
Summary:    SailfishOS Logger
Version:    0.0.1
Release:    1
Group:      Applications/System
License:    BSD
URL:        https://github.com/VDVsx/harbour-saillogger
Source0:    %{name}-%{version}.tar.bz2

Requires:   sailfishsilica-qt5 >= 0.11.0
BuildRequires: pkgconfig(sailfishapp)
BuildRequires: pkgconfig(Qt5Quick)
BuildRequires: pkgconfig(Qt5Qml)
BuildRequires: pkgconfig(Qt5Core)
BuildRequires: pkgconfig(Qt5DBus)
BuildRequires: desktop-file-utils


%description
Application to collect sailfishOS logs.

%prep
%setup -q -n %{name}-%{version}

%build
%qmake5 VERSION=%{version}
make %{?_smp_mflags}

%install
rm -rf %{buildroot}
%qmake5_install

desktop-file-install --delete-original \
  --dir %{buildroot}%{_datadir}/applications \
   %{buildroot}%{_datadir}/applications/*.desktop

%files
%defattr(-,root,root,-)
%{_bindir}/%{name}
%{_datadir}/%{name}/qml
%{_datadir}/%{name}/qml/harbour/saillogger/qmldir
%{_datadir}/%{name}/qml/harbour/saillogger/libharboursaillogger.so
%{_datadir}/applications/%{name}.desktop
