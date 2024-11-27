#include "RenderUtils.h"
void RenderUtils::DrawCircle(SDL_Renderer* renderer, int centreX, int centreY, int radius) {
	//draws a circle by drawing horizontal lines of varying length on top of each other
	for (int i = centreY - radius; i < centreY + radius; i++) {
		//calculate horizontal line length using trigonometry
		int a = i - centreY;
		double angle = SDL_asin((float)a / (float)radius);
		float lineLength = SDL_cos(angle) * radius;
		SDL_RenderDrawLine(renderer, (float)centreX + lineLength, i, (float)centreX - lineLength, i);
	}
}

void RenderUtils::RenderBody(SDL_Renderer* renderer, vector<LineData*>* lineData)
{
	vector<SDL_Point>* points = new vector<SDL_Point>();
	for (LineData* line : *lineData) {
		points->push_back(SDL_Point{ (int)line->pos1.x, (int)line->pos1.y });
		points->insert(points->begin(), SDL_Point{ (int)line->pos2.x, (int)line->pos2.y });
	}
	vector<Sint16> xcoords;
	vector<Sint16> ycoords;
	for (SDL_Point p : *points) {
		xcoords.push_back(p.x);
		ycoords.push_back(p.y);
	}
	Uint8 r = 255, g = 0, b = 0, a = 255; // Red color with full opacity
	GFX_filledPolygonRGBA(renderer, xcoords.data(), ycoords.data(), points->size(), r, g, b, a);

}
