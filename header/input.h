#ifndef INPUT_H
#define INPUT_H

#include "element.h"

#define I_MAX_STATES 3

enum InputState { I_INACTIVE, I_HOVERED, I_ACTIVE };

struct Input {
	RectangleShape background;
	Text text;
	Font font;
	StateColors stateColors[I_MAX_STATES];
	InputState state;
	string value;
	string placeholder;
	int cursorLocation;
	int startPosition;
	int displayLength;
};

Input createInput(StateColors stateColor[],Font& font, int x, int y, int width,
				int height, int charsize, int borderThickness, string displayText, string placeholder);

void updateInputState(Input &input, Event event, MouseEventType type, Input *& activeInput);

void updateInputText(Input &input, string newValue, string placeholder);

void drawInput(RenderWindow& window, Input& input);

void handleInput(Event event, Input& input);

void shrinkInput(Input& input);

void insertChar(Input* activeInput, char c);

void moveCursor(Input* activeInput, int direction);

void eraseChar(Input* activeInput);

void drawCursor(RenderWindow& window, Input* activeInput);

#endif