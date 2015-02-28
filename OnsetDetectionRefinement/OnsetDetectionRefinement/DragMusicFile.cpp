#include "DragMusicFile.h"
#include "Game.h";

DragMusicFile::DragMusicFile(SDL_Renderer* r, ContentManager* c)
{
	conMan = c;
	rend = r;
	path = NULL;

	t = new TextRenderer(r, "../Fonts/DIMITRI.ttf", 38);
	white = { 255, 255, 255 };

	t2 = new TextRenderer(r, "../Fonts/DIMITRI.ttf", 28);
	t3 = new TextRenderer(r, "../Fonts/DIMITRI.ttf", 28);
	t4 = new TextRenderer(r, "../Fonts/DIMITRI.ttf", 38);

	t->message = "PLEASE DRAG IN A MUSIC FILE";
	textTure = t->RenderText(t->message, white);
	textRect.x = 340;
	textRect.y = 300;
	textRect.w = 500;
	textRect.h = 50;

	SDL_RenderCopy(r, textTure, 0, &textRect);

	doOnce = false;
	transOutBool = false;
	transOutTimer = 0;
	DEBUG_MSG("DragFile Scene Created");

	conMan->LoadTexture("../Textures/transitionIn.png", "transIn", 4000, 1200, 1);
	transInPos = new Vector2D(-1000, 0);
	transOutPos = new Vector2D(-3000, 0);
}

DragMusicFile::~DragMusicFile()
{
	delete t;
	delete conMan;
	delete rend;
	delete t;
	delete t2;
	delete textTure;
	delete textTure2;
	delete path;
}

void DragMusicFile::Event()
{

}

void DragMusicFile::Update(SDL_DisplayMode window)
{
	screenWidth = window.w;

	
	if (transIn())
	{
		if (TheGame::Instance()->Gete()->type == SDL_DROPFILE && !done)
		{
			SDL_Event* S = TheGame::Instance()->Gete();
			path = S->drop.file;
			printf("File Dropped: %s", path);
			BeatDetector::Instance()->Load(1024, path);
			done = true;
			DEBUG_MSG(BeatDetector::Instance()->getSongName());
		}

		if (done)
		{
			t->message = "Thank you. Please press Enter to begin";
			textTure = t->RenderText(t->message, white);

			if (!doOnce)
			{

				std::string songName = BeatDetector::Instance()->getSongName();
				int lastindex = songName.find_last_of(".");
				std::string rawname = songName.substr(0, lastindex);

				t2->message = rawname;

				std::string artistName = BeatDetector::Instance()->getArtistName();

				if (artistName != "none")
				{
					artistName.insert(0, " - ");
					t3->message = artistName;
				}
				else
					t3->message = " - Unknown Artist";

				textTure2 = t2->RenderText(t2->message, white);
				textTure3 = t3->RenderText(t3->message, white);

				textRect2.x = window.w / 2 - 280;
				textRect2.y = 150;
				textRect2.w = 300;
				textRect2.h = 50;

				textRect3.x = window.w / 2 - 280;
				textRect3.y = 210;
				textRect3.w = 300;
				textRect3.h = 50;

				if (rawname.length() < 6)
				{
					textRect2.w = 300;
					textRect2.h = 50;
				}
				if (rawname.length() < 10 && rawname.length() > 6)
				{
					textRect2.w = 400;
					textRect2.h = 50;
				}
				if (rawname.length() < 15 && rawname.length() > 10)
				{
					textRect2.w = 600;
					textRect2.h = 50;
				}
				if (rawname.length() > 15)
				{
					textRect2.w = 600;
					textRect2.h = 50;
					textRect2.x -= 100;
				}

				if (artistName.length() < 6)
				{
					textRect3.w = 300;
					textRect3.h = 50;
				}

				if (artistName.length() < 10 && artistName.length() > 6)
				{
					textRect3.w = 400;
					textRect3.h = 50;
				}

				if (artistName.length() < 15 && artistName.length() > 10)
				{
					textRect3.w = 600;
					textRect3.h = 50;
				}

				std::string length;
				int mins = BeatDetector::Instance()->getSongLength()->getMinutes();
				int secs = BeatDetector::Instance()->getSongLength()->getSeconds();

				length = std::to_string(mins);
				int end = length.size();
				length.insert(end, ":");
				end = length.size();
				length.insert(end, std::to_string(secs));

				t4->message = length;
				textRect4.x = window.w / 2 - 180;
				textRect4.y = 270;
				textRect4.w = 100;
				textRect4.h = 50;

				textTure4 = t4->RenderText(t4->message, white);

				SDL_RenderCopy(rend, textTure2, 0, &textRect2);
				SDL_RenderCopy(rend, textTure3, 0, &textRect3);
				SDL_RenderCopy(rend, textTure4, 0, &textRect4);

				doOnce = true;
			}

		}
	}
	

	textRect.x = window.w / 2 - 350;
	textRect.y = window.h / 2 - 100;

	
	

	//if (BeatDetector::Instance()->isLoaded());
}

void DragMusicFile::Draw()
{
	SDL_RenderCopy(rend, textTure, 0, &textRect);

	if (done)
	{
		SDL_RenderCopy(rend, textTure2, 0, &textRect2);
		SDL_RenderCopy(rend, textTure3, 0, &textRect3);
		SDL_RenderCopy(rend, textTure4, 0, &textRect4);
	}
	if (transInPos->m_x < screenWidth)
	{
		conMan->DrawTexture("transIn", transInPos, SDL_FLIP_NONE);
	}

	if (done)
		conMan->DrawTexture("transOut", transOutPos, SDL_FLIP_NONE);
	
}

bool DragMusicFile::readyToTransition()
{
	return done;
}

int DragMusicFile::getHighScore()
{
	return 0;
}

bool DragMusicFile::transOut()
{
	if (!transOutBool)
		transOutTimer = SDL_GetTicks();

	transOutBool = true;

	//int i = SDL_GetTicks();

	if (SDL_GetTicks() - transOutTimer < 1000)
	{
		transOutPos->m_x += 40;
		conMan->DrawTexture("transOut", transOutPos, SDL_FLIP_NONE);
		return false;
	}

	return true;
}

bool DragMusicFile::transIn()
{
	if (transInPos->m_x > screenWidth)
	{
		return true;
	}
	transInPos->m_x += 25;

	return false;
}

