CC=g++
CFLAGS=-Wall -std=c++11
DEPS = BinaryImageProcessor.h uandf.h
OBJ = BinaryImageProcessor.o uandf.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

BinaryImageProcessor: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o BinaryImageProcessor

run: BinaryImageProcessor
	./BinaryImageProcessor < infile

.PHONY: clean run


# make run: to run on terminal
# make clean run: to clean first then run on terminal