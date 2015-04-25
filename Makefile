CXX=clang++
NOWARNFLAGS=-Wno-null-conversion -Wno-null-arithmetic
CXXFLAGS=-Wall -Wextra -std=c++14 -pedantic $(NOWARNFLAGS)
SERVER_MAIN=server_main.cc
QUEUE_TEST=tests/queue.cc
QUEUE_OBJ=$(QUEUE_TEST:.cc=.o)

LIBS=
BIN_DIR=_bin

all: broadcaster listener

server:
	$(CXX) $(CXXFLAGS) -I src/ $(SERVER_MAIN) -o $(BIN_DIR)/$@ $(LIBS)

slave:
	$(CXX) $(CXXFLAGS) -I src/ $(SLAVE_TEST) -o $(BIN_DIR)/$@ $(LIBS)


testqueue: | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I src/ $(QUEUE_TEST) -o $(BIN_DIR)/$@ $(LIBS)


$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf _bin

.PHONY: clean all
