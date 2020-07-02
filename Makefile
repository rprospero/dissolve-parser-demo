INCLUDE = -I/nix/store/qcl8qnc5l5jc9y7cpm98551gd6f7jwfc-antlr-runtime-cpp-4.7.2-dev/include/antlr4-runtime/
LINK = -L/nix/store/2hk6ifgb99sjkgli9843s4n3g7y52m55-antlr-runtime-cpp-4.7.2/lib/ -lantlr4-runtime


OBJ = .o
GRAMMAR = Dissolve
CC = g++ -g -Og -std=c++17

PARSE_OBJ = $(GRAMMAR)Lexer$(OBJ) $(GRAMMAR)Parser$(OBJ)

VISITOR_OBJ = Visitor$(OBJ) Visitor-species$(OBJ) Visitor-master$(OBJ)

all: cpp_parser.o types.o $(PARSE_OBJ) $(VISITOR_OBJ)
	$(CC) $(LINK) $(PARSE_OBJ) $(VISITOR_OBJ) cpp_parser.o types.o

$(GRAMMAR)Lexer.cpp : $(GRAMMAR).g4
	antlr -Dlanguage=Cpp -visitor $(GRAMMAR).g4

types.o: types.cpp types.h
	$(CC) -c -o $@ $< $(INCLUDE)

%.o: %.cpp
	$(CC) -c -o $@ $< $(INCLUDE)

clean:
	rm -rf *.o a.out
