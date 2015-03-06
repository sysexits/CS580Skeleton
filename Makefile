LDFLAGS = -framework OpenGL -lglfw3 -I/usr/local/Cellar/glfw3/3.1/include -lGLEW -I/usr/local/Cellar/glew/1.11.0/include

all: program

program: ./src/InitShader.o ./src/LoadBMP.o ./src/main.o 
	g++ ./src/InitShader.o ./src/LoadBMP.o ./src/main.o -o program $(LDFLAGS)

main.o: ./src/main.cpp
	g++ $(LDFLAGS) -c ./src/main.cpp

InitShader.o: ./src/InitShader.cpp
	g++ $(LDFLAGS) -c ./src/InitShader.cpp

LoadBMP.o: ./src/LoadBMP.o
	g++ $(LDFLAGS) -c ./src/LoadBMP.o

clean:
	rm ./src/*o program
