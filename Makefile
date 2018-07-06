objects = main.o Lexical/Lexical.o Grammar/Grammar.o Semantic/Semantic.o

Naive: $(objects)
	g++ -o Naive $(objects)

.PHONY : clean

clean:
	rm Naive $(objects)
