#include <SFML/Graphics.hpp>
#include <iostream>

#include "button.h"
#include "element.h"
#include "textbox.h"
#include "input.h"
#include "menu.h"
#include "backend.h"




#define W_WIDTH 1280
#define W_HEIGHT 720
#define TITLE "FORMULA EDITOR"
#define BUTTONS 6

using namespace sf;
using namespace std;


int main()
{

    RenderWindow window( VideoMode (W_WIDTH, W_HEIGHT), TITLE);

    window.setPosition(Vector2i(VideoMode::getDesktopMode().width / 2 - W_WIDTH / 2,
                                VideoMode::getDesktopMode().height / 2 - W_HEIGHT / 2));
   
    int btnWidth = W_WIDTH / (BUTTONS - 1), btnHeight = 32;
    Button button[BUTTONS];

    string buttonString[BUTTONS] = { "Open", "Save", "Print", "Formula", "About","Convert"};

    Font font; font.loadFromFile("arial.ttf");
    Color darkGrey(40, 40, 40);
    Color lightGrey(178, 178, 178);
    Color bg(230, 230, 230);
    StateColors stateColors[B_MAX_STATES];

    stateColors[1] = {Color::White, darkGrey, lightGrey};
    stateColors[0] = { Color::White , darkGrey, lightGrey};
    stateColors[2] = { Color::White, darkGrey, darkGrey };

    /// load icons for every button
    string forIcon[BUTTONS] = { "open.png", 
                                "save.png", 
                                "print.png", 
                                "formula.png", 
                                "about.png", 
                                "convert.png"};
    Texture icons[BUTTONS];
    for (int i = 0; i < BUTTONS - 1; ++i) {
        icons[i].loadFromFile(forIcon[i]);
        button[i] = createButton(buttonString[i], font, 18 , i * btnWidth, 0, btnWidth, btnHeight + 10, stateColors, 1, &icons[i]);
    }
    icons[5].loadFromFile(forIcon[5]);
    button[5] = createButton(buttonString[5], font, 18, (W_WIDTH - btnWidth ) / 2, (W_HEIGHT - btnHeight) / 2, btnWidth, btnHeight, stateColors, 1, &icons[5]);
    
    Vector2i oldClick;
    /// for input
    float x = (W_WIDTH - btnWidth * 2) / 2, y = (W_HEIGHT - 15*btnHeight) / 2;
    string displayText, placeHolder="";
    Input input = createInput(stateColors, font, x, y, btnWidth * 2, btnHeight*5, 36, 1, displayText, placeHolder);
    Input* activeInput = nullptr; 
    
    bool inputVisible[BUTTONS] = {0};

    while (window.isOpen()) {
        Event event;
        ///handle events;
        while (window.pollEvent(event)) {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                cout << "Handling event closed" << endl;
                exit(EXIT_SUCCESS);
                break;
            case Event::MouseButtonReleased:
                for (int i = 0; i < BUTTONS; ++i)
                    updateButtonState(button[i], event, RELEASE, oldClick);
               
                break;
            case Event::MouseButtonPressed:

                oldClick = Vector2i(event.mouseButton.x, event.mouseButton.y);
                for (int i = 0; i < BUTTONS; ++i) {
                    updateButtonState(button[i], event, CLICK, oldClick);
                }

                for (int i = 0; i < BUTTONS; ++i) {
                    inputVisible[i] = button[i].state == B_CLICKED ? true : false;
                }
                break;
            case Event::MouseMoved:
                for (int i = 0; i < BUTTONS; ++i) {
                    updateButtonState(button[i], event, MOVE, oldClick);
                }
                
                break;
            
            }
            
        }
        ///clear window
        window.clear(bg);

        for (int i = 0; i < BUTTONS - 1; ++i) {
            drawButton(window, button[i]);
        }
        
        for (int i = 0; i < BUTTONS; ++i)
        {
            if (inputVisible[i] == true) {
                switch (i) {
                    case 3:
                        handleFormula(W_WIDTH, W_HEIGHT, font, 36, stateColors);
                        inputVisible[i] = false;
                        break;
                    case 4:
                        handleAbout(300, 100 , font, 18);
                        inputVisible[i] = false;
                        break;
                        
                }
            }
        }
        
        window.display();
    }
    return 0;
}   
