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

install:
	make
	cp ./mks.out /usr/local/bin/mks

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o
