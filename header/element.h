#ifndef ELEMENT_H
#define ELEMENT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

enum MouseEventType{MOVE, RELEASE, CLICK, DCLICK};

struct StateColors {
	Color text, background, border;
};

bool isHovered(FloatRect box, int mouseX, int mouseY);


RectangleShape createRect(int x, int y, int width, int height, Color fill,
    Color outline = Color::Transparent,
    int borderThickness = 0);



Text CreateText(string textString, Font& font, int charsize, int x, int y, int width, Color text);


void drawText(RenderWindow& window, Text text);

#endif
