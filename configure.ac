AC_INIT([libnexthopgroup], [1.0])
AC_CONFIG_SRCDIR([scripts/render_schema.py])
AC_CONFIG_AUX_DIR([config])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_MACRO_DIR([m4])

# Language and compiler
AC_LANG([C++])
AC_PROG_CXX
AC_PROG_LIBTOOL

# Require Python 3 for code generation
AM_PATH_PYTHON([3.6], [], [AC_MSG_ERROR([Python 3.6+ is required for code generation])])

# Optional: enable debug build
AC_ARG_ENABLE([debug],
  [AS_HELP_STRING([--enable-debug], [Compile with debugging flags])],
  [case "${enableval}" in
    yes) debug=true ;;
    no)  debug=false ;;
    *) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
  esac],
  [debug=false]
)

# Set CXXFLAGS
CXXFLAGS_COMMON="-std=c++17 -fPIC -Wall -Wextra"
if test "x$debug" = "xtrue"; then
    CXXFLAGS_COMMON="$CXXFLAGS_COMMON -O0 -g -DDEBUG"
fi
AC_SUBST([CXXFLAGS_COMMON])

# Output
AC_CONFIG_FILES([Makefile])
AC_OUTPUT