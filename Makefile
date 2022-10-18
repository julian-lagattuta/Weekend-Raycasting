CFLAG= -gdwarf-2 -std=c++20

PROJECT := main.exe

DIR_SRC += .

SRC_ASM += $(wildcard $(addsuffix /*.asm, $(DIR_SRC)))
SRC_CPP += $(wildcard $(addsuffix /*.cpp, $(DIR_SRC)))
SRC_HPP += $(wildcard $(addsuffix /*.hpp, $(DIR_SRC)))
OBJ := $(patsubst %.cpp, %.o, $(SRC_CPP))
OBJ += $(patsubst %.asm, %.o, $(SRC_ASM))
EXE := $(PROJECT)
DIR_INC=
CC_PREFIX := 
CC := $(CC_PREFIX)g++
CLIB = -L .

.PHONY:all

all: $(EXE) run


%.o : %.asm
	nasm  -felf64 $< -o $@
$(EXE): $(SRC_HPP) $(SRC_CPP)
	    $(CC) $(CFLAG)  $(CLIB) $(SRC_CPP)    -o $@ 

run:
	$(EXE)
clean:
	    rm -rf $(EXE) $(OBJ) 

