check_PROGRAMS=tpbuff_ut

TESTS=tpbuff_ut

nodist_tpbuff_ut_SOURCES=test.tpp.cpp\
						 conf_common.tpp.cpp

tpbuff_ut_SOURCES=test.cpp


tpbuff_ut_CPPFLAGS = -I$(top_builddir)/src/tpbuff
tpbuff_ut_LDADD=$(top_builddir)/src/tpbuff/.libs/libtpbuff.a

$(tpbuff_ut_SOURCES: .cpp=.o): test.tpp.cpp

test.tpp.cpp: test.tpp
	$(top_builddir)/src/tpp/tpp --cppout=. test.tpp

clean-local:
	@-rm test.tpp.*
