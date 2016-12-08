INC_DIR=../include

LDFLAGS=-L$(TACC_GRVY_LIB) -lgrvy

OBJS=main.o progopt.o euler.o datatypes.o

all: main.x

debug: CXXFLAGS += -DDEBUG -g
debug: all

main.x: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -I$(INC_DIR) -o $@ $(LDFLAGS)

%.o: %.cxx
	$(CXX) $(CXXFLAGS) $^ -I$(INC_DIR) -I$(TACC_GRVY_INC) -c -o $@

.PHONY: clean distclean

clean:
	rm -f *.o

distclean: clean
	rm -f main.x
