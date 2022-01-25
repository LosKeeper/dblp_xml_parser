CC ?= gcc
CFLAGS ?= -Wall -Wextra -Werror -g -fprofile-arcs -ftest-coverage -fno-stack-protector
LDLIBS=-lm

INCLUDE_PATH = ../include

TARGET   = tests

SRCDIR   = ../src
OBJDIR   = ../obj

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.h)
OBJECTS0  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJECTS = $(filter-out $(OBJDIR)/dblp-parsing.o,$(OBJECTS0))



tests: $(OBJECTS) ../obj/tests.o

	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "Linking complete!"



$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)

../obj/tests.o: tests.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)


.PHONY: clean cov
clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/*.gcda
	rm -f $(OBJDIR)/*.gcno
	rm -f $(BINDIR)/$(TARGET)
