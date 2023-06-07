CXX  = g++
ODIR = out
SDIR = src
IDIR = include

INCLUDE = -I$(IDIR)
WARNINGS = -Wall -Wextra -Wold-style-cast
CXXFLAGS = -g -std=c++17 $(WARNINGS) $(INCLUDE)

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system


SRCS = $(wildcard $(SDIR)/*.cpp)
HDRS = $(wildcard $(IDIR)/*.hpp)
OBJS = $(SRCS:%.cpp=%.o)
DEPS = $(OBJS:%.o=%.d)

doodle.exe : $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

$(ODIR)/% : $(SDIR)/%.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $< $(CFLAGS)

-include $(DEPS)

.PHONY : clean
clean : 
	-rm $(DEPS) $(OBJS) doodle.exe
