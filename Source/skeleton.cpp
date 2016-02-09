#include <iostream>
#include <glm/glm.hpp>
#include <SDL.h>
#include "SDLauxiliary.h"
#include "TestModel.h"

using namespace std;
using glm::vec3;
using glm::mat3;

/* ----------------------------------------------------------------------------*/
/* GLOBAL VARIABLES                                                            */
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;
SDL_Surface* screen;
int t;

/* ----------------------------------------------------------------------------*/
/* FUNCTIONS                                                                   */
void Update();
void Draw();
void Interpolate(float a, float b, vector<float>& result);

int main(int argc, char* argv[])
{
	screen = InitializeSDL(SCREEN_WIDTH, SCREEN_HEIGHT);
	t = SDL_GetTicks();	// Set start value for timer.

	while(NoQuitMessageSDL())
	{
		Update();
		Draw();
	}

	SDL_SaveBMP(screen, "screenshot.bmp");

	vector<float> result(10);
	Interpolate(5, 14, result);
	for( unsigned int i = 0; i < result.size(); ++i)
		cout << result[i] << " ";
	cout << endl;
	return 0;
}

void Update()
{
	// Compute frame time:
	int t2 = SDL_GetTicks();
	float dt = float(t2-t);
	t = t2;
	cout << "Render time: " << dt << " ms." << endl;
}

void Draw()
{
	if(SDL_MUSTLOCK(screen))
		SDL_LockSurface(screen);

	for(int y = 0; y < SCREEN_HEIGHT; ++y)
	{
		for(int x = 0; x < SCREEN_WIDTH; ++x)
		{
			vec3 color(0.0, 1.0, 0.0);
			PutPixelSDL(screen, x, y, color);
		}
	}

	if(SDL_MUSTLOCK(screen))
		SDL_UnlockSurface(screen);

	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

void Interpolate(float a, float b, vector<float>& result)
{
	for( unsigned int i=0; i < result.size(); i++)
		result[i] = a + i * (b - a) / (result.size() - 1);
}
