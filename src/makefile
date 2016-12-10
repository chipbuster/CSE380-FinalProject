INC_DIR=../include

#This line generate by Intel Line Link Advisor
MKL_LINK_LINE= -L$(TACC_MKL_LIB) -Wl,--no-as-needed -lmkl_intel_ilp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl

LDFLAGS=-L$(TACC_GRVY_LIB) -L$(TACC_GSL_LIB) -lgrvy -lgsl $(MKL_LINK_LINE)
CXXFLAGS=-Wall -fopenmp

OBJS=main.o progopt.o simple.o datatypes.o dumpsolution.o charged.o

all: main.x

opt: CXXFLAGS += -O3
opt: all

debug: CXXFLAGS += -DDEBUG -g -O0
debug: all

main.x: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -I$(INC_DIR) -o $@ $(LDFLAGS)

%.o: %.cxx
	$(CXX) $(CXXFLAGS) $^ -I$(INC_DIR) -I$(TACC_GSL_INC) -I$(TACC_GRVY_INC) -c -o $@

.PHONY: clean distclean

clean:
	rm -f *.o *.csv

distclean: clean
	rm -f main.x

purge: distclean
	rm -f *.csv
