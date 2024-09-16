CXX=g++
CFLAGS=-g -Wall -Wno-deprecated
SRC=src
SRCS=$(wildcard $(SRC)/*.cc)

BINDIR=bin
BIN=$(BINDIR)/pomodoro

all:$(BIN)

$(BIN): $(SRCS)
	$(CXX) $(CFLAGS) $(SRCS) -o $@

clean:
	rm -r $(BINDIR)/* 
