bindir = $(srcdir)/bin

cutsrcs = \
	$(srcdir)/src/ConfigModel.cpp \
	$(srcdir)/src/ConfigTable.cpp \
	$(srcdir)/src/Cut.cpp \
	$(srcdir)/src/CutModel.cpp \
	$(srcdir)/src/CutString.cpp \
	$(srcdir)/src/FileSystem.cpp \
	$(srcdir)/src/GuiConfigurable.cpp \
	$(srcdir)/src/JoinerConfigurable.cpp \
	$(srcdir)/src/Misc.cpp \
	$(srcdir)/src/Parse.cpp \
	$(srcdir)/src/Selection.cpp \
	$(srcdir)/src/TextConfigurable.cpp

allsrcs = $(cutsrcs) \
	$(srcdir)/src/AllController.cpp \
	$(srcdir)/src/AllModels.cpp \
	$(srcdir)/src/BoolConfigurable.cpp \
	$(srcdir)/src/ConfigPage.cpp \
	$(srcdir)/src/Controller.cpp \
	$(srcdir)/src/CrossSecDB.cpp \
	$(srcdir)/src/CutController.cpp \
	$(srcdir)/src/CutflowAnalyzer.cpp \
	$(srcdir)/src/CutflowAnalyzerMaster.cpp \
	$(srcdir)/src/DatacardController.cpp \
	$(srcdir)/src/DatacardModel.cpp \
	$(srcdir)/src/FileController.cpp \
	$(srcdir)/src/FileEntry.cpp \
	$(srcdir)/src/FileModel.cpp \
	$(srcdir)/src/FitConfig.cpp \
	$(srcdir)/src/FlatUncertainty.cpp \
	$(srcdir)/src/GlobalModel.cpp \
	$(srcdir)/src/Hist.cpp \
	$(srcdir)/src/Hist2D.cpp \
	$(srcdir)/src/HistAnalysis.cpp \
	$(srcdir)/src/HistAnalyzer.cpp \
	$(srcdir)/src/HistAnalyzerMaster.cpp \
	$(srcdir)/src/HistModel.cpp \
	$(srcdir)/src/HistSplit.cpp \
	$(srcdir)/src/Job.cpp \
	$(srcdir)/src/JobSorter.cpp \
	$(srcdir)/src/JSONAnalyzerMaster.cpp \
	$(srcdir)/src/JSONAnalyzer.cpp \
	$(srcdir)/src/JSONModel.cpp \
	$(srcdir)/src/Lock.cpp \
	$(srcdir)/src/LumiSelection.cpp \
	$(srcdir)/src/MainController.cpp \
	$(srcdir)/src/MainWindow.cpp \
	$(srcdir)/src/MiniCutController.cpp \
	$(srcdir)/src/MiniFileController.cpp \
	$(srcdir)/src/MiniFitController.cpp \
	$(srcdir)/src/OnTheFlyModel.cpp \
	$(srcdir)/src/OnTheFlyReweighter.cpp \
	$(srcdir)/src/Plot.cpp \
	$(srcdir)/src/PlotModel.cpp \
	$(srcdir)/src/PlotStyleModel.cpp \
	$(srcdir)/src/Progress.cpp \
	$(srcdir)/src/RateParams.cpp \
	$(srcdir)/src/ReweightModel.cpp \
	$(srcdir)/src/ReweightReader.cpp \
	$(srcdir)/src/Runner.cpp \
	$(srcdir)/src/SelectionDisplay.cpp \
	$(srcdir)/src/SimpleController.cpp \
	$(srcdir)/src/SimpleModel.cpp \
	$(srcdir)/src/Tree.cpp

AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = crombie2 crombie2catch crombie2cut

crombie2_SOURCES = $(allsrcs) \
	$(srcdir)/src/main.cpp

crombie2catch_SOURCES = $(allsrcs) \
	$(srcdir)/test/test_configurable.cpp \
	$(srcdir)/test/test_cutstring.cpp \
	$(srcdir)/test/test_datacardmodel.cpp \
	$(srcdir)/test/test_fileentry.cpp \
	$(srcdir)/test/test_filemodel.cpp \
	$(srcdir)/test/test_fit.cpp \
	$(srcdir)/test/test_hist.cpp \
	$(srcdir)/test/test_lumiselection.cpp \
	$(srcdir)/test/test_misc.cpp \
	$(srcdir)/test/test_parser.cpp \
	$(srcdir)/test/test_simplemodel.cpp \
	$(srcdir)/test/test_shell.cpp \
	$(srcdir)/test/test_testconfig.cpp \
	$(srcdir)/test/utils.cpp \
	$(srcdir)/test/main.cpp

crombie2cut_SOURCES = $(cutsrcs) \
	$(srcdir)/src/crombie2cut.cpp

AM_CPPFLAGS = @GTK_CFLAGS@ -I$(srcdir)/include -std=c++17 \
	`root-config --cflags | sed s/-std=c++11//`
AM_LDFLAGS = @GTK_LIBS@ \
	`root-config --libs --ldflags`
