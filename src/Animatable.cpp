#include "Animatable.h"

#pragma region DetailElement
DetailElement::DetailElement(float pAngle, float pDistance, float pRadius, SDL_Color pColour)
{
	angle = pAngle;
	distance = pDistance;
	radius = pRadius;
	colour = pColour;
}
void DetailElement::Render(SDL_Renderer* renderer, Position connectedElementPos, float baseAngle) {
	Position p = CalculatePosition(connectedElementPos, baseAngle);
	SDL_SetRenderDrawColor(renderer,colour.r, colour.g, colour.b, colour.a);
	RenderUtils::DrawCircle(renderer, p.x, p.y, radius);
}
Position DetailElement::CalculatePosition(Position connectedElementPos, float baseAngle) {
	//calculate the position in relation to the circle using the parametric equation of a circle
	float newX = distance * (cos(angle + baseAngle));
	float newY = distance * (sin(angle + baseAngle));
	newX = connectedElementPos.x + newX;
	newY = connectedElementPos.y + newY;
	return Position(newX, newY);

}
#pragma endregion DetailElement

#pragma region AnimationElement
AnimationElement::AnimationElement(int pRadius, SDL_Color pColour, int positionOffset) {
	next = nullptr;
	radius = pRadius;
	colour = pColour;
	x = 50;
	y = positionOffset;
	details = *new vector<DetailElement*>();
	angle = 0;
	angleConstraint = 0.25 * M_PI;
}
void AnimationElement::AddDetail(float angle, float distance, float radius, SDL_Color pColour)
{
	details.push_back(new DetailElement(angle, distance, radius, pColour));
}
float WrapAngle(float angle) {
	while (angle < 0) angle += 2 * M_PI;
	while (angle >= 2 * M_PI) angle -= 2 * M_PI;
	return angle;
}
//constrain this element's position to the previous elements radius
Position AnimationElement::MoveElement(float prevX, float prevY, int previousRadius, float previousAngle)
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
	// Calculate the angle of the current position

	angle = WrapAngle(CalculateAngle(prevX, prevY));
	float thisAngle = WrapAngle(CalculateAngle(prevX, prevY));
	float wrappedPreviousAngle = WrapAngle(previousAngle);

	// Compute angular difference
	float deltaAngle = WrapAngle(thisAngle - wrappedPreviousAngle);
	if (deltaAngle > M_PI) deltaAngle -= 2 * M_PI;

	// Apply angle constraint
	if (abs(deltaAngle) > angleConstraint) {
		float constrainedAngle = wrappedPreviousAngle + (deltaAngle > 0 ? angleConstraint : -angleConstraint);
		constrainedAngle = WrapAngle(constrainedAngle);
		finalX = prevX + (previousRadius * cos(constrainedAngle));
		finalY = prevY + (previousRadius * sin(constrainedAngle));
		return Position(finalX, finalY);
	}
	return *new Position{finalX, finalY};
}
float AnimationElement::CalculateAngle(float prevX, float prevY)
{
	float angle = atan2(y - prevY, x - prevX);
	return WrapAngle(angle);
}
//passes through the chain updating each element's position
void AnimationElement::UpdatePosition(float prevX, float prevY, int prevRadius, float previousAngle){
	//update own position based on previous position
	Position newPosition = MoveElement(prevX, prevY, prevRadius, previousAngle);
	x = newPosition.x;
	y = newPosition.y;
	//update next element position
	if (next != nullptr) {
		next->UpdatePosition(x, y, radius, angle);
	}
}
void AnimationElement::UpdatePosition(float prevX, float prevY)
{
	float calculatedAngle = CalculateAngle(prevX, prevY);
	UpdatePosition(prevX, prevY, 5, calculatedAngle);
}
//render the element
void AnimationElement::Render(SDL_Renderer* renderer) {
	//render own element
	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
	RenderUtils::DrawCircle(renderer, x, y, radius);
	//render next element
	if (next != nullptr) {
		next->Render(renderer);
	}
}
//render the details of this element, seperated to ensure details are always rendered on top of the body
void AnimationElement::RenderDetails(SDL_Renderer* renderer, float prevX, float prevY)
{
	//render details
	for (DetailElement* d : details) {
		d->Render(renderer, *new Position(x, y), angle);
	}
	//begin next element's detail rendering
	if (next != nullptr) {
		next->RenderDetails(renderer, x, y);
	}
}
//get the next element in the chain
AnimationElement* AnimationElement::GetNext()
{
	return next;
}
//set the next element of the chain
void AnimationElement::SetNext(AnimationElement* nextToSet) {
	next = nextToSet;
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
	first->UpdatePosition(x, y);
}
//render the creature
void Animatable::Render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	first->Render(renderer);
	first->RenderDetails(renderer, x, y);
}
//set the position of the head of the creature
void Animatable::MoveTo(int newX, int newY) {
	x = newX;
	y = newY;
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