CXX      := clang++
CXXFLAGS := -Wall -Werror -Wpedantic -std=c++11 -Wno-unused-function
SRCDIR   := src
BUILDDIR := build
TARGET   := bin/intelevator

SRCEXT   := cpp
SOURCES  := $(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS  := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
LIB      := -L/usr/local/lib/ -lyaml-cpp -lglog
INC      := -I include

TEST     := $(TARGET)-test
TDIR     := test
TSOURCES := $(wildcard $(TDIR)/*.$(SRCEXT))
TOBJECTS := $(patsubst $(TDIR)/%,$(BUILDDIR)/%,$(TSOURCES:.$(SRCEXT)=.o))
TLIB     := $(LIB) -lgtest -lgtest_main

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CXX) $(CXXFLAGS) $(LIB) $^ -o $(TARGET)"; $(CXX) $(CXXFLAGS) $(LIB) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<"; $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)/%.o: $(TDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<"; $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

$(TEST): $(filter-out $(BUILDDIR)/main.o, $(OBJECTS)) $(TOBJECTS)
	@echo " Linking tests..."
	@echo " $(CXX) $(CXXFLAGS) $(TLIB) $(INC) $^ -o $(TEST)"; $(CXX) $(CXXFLAGS) $(TLIB) $(INC) $^ -o $(TEST)

test: $(TEST)
	./$(TEST)

run: $(TARGET)
	./$(TARGET)

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET) $(TEST)"; $(RM) -r $(BUILDDIR) $(TARGET) $(TEST)

rebuild: clean $(TARGET) $(TEST)