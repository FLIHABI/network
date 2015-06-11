CXX=g++
#NOWARNFLAGS=-Wno-null-conversion -Wno-null-arithmetic
CXXFLAGS=-m32 -Wall -Wextra -std=c++14 -pedantic -I include $(NOWARNFLAGS)
SRC=broadcaster.cc listener.cc server.cc slave.cc utils.cc
SERVER_TEST=tests/server_main.cc
SLAVE_TEST=tests/slave_main.cc
QUEUE_TEST=tests/queue.cc

LIBS=-pthread #-lstdc++
STATICLIBS=-static
BIN_DIR=_bin
BUILD_DIR=_build
OBJ=$(SRC:.cc=.o)
OBJ_FILES=$(addprefix $(BUILD_DIR)/, $(OBJ))

all: $(BIN_DIR) $(BUILD_DIR) server slave

server: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -I src/ $^ $(SERVER_TEST) -o $(BIN_DIR)/$@ $(LIBS)

slave: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -I src/ $^ $(SLAVE_TEST) -o $(BIN_DIR)/$@ $(LIBS)

_build/%.o: src/%.cc
	$(CXX) $(CXXFLAGS) -I src/ -c $^ -o $@

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

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: clean all
