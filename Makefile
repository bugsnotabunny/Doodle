CC = g++
ODIR = out
SDIR = src

CXXFLAGS = -g -Wall -Wextra -Wold-style-cast -std=c++17

_OBJS = $(wildcard $(SDIR)/*.cpp)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: all

all: $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(_OBJS))

clean:
	echo $(OBJS)
	rm -f $(ODIR)/*.o