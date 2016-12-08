INC_DIR=../inc

all: main.x

main.x: main.o
	$(CXX) $^ -o $@

main.o: main.cxx
	$(CXX) -I$(INC_DIR) $^ -c -o $@

.PHONY: clean

clean:
	rm *.o main
