#include "TextRenderer.h"

TextRenderer::TextRenderer(SDL_Renderer* r, std::string fontFile, int fontSize)
{
	if (TTF_Init() == -1)
	{
		std::cout << TTF_GetError() << std::endl;
	}

	textRend = r;

	//Gets our font
	font = TTF_OpenFont(fontFile.c_str(), fontSize);

	if (font == nullptr)
		throw std::runtime_error("Failed to load font: " + fontFile + TTF_GetError());
	else
		std::cout << "Font get" << std::endl;
}

TextRenderer::~TextRenderer()
{
	delete font;
	delete textRend;
}


SDL_Texture* TextRenderer::RenderText(std::string message, SDL_Color color)
{
	//Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns
	SDL_Surface *surf = TTF_RenderText_Solid(font, message.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(textRend, surf);

	//Clean up unneeded stuff
	SDL_FreeSurface(surf);
	//TTF_CloseFont(font);

	return texture;
}