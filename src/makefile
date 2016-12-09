INC_DIR=../include

LDFLAGS=-L$(TACC_GRVY_LIB) -lgrvy
CXXFLAGS=-Wall

OBJS=main.o progopt.o simple.o datatypes.o dumpsolution.o

all: main.x

opt: CXXFLAGS += -O3
opt: all

debug: CXXFLAGS += -DDEBUG -g -O0
debug: all

main.x: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -I$(INC_DIR) -o $@ $(LDFLAGS)

%.o: %.cxx
	$(CXX) $(CXXFLAGS) $^ -I$(INC_DIR) -I$(TACC_GRVY_INC) -c -o $@

.PHONY: clean distclean

clean:
	rm -f *.o *.csv

distclean: clean
	rm -f main.x

purge: distclean
	rm -f *.csv
