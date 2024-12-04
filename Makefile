CC = clang
OUTDIR = bin

FNAME = $(filename)
ifeq ($(filename),)
FNAME := $(day)
endif

SOURCE = src/$(day)/$(FNAME).c src/io.c

build:
	$(CC) $(SOURCE) -o $(OUTDIR)/$(day)

run: build
	./bin/$(day)

clean:
	rm -rf bin/*
