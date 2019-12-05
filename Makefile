EXE = robotplanner

SRC_DIR = ./src
INCLUDE_DIR = ./include
BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj

OBJS := $(addprefix $(OBJ_DIR)/, main.o init.o path.o)
COMMONS := $(addprefix $(INCLUDE_DIR)/, struct.h global.h)

CXX = g++
CXXFLAGS := -O2 -Wall -pedantic -ansi

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) -o $(BUILD_DIR)/$(EXE) $(CXXFLAGS) $(OBJS)

$(OBJ_DIR)/main.o: 	$(SRC_DIR)/main.cpp $(COMMONS)
	$(CXX) -c -o $@ $(CXXFLAGS) $(SRC_DIR)/main.cpp 

$(OBJ_DIR)/init.o: 	$(SRC_DIR)/initDefn.cpp $(INCLUDE_DIR)/initDefn.h $(COMMONS)
	$(CXX) -c -o $@ $(CXXFLAGS) $(SRC_DIR)/initDefn.cpp

$(OBJ_DIR)/path.o: 	$(SRC_DIR)/pathDefn.cpp $(INCLUDE_DIR)/pathDefn.h $(COMMONS)
	$(CXX) -c -o $@ $(CXXFLAGS) $(SRC_DIR)/pathDefn.cpp

$(shell mkdir -p $(OBJ_DIR))

.PHONY: all clean

clean:
	rm -rf $(BUILD_DIR)/$(EXE) $(OBJ_DIR)
