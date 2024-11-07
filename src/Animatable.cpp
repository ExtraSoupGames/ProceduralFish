#include "Animatable.h"
AnimationElement::AnimationElement(int pRadius, SDL_Color pColour) {
	next = nullptr;
	radius = pRadius;
	colour = pColour;
	x = 0;
	y = 0;
}
void AnimationElement::SetNext(AnimationElement *nextToSet) {
	next = nextToSet;
}
Animatable::Animatable(vector<int> radii, vector<SDL_Color> colours) {
	if (radii.size() != colours.size()) {
		throw new exception("must input same amount of radii and colours to animatable constructor");
	}
	if (radii.size() < 1) {
		throw new exception("Animatable must have positive integer number of elements");
	}
	first = new AnimationElement(radii[0], colours[0]);
	AnimationElement* current = first;
	AnimationElement* next;
	for (int i = 1; i < radii.size(); i++) {
		next = new AnimationElement(radii[i], colours[i]);
		cout << "Initializing element at position: " << i << endl;
		current->SetNext(next);
		current = next;
	}
}