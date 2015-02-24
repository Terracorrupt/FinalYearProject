#include "DragMusicFile.h"
#include "Game.h";

DragMusicFile::DragMusicFile(SDL_Renderer* r, ContentManager* c)
{
	conMan = c;
	rend = r;
	path = NULL;

	t = new TextRenderer(r, "../Fonts/DIMITRI.ttf", 28);
	white = { 255, 255, 255 };

	t->message = "PLEASE DRAG IN A MUSIC FILE";
	textTure = t->RenderText(t->message, white);
	textRect.x = 400;
	textRect.y = 300;
	textRect.w = 500;
	textRect.h = 50;

	SDL_RenderCopy(r, textTure, 0, &textRect);

	DEBUG_MSG("DragFile Scene Created");

	

}

DragMusicFile::~DragMusicFile()
{
	delete t;
	delete conMan;
	delete rend;
}

void DragMusicFile::Event()
{

}

void DragMusicFile::Update(SDL_DisplayMode window)
{
	if (TheGame::Instance()->Gete()->type == SDL_DROPFILE && !done)
	{
		SDL_Event* S = TheGame::Instance()->Gete();
		path = S->drop.file;
		printf("File Dropped: %s", path);
		BeatDetector::Instance()->Load(1024, path);
		done = true;
	}

	if (done)
		t->message = "Thank you. Please press space to begin";
	
	textRect.x = window.w / 2 - 350;
	textRect.y = window.h / 2 - 100;


	//if (BeatDetector::Instance()->isLoaded());
}

void DragMusicFile::Draw()
{
	SDL_RenderCopy(rend, textTure, 0, &textRect);
}
