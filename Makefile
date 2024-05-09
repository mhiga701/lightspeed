CC	:= gcc
CFLAGS	:= -W -Wall -g

TARGETS  := ardread readsend writevals
SRCFILES := $(wildcard *.c)
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES))

CONV_IMGS := rainbow

.PHONY: all clean 

all: $(TARGETS) $(CONV_IMGS)

$(TARGETS):
	$(CC) $@.c $(CFLAGS)

$(CONV_IMGS):
	input=$@.jpg runipy coordinates.ipynb
	./hex.sh polar_$@.txt polar_$@.hex

clean:
	rm -f *~ *.o *.txt *_resized.jpg *.hex $(TARGETS)
