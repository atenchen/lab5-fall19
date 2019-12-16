FLAGS = -DEXTRA -Wall -Werror -g -std=c++14
FILE1 = lab5
FILE2 = BSTree

all: $(FILE1).o 
	g++ $(FLAGS) $(FILE1).o -o $(FILE1)

$(FILE1).o: $(FILE1).cpp $(FILE2).h
	g++ -c -I . $(FLAGS) $(FILE1).cpp -o $(FILE1).o

run: all
	./$(FILE1)

memcheck: all
	valgrind --leak-check=full ./$(FILE1)

clean:
	rm -rf *.o $(FILE1)
