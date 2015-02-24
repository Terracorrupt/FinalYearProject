#ifndef DRAGMUSIC
#define DRAGMUSIC

#include "Scene.h"

class DragMusicFile : public Scene
{
public:
	DragMusicFile(SDL_Renderer*, ContentManager* c);
	~DragMusicFile();
	void Update(SDL_DisplayMode );
	void Draw();
	void Event();
private:
	ContentManager * conMan;
	SDL_Renderer* rend;
	TextRenderer* t;
	TextRenderer* t2;
	SDL_Texture* textTure;
	SDL_Texture* textTure2;
	SDL_Color blue, green, red, yellow, orange, white, activeComboColor;
	SDL_Rect textRect;
	SDL_Rect textRect2;
	char* path;
	bool done;
};
#endif