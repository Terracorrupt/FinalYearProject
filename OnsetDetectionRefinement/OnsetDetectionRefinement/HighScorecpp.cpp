#include "HighScoreScreen.h"

HighScoreScreen::HighScoreScreen(SDL_Renderer* r, ContentManager* c, int h)
{
	conMan = c;
	rend = r;
	highScore = h;

	t = new TextRenderer(r, "../Fonts/DIMITRI.ttf", 28);
	white = { 255, 255, 255 };

	highScoreText = "SCORE: ";

	highScoreText += std::to_string(highScore);

	t->message = highScoreText;
	textTure = t->RenderText(t->message, white);
	textRect.x = 500;
	textRect.y = 300;
	textRect.w = 200;
	textRect.h = 50;

	SDL_RenderCopy(r, textTure, 0, &textRect);

	DEBUG_MSG("HighScoreScreen Created");

	initialTicks = SDL_GetTicks();

	DEBUG_MSG(highScore);

	transition = false;

	//BeatDetector::Instance()->Instance == 0;


}

HighScoreScreen::~HighScoreScreen()
{
	delete t;
	delete conMan;
	delete rend;

}

void HighScoreScreen::Event()
{

}

void HighScoreScreen::Update(SDL_DisplayMode window)
{
	textRect.x = window.w / 2 - 100;
	textRect.y = window.h / 2 - 100;

	if (SDL_GetTicks() - initialTicks > 500)
	{
		transition = true;
	}
}

void HighScoreScreen::Draw()
{
	SDL_RenderCopy(rend, textTure, 0, &textRect);
}

bool HighScoreScreen::readyToTransition()
{
	return transition;
}

int HighScoreScreen::getHighScore()
{
	return 0;
}

bool HighScoreScreen::transOut()
{
	//while (transPos->m_x < 0)
	//transPos->m_x += 10;

	return true;
}

bool HighScoreScreen::transIn()
{
	return true;
}