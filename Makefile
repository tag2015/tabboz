# TABBOZ-NG MAKEFILE PRINCIPALE

# Rileva OS
ifeq ($(OS),Windows_NT)     # Windows_NT su XP, 2000, 7, Vista, 10...
    DETECTED_OS := WIN
else
    DETECTED_OS := $(shell uname)  # Unix-like
endif

.PHONY: gui
.SILENT: gui all

GUI_DIR = gui

CPPFILES = $(wildcard *.cpp)
OBJFILES = $(CPPFILES:.cpp=.o)
GUIOBJFILES = $(wildcard $(GUI_DIR)/*.o )

COMPILER = $(shell fltk-config  --use-images --cxx --cxxflags --optim)
LINK = $(shell fltk-config  --use-images --ldstaticflags)
ifeq ($(DETECTED_OS),WIN)   #per i suoni
	LINK += -lwinmm
endif
# static build
COMPILER += -static -static-libgcc -static-libstdc++

POSTBUILD = fltk-config --post # Required on OSX, does nothing on other platforms

all: common gui
	echo;
	echo "Run 'make tabbozng' to build executable"

common:	$(OBJFILES)

%.o: %.cpp
	$(COMPILER) -c $< -o $@

gui:
	echo;
	echo "=== making gui ===";
	(cd $(GUI_DIR); $(MAKE) $(MFLAGS)) || exit 1;

clean:
	rm *.o

tabbozng: $(OBJFILES) $(GUIOBJFILES)
	$(COMPILER) $^ $(LINK) -o $@
	$(POSTBUILD) $@