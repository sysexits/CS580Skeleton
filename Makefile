# You should install via homebrew : 
# 	brew install glew
# 	brew install glfw3

INCLUDE=-I/usr/local/include -I/opt/X11/include

LDFLAGS=-framework OpenGL
LDFLAGS+=-lglfw3 -lglew

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
