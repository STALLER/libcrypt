EXEC=$(wildcard *.cpp)
OBJECT=$(patsubst %.cpp,%.o,$(EXEC))
EX=crypt

CC=g++
INCLUDE_DIR=includes
CFLAGS=-I$(INCLUDE_DIR)/ -std=c++0x

.PHONY: clean all cleanall

all: $(EX)
	
$(EX): $(OBJECT)
	$(CC) $(OBJECT) -o $(EX)

%.o: %.cpp $(INCLUDE_DIR)/%.h
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f *.o

cleanall: clean
	rm -f $(EX)
