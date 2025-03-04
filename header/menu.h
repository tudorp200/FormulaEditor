#ifndef MENU_H
#define MENU_H

#include "button.h"
#include "element.h"
#include "textbox.h"
#include "input.h"
#include <windows.h>
#include <fstream> // Include for file operations
#include <iostream>

void handleFormula(int width, int height, Font& font, int charsize, StateColors stateColors[]);

void handleAbout(int width, int height, Font& font, int charsize);

void handleSave(string formula);

#endif


