# TABBOZ-NG MAKEFILE PER GUI

CPPFILES = $(wildcard *.cpp)
OBJFILES = $(CPPFILES:.cpp=.o)
COMPILER = $(shell fltk-config  --use-images --cxx --cxxflags --optim)

all: $(OBJFILES)

%.o: %.cpp
	$(COMPILER) -c $< -o $@

clean:
	rm *.o