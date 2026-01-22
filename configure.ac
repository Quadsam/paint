AC_PREREQ([2.71])
AC_INIT([paint],[m4_esyscmd_s([git describe --tags])],[bugs@quadsam.com])
AC_CONFIG_SRCDIR([src/paint.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_PROG_CC
AC_TYPE_SIZE_T
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset])
PKG_CHECK_MODULES([SDL2], [sdl2 >= 2.0.22],
        [AC_DEFINE([HAVE_SDL2], [1], [Have sdl2])],
        [AC_MSG_ERROR([SDL2 is required!])])
AC_SUBST([SDL_CFLAGS])
AC_SUBST([SDL_LIBS])
AM_INIT_AUTOMAKE()
AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
