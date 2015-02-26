#include "Texture.h"

Texture::Texture(SDL_Renderer* renderer, std::string fileName, int w, int h, int frames)
{
	m_p_Renderer = renderer;

	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == 0)
	{
		DEBUG_MSG("Image wasnt loaded");
	}

	texture = SDL_CreateTextureFromSurface(renderer, pTempSurface);
	DEBUG_MSG("Image in texture Created");

	SDL_FreeSurface(pTempSurface);

	width = w;
	height = h;

	frameCount = frames;
	currentRow = 0;
	rotation = 0;
}



Texture::~Texture()
{
	SDL_DestroyTexture(texture);
	delete m_p_Renderer;
	delete font;
	delete center;
}

void Texture::Update()
{
	currentFrame = int(((SDL_GetTicks() / 100) % frameCount));
}

// draw image to screen/single image
void Texture::Draw(Vector2D* position, SDL_RendererFlip flip)
{
	srcRect.x = width;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	center = new SDL_Point();

	center->x = srcRect.w / 2;
	center->y = srcRect.h / 2;

	destRect.x = (int)position->GetX();
	destRect.y = (int)position->GetY();

	//if (rotation>0)
		SDL_RenderCopyEx(m_p_Renderer, texture, 0, &destRect, rotation, center, flip);
	
}



//used for animating images
void Texture::Animate(Vector2D* position, SDL_RendererFlip flip)
{
	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	SDL_Point* center = new SDL_Point();

	center->x = srcRect.w / 2;
	center->y = srcRect.h / 2;
	destRect.x = (int)position->GetX();
	destRect.y = (int)position->GetY();
	SDL_RenderCopyEx(m_p_Renderer, texture, &srcRect, &destRect, 0, center, flip);
}

// get the width of a texture
int Texture::getWidth()
{
	int w;
	SDL_QueryTexture(texture, NULL, NULL, &w, NULL);
	return w / frameCount;
}

// get the height of a texture
int Texture::getHeight()
{
	return height;
}

// set the row/ for animation
void Texture::setRow(int row)
{
	currentRow = row;
};
