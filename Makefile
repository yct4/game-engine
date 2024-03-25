CC = g++
CFLAGS = -std=gnu++11
SRCS = src/constants.hpp src/utils.hpp src/main.cpp src/Game.cpp src/Game.hpp src/Enemy.hpp src/Enemy.cpp src/PotionSlot.hpp src/PotionSlot.cpp src/Cauldron.hpp src/Cauldron.cpp src/LevelDesigner.hpp
PROG = game

SDL2 = -I include -L lib -l SDL2-2.0.0 -l SDL2 -l SDL2main -l SDL2_image -l SDL2_mixer -l glfw
LIBS = $(SDL2)

build: src/main.cpp src/glad.c
	$(CC) $(CFLAGS) src/main.cpp src/glad.c $(LIBS)
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
