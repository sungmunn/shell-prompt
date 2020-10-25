# TP3 (C++) - Makefile
# @author const39

CMD:= g++
BIN := bin

COLOR := Color
PARSER := Parser

all: main

main: color parser
	$(CMD) -o $(BIN)/exec $(BIN)/$(COLOR).o $(BIN)/$(PARSER).o Main.cpp

color: $(COLOR).hpp $(COLOR).cpp mkdir
	$(CMD) -c -o $(BIN)/$(COLOR).o $(COLOR).cpp

parser: $(PARSER).hpp $(PARSER).cpp mkdir
	$(CMD) -c -o $(BIN)/$(PARSER).o $(PARSER).cpp

# $(BIN)/%.o: %.cpp $(BIN)
#  	$(CMD) -c -o $(BIN)/$(COLOR).o $(COLOR).cpp

mkdir:
	mkdir -p $(BIN)

clean	:
	rm -f *.o