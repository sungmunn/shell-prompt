# TP3 (C++) - Makefile
# @author const39

CMD:= g++
BIN := bin

COLOR := Color

all: main

main: color
	$(CMD) -o $(BIN)/exec $(BIN)/$(COLOR).o Main.cpp

color: $(COLOR).hpp $(COLOR).cpp mkdir
	$(CMD) -c -o $(BIN)/$(COLOR).o $(COLOR).cpp

# $(BIN)/%.o: %.cpp $(BIN)
#  	$(CMD) -c -o $(BIN)/$(COLOR).o $(COLOR).cpp

mkdir:
	mkdir -p $(BIN)

clean	:
	rm -f *.o