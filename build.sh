#!/usr/bin/env bash

antlr -Dlanguage=Cpp -visitor Dissolve.g4
g++ -I/nix/store/qcl8qnc5l5jc9y7cpm98551gd6f7jwfc-antlr-runtime-cpp-4.7.2-dev/include/antlr4-runtime/ -L/nix/store/2hk6ifgb99sjkgli9843s4n3g7y52m55-antlr-runtime-cpp-4.7.2/lib/ -lantlr4-runtime DissolveLexer.cpp DissolveParser.cpp  Visitor.cpp cpp_parser.cpp
