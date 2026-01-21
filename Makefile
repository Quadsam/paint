CFLAGS  += `pkg-config --cflags sdl2` -Wall -Wextra -Werror -pedantic -ggdb 
LDFLAGS += `pkg-config --libs-only-other sdl2`
LDLIBS  += `pkg-config --libs-only-l sdl2` -lm

all: paint

clean:
	$(RM) -v paint *.o

splint: paint.c
	splint +matchanyintegral $^

paint: paint.o
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^

paint.o: paint.c
	$(CC) $(CFLAGS) -c -o $@ $^
