CC = g++
CFLAGS = -std=c++20 -Wall -I./include -I./third_party -I./third_party/sqlite_modern_cpp -I./third_party/sqlite_modern_cpp/lists -I./third_party/sqlite_modern_cpp/utility
SRCDIR = src
TESTDIR = tests
OBJDIR = build
BINDIR = bin

SRCS = adm.cpp bibliotecario.cpp coluna_sql.cpp db_acervo.cpp db_administradores.cpp db_usuarios.cpp entidadebase.cpp livro.cpp usuario.cpp
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))
MAIN = program/main.cpp
TARGET = biblioteca

TEST_SRCS = $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJS = $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.o,$(TEST_SRCS))
TEST_TARGET = test

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN)
	$(CC) $(CFLAGS) -o $@ $^ -lsqlite3

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_TARGET)

$(TEST_TARGET): $(OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lsqlite3

clean:
	rm -rf $(OBJDIR)/*.o $(TARGET) $(TEST_TARGET)
