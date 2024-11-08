#include "Animatable.h"
Position AnimationElement::MoveElement(float prevX, float prevY, int previousRadius)
{
	float a = x - prevX;
	float b = y - prevY;
	float distance = sqrt((a * a) + (b * b));
	float normalisedX = a / distance;
	float normalisedY = b / distance;
	float finalX = prevX + (normalisedX * previousRadius);
	float finalY = prevY + (normalisedY * previousRadius);
	return *new Position{finalX, finalY};
}
AnimationElement::AnimationElement(int pRadius, SDL_Color pColour, int positionOffset) {
	next = nullptr;
	radius = pRadius;
	colour = pColour;
	x = 50;
	y = positionOffset;
}
void AnimationElement::SetNext(AnimationElement *nextToSet) {
	next = nextToSet;
}
void AnimationElement::UpdatePosition(float prevX, float prevY, int prevRadius){
	//update own position based on previous position
	Position newPosition = MoveElement(prevX, prevY, prevRadius);
	x = newPosition.x;
	y = newPosition.y;
	//update next element position
	if (next != nullptr) {
		next->UpdatePosition(x, y, radius);
	}
}
void AnimationElement::Render(SDL_Renderer* renderer) {
	//render own element
	//TODO
	RenderUtils::DrawCircle(renderer, x, y, radius);
	//render next element
	if (next != nullptr) {
		next->Render(renderer);
	}
}
Animatable::Animatable(vector<int> radii, vector<SDL_Color> colours) {
#pragma region errors
	if (radii.size() != colours.size()) {
		throw new exception("must input same amount of radii and colours to animatable constructor");
	}
	if (radii.size() < 1) {
		throw new exception("Animatable must have positive integer number of elements");
	}
#pragma endregion errors
	//populate a "chain" of animationElement
	float spacingModifier = 1;
	chainLength = radii.size();
	int positionOffset = 0;
	x = 0;
	y = 0;
	first = new AnimationElement(radii[0], colours[0], positionOffset);
	AnimationElement* current = first;
	AnimationElement* next;
	for (int i = 1; i < chainLength; i++) {
		next = new AnimationElement(radii[i], colours[i], positionOffset);
		positionOffset += radii[i] * spacingModifier;
		cout << "Initializing element at position: " << i << endl;
		current->SetNext(next);
		current = next;
	}
}
void Animatable::Update() {
	first->UpdatePosition(x, y, 1);
}
void Animatable::Render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	first->Render(renderer);
}
void Animatable::MoveTo(int newX, int newY) {
	x = newX;
	y = newY;
	cout << "Moved head to: " << x << " - " << y << endl;
}