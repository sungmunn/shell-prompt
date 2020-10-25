# TP3 (C++) - Makefile
# @author const39

CMD:= g++
BIN := bin
EXEC := shell_prompt

COLOR := Color
PARSER := Parser

all: main clear

main: color parser
	$(CMD) -o $(EXEC) $(COLOR).o $(PARSER).o Main.cpp

color: $(COLOR).hpp $(COLOR).cpp
	$(CMD) -c -o $(COLOR).o $(COLOR).cpp

parser: $(PARSER).hpp $(PARSER).cpp
	$(CMD) -c -o $(PARSER).o $(PARSER).cpp

# $(BIN)/%.o: %.cpp $(BIN)
#  	$(CMD) -c -o $(BIN)/$(COLOR).o $(COLOR).cpp

# mkdir:
# 	mkdir -p $(BIN)

clear:
	rm -f *.o