#include "Game.h"
#include <iostream>

using namespace std;

Game* Game::s_pInstance = 0;

Game::Game() : m_running(true)
{
}

Game::~Game()
{
}

bool Game::Initialize(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		DEBUG_MSG("SDL Init success");
		m_p_Window = SDL_CreateWindow(title, xpos, ypos, width, height, 0);

		if (m_p_Window != 0)
		{
			DEBUG_MSG("Window creation success");
			m_p_Renderer = SDL_CreateRenderer(m_p_Window, -1, 0);

			if (m_p_Renderer != 0)
			{
				DEBUG_MSG("Renderer creation success");
			}
			else
			{
				DEBUG_MSG("Renderer init fail");
				return false;
			}
		}
		else
		{
			DEBUG_MSG("Window init fail");
			return false;
		}
	}
	else
	{
		DEBUG_MSG("SDL init fail");
		return false;
	}
	conMan = new ContentManager(m_p_Renderer);

	sceneManager->Instance()->Load();
	//sceneManager->Initialize();
	//sceneManager->Load();

	m_running = true;

	return true;
}

void Game::Render()
{
	//Set to black
	SDL_SetRenderDrawColor(m_p_Renderer, 0, 0, 0, 255);

	//Clear Window to black, Think of as spritebatch.draw
	SDL_RenderClear(m_p_Renderer);

	//Draw
	SceneManager::Instance()->NextScene(m_p_Renderer,conMan)->Draw();

	//Show Window, spritebatch.end
	SDL_RenderPresent(m_p_Renderer);

}

void Game::Update()
{
	//while (m_running)
	//{

	//SDL_RenderClear(m_p_Renderer);

		//Insert your hopes and dreams here
		//while (SDL_PollEvent(&e))
		//{

		//}


		//Have we switched state?
		//Events();

		//Update dem scenes yo
		SceneManager::Instance()->NextScene(m_p_Renderer, conMan)->Update();


		//SDL_RenderPresent(m_p_Renderer);

	//}
}

void Game::HandleEvents()
{
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_running = false;
			break;
		}
	}
	SceneManager::Instance()->NextScene(m_p_Renderer, conMan)->Event();
	//sceneManager->HandleEvents();
}

bool Game::IsRunning()
{
	return m_running;
}

void Game::CleanUp()
{
	DEBUG_MSG("Cleaning Up");
	SDL_DestroyWindow(m_p_Window);
	m_p_Window = NULL;
	delete(sceneManager);
	SDL_DestroyRenderer(m_p_Renderer);
	m_p_Renderer = NULL;

	SDL_Quit();
};


