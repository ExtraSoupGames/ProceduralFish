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

void RenderUtils::RenderLines(SDL_Renderer* renderer, vector<LineData*>* lineData)
{
	vector<SDL_Point>* points = new vector<SDL_Point>();
	for (LineData* line : *lineData) {
		points->push_back(SDL_Point{ (int)line->pos1.x, (int)line->pos1.y });
		points->insert(points->begin(), SDL_Point{ (int)line->pos2.x, (int)line->pos2.y });
	}
	SDL_Point* arrPoints = points->data();
	SDL_RenderDrawLines(renderer, arrPoints, points->size());
	SDL_Point firstPoint = *points->begin();
	SDL_Point lastPoint = *(points->end() - 1);
	SDL_RenderDrawLine(renderer, firstPoint.x, firstPoint.y, lastPoint.x, lastPoint.y);

}
