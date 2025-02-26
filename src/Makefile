#: -g for debug, -O3 for optimization

CFLAGS = -g -O3



# Default target

all: uimain


# Object file dependencies

tokenizer.o: tokenizer.h

history.o: history.h

#tester.o: tokenizer.h history.h



# Build the tester executable

uimain: tokenizer.o history.o uimain.o

	cc -o $@ $^ $(CFLAGS)



# Clean generated files

clean:

	rm -f *.o uimain

