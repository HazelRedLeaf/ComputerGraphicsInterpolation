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
void Interpolate(vec3 a, vec3 b, vector<vec3>& result);

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

	// colours at the four corners of the screen: 
	vec3 topLeft(1,0,0);		// red
	vec3 topRight(0,0,1);		// blue
	vec3 bottomRight(0,1,0);	// green
	vec3 bottomLeft(1,1,0);		// yellow

	// interpolate both sides of the screen first
	vector<vec3> leftSide(SCREEN_HEIGHT);
	vector<vec3> rightSide(SCREEN_HEIGHT);
	Interpolate(topLeft, bottomLeft, leftSide);
	Interpolate(topRight, bottomRight, rightSide);

	for(int y = 0; y < SCREEN_HEIGHT; ++y)
	{
		vector<vec3> imageRow(SCREEN_WIDTH);
		Interpolate(leftSide[y], rightSide[y], imageRow);
		for(int x = 0; x < SCREEN_WIDTH; ++x)
		{
			PutPixelSDL(screen, x, y, imageRow[x]);
		}
	}

	if(SDL_MUSTLOCK(screen))
		SDL_UnlockSurface(screen);

	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

void Interpolate(vec3 a, vec3 b, vector<vec3>& result)
{
	for( unsigned int i=0; i < result.size(); i++)
	{
		result[i].x = a.x + i * (b.x - a.x) / (result.size() - 1);
		result[i].y = a.y + i * (b.y - a.y) / (result.size() - 1);
		result[i].z = a.z + i * (b.z - a.z) / (result.size() - 1);
	}
}

/* Simple case
void Interpolate(float a, float b, vector<float>& result)
{
	for( unsigned int i=0; i < result.size(); i++)
		result[i] = a + i * (b - a) / (result.size() - 1);
} */
