COMPILER_FLAGS = -O3 -I eigen-3.4.0/ -lm -lpthread -lX11

LEX = flex

CXX = g++

CC = gcc

O_FILES = Ray.o

RayTracer: RayTracer.cpp $(O_FILES)
	$(CXX) RayTracer.cpp Primitive.cpp $(O_FILES) -o RayTracer $(COMPILER_FLAGS)

Ray.o: Ray.cpp
	$(CXX) -c Ray.cpp -o Ray.o $(COMPILER_FLAGS)

clean:
	rm *.o RayTracer
