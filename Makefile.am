bindir = $(srcdir)/bin
allsrcs = \
	$(srcdir)/src/ConfigModel.cpp \
	$(srcdir)/src/FileSystem.cpp \
	$(srcdir)/src/Parse.cpp \
	$(srcdir)/src/Cut.cpp \
	$(srcdir)/src/Configurable.cpp \
	$(srcdir)/src/Misc.cpp

AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = testgui testcrombie2

testgui_SOURCES = $(srcdir)/src/helloworld.cpp $(srcdir)/src/main.cpp
testcrombie2_SOURCES = $(allsrcs) $(srcdir)/test/main.cpp

AM_CPPFLAGS = @GTK_CFLAGS@ -I$(srcdir)/include -std=c++17 \
	`root-config --cflags | sed s/-std=c++11//`
AM_LDFLAGS = @GTK_LIBS@ \
	`root-config --libs --ldflags`
