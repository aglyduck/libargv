AUTOMAKE_OPTIONS=foreign

lib_LIBRARIES=libargv.a
libargv_a_SOURCES=argvlib.c strtok_r.c estrtok_r.c

include_HEADERS=argv.h

noinst_PROGRAMS=atest
atest_SOURCES=atest.cpp #argvlib.c strtok_r.c
atest_LDADD=libargv.a