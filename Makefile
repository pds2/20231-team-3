CC = g++
CFLAGS = -std=c++20 -Wall -I./include -I./third_party -I./third_party/sqlite_modern_cpp -I./third_party/sqlite_modern_cpp/lists -I./third_party/sqlite_modern_cpp/utility
SRCDIR = src
TESTDIR = tests
BUILDDIR = build
BINDIR = bin

SRCS = $(wildcard $(SRCDIR)/.cpp)
TEST_SRCS = $(wildcard $(TESTDIR)/.cpp)
OBJDIR = $(BUILDDIR)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
TEST_OBJS = $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.o,$(TEST_SRCS))
MAIN = main.cpp
TARGET = biblioteca
TEST_TARGET = test

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN)
    $(CC) $(CFLAGS) -o $@ $^ -lsqlite3

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
    @mkdir -p $(OBJDIR)
    $(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/entidadebase.o: $(SRCDIR)/entidadebase.cpp $(SRCDIR)/livro.hpp $(SRCDIR)/db_acervo.hpp
    @mkdir -p $(OBJDIR)
    $(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/bibliotecario.o: $(SRCDIR)/bibliotecario.cpp $(SRCDIR)/entidadebase.hpp $(SRCDIR)/usuario.hpp
    @mkdir -p $(OBJDIR)
    $(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_TARGET)

$(TEST_TARGET): $(OBJS) $(TEST_OBJS)
    $(CC) $(CFLAGS) -o $@ $^ -lsqlite3

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
    @mkdir -p $(OBJDIR)
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -rf $(BUILDDIR) $(TARGET) $(TEST_TARGET)