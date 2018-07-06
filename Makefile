objects = main.o Lexical/Lexical.o Grammar/Grammar.o Semantic/Semantic.o

project = Naive

$(project) : $(objects)
	g++ -o $(project) $(objects)

.PHONY : clean

clean:
	-rm $(project) $(objects)

