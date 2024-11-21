#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "SDL.h"
#include "RenderUtils.h"
using namespace std;
class DetailElement {
	//angle in relation to the connected element
	float angle;
	//distance from the centre of the connected element
	float distance;
	//for rendering
	float radius;
	//for rendering
	SDL_Color colour;
public:
	DetailElement(float pAngle, float pDistance, float pRadius, SDL_Color pColour);
	void Render(SDL_Renderer* renderer, Position connectedElementPos, float baseAngle);
	Position CalculatePosition(Position connectedElementPos, float baseAngle);
};
//one element of a creature, connected by pointers to the next one along
class AnimationElement {
	AnimationElement* next;
	float x;
	float y;
	float radius;
	float angleConstraint;
	float angle;
	SDL_Color colour;
	vector<DetailElement*> details;
	Position MoveElement(float prevX, float prevY, int prevRadius, float previousAngle);
	float CalculateAngle(float prevX, float prevY);
public:
	AnimationElement(int radius, SDL_Color colour, int positionOffset);
	void AddDetail(float angle, float distance, float radius, SDL_Color pColour);
	//passing through the body chain
	void UpdatePosition(float prevX, float prevY, int prevRadius, float previousAngle);
	//the initial element has no angle or radius
	void UpdatePosition(float prevX, float prevY);
	void Render(vector<LineData*>* lineData);
	LineData* GetLinePoints();
	void RenderDetails(SDL_Renderer* renderer, float prevX, float prevY);
	void SetNext(AnimationElement* nextToSet);
	AnimationElement* GetNext();
};
//A whole creature, for example a fish
class Animatable {
	int chainLength;
	AnimationElement* first;
	float x;
	float y;
public:
	Animatable(vector<int> radii);
	void Update();
	void Render(SDL_Renderer* renderer);
	void MoveTo(int newX, int newY);
	AnimationElement* GetElementAt(int index);
};