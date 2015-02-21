#ifndef GAME_H
#define GAME_H

#include "Debug.h"
#include <SDL.h>
#include "SceneManager.h"

class Game
{
public:
	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool Initialize(const char*, int, int, int, int, int);
	void Render();
	void Update();
	void HandleEvents();
	bool IsRunning();
	void CleanUp();
private:
	Game();
	~Game();
	SceneManager* sceneManager;
	static Game* s_pInstance;
	bool m_running;
	SDL_Window* m_p_Window;
	SDL_Renderer* m_p_Renderer;
	ContentManager* conMan;
	SDL_Event e;
};
#endif
typedef Game TheGame;