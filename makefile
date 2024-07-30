
INC_DIR=include
TEST_SRC_DIR=tests
OBJ_DIR=obj
TEST_BIN_DIR=bin/tests

CC=gcc
CFLAGS=-I$(INC_DIR)
LIBS=-lcunit
ALL_TESTS=$(addprefix $(TEST_BIN_DIR)/, test_vector.exe test_affine.exe)

.PHONY: all
all: $(ALL_TESTS)

$(TEST_BIN_DIR)/%.exe: $(OBJ_DIR)/%.obj
	-@mkdir -p $(@D)
	$(CC) -o $@ $< $(LIBS)

$(OBJ_DIR)/%.obj: $(TEST_SRC_DIR)/%.c
	-@mkdir -p $(@D)
	$(CC) -c -o $@ $(CFLAGS) $<

.PHONY: clean
clean:
	-@rm -rf $(OBJ_DIR)
	-@rm -rf $(TEST_BIN_DIR)
