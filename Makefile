# htgen

PROJ=htgen
CC=gcc
CFLAGS=
LDFLAGS=

SRC = htgen.c

all: $(PROJ)

$(PROJ): 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC)
	
clean:
	rm -f $(PROJ)
	

