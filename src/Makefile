OUTPUT=output
GENERATED=antlr4-generated
GRAMMAR=ccomp.g4
COMPILER=ccomp

ANTLR4_BINDIR=/usr/bin
ANTLR4_INCDIR=/usr/include/antlr4-runtime
ANTLR4_LIBDIR=/usr/lib/x86_64-linux-gnu

AST=Expression.cpp Function.cpp Instruction.cpp Program.cpp ReturnInstr.cpp Symbol.cpp
SOURCES=$(AST) BasicBlock.cpp CFG.cpp IRInstr.cpp Visitor.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)

CC=clang++
CCARGS=-g -c -I $(ANTLR4_INCDIR) -I $(GENERATED) -std=c++11 -Wno-defaulted-function-deleted -Wno-unknown-warning-option
LDARGS=-g

all: ccomp

ccomp: dirs antlr $(OBJECTS) 
	$(CC) $(CCARGS) $(GENERATED)/ccompBaseVisitor.cpp -o $(OUTPUT)/ccompBaseVisitor.o 
	$(CC) $(CCARGS) $(GENERATED)/ccompLexer.cpp -o $(OUTPUT)/ccompLexer.o 
	$(CC) $(CCARGS) $(GENERATED)/ccompVisitor.cpp -o $(OUTPUT)/ccompVisitor.o 
	$(CC) $(CCARGS) $(GENERATED)/ccompParser.cpp -o $(OUTPUT)/ccompParser.o  
	$(CC) $(LDARGS) $(addprefix $(OUTPUT)/,$(OBJECTS)) $(OUTPUT)/ccompBaseVisitor.o $(OUTPUT)/ccompLexer.o $(OUTPUT)/ccompVisitor.o $(OUTPUT)/ccompParser.o $(ANTLR4_LIBDIR)/libantlr4-runtime.a -o $(COMPILER)

%.o : %.cpp
	$(CC) $(CCARGS) $< -o $(OUTPUT)/$@

antlr: $(GRAMMAR)
	$(ANTLR4_BINDIR)/antlr4 -visitor -no-listener -Dlanguage=Cpp -o $(GENERATED) $(GRAMMAR)

dirs:
	mkdir -p $(OUTPUT) 
	mkdir -p $(GENERATED) 

clean:
	rm -rf $(OUTPUT)
	rm -rf $(GENERATED)
