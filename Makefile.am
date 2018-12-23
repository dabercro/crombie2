bindir = $(srcdir)/bin
testsrcs = \
	$(srcdir)/src/FileSystem.cpp \
	$(srcdir)/src/Parse.cpp \
	$(srcdir)/src/Configurable.cpp \
	$(srcdir)/src/ConfigModel.cpp \
	$(srcdir)/src/Cut.cpp \
	$(srcdir)/src/Misc.cpp

allsrcs = \
	$(srcdir)/src/ConfigPage.cpp \
	$(srcdir)/src/ConfigTable.cpp \
	$(srcdir)/src/Controller.cpp \
	$(srcdir)/src/GlobalController.cpp \
	$(srcdir)/src/GlobalModel.cpp \
	$(srcdir)/src/MainController.cpp \
	$(srcdir)/src/MainWindow.cpp \
	$(srcdir)/src/UpdateBox.cpp \
	$(srcdir)/src/main.cpp

AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = crombie2 crombie2catch

crombie2_SOURCES = $(testsrcs) $(allsrcs)

crombie2catch_SOURCES = $(testsrcs) \
	$(srcdir)/test/test_parser.cpp \
	$(srcdir)/test/test_configurable.cpp \
	$(srcdir)/test/test_testconfig.cpp \
	$(srcdir)/test/main.cpp

AM_CPPFLAGS = @GTK_CFLAGS@ -I$(srcdir)/include -std=c++17 \
	`root-config --cflags | sed s/-std=c++11//`
AM_LDFLAGS = @GTK_LIBS@ \
	`root-config --libs --ldflags`
