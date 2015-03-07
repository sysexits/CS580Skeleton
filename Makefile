# You should install via homebrew : 
# 	brew install glew
# 	brew install glfw3

INCLUDE=-I/usr/local/Cellar/glew/1.11.0/include -I/usr/local/Cellar/glfw3/3.1/include

LDFLAGS=-framework OpenGL
LGFLAGS+=-L/usr/local/Cellar/glew/1.11.0/lib -L/usr/local/Cellar/glfw3/3.1/lib
LDFLAGS+=-lglew -lglfw3

SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=program

src/%.o: src/%.cpp
	g++ -c -o src/$*.o src/$*.cpp $(INCLUDE)

$(EXECUTABLE): $(OBJECTS)
	g++ $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)

all: $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJECTS)
