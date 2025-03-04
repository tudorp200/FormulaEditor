#include "button.h"

Button createButton(string text, Font& font, int charSize, int x, int y,
    int width, int height, StateColors stateColors[B_MAX_STATES],
    unsigned int borderThickness, Texture* icone) {
    
    Button button;
    button.state = B_INACTIVE;
    button.fullText = text;

    for (int i = 0; i < B_MAX_STATES; ++i)
        button.stateColors[i] = stateColors[i];

    button.background = createRect(x, y, width, height, stateColors[button.state].background, stateColors[button.state].border, borderThickness);

    FloatRect bgBounds = button.background.getLocalBounds();

    button.text = CreateText(text, font, charSize, x, y, bgBounds.width - 2 * (borderThickness + 1), stateColors[button.state].text);

    FloatRect textBounds = button.text.getLocalBounds();

    int offSetX = bgBounds.width / 2 - 1;

    if (text.size() > 0)
        offSetX -= textBounds.width / 2 + textBounds.left;

    int offsetYText = (bgBounds.height - charSize) / 2;

    if (icone) {
        button.icon.setTexture(*icone);
        FloatRect iconBounds = button.icon.getGlobalBounds();

        offSetX -= iconBounds.width / 2;

        if (text.size() > 0) {
            offSetX -= 2;
        }

        int offsetYIcon = (bgBounds.height - iconBounds.height) / 2;

        button.text.setPosition(x + iconBounds.width + 4 + offSetX,
            y + offsetYText);
        button.icon.setPosition(x + offSetX, y + offsetYIcon);
    }
    else {
        button.text.setPosition(x + offSetX, y + offsetYText);
    }
    
    return button;
}

void updateButtonState(Button& button, Event event, MouseEventType type, Vector2i& oldClick) {
    FloatRect buttonBounds =
        button.background.getGlobalBounds(); // get bounds of button

    switch (type) {
    case RELEASE:
        if (button.state == B_CLICKED) {
            if (isHovered(buttonBounds, event.mouseButton.x, event.mouseButton.y))
                button.state = B_HOVERED;
            else
                button.state =  B_INACTIVE;
        }
        break;
    case CLICK:
        if (isHovered(buttonBounds, event.mouseButton.x, event.mouseButton.y))
            button.state = B_CLICKED;
        else
            button.state = B_INACTIVE;

        if (button.state == B_CLICKED) {
            oldClick = Vector2i(event.mouseButton.x, event.mouseButton.y);
        }

        break;

    case MOVE:
        ///if (button.state != B_CLICKED) {
            if (isHovered(buttonBounds, event.mouseButton.x, event.mouseButton.y))
                button.state = B_HOVERED;
            else
                button.state = B_INACTIVE;
        //}
        break;
    }
}

void drawButton(RenderWindow& window, Button button) {
    
    button.text.setFillColor(button.stateColors[button.state].text);
    button.background.setFillColor(button.stateColors[button.state].background);
    button.background.setOutlineColor(button.stateColors[button.state].border);
    
    window.draw(button.background);
    window.draw(button.text);

    if (button.icon.getTexture()) {
        window.draw(button.icon);
    }
}
