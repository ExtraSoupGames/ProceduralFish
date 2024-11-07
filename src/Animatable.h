#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "SDL.h"
using namespace std;
class AnimationElement {
	AnimationElement* next;
	int x;
	int y;
	int radius;
	SDL_Color colour;
public:
	AnimationElement(int radius, SDL_Color colour);
	void SetNext(AnimationElement* nextToSet);
};
class Animatable {
	AnimationElement* first;
	Animatable(vector<int> radii, vector<SDL_Color> colours);
};