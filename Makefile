CXX=g++
CFLAGS=-g -Wall -Wno-deprecated
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.cc)
OBJS=$(patsubst $(SRC)/%.cc, $(OBJ)/%.o, $(SRCS))

BINDIR=bin
BIN=$(BINDIR)/pomodoro

all:$(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.cc
	$(CXX) $(CFLAGS) -c $^ -o $@

clean:
	rm -r $(BINDIR)/* $(OBJ)/*
