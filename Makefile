CC = gcc
CFLAGS = -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces

# Use raylib from the local directory
RAYLIB_PATH = raylib
INCLUDES = -I$(RAYLIB_PATH)/src
LDFLAGS = -L$(RAYLIB_PATH)/src -lraylib -lm -lpthread -ldl -lrt -lX11

SOURCES = julia_set.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = julia_set

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) check_raylib
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

check_raylib:
	@if [ ! -f "$(RAYLIB_PATH)/src/libraylib.a" ]; then \
		echo "Error: raylib library not found at $(RAYLIB_PATH)/src/libraylib.a"; \
		echo "Please build raylib first:"; \
		echo "cd $(RAYLIB_PATH)/src && make PLATFORM=PLATFORM_DESKTOP"; \
		exit 1; \
	fi

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean check_raylib
