#******************************************************************************
#	@Author: 	Anurag J K
#	@date:		17AUG2020
#	@file 		Makefile
#******************************************************************************

CC=g++
EXE_OUT=pgm
CFLAGS=\
		-I. \
		-Wall \
		-std=c++11 \

EXTRA_LIB=.
EXTRA_INC=.

OBJ_DIR=./obj
CXX_SRC_DIR=.

OBJ_FILES= \
		$(OBJ_DIR)/p.o \
		$(OBJ_DIR)/cmn.o \
		$(OBJ_DIR)/atg.o \

EXTRA_FLAGS=\
		-lPocoFoundation \
		-lPocoUtil \


$(EXE_OUT): $(OBJ_FILES)
	@echo "[LD] "$(OBJ_FILES)
	@echo "[BINARY OUTPUT] "$(EXE_OUT)
	@$(CC) $(OBJ_FILES) $(EXTRA_FLAGS) -o $(EXE_OUT)


$(OBJ_DIR)/%.o: $(CXX_SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "[CC] "$@
	@$(CC) -c $(CFLAGS) -o $@ $<

$(OBJ_DIR):
	@echo "[MKDIR] "$@
	@mkdir -p $@

all: $(EXE_OUT)


clean:
	@echo "[clean] "$(OBJ_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "[clean] "$(EXE_OUT)
	@rm -rf pgm
