#include "ContentManager.h"

ContentManager::ContentManager(SDL_Renderer* rend)
{
	renderer = rend;
	//Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

ContentManager::~ContentManager()
{
	for (it_typeTexture iterator = textures.begin(); iterator != textures.end(); ++iterator)
	{
		delete(iterator->second);
	}

	/*for (it_typeSound iterator = sounds.begin(); iterator != sounds.end(); ++iterator)
	{
		delete(iterator->second);
	}

	for (it_typeMusic iterator = music.begin(); iterator != music.end(); ++iterator)
	{
		delete(iterator->second);
	}*/
}

// load in a texture
void ContentManager::LoadTexture(std::string fileName, std::string id, int w, int h, int frames)
{
	textures[id] = new Texture(renderer, fileName, w, h, frames);
	DEBUG_MSG("Texture Created");
}

// update all the textures
void ContentManager::Update()
{
	for (it_typeTexture iterator = textures.begin(); iterator != textures.end(); ++iterator)
	{
		textures[iterator->first]->Update();
	}
}

//draw all the textures
void ContentManager::DrawTexture(std::string id, Vector2D* position, SDL_RendererFlip flip)
{
	textures[id]->Draw(position, flip);
}

void ContentManager::DrawTexture(std::string id, Vector2D* position, SDL_RendererFlip flip, float rotation)
{
	textures[id]->Draw(position, flip);
	textures[id]->rotation = rotation;
}

// animate all the textures
void ContentManager::AnimateTexture(std::string id, Vector2D* position, SDL_RendererFlip flip)
{
	textures[id]->Animate(position, flip);
}

// load in music
//void ContentManager::LoadMusic(std::string filename, std::string id)
//{
//	music[id] = Mix_LoadMUS(filename.c_str());
//}
//
//// load in a sound effect
//void ContentManager::LoadSound(std::string filename, std::string id)
//{
//	sounds[id] = Mix_LoadWAV(filename.c_str());
//}
//
//// play music
//void ContentManager::PlayMusic(std::string id)
//{
//	Mix_PlayMusic(music[id], -1);
//}
//
//// play sound effects
//void ContentManager::PlaySound(std::string id)
//{
//	Mix_PlayChannel(-1, sounds[id], 0);
//};