# Check if clang is installed
CLANG_INSTALLED := $(shell command -v clang 2> /dev/null)

# If clang is installed (CLANG_INSTALLED variable is not empty),
# use it as the compiler, otherwise, default to gcc
ifeq ($(strip $(CLANG_INSTALLED)),)
    CC := gcc
else
    CC := clang
endif

CFLAGS = -Wall -Wextra -pedantic -g -O2

SRCS = game.c fetch_text.c text_helpers.c
OBJS = $(SRCS:.c=.o)
TARGET = game

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) -lncurses

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)