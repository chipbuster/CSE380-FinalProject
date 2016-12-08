INC_DIR=../include

LDFLAGS=-L$(TACC_GRVY_LIB) -lgrvy

all: main.x

main.x: main.o progopt.o
	$(CXX) $^ -o $@ $(LDFLAGS)

main.o: main.cxx
	$(CXX) -I$(INC_DIR) $^ -c -o $@

progopt.o: progopt.cxx
	$(CXX) -I$(INC_DIR) -I$(TACC_GRVY_INC) $^ -c -o $@ $(LDFLAGS)

.PHONY: clean distclean

clean:
	rm -f *.o

distclean: clean
	rm -f main.x
