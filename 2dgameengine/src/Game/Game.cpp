#include "Game.hpp"
#include "../Logger/Logger.hpp"
#include "../ECS/ECS.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>


Game::Game(){
	isRunning = false;
	 registry = std::make_unique<Registry>();
	Logger::Log("Game Constructor called");
}

Game::~Game(){
	 Logger::Log("Game destroyer called");
	
}
glm::vec2 playerPosition;
glm::vec2 playerVelocity;


void Game::Setup(){
	Entity tank = registry->CreateEntity();

	registry->AddComponent<TransformComponent>(tank, glm::vec2(10.0,30.0), glm::vec2(1.0,1.0), 0.0);
	registry->AddComponent<RigidBodyComponent>(tank, glm::vec2(10.0, 0.0));
	
}

void Game::Update(){

	int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPrevFrame);
	if(timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
		SDL_Delay(timeToWait); 

	deltaTime = (SDL_GetTicks() - millisecsPrevFrame) / 1000.0;

	//Store curr frametime
	millisecsPrevFrame = SDL_GetTicks();
	playerPosition.x += playerVelocity.x * deltaTime;
	playerPosition.y += playerVelocity.y * deltaTime;

}

void Game::Initilize(){
	if(SDL_Init(SDL_INIT_EVERYTHING) !=0){
		Logger::Err("Error initilizing SDL");
		return;
	}
	SDL_DisplayMode displaymode;
	SDL_GetCurrentDisplayMode(0, &displaymode);
	windowWidth = 800;//displaymode.w;
    windowHeight = 600;//displaymode.h;
	window = SDL_CreateWindow("SlimEngine", 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		windowWidth, 
		windowHeight,
		SDL_WINDOW_SHOWN);
	if(!window){
		Logger::Err("Error creating SDL window");
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!renderer){
		Logger::Err("Error creating SDL renderer");
		return;
	}
	//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	isRunning = true;
}



void Game::Run(){
	Setup();
	while(isRunning){
		ProcessInput();
		Update();
		Render();
	}
}

void Game::ProcessInput(){
	SDL_Event sdlEvent;
	while(SDL_PollEvent(&sdlEvent)){
		switch(sdlEvent.type){
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if(sdlEvent.key.keysym.sym == SDLK_ESCAPE){
					isRunning = false;
				}
				break;
		}
	}
}



void Game::Render(){
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);
	
	SDL_Surface* surface = IMG_Load("./assets/images/truck-ford-left.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_Rect dst = {static_cast<int>(playerPosition.x),static_cast<int>(playerPosition.y),20,20};

	SDL_RenderCopy(renderer, texture, NULL, &dst); 
	
	SDL_DestroyTexture(texture);
	SDL_RenderPresent(renderer);

}

void Game::Destroy(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

