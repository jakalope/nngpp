
# defaults
CXX = g++
CATCH_INC =
NNG_INC =
NNG_LNK = -lnng -lmbedtls -lmbedx509 -lmbedcrypto

ENV =
include $(ENV)

BASE_DIR = $(shell pwd)
BIN_DIR = $(BASE_DIR)/bin
INC_DIR = $(BASE_DIR)/include
TEST_DIR = $(BASE_DIR)/test
DEMO_DIR = $(BASE_DIR)/demo

INC_FLG = -I$(INC_DIR) -I$(NNG_INC) -I$(CATCH_INC)
LIB_FLG = $(NNG_LNK) -lpthread

REL_FLG = -Wall -Wextra -std=c++17 -march=native -O3 -DNDEBUG -Wno-unused-parameter
DBG_FLG = -Wall -Wextra -std=c++17 -march=native -g -Wno-unused-parameter

TEST_FILES = $(shell echo $(TEST_DIR)/*.cpp)
TEST_BIN = $(BIN_DIR)/test

DEMO_FILES = $(shell echo $(DEMO_DIR)/*/*.cpp)
DEMO_BINS = $(patsubst $(DEMO_DIR)/%.cpp,$(BIN_DIR)/%,$(DEMO_FILES))

$(BIN_DIR)/%: $(DEMO_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(INC_FLG) $(REL_FLG) -o $@ $^ $(LIB_FLG)

demo: $(DEMO_BINS)

$(TEST_BIN): $(TEST_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(INC_FLG) $(DBG_FLG) -o $@ $^ $(LIB_FLG)

test: $(TEST_BIN)
	@$(TEST_BIN)

clean:
	@rm -rf $(TEST_BIN) $(DEMO_BINS)

.PHONY: demo test clean
