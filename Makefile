CC = clang
OUTDIR = bin
SOURCE = src/$(day)/$(day).c src/io.c

build:
	$(CC) $(SOURCE) -o $(OUTDIR)/$(day)

run: build
	./bin/$(day)

clean:
	rm -rf bin/*
