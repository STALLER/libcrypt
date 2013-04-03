EXEC=$(wildcard *.cpp)
OBJECT=$(patsubst %.cpp,%.o,$(EXEC))
EX=crypt

CC=g++
CFLAGS=-I. -std=c++0x

.PHONY: clean all cleanall

all: $(EX)
	
$(EX): $(OBJECT)
	$(CC) $(OBJECT) -o $(EX)

%.o: %.cpp %.h
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f *.o

cleanall: clean
	rm -f $(EX)
