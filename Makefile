compile:
	g++ *.cpp -std=c++17  -lm -D_GNU_SOURCE=1 -D_REENTRANT -I/usr/include/SDL -lSDL
run: 
	./a.out
