#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "SDL.h"
#include "RenderUtils.h"
using namespace std;
class AnimationElement {
	AnimationElement* next;
	int x;
	int y;
	int radius;
	SDL_Color colour;
public:
	AnimationElement(int radius, SDL_Color colour, int positionOffset);
	void SetNext(AnimationElement* nextToSet);
	void UpdatePosition(int prevX, int prevY);
	void Render(SDL_Renderer* renderer, int prevX, int prevY);
};
class Animatable {
	int chainLength;
	AnimationElement* first;
public:
	Animatable(vector<int> radii, vector<SDL_Color> colours);
	void Update();
	void Render(SDL_Renderer* renderer);
};