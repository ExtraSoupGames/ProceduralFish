#include "RenderUtils.h"
void RenderUtils::DrawCircle(SDL_Renderer* renderer, int centreX, int centreY, int radius) {
	//draws a circle by drawing horizontal lines of varying length on top of each other
	for (int i = centreY - radius; i < centreY + radius; i++) {
		//calculate horizontal line length using trigonometry
		int a = i-centreY;
		double angle = SDL_asin((float)a / (float)radius);
		float lineLength = SDL_cos(angle) * radius;
		SDL_RenderDrawLine(renderer, (float)centreX + lineLength, i, (float)centreX - lineLength, i);
	}
}