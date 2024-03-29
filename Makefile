exec = mks.out
sources = $(wildcard src/*.cpp)
objects = $(sources:.cpp=.o)
flags = -g -std=c++11 

$(exec): $(objects)
	g++ $(objects) $(flags) -o $(exec)

%.o: %.cpp include/%.h
	g++ -c $(flags) $< -o $@

test:
	./$(exec) ./samples/test.meks

memory:
	leaks -atExit -- ./$(exec) ./samples/test.meks | grep LEAK

install:
	make
	cp ./mks.out /usr/local/bin/mks

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o

ast:
	python3 ./tool/generate_ast.py ./src
