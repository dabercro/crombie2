# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([crombie2], [0.1], [dabercro@mit.edu])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Checks for programs.
AC_PROG_CXX

PKG_PROG_PKG_CONFIG([0.29])
PKG_CHECK_MODULES([GTK], [gtkmm-2.4 >= 2.24])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
