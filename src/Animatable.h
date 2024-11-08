#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "SDL.h"
#include "RenderUtils.h"
using namespace std;
struct Position {
	float x;
	float y;
};
class AnimationElement {
	AnimationElement* next;
	float x;
	float y;
	float radius;
	SDL_Color colour;
	Position MoveElement(float prevX, float prevY, int prevRadius);
public:
	AnimationElement(int radius, SDL_Color colour, int positionOffset);
	void SetNext(AnimationElement* nextToSet);
	void UpdatePosition(float prevX, float prevY, int prevRadius);
	void Render(SDL_Renderer* renderer);
};
class Animatable {
	int chainLength;
	AnimationElement* first;
	float x;
	float y;
public:
	Animatable(vector<int> radii, vector<SDL_Color> colours);
	void Update();
	void Render(SDL_Renderer* renderer);
	void MoveTo(int newX, int newY);
};