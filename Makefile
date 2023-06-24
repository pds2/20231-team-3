CC = g++
CFLAGS = -std=c++17 -Wall -I./include -I./third-party -I./third-party/sqlite_modern_cpp -lsqlite3
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