#include "TrackVisualizer.h"

TrackVisualizer::TrackVisualizer(ContentManager* c, SDL_Renderer* r)
{
	width = 70;
	height = 76;
	conMan = c;
	alive = true;
	renderer = r;
	songName = BeatDetector::Instance()->getSongName();
	artistName = BeatDetector::Instance()->getArtistName();
	visPos = new Vector2D(950, 70);

	int lastindex = songName.find_last_of(".");

	std::string rawname = songName.substr(0, lastindex);

	std::cout << "Song Name:: " << rawname << std::endl;

	songLengthInSeconds = BeatDetector::Instance()->getTime();

	onePercent = (float) songLengthInSeconds / 100;
	initialMillis = onePercent * 100;

	//if (onePercent < 1)
	//{
		// (onePercent)
	//}

	t = new TextRenderer(r, "../Fonts/DIMITRI.ttf", 28);
	white = { 255, 255, 255 };
	t->message = rawname;

	t2 = new TextRenderer(r, "../Fonts/DIMITRI.ttf", 28);

	if (artistName != "none")
	{
		artistName.insert(0, " - ");
		t2->message = artistName;
	}
	else
		t2->message = " - Unknown Artist";
		

	textTure = t->RenderText(t->message, white);
	textTure2 = t2->RenderText(t2->message, white);

	textRect.x = 800;
	textRect.y = 15;
	textRect.w = 400;
	textRect.h = 50;

	textRect2.x = 1200;
	textRect2.y = 15;
	textRect2.w = 400;
	textRect2.h = 50;

	if (rawname.length() < 10)
	{
		textRect.w = 200;
		textRect.h = 50;
	}
	if (rawname.length() < 15)
	{
		textRect.w = 250;
		textRect.h = 50;
	}

	if (artistName.length() < 10)
	{
		textRect2.w = 200;
		textRect2.h = 50;
	}

	if (artistName.length() < 15)
	{
		textRect2.w = 250;
		textRect2.h = 50;
	}

	//ACTUAL TRACK POSITION.... POSITION
	position = new Vector2D(970,80);

	initialPos = position;
	prevSeconds = 0;

	finalPos = new Vector2D(initialPos->m_x + 430, initialPos->m_y);
	hundredPercent = (finalPos->m_x - initialPos->m_x) / 1;
	difference = 0;

	SDL_RenderCopy(r, textTure, 0, &textRect);

	valueToIncrease = initialMillis;
}

TrackVisualizer::~TrackVisualizer()
{
	delete(conMan->textures["track"]);
	delete(conMan->textures["vis"]);
	delete t;
	delete t2;

	SDL_DestroyTexture(textTure);
	SDL_DestroyTexture(textTure2);

	delete textTure;
	delete textTure2;
	delete renderer;
	delete current;
	delete finalPos;
	delete conMan;
	delete position;
}

void TrackVisualizer::Initialize()
{
	position = new Vector2D(0, 0);
}

void TrackVisualizer::Load()
{
	conMan->LoadTexture("../Textures/trackVis.png", "vis", 500, 50, 1);
	conMan->LoadTexture("../Textures/trackPos.png", "pos", 25, 25, 1);
}

void TrackVisualizer::Update(SDL_DisplayMode window)
{
	current = BeatDetector::Instance()->getCurrentTime();

	//Convert current beat to seconds
	if (current->getSeconds()!=60)
		currentSeconds = current->getSeconds() + (current->getMinutes() * 60);

	DEBUG_MSG(current->getSeconds());

	//std::cout << currentSeconds << std::endl;
	
	//Change position based of current seconds
	//As difference gets smaller, get to end of track
	//START: 970 END: 1400. 100% = 430

	currentMillis = (currentSeconds * 100) + current->getMilliseconds();

	if (currentSeconds!=0)
		difference = ((float)currentSeconds / (float) songLengthInSeconds) * 100;


	//INITIAL POS X IS 0, FINAL POS is 100%, NEW POSITION IS 

	if (currentMillis >= initialMillis && (difference <101))
	{
		position->m_x += 4.3;
		initialMillis += valueToIncrease;
	}
		

	prevSeconds = currentSeconds;
}

void TrackVisualizer::Draw()
{
	//textTure2 = t->RenderText(t->message, white);

	SDL_RenderCopy(renderer, textTure, 0, &textRect);
	SDL_RenderCopy(renderer, textTure2, 0, &textRect2);

	conMan->DrawTexture("vis", visPos, SDL_FLIP_NONE);
	conMan->DrawTexture("pos", position, SDL_FLIP_NONE);
}