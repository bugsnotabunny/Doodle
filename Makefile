CC = /usr/bin/x86_64-pc-linux-gnu-g++
ODIR = out
SDIR = src

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

CXXFLAGS = -g -Wall -Wextra -Wold-style-cast -std=c++17

_OBJS = $(wildcard $(SDIR)/*.cpp)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $< $(CFLAGS)

.PHONY: all

all: $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(_OBJS))
	$(CC) $(CXXFLAGS) -o $(ODIR)/main.exe $(ODIR)/*.o $(LIBS)

clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.exe
