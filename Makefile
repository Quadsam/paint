CFLAGS  += `pkg-config --cflags sdl2` -Wall -Wextra -Werror -pedantic -ggdb 
LDFLAGS += `pkg-config --libs-only-other sdl2`
LDLIBS  += `pkg-config --libs-only-l sdl2` -lm
PREFIX  := /usr/local


all: paint

install: paint
	install -Dvm755 $^ $(DESTDIR)$(PREFIX)/bin/$^
	strip $(DESTDIR)$(PREFIX)/bin/$^

clean:
	$(RM) -fv paint *.o dist/

paint: paint.o
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^

paint.o: paint.c
	$(CC) $(CFLAGS) -c -o $@ $^
