#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT(bamf, 0.5.6, dx-team@canonical.com)
AC_PREREQ(2.69)
AC_SUBST(LIBBAMF_VER, 3)
AC_SUBST(LIBBAMF_SONAME, 2:0:0)

AC_CONFIG_SRCDIR(src/main.c)
AC_CONFIG_HEADERS(config.h)

AM_INIT_AUTOMAKE([foreign tar-pax])
AM_SILENT_RULES([yes])

AC_CONFIG_MACRO_DIR([m4])

GNOME_COMMON_INIT

AM_MAINTAINER_MODE
AC_ISC_POSIX
AC_SUBST(ACLOCAL_AMFLAFS, "$ACLOCAL_FLAGS -I m4")

PKG_PROG_PKG_CONFIG
if test "x$PKG_CONFIG" = "x"; then AC_MSG_ERROR([You need to install pkg-config]); fi

LT_INIT([disable-static])
LT_LIB_M

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_HEADER_STDC

#
# pkg-config
#
PKG_PROG_PKG_CONFIG

#
# glib
#
PKG_CHECK_MODULES(GLIB, glib-2.0 >= 2.38.0 gio-2.0 >= 2.30.0 gio-unix-2.0 gobject-2.0 gmodule-2.0)

#
# gdbus-codegen
#
AC_PATH_PROG([GDBUS_CODEGEN], [gdbus-codegen])
if test -z "$GDBUS_CODEGEN"; then AC_MSG_ERROR([gdbus-codegen is required but was not found]); fi

#
# libwnck
#
PKG_CHECK_MODULES(WNCK, libwnck-3.0 >= 3.4.7)

#
# libgtop
#
PKG_CHECK_MODULES(GTOP, libgtop-2.0)

#
# libsn
#
PKG_CHECK_MODULES(SN, libstartup-notification-1.0)

#
# x11
#
PKG_CHECK_MODULES(X, x11)

#
# DbusMenu
#
AC_ARG_ENABLE([export-actions-menu],
              AS_HELP_STRING([--enable-export-actions-menu=@<:@no/yes@:>@],[export window actions menus (requires dbusmenu) @<:@default=no@:>@]),,
              [enable_export_actions_menu=no])

AM_CONDITIONAL([EXPORT_ACTIONS_MENU],[test "x$enable_export_actions_menu" != "xno"])

if test "x$enable_export_actions_menu" = "xyes"; then
  PKG_CHECK_MODULES(DBUSMENU, [dbusmenu-glib-0.4, dbusmenu-gtk3-0.4])
fi

###########################
# GObject Introspection
###########################

GOBJECT_INTROSPECTION_CHECK([0.10.2])

###########################
# Vala API Generation
###########################

if test "$enable_introspection" = "yes"; then
  AC_PATH_PROG([VALA_API_GEN], [vapigen])
  if test -z "$VALA_API_GEN"; then
    AC_MSG_ERROR([vapigen is needed to build introspection])
    HAVE_INTROSPECTION=0
    enable_introspection="no"
  fi
fi

###########################
# GTK-DOC
###########################
GTK_DOC_CHECK(1.0)

###########################
# gtester2xunit checks    #
###########################

AC_PATH_PROG([PYTHON],[python3])
AC_MSG_CHECKING(for gtester2xunit dependencies)
if !($PYTHON -c "from lxml import etree" 2> /dev/null); then
  AC_MSG_RESULT([no])
  AC_MSG_ERROR([You need to install python3-lxml]);
fi
AC_MSG_RESULT([yes])

###########################
# Headless tests
###########################
AC_ARG_ENABLE([headless-tests],
              AS_HELP_STRING([--enable-headless-tests=@<:@no/yes@:>@],[enable headless test suite (requires Xvfb) @<:@default=no@:>@]),,
              [enable_headless_tests=no])

AM_CONDITIONAL([ENABLE_HEADLESS_TESTS],[test "x$enable_headless_tests" != "xno"])

if test "x$enable_headless_tests" = "xyes"; then
  AC_PATH_PROG([XVFB],[Xvfb])
  AC_PATH_PROG([DBUS_RUN_SESSION],[dbus-run-session])

  if test -z "$XVFB" -o -z "$DBUS_RUN_SESSION"; then
    AC_MSG_ERROR([Xvfb and dbus-run-session are needed for headless-tests])
  fi
fi

###########################
# gcov coverage reporting
###########################
AC_TDD_GCOV
AM_CONDITIONAL([HAVE_GCOV], [test "x$ac_cv_check_gcov" = xyes])
AM_CONDITIONAL([HAVE_LCOV], [test "x$ac_cv_check_lcov" = xyes])
AM_CONDITIONAL([HAVE_GCOVR], [test "x$ac_cv_check_gcovr" = xyes])
AC_SUBST(COVERAGE_CFLAGS)
AC_SUBST(COVERAGE_LDFLAGS)

#
# Gnome/GTK checks
#
AM_PATH_GTK_3_0

# Compile warnings
AC_ARG_ENABLE(compile-warnings,
              AS_HELP_STRING([--enable-compile-warnings=@<:@no/minimum/yes/maximum/error@:>@],
                             [Turn on compiler warnings]),,
              [enable_compile_warnings=maximum])

warning_flags=

case "$enable_compile_warnings" in
no)
warning_flags=
;;
minimum)
warning_flags="-Wall"
;;
yes)
warning_flags="-wall -Wno-error=deprecated-declarations"
;;
maximum|error)
warning_flags="-Wall -Wno-error=deprecated-declarations -Wempty-body -Wformat-security -Winit-self -Warray-bounds -Wimplicit-function-declaration"
if test "$enable_compile_warnings" = "error" ; then
    warning_flags="$warning_flags -Werror"
fi
;;
*)
AC_MSG_ERROR(Unknown argument '$enable_compile_warnings' to --enable-compile-warnings)
;;
esac
AC_MSG_CHECKING(what warning flags to pass to the C compiler)
AC_MSG_RESULT($warning_flags)

dnl CFLAGS
CFLAGS="$CFLAGS $warning_flags $LIBM"

AC_SUBST(BAMFDAEMON_CFLAGS)
AC_SUBST(BAMFDAEMON_LIBS)

origgiomodulesdir=`pkg-config --variable=giomoduledir gio-2.0`
# Make giomodulesdir honour 'prefix', so that distcheck works.
giomodulesdir=`echo "$origgiomodulesdir" | sed 's|/usr|${prefix}|'`
AC_SUBST(giomodulesdir)

AC_OUTPUT([
Makefile
lib/libbamf-private/Makefile
lib/libbamf/Makefile
lib/libbamf/libbamf3.pc
src/Makefile
tests/Makefile
tests/bamfdaemon/Makefile
tests/libbamf/Makefile
data/Makefile
doc/Makefile
doc/reference/Makefile
doc/reference/libbamf/Makefile
])

cat <<EOF

${PACKAGE}-${VERSION}

  Build Environment
    Install Prefix:       ${prefix}
    Introspection:        ${enable_introspection}
    Headless tests:       ${enable_headless_tests}
    Coverage Reporting:   ${use_gcov}
    Export actions menus: ${enable_export_actions_menu} 
    Compiler Flags:       ${CFLAGS}

EOF
