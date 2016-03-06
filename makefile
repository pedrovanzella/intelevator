CPP      := clang++
CFLAGS   := -Wall -Werror -Wpedantic -std=c++11
SRCDIR   := src
BUILDDIR := build
TARGET   := bin/intelevator

SRCEXT   := cpp
SOURCES  := $(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS  := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
LIB      := -pthread
INC      := -I include

$(TARGET) : $(OBJECTS)
	@echo " Linking..."
	@echo " $(CPP) $^ -o $(TARGET) $(LIB)"; $(CPP) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CPP) $(CFLAGS) $(INC) -c -o $@ $<"; $(CPP) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)
