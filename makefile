CPP      := clang++
CXXFLAGS := -Wall -Werror -Wpedantic -std=c++11
SRCDIR   := src
BUILDDIR := build
TARGET   := bin/intelevator

SRCEXT   := cpp
SOURCES  := $(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS  := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
LIB      := ""
INC      := -I include

$(TARGET) : $(OBJECTS)
	@echo " Linking..."
	@echo " $(CPP) $(CXXFLAGS) $^ -o $(TARGET) $(LIB)"; $(CPP) $(CXXFLAGS) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CPP) $(CXXFLAGS) $(INC) -c -o $@ $<"; $(CPP) $(CXXFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)
