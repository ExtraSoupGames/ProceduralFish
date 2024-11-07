#include "Animatable.h"
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
void AnimationElement::UpdatePosition(int prevX, int prevY){
	//update own position based on previous position
	//TODO
	//update next element position
	if (next != nullptr) {
		next->UpdatePosition(x, y);
	}
}
void AnimationElement::Render(SDL_Renderer* renderer, int prevX, int prevY) {
	//render own element
	//TODO
	RenderUtils::DrawCircle(renderer, x, y, radius);
	//render next element
	if (next != nullptr) {
		next->Render(renderer, x, y);
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
	float spacingModifier = 0.8f;
	chainLength = radii.size();
	int positionOffset = 0;
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
	first->UpdatePosition(0, 0);
}
void Animatable::Render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	first->Render(renderer, 0, 0);
}