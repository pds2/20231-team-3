CC = g++
CFLAGS = -std=c++17 -Wall -I./include -I./third_party 
SRCDIR = src
TESTDIR = tests
BUILDDIR = build

SRCS = $(SRCDIR)/entidadebase.cpp $(SRCDIR)/bibliotecario.cpp $(SRCDIR)/acervo.cpp $(SRCDIR)/adm.cpp $(SRCDIR)/livro.cpp $(SRCDIR)/usuario.cpp
TEST_SRCS = $(TESTDIR)/teste_code.cpp
OBJDIR = $(BUILDDIR)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
TEST_OBJS = $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.o,$(TEST_SRCS))

MAIN = main.cpp
TARGET = biblioteca
TEST_TARGET = test

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(TEST_TARGET)

$(TEST_TARGET): $(OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR) $(TARGET) $(TEST_TARGET)
