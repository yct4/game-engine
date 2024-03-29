CC = g++
CFLAGS = -std=gnu++11
SRCS = src/main.cpp src/types.hpp src/util.hpp
PROG = game

SDL2 = -I include -L lib -l SDL2-2.0.0 -l SDL2 -l SDL2main -l SDL2_image -l SDL2_mixer
LIBS = $(SDL2)

build: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBS)
	./a.out

$(PROG): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBS)
	./a.out

csv: src/LevelDesigner.hpp src/LevelDesignerTester.cpp
	$(CC) $(CFLAGS) src/LevelDesigner.hpp src/LevelDesignerTester.cpp $(LIBS)
	./a.out

clean:
	find . -type f -name "*.sw[klmnop]" -delete
	find . -type f -name "*.gch" -delete

.PHONY: setup-windows setup-osx
