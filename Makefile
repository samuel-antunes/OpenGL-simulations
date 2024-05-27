CC=gcc
CFLAGS=-Iinclude -O2
LDFLAGS=-lGL -lGLU -lglut -lm

# Define the sources and the target
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
TARGET=nbody_simulator

# Default rule to build the program
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Generic rule for compiling C files to object files
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Rule to clean the build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Rule to run the program
run: $(TARGET)
	./$(TARGET)

