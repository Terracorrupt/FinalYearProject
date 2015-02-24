#include "Game.h"
#include <iostream>

using namespace std;

Game* Game::s_pInstance = 0;

Game::Game() : m_running(true)
{

	e = new SDL_Event();
}

Game::~Game()
{
	delete sceneManager;
	delete s_pInstance;
	delete m_p_Renderer;
	delete m_p_Window;
	delete conMan;
}

SDL_Event* Game::Gete()
{
	return e;
}

bool Game::Initialize(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{

		int should_be_zero = SDL_GetCurrentDisplayMode(0, &current);

		DEBUG_MSG("SDL Init success");
		m_p_Window = SDL_CreateWindow(title, 40, 40, current.w - 100, current.h - 100, 0);

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
		
		int should_be_zero = SDL_GetCurrentDisplayMode(0, &current);
		//Have we switched state?
		//Events();
		DEBUG_MSG(current.w);

		//Move from Menu to DragMusicFile
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN) && SceneManager::Instance()->getCurrent() == 2)
		{
			SceneManager::Instance()->setCurrent(3);
		}
		//Move from DragMusicFile to Level
		else if (SceneManager::Instance()->getCurrent() == 3 && TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
		{
			SceneManager::Instance()->setCurrent(4);
		}


		//Update dem scenes yo
		SceneManager::Instance()->NextScene(m_p_Renderer, conMan)->Update(current);


		//SDL_RenderPresent(m_p_Renderer);

	//}
}

void Game::HandleEvents()
{
	if (SDL_PollEvent(e))
	{
		switch (e->type)
		{
		case SDL_QUIT:
			m_running = false;
			break;
		}

		TheInputHandler::Instance()->event(e);

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


