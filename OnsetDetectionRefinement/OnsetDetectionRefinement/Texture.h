#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <iostream>
#include <map>
#include <string>
#include "Vector2D.h"
#include "SDL_image.h"
#include "Debug.h"

using namespace std;

class Texture
{
public:
	Texture(SDL_Renderer* , std::string , int , int , int );
	~Texture();

	void Draw(Vector2D*, SDL_RendererFlip );
	void Animate(Vector2D* , SDL_RendererFlip );
	void Update();
	void setRow(int);
	int getWidth();
	int getHeight();
	int width;
	int height;
	int frameCount;
	int currentFrame;
	int currentRow;
	SDL_Rect srcRect;
	SDL_Rect destRect;
	SDL_Texture* texture;
	Vector2D* imagePosition;
	SDL_Renderer* m_p_Renderer;
	float rotation;
};
#endif