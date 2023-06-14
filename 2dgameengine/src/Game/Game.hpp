#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "../ECS/ECS.hpp"

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game{
	

	private:
		bool isRunning;
		double deltaTime;
		int millisecsPrevFrame = 0;
		SDL_Window* window;
		SDL_Renderer* renderer;
		glm::vec2 playerPosition;
   		 glm::vec2 playerVelocity;

   		 std::unique_ptr<Registry> registry;
   		 
	public:
		Game();
		~Game();
		void Initilize();
		void Run();
		void ProcessInput();
		void Update();
		void Render();
		void Destroy();
		void Setup();

		int windowWidth;
		int windowHeight;
};

#endif