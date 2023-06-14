build: 
	g++ -Wall -std=c++17 -I"./libs/" src/*.cpp src/Game/*.cpp src/Logger/*.cpp src/ECS/*.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua -o gameengine; 
run:
	./gameengine
clean:
	rm gameengine