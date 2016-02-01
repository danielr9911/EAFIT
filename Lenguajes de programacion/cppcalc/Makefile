CPPFLAGS=-g
OBJECTS=calc.o scanner.o token.o ast.o parser.o calculator.o

calc: $(OBJECTS)
	g++ $(CPPFLAGS) -o $@ $(OBJECTS)

calc.o: calc.cpp scanner.h token.h
	g++ $(CPPFLAGS) -c $<

calculator.o: calculator.cpp calculator.h parser.h ast.h
	g++ $(CPPFLAGS) -c $<

scanner.o: scanner.cpp scanner.h token.h
	g++ $(CPPFLAGS) -c $<

token.o: token.cpp token.h
	g++ $(CPPFLAGS) -c $<

ast.o: ast.cpp ast.h
	g++ $(CPPFLAGS) -c $<

parser.o: parser.cpp parser.h
	g++ $(CPPFLAGS) -c $<

clean:
	rm -f *.o
	rm -f calc
