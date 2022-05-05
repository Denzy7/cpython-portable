/* -*- C -*- ***********************************************
Copyright (c) 2000, BeOpen.com.
Copyright (c) 1995-2000, Corporation for National Research Initiatives.
Copyright (c) 1990-1995, Stichting Mathematisch Centrum.
All rights reserved.

See the file "Misc/COPYRIGHT" for information on usage and
redistribution of this file, and for a DISCLAIMER OF ALL WARRANTIES.
******************************************************************/

/* Module configuration */

/* !!! !!! !!! This file is edited by the makesetup script !!! !!! !!! */

/* This file contains the table of built-in modules.
   See create_builtin() in import.c. */

/*
 * plaform agnostic config.c, works with just about anything
 */

#include "Python.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32) || defined (__MINGW32__)
extern PyObject* PyInit_nt(void);
extern PyObject* PyInit_winreg(void);
extern PyObject* PyInit__winapi(void);
#else
extern PyObject* PyInit_posix(void);
extern PyObject* PyInit__posixsubprocess(void);
#ifdef HAVE_LIBREADLINE
extern PyObject* PyInit_readline(void);
#endif
#endif

extern PyObject* PyInit__signal(void);
extern PyObject* PyInit_faulthandler(void);
extern PyObject* PyInit__peg_parser(void);
extern PyObject* PyInit__thread(void);
extern PyObject* PyInit__weakref(void);
extern PyObject* PyInit__io(void);
extern PyObject* PyInit__codecs(void);

//Extra mods
extern PyObject* PyInit_itertools(void);
extern PyObject* PyInit__collections(void);
extern PyObject* PyInit__sre(void);
extern PyObject* PyInit_math(void);
extern PyObject* PyInit_atexit(void);
extern PyObject* PyInit_time(void);
#ifdef HAVE_LIBZ
// to deflate bootstrap.zip
extern PyObject* PyInit_zlib(void);
#endif

//stdlibs
extern PyObject* PyInit__blake2(void);
extern PyObject* PyInit__md5(void);
extern PyObject* PyInit__sha1(void);
extern PyObject* PyInit__sha256(void);
extern PyObject* PyInit__sha512(void);
extern PyObject* PyInit__sha3(void);
extern PyObject* PyInit_errno(void);
extern PyObject* PyInit_select(void);
extern PyObject* PyInit__struct(void);
extern PyObject* PyInit_binascii(void);
extern PyObject* PyInit__csv(void);
extern PyObject* PyInit__datetime(void);
extern PyObject* PyInit__heapq(void);
extern PyObject* PyInit__json(void);
extern PyObject* PyInit__socket(void);
extern PyObject* PyInit_array(void);
#ifdef HAVE_LIBSQLITE3
extern PyObject* PyInit__sqlite3(void);
#endif
//#ifdef HAVE_LIBFFI
//extern PyObject* PyInit__ctypes(void);
//#endif

/* -- ADDMODULE MARKER 1 -- */

extern PyObject* PyMarshal_Init(void);
extern PyObject* PyInit__imp(void);
extern PyObject* PyInit_gc(void);
extern PyObject* PyInit__ast(void);
extern PyObject* _PyWarnings_Init(void);

extern PyObject* PyInit__string(void);

struct _inittab _PyImport_Inittab[] = {

    #if defined(_WIN32) || defined (__MINGW32__)
    {"nt", PyInit_nt},
    {"_winapi", PyInit__winapi},
    {"winreg", PyInit_winreg},
    #else
    {"posix", PyInit_posix},
    {"_posixsubprocess", PyInit__posixsubprocess},
    #ifdef HAVE_LIBREADLINE
    {"readline", PyInit_readline},
    #endif

    #endif

    {"_signal", PyInit__signal},
    {"faulthandler", PyInit_faulthandler},
    {"_peg_parser", PyInit__peg_parser},
    {"_thread", PyInit__thread},
    {"_weakref", PyInit__weakref},
    {"_io", PyInit__io},
    {"_codecs", PyInit__codecs},

    //Extra mods
    {"itertools", PyInit_itertools},
    {"_collections", PyInit__collections},
    {"_sre", PyInit__sre},
    {"math", PyInit_math},
    {"atexit", PyInit_atexit},
    {"time", PyInit_time},
    #ifdef HAVE_LIBZ
    {"zlib", PyInit_zlib},
    #endif

    //stdlib

    {"_blake2", PyInit__blake2},
    {"_md5", PyInit__md5},
    {"_sha1", PyInit__sha1},
    {"_sha256", PyInit__sha256},
    {"_sha3", PyInit__sha3},
    {"_sha512", PyInit__sha512},
    {"errno", PyInit_errno},
    {"select", PyInit_select},
    {"_struct", PyInit__struct},
    {"binascii", PyInit_binascii},
    {"_csv", PyInit__csv},
    {"_datetime", PyInit__datetime},
    {"_heapq", PyInit__heapq},
    {"_json", PyInit__json},
    {"_socket", PyInit__socket},
    {"array", PyInit_array},
    #ifdef HAVE_LIBSQLITE3
    {"_sqlite3",PyInit__sqlite3},
    #endif

//    #ifdef HAVE_LIBFFI
//    {"_ctypes", PyInit__ctypes},
//    #endif


/* -- ADDMODULE MARKER 2 -- */


    /* This module lives in marshal.c */
    {"marshal", PyMarshal_Init},

    /* This lives in import.c */
    {"_imp", PyInit__imp},

    /* This lives in Python/Python-ast.c */
    {"_ast", PyInit__ast},

    /* These entries are here for sys.builtin_module_names */
    {"builtins", NULL},
    {"sys", NULL},

    /* This lives in gcmodule.c */
    {"gc", PyInit_gc},

    /* This lives in _warnings.c */
    {"_warnings", _PyWarnings_Init},

    /* This lives in Objects/unicodeobject.c */
    {"_string", PyInit__string},

    /* Sentinel */
    {0, 0}
};
#ifdef __cplusplus
}
#endif
