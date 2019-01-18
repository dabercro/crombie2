# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([crombie2], [0.1], [dabercro@mit.edu])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Checks for programs.
AC_PROG_CXX

PKG_PROG_PKG_CONFIG([0.23])
PKG_CHECK_MODULES([GTK], [gtkmm-2.4 >= 2.18])
PKG_CHECK_MODULES([MARIADB], [libmariadb >= 3.0])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
