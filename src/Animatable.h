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
	Position(float pX, float pY) {
		x = pX;
		y = pY;
	}
};
class DetailElement {
	//in relation to connected element
	float angle;
	float distance;
	//for rendering
	float radius;
	SDL_Color colour;
public:
	void Render(SDL_Renderer* renderer, Position connectedElementPos);
	Position CalculatePosition(Position connectedElementPos);
};
//one element of a creature, connected by pointers to the next one along
class AnimationElement {
	AnimationElement* next;
	float x;
	float y;
	float radius;
	SDL_Color colour;
	vector<DetailElement*> details;
	Position MoveElement(float prevX, float prevY, int prevRadius);
public:
	AnimationElement(int radius, SDL_Color colour, int positionOffset);
	void SetNext(AnimationElement* nextToSet);
	void UpdatePosition(float prevX, float prevY, int prevRadius);
	void Render(SDL_Renderer* renderer);
	AnimationElement* GetNext();
};
//A whole creature, for example a fish
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
	AnimationElement* GetElementAt(int index);
};