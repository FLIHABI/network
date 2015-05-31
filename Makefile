CXX=g++
NOWARNFLAGS=-Wno-null-conversion -Wno-null-arithmetic
CXXFLAGS=-m32 -Wall -Wextra -std=c++14 -pedantic $(NOWARNFLAGS)
SERVER_TEST=tests/server_main.cc
SLAVE_TEST=tests/slave_main.cc
QUEUE_TEST=tests/queue.cc
QUEUE_OBJ=$(QUEUE_TEST:.cc=.o)

LIBS=-pthread #-lstdc++
STATICLIBS=-static
BIN_DIR=_bin

all: server slave

server: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I src/ $(SERVER_TEST) -o $(BIN_DIR)/$@ $(LIBS)

slave: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I src/ $(SLAVE_TEST) -o $(BIN_DIR)/$@ $(LIBS)


testqueue: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I src/ $(QUEUE_TEST) -o $(BIN_DIR)/$@ $(LIBS)

static: static-slave

static-server: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(STATICFLAGS) -I src/ $(SERVER_TEST)\
	    -o $(BIN_DIR)/$@ $(STATICLIBS) $(LIBS)

static-slave: | $(BIN_DIR)
	$(CXX) -m32 $(CXXFLAGS) $(STATICFLAGS) -I src/ $(SLAVE_TEST)\
	    -o $(BIN_DIR)/$@ $(STATICLIBS) $(LIBS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf _bin

.PHONY: clean all
