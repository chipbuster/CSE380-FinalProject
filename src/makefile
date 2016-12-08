INC_DIR=../include

LDFLAGS=-L$(TACC_GRVY_LIB) -lgrvy

OBJS=main.o progopt.o euler.o

all: main.x

main.x: $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

main.o: main.cxx
	$(CXX) -I$(INC_DIR) $^ -c -o $@

progopt.o: progopt.cxx
	$(CXX) $^ -I$(INC_DIR) -I$(TACC_GRVY_INC)  -c -o $@

euler.o: euler.cxx
	$(CXX) $^ -I$(INC_DIR) -c -o $@

.PHONY: clean distclean

clean:
	rm -f *.o

distclean: clean
	rm -f main.x
