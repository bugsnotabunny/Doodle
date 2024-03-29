CXX  = g++
ODIR = out
SDIR = src
IDIR = include
EXE = doodle

INCLUDE = -I$(IDIR)
WARNINGS = -Wall -Wextra -Wold-style-cast
CXXFLAGS = -g -std=c++17 $(WARNINGS) $(INCLUDE)

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRCS = $(shell find . -name "*.cpp")
OBJS = $(SRCS:%.cpp=%.o)
DEPS = $(OBJS:%.o=%.d)

$(EXE) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

$(ODIR)/% : $(SDIR)/%.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $< $(CFLAGS)

-include $(DEPS)

.PHONY : clean compile-commands
clean :
	-rm $(DEPS) $(OBJS) $(EXE)

compile-commands :
	make clean
	bear -- make $(EXE)

all : $(EXE)
