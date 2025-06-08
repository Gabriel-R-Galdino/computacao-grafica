# O executável será gerado na pasta build/
# Detecta o sistema operacional
UNAME_S := $(shell uname -s)

# Compilador e flags
CC = gcc
CFLAGS = -Wall

# Bibliotecas por sistema
ifeq ($(UNAME_S), Linux)
    LIBS = -lGL -lGLU -lglut -lm
    RM = rm -f
    EXE_EXT =
else ifeq ($(OS), Windows_NT)
    LIBS = -lfreeglut -lglu32 -lopengl32
    RM = rm -f
    EXE_EXT = .exe
endif

# Arquivos
TARGET = main
SRC = main.c
BUILD_DIR = build
BIN = $(BUILD_DIR)/$(TARGET)$(EXE_EXT)

# Targets
all: $(BUILD_DIR) $(BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN) $(LIBS)

run: all
	./$(BIN)

clean:
	$(RM) $(BIN)

