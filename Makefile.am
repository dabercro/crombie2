bindir = $(srcdir)/bin

allsrcs = \
	$(srcdir)/src/ConfigModel.cpp \
	$(srcdir)/src/ConfigPage.cpp \
	$(srcdir)/src/ConfigTable.cpp \
	$(srcdir)/src/Configurable.cpp \
	$(srcdir)/src/Controller.cpp \
	$(srcdir)/src/Cut.cpp \
	$(srcdir)/src/CutController.cpp \
	$(srcdir)/src/CutModel.cpp \
	$(srcdir)/src/CutString.cpp \
	$(srcdir)/src/FileSystem.cpp \
	$(srcdir)/src/GlobalController.cpp \
	$(srcdir)/src/GlobalModel.cpp \
	$(srcdir)/src/MainController.cpp \
	$(srcdir)/src/MainWindow.cpp \
	$(srcdir)/src/MiniCutController.cpp \
	$(srcdir)/src/Misc.cpp \
	$(srcdir)/src/Parse.cpp \
	$(srcdir)/src/PlotController.cpp \
	$(srcdir)/src/PlotModel.cpp

AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = crombie2 crombie2catch

crombie2_SOURCES = $(allsrcs) \
	$(srcdir)/src/main.cpp

crombie2catch_SOURCES = $(allsrcs) \
	$(srcdir)/test/test_configurable.cpp \
	$(srcdir)/test/test_parser.cpp \
	$(srcdir)/test/test_testconfig.cpp \
	$(srcdir)/test/utils.cpp \
	$(srcdir)/test/main.cpp

AM_CPPFLAGS = @GTK_CFLAGS@ -I$(srcdir)/include -std=c++17 \
	`root-config --cflags | sed s/-std=c++11//`
AM_LDFLAGS = @GTK_LIBS@ \
	`root-config --libs --ldflags`
