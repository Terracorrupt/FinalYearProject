#include <SDL.h>
#include "SDL_image.h"
#include <SDL_ttf.h>
#include <stdexcept>
#include <string>
#include <iostream>

class TextRenderer
{
private:
	SDL_Renderer* textRend;
	TTF_Font *font;
	
public:
	TextRenderer(SDL_Renderer*, std::string, int);
	~TextRenderer();
	SDL_Texture* RenderText(std::string, SDL_Color);
	std::string message;
};