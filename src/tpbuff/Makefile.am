lib_LTLIBRARIES=libtpbuff.la

libtpbuff_la_SOURCES=tpb_binarchive.cpp\
					 tpb_command.cpp\
					 tpb_tpbuff.cpp

libtpbuff_la_LDFLAGS = -version-info 1:0:0 $(AM_LDFLAGS)

libtpbuffincdir = @includedir@/tm
libtpbuffinc_HEADERS =  tpb_binarchive.h\
						   tpb_command.h\
						   tpb_inputarchive.h\
						   tpb_outputarchive.h\
						   tpb_tpbuff.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = tpbuff.pc

EXTRA_DIST = tpbuff.pc.in

