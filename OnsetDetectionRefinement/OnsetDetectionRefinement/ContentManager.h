#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include <SDL.h>
#include <iostream>
#include <map>
#include <string>
//#include <SDL_mixer.h>
#include "Vector2D.h"
#include "SDL_image.h"
#include "Debug.h"
#include "Texture.h"

using namespace std;

class ContentManager
{
public:
	ContentManager(SDL_Renderer* renderer);
	~ContentManager();

	void LoadTexture(std::string fileName, std::string id, int width, int height, int frames);
	void Update();
	void DrawTexture(std::string id, Vector2D* position, SDL_RendererFlip flip);
	void DrawTexture(std::string id, Vector2D* position, SDL_RendererFlip flip, float imgoingtokillmyself);
	void AnimateTexture(std::string id, Vector2D* position, SDL_RendererFlip flip);
	//void LoadMusic(std::string filename, std::string id);
	//void PlayMusic(std::string id);
	//void LoadSound(std::string filename, std::string id);
	//void PlaySound(std::string id);

	SDL_Renderer* renderer;
	std::map<std::string, Texture*> textures;
	//std::map<std::string, Mix_Music*> music;
	//std::map<std::string, Mix_Chunk*> sounds;

	typedef std::map<std::string, Texture*>::iterator it_typeTexture;
	//typedef std::map<std::string, Mix_Chunk*>::iterator it_typeSound;
	//typedef std::map<std::string, Mix_Music*>::iterator it_typeMusic;
};
#endif