#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "SDL.h"
#include "RenderUtils.h"
using namespace std;
struct Position {
	int x;
	int y;
};
class AnimationElement {
	AnimationElement* next;
	int x;
	int y;
	int radius;
	SDL_Color colour;
	Position MoveElement(int prevX, int prevY, int prevRadius);
public:
	AnimationElement(int radius, SDL_Color colour, int positionOffset);
	void SetNext(AnimationElement* nextToSet);
	void UpdatePosition(int prevX, int prevY, int prevRadius);
	void Render(SDL_Renderer* renderer);
};
class Animatable {
	int chainLength;
	AnimationElement* first;
	int x;
	int y;
public:
	Animatable(vector<int> radii, vector<SDL_Color> colours);
	void Update();
	void Render(SDL_Renderer* renderer);
	void MoveTo(int newX, int newY);
};