#include "menu.h"

void handleFormula(int width, int height, Font& font, int charsize, StateColors stateColors[]) {

	RenderWindow window(VideoMode(width, height), "Formula Log");
	string displayText, placeholder = "";

	

	Input input = createInput(stateColors, font, 0, 0, width, 100, charsize, 1, displayText, placeholder);
	Input* activeInput = nullptr;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				window.close();
			
				break;
			case Event::MouseButtonReleased:
				updateInputState(input, event, RELEASE, activeInput);
				break;
			case Event::MouseButtonPressed:
				if (activeInput && !isHovered(activeInput->background.getGlobalBounds(),
					event.mouseButton.x, event.mouseButton.y)) {
					activeInput->state = I_INACTIVE;
					activeInput = nullptr;
				}
				updateInputState(input, event, CLICK, activeInput);
				break;
			case Event::MouseMoved:
				updateInputState(input, event, MOVE, activeInput);
				break;
			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::Enter:
					/// verific daca e scrisa corect si daca e o afisez frumos
					/// daca nu afisez o eroare 
					/// convert to png 
					break;
				case Keyboard::Backspace:
					if (activeInput) {
						eraseChar(activeInput);
						updateInputText(*activeInput, activeInput->value, "");
					}
					break;
				case Keyboard::Left:
					if (activeInput)
						moveCursor(activeInput, -1);
					break;
				case Keyboard::Right:
					if (activeInput)
						moveCursor(activeInput, 1);
					break;

				}
				break;
			case Event::TextEntered:
				if (activeInput) {
				char enteredChar = event.text.unicode;
				if (enteredChar < 128 && enteredChar > 31)
					insertChar(activeInput, enteredChar);
				}
				break;

			}
		}

		window.clear(Color(230, 230, 230));
		drawInput(window, input);
		window.display();
	}
}

void handleAbout(int width, int height, Font& font, int charsize) {
	RenderWindow window(VideoMode(width, height), "ABOUT");
	// center window on the screen
	window.setPosition(
		Vector2i(VideoMode::getDesktopMode().width / 2 - width / 2,
			VideoMode::getDesktopMode().height / 2 - height / 2));

	TextBox textbox = createTextBox("FomurlaEditor DEMO\n ©Realised by us", font, charsize, 0, 0, width,
		height, Color::Black, Color::White, Color::White, 1);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				window.close();
				break;
			}
			Color bg(230, 230, 230);
			window.clear(bg);
			drawTextBox(window, textbox);
			window.display();
		}
	}
}

