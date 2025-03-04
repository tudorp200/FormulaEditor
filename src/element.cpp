#include "element.h"

bool isHovered(FloatRect box, int mouseX, int mouseY) {
    if ((box.left <= mouseX && mouseX <= box.left + box.width) &&
        (box.top <= mouseY && mouseY <= box.top + box.height)) {
        return true;
    }

    return false;
}

RectangleShape createRect(int x, int y, int width, int height, Color fill,
    Color outline, int borderThickness) {
    RectangleShape r;

    r.setPosition(x, y);
    r.setSize(Vector2f(width, height));
    r.setFillColor(fill);
    r.setOutlineColor(outline);
    r.setOutlineThickness(borderThickness);

    return r;
}

Text CreateText(string textString, Font& font, int charsize, int x, int y, int width, Color text) {
    Text textobj; 
    textobj.setFont(font);
    textobj.setPosition(x, y);
    textobj.setCharacterSize(charsize);
    textobj.setFillColor(text);
    textobj.setStyle(Text::Regular);
    textobj.setString(textString);


    return textobj;
}

void drawText(RenderWindow& window, Text text) { window.draw(text); }
