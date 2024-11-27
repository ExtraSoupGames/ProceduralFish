#pragma once
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include <vector>
using namespace std;
struct Position {
	float x;
	float y;
	Position(float pX, float pY) {
		x = pX;
		y = pY;
	}
	Position operator-(Position& const other) {
		return Position(x - other.x, y - other.y);
	}
	float GetMagnitude() {
		return sqrt(x * x + y * y);
	}
	float DotProduct(Position other) {
		return (x * other.x) + (y * other.y);
	}
	void Rotate(float oldAngle, float newAngle, Position rotateAround) {
		float distance = (rotateAround - * new Position(x, y)).GetMagnitude();
		//new vector is a vector starting at rotateAround, extending distance in newAngle
		x = rotateAround.x + (distance * cos(newAngle));
		y = rotateAround.y + (distance * sin(newAngle));
	}
};
struct LineData {
	Position pos1;
	Position pos2;
};
class RenderUtils {
public:
	static void DrawCircle(SDL_Renderer* renderer, int centreX, int centreY, int radius);
	static void RenderBody(SDL_Renderer* renderer, vector<LineData*>* lineData);
};