CC = g++
CFLAGS = -std=c++20 -Wall -I./include -I./third_party
SRCDIR = src
TESTDIR = tests
OBJDIR = build
BINDIR = bin

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)%.cpp,$(OBJDIR)%.o,$(SRCS))
MAIN = program/main.cpp
TARGET = bin/biblioteca

TEST_SRCS = $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJS = $(patsubst $(TESTDIR)%.cpp,$(OBJDIR)%.o,$(TEST_SRCS))
TEST_MAIN = program/tester.cpp
TEST_TARGET = bin/test

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ -lsqlite3

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_TARGET)

$(TEST_TARGET): $(OBJS) $(TEST_OBJS) $(TEST_MAIN)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ -lsqlite3

clean:
	rm -rf $(OBJDIR)/*.o $(TARGET) $(TEST_TARGET)
