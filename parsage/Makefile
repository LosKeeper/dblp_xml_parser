CC ?= gcc
CFLAGS ?= -Wall

tests : tests.o xmlp.o
	$(CC) $(CFLAGS) -o tests tests.o xmlp.o -g

xmlp.o : xmlp.h xmlp.c
	$(CC) $(CFLAGS) -o xmlp.o -c xmlp.c -g

tests.o : tests.c
	$(CC) $(CFLAGS) -o tests.o -c tests.c -g

parsage_test : parsage_test.c
	$(CC) $(CFLAGS) -o parsage_test parsage_test.c

clean:
	rm -fr *.o
	rm -f tests
	rm -f parsage_test