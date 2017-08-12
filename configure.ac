dnl Process this file with autoconf to produce a configure script.

define([svnversion], esyscmd([sh -c "LANG=en_US.UTF-8 LANGUAGE=en_US.UTF-8 svnversion|sed s/:/./g| sed s/M//g |tr -d '\n'"])) 

dnl Initialization
AC_INIT([tpbuff], [1.0], [root@gnetis.com])
AC_CONFIG_AUX_DIR(auxdir)
AM_INIT_AUTOMAKE
AM_MAINTAINER_MODE

dnl Package information
AC_CONFIG_MACRO_DIR([m4])

dnl Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_HEADER_STDC

# Checks for gnu bison.
AC_PROG_YACC
if test x"$YACC" != x"bison -y"; then
    AC_MSG_ERROR([You must install the gnu bison and its version must be 2.6 or more])
else
    flex_ver=$($YACC -V | sed -n '1p' | cut -f 4 -d " ")
    ver1=$(echo $flex_ver | cut -f 1 -d ".")
    ver2=$(echo $flex_ver | cut -f 2 -d ".")
    if test $ver1 -lt 2 || (test ver1 -eq 2 && test $ver2 -lt 6);then
        AC_MSG_ERROR([The gnu bison version must be 2.6 or more])
    fi
fi
#checks for gnu flex
AC_PROG_LEX
if test x"$LEX" != x"flex"; then
    AC_MSG_ERROR([You must install the gnu flex and its version must be 2.5.35 or more])
else 
    flex_ver=$($LEX -V | cut -f 2 -d " ")
    ver1=$(echo $flex_ver | cut -f 1 -d ".")
    ver2=$(echo $flex_ver | cut -f 2 -d ".")
    ver3=$(echo $flex_ver | cut -f 3 -d ".")
    if test $ver1 -lt 2 || (test $ver1 -eq 2 && (test $ver2 -lt 5 || (test $ver2 -eq 5 && test $ver3 -lt 34)));then
        AC_MSG_ERROR([The gnu flex version must be 2.5.34 or more])
    fi
fi
dnl Checks for libraries.
dnl AC_CHECK_LIB(LIBRARY, FUNCT, [ACT-IF-FOUND], [ACT-IF-NOT])
dnl Check header
dnl AC CHECK HEADERS(HEADERS...)
dnl
dnl Checks for typedefs, structures, and compiler characteristics.
dnl
dnl Checks for library functions.

dnl tang check, keep it anyway, our prefix=/tang
dnl AC_PLATFORM_CHECK([tang])
dnl option --enable-log=n, LOGLEVEL definition
dnl AC_SET_DEFAULT_LOGLEVEL([6])
dnl option --enable-profile=gprofile/profile/no to enable program profile.
dnl AC_SET_DEFAULT_PROFILE([disable])

dnl Check module with PKG_CONFIG
dnl PKG_CHECK_MODULES([DBUS], [dbus-1])


dnl Doxygen check and configure
dnl DX_HTML_FEATURE(ON)
dnl DX_CHM_FEATURE(OFF)
dnl DX_CHI_FEATURE(OFF)
dnl DX_MAN_FEATURE(OFF)
dnl DX_RTF_FEATURE(OFF)
dnl DX_XML_FEATURE(OFF)
dnl DX_PDF_FEATURE(OFF)
dnl DX_PS_FEATURE(OFF)
dnl DX_INIT_DOXYGEN(tpbuff, doxygen.cfg)

AC_CONFIG_HEADERS([config.h])
dnl Final Output
AC_OUTPUT([
Makefile
src/Makefile src/tpp/Makefile
test/Makefile test/ut/Makefile test/ut/tpp/Makefile
])

