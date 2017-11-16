noinst_LTLIBRARIES=libtpp.la

libtpp_la_SOURCES=tp_symbol_list.c\
			 tp_cxx_generator.c\
			 tp_java_generator.c\
				   flex_tp.l\
				   bison_tp.y

bin_PROGRAMS=tpp
tpp_SOURCES=tpp.c
tpp_LDADD=libtpp.la

BUILT_SOURCES=bison_tp.h
AM_YFLAGS=-d
AM_LFLAGS = -olex.yy.c

clean-local:
	rm *.o bison_tp.c bison_tp.h flex_tp.c
