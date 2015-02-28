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
	bool readyToTransition();
	int getHighScore();
	bool transOut();
	bool transIn();
private:
	ContentManager * conMan;
	SDL_Renderer* rend;
	TextRenderer* t;
	TextRenderer* t2;
	TextRenderer* t3;
	TextRenderer* t4;
	SDL_Texture* textTure;
	SDL_Texture* textTure2;
	SDL_Texture* textTure3;
	SDL_Texture* textTure4;
	SDL_Color blue, green, red, yellow, orange, white, activeComboColor;
	SDL_Rect textRect;
	SDL_Rect textRect2;
	SDL_Rect textRect3;
	SDL_Rect textRect4;
	char* path;
	bool done;
	bool doOnce;
	Vector2D * transInPos;
	int screenWidth;
	int transOutTimer;
	bool transOutBool;
	Vector2D* transOutPos;
};
#endif