CC := gcc
CFLAGS := -O3

C_FILES := $(wildcard *.c)
H_FILES := $(wildcard *.h)

.PHONY: all clean

all: wappysav
	@:

wappysav: $(C_FILES) $(H_FILES)
	$(CC) $(CFLAGS) $(C_FILES) -o wappysav

clean:
	$(RM) wappysav
