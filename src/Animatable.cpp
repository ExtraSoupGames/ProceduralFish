#include "Animatable.h"

#pragma region DetailElement
void DetailElement::Render(SDL_Renderer* renderer, Position connectedElementPos) {
	Position p = CalculatePosition(connectedElementPos);
	RenderUtils::DrawCircle(renderer, p.x, p.y, radius);
}
Position DetailElement::CalculatePosition(Position connectedElementPos) {
	//calculate the position in relation to the circle using the parametric equation of a circle
	float x = radius * (cos(angle));
	float y = radius * (sin(angle));
}
#pragma endregion DetailElement

#pragma region AnimationElement
AnimationElement::AnimationElement(int pRadius, SDL_Color pColour, int positionOffset) {
	next = nullptr;
	radius = pRadius;
	colour = pColour;
	x = 50;
	y = positionOffset;
}
//constrain this element's position to the previous elements radius
Position AnimationElement::MoveElement(float prevX, float prevY, int previousRadius)
{
	//calculate vector of previous element to new
	float a = x - prevX;
	float b = y - prevY;
	//find the magnitude of the vector
	float distance = sqrt((a * a) + (b * b));
	//normalise the vector
	float normalisedX = a / distance;
	float normalisedY = b / distance;
	//extend the normalised vector to the radius of the previous element
	float finalX = prevX + (normalisedX * previousRadius);
	float finalY = prevY + (normalisedY * previousRadius);
	return *new Position{finalX, finalY};
}
//set the next element of the chain
void AnimationElement::SetNext(AnimationElement *nextToSet) {
	next = nextToSet;
}
//passes through the chain updating each element's position
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
//render the element
void AnimationElement::Render(SDL_Renderer* renderer) {
	//render own element
	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
	RenderUtils::DrawCircle(renderer, x, y, radius);
	//render details
	for (DetailElement* d : details) {
		d->Render(renderer, *new Position(x, y));
	}
	//render next element
	if (next != nullptr) {
		next->Render(renderer);
	}
}
AnimationElement* AnimationElement::GetNext()
{
	return next;
}
#pragma endregion AnimationElement

#pragma region Animatable
Animatable::Animatable(vector<int> radii, vector<SDL_Color> colours) {
#pragma region errors
	if (radii.size() != colours.size()) {
		throw new exception("must input same amount of radii and colours to animatable constructor");
	}
	if (radii.size() < 1) {
		throw new exception("Animatable must have positive integer number of elements");
	}
#pragma endregion errors
	x = 0;
	y = 0;
	//populate a "chain" of animationElement
	chainLength = radii.size();
	int positionOffset = 0;
	first = new AnimationElement(radii[0], colours[0], positionOffset);
	AnimationElement* current = first;
	AnimationElement* next;
	for (int i = 1; i < chainLength; i++) {
		next = new AnimationElement(radii[i], colours[i], positionOffset);
		positionOffset += radii[i];
		current->SetNext(next);
		current = next;
	}
}
//update each element in the body of the creature
void Animatable::Update() {
	first->UpdatePosition(x, y, 1);
}
//render the creature
void Animatable::Render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	first->Render(renderer);
}
//set the position of the head of the creature
void Animatable::MoveTo(int newX, int newY) {
	x = newX;
	y = newY;
	cout << "Moved head to: " << x << " - " << y << endl;
}
AnimationElement* Animatable::GetElementAt(int index)
{
	if (index > chainLength) {
		throw new exception("index out of bounds of chain");
	}
	AnimationElement* current = first;
	for (int i = 0; i < index; i++) {
		current = current->GetNext();
	}
	return current;
}
#pragma endregion Animatable