
TARGET_LIB=libstrut.so

CFLAGS= -fPIC -Wall -Wextra -g
LDFLAGS= -shared

OBJECTS=$(patsubst %.c, %.o, $(wildcard *.c))
HEADERS=$(wildcard *.h)

all: $(TARGET_LIB)


%.o: %.c $(HEADERS)


$(TARGET_LIB): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(TARGET_LIB) $(OBJECTS)

