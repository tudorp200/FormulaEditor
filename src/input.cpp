#include "input.h"

Input createInput(StateColors stateColor[],Font& font, int x, int y, int width, 
				  int height, int charsize, int borderThickness, string displayText, string placeholder) {
	Input input;
	input.state = I_INACTIVE;
	input.placeholder = placeholder;
	input.value = displayText;
	for (int i = 0; i < I_MAX_STATES; ++i)
		input.stateColors[i] = stateColor[i];

	input.background = createRect(x, y, width, height, stateColor[input.state].background
									,stateColor[input.state].border, borderThickness);

	string value = displayText == "" ? placeholder : displayText;

	input.text = CreateText(value, font, charsize, x + 10, y, 
							input.background.getGlobalBounds().width - 2 * (borderThickness + 1) - 10, 
							stateColor[input.state].text);

	// display only a segment of the text so it fits in the text box
	input.startPosition = 0;
	input.displayLength = input.value.size();
	input.cursorLocation = input.displayLength;

	input.text.setString(value);
	shrinkInput(input);

	float textWidth = input.text.getGlobalBounds().width;
	float boxWidth = input.background.getGlobalBounds().width;
	float offsetX = (boxWidth - textWidth) / 2.0f;
	
	int offsetY = input.background.getGlobalBounds().top +
				  input.background.getGlobalBounds().height / 2 -
				  input.text.getGlobalBounds().top -
				  input.text.getGlobalBounds().height / 2;

	input.text.setPosition(x, y + offsetY- 20);

	return input;
}


void drawInput(RenderWindow& window, Input& input) {
	
	input.text.setFillColor(input.stateColors[input.state].text);
	input.background.setFillColor(input.stateColors[input.state].background);
	input.background.setOutlineColor(input.stateColors[input.state].border);

	
	window.draw(input.background);
	window.draw(input.text);
	drawCursor(window, &input);
}

void updateInputState(Input& input, Event event, MouseEventType type, Input*& activeInput) {
	FloatRect inputBounds = input.background.getGlobalBounds();

	switch (type) {
	case CLICK:
		// update the currently active input
		if (isHovered(inputBounds, event.mouseButton.x, event.mouseButton.y)) {
			activeInput = &input;
			activeInput->state = I_ACTIVE;
		}

		break;
	case MOVE:
		if (input.state != I_ACTIVE) {
			input.state = isHovered(inputBounds, event.mouseMove.x, event.mouseMove.y)
				? I_HOVERED
				: I_INACTIVE;
		}
		break;
	}
}

void updateInputText(Input& input, string newValue, string newPlaceholder) {
	// update the input of the explorer
	input.value = newValue;

	if (newPlaceholder.size() > 0) {
		input.placeholder = newPlaceholder;
	}

	input.text.setString(input.value == "" ? input.placeholder: input.value);

	input.displayLength = input.value.size();
	input.cursorLocation = input.value.size();
	input.startPosition = 0;

	shrinkInput(input);
}

void handleInput(Event event, Input& input) {
	if (input.state == I_ACTIVE && event.type == Event::TextEntered) {
		if (event.text.unicode < 128) {
			if (event.text.unicode == '\b') { // Backspace
				if (!input.value.empty()) {
					eraseChar(&input); // Remove the last character
					updateInputText(input, input.value, input.placeholder);
				}
			}
			else if (event.text.unicode != '\r') { // Enter key
				char typedChar = static_cast<char>(event.text.unicode);;
				insertChar(&input, typedChar);
				updateInputText(input, input.value, "");
			}
		}
	}
}

void shrinkInput(Input& input) {
	while (input.text.getGlobalBounds().width >
		input.background.getGlobalBounds().width - 20) {
		// if the cursor is at the end of the input
		if (input.cursorLocation == input.displayLength) {
			input.cursorLocation--; // move cursor back
			input.displayLength--;  // shrink display length
			input.startPosition++;  // advance start position
		}
		// if the cursor is anywhere before the end
		else {
			input.displayLength--; // shrink display length
		}

		input.text.setString(
			input.value.substr(input.startPosition,
				input.displayLength)); // update string
	}
}

void insertChar(Input* activeInput, char c) {
	activeInput->value.insert(
		activeInput->startPosition + activeInput->cursorLocation, 1, c);

	// expand the displayed text if there is space
	if (activeInput->text.getGlobalBounds().width <
		activeInput->background.getGlobalBounds().width -
		2 * activeInput->text.getCharacterSize()) {
		activeInput->displayLength++;  // increse number of chars shown
		activeInput->cursorLocation++; // advance cursor
	}
	// move the cursor after the added character
	else {
		moveCursor(activeInput, 1);
	}

	activeInput->text.setString(
		activeInput->value.substr(activeInput->startPosition,
			activeInput->displayLength)); // update string
}

void eraseChar(Input* activeInput) {
	// delete the character before the cursor position
	if (activeInput->startPosition + activeInput->cursorLocation > 0) {
		activeInput->value.erase(
			activeInput->startPosition + activeInput->cursorLocation - 1, 1);

		// first case: text is smaller than the input or equal
		if (activeInput->displayLength == activeInput->value.size() + 1) {
			// a: the cursor is not at the beginning of the text
			if (activeInput->cursorLocation > 0) {
				activeInput->displayLength--; // shrink displayed text
				activeInput->cursorLocation--;
			}
		}
		// second case: text is larger than the input
		else {
			// a: there is no text to the right of the displayed text
			//    so try to expand the text from the left
			//
			//    being at this case implies that startPosition > 0
			if (activeInput->startPosition + activeInput->displayLength ==
				activeInput->value.size() + 1) {
				activeInput->startPosition--;
			}
			// b: there is text to the right of the displayed text
			//    so try to expand the input from the right
			else {
				// move cursor to the left if possible
				if (activeInput->cursorLocation > 0) {
					activeInput->cursorLocation--;
				}
				// move start position to the left if cursor can't be moved
				else {
					activeInput->startPosition--;
				}
			}
		}
	}

	string newValue = activeInput->value.substr(activeInput->startPosition,
		activeInput->displayLength);

	activeInput->text.setString(
		newValue == "" ? activeInput->placeholder : newValue); // update string
}




void moveCursor(Input* activeInput, int direction) {
	// update the cursor's location only if it doesn't get out of the input's
	// bounds
	int newCursorLocation = activeInput->cursorLocation + direction;
	int newStartPosition = activeInput->startPosition + direction;

	if (0 <= newCursorLocation &&
		newCursorLocation <= activeInput->displayLength) {
		activeInput->cursorLocation = newCursorLocation;
	}
	// move the start position if cursor location can't be updated
	else if (0 <= newStartPosition &&
		newStartPosition + activeInput->displayLength <=
		activeInput->value.size()) {
		activeInput->startPosition = newStartPosition;
	}

	activeInput->text.setString(
		activeInput->value.substr(activeInput->startPosition,
			activeInput->displayLength)); // update string
}

void drawCursor(RenderWindow& window, Input* activeInput) {
	if (activeInput && activeInput->state == I_ACTIVE) {
		int charSize = activeInput->text.getCharacterSize();
		Vector2f textPos =
			activeInput->text.findCharacterPos(activeInput->cursorLocation);
		FloatRect inputBounds = activeInput->background.getGlobalBounds();

		RectangleShape r(Vector2f(1, 9 * charSize / 10));
		r.setFillColor(activeInput->stateColors[activeInput->state].text);
		r.setPosition(Vector2f(textPos.x, inputBounds.top + inputBounds.height / 2 -
			r.getGlobalBounds().height / 2));

		window.draw(r);
	}
}
