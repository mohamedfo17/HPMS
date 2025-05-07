# Compiler and flags
CC = gcc
CFLAGS = -g -Iheaders

# Source files
SRC = main.c \
      src/departments.c \
      src/doctors.c \
      src/hospital.c \
      src/nav.c \
      src/patients.c \
      src/treeDoc.c \
      src/treePat.c

# Output
OUT = main.exe

# Build target
all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

# Clean build artifacts
clean:
	del /Q $(OUT)
