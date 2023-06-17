CC = g++
CFLAGS = -std=c++11 -Wall -I./include
SRCDIR = src
BUILDDIR = build

SRCS = $(SRCDIR)/entidadebase.cpp $(SRCDIR)/acervo.cpp $(SRCDIR)/adm.cpp $(SRCDIR)/livro.cpp $(SRCDIR)/usuario.cpp
OBJDIR = $(BUILDDIR)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

MAIN = main.cpp
TARGET = biblioteca

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR) $(TARGET)
