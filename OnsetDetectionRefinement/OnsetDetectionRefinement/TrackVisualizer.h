#ifndef TRACKVISUALIZER_H
#define TRACKVISUALIZER_H

#include "GameObject.h"
#include "BeatDetector.h"

class TrackVisualizer : public GameObject
{
public:
	TrackVisualizer(ContentManager* c, SDL_Renderer* r);
	~TrackVisualizer();
	void Initialize();
	void Load();
	void HandleEvents();
	void Update(SDL_DisplayMode window);
	void Draw();
	void SetSpawn(Vector2D* spawn);
	int songLengthInSeconds;
	bool direction;
	Vector2D* initialPos;
	Vector2D* visPos;
	std::string songName;
	std::string artistName;
	TextRenderer* t;
	TextRenderer* t2;
	SDL_Texture * textTure;
	SDL_Texture * textTure2;
	SDL_Color blue, green, red, yellow, orange, white;
	SDL_Rect textRect;
	SDL_Rect textRect2;
	TimeStamp* current;
	int currentSeconds;
	int prevSeconds;
	float difference;
	float onePercent;
	float hundredPercent;
	Vector2D* finalPos;
	int currentMillis;
	int initialMillis;
	int valueToIncrease;
};
#endif