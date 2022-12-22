#include <SFML/Graphics.hpp>
#include <iostream>
#include "helpers/Helpers.h"
#include "asset_manager.hpp"

using namespace std;
using namespace sf;


info Preview() {
    info result;
    int LENGTH = 1500, HEIGHT = 800;
    int MLENGTH = 500, MHEIGHT = 600;
    int WLenght = 600, WHeight = 200;
    float BLength = 250, BHeight = 100, StepButton = BLength + 50;
    float XButton = (LENGTH - MLENGTH - StepButton + BLength) / 2, YButton = 650;
    int Ch_sz = 45, Ch_sz_w = 30;
    Color Color_for_text = Color::Black;
    Font font;
    font.loadFromFile(ASSET_PREFIX + "/Basic Comical Italic NC.ttf");
    string s_font = ASSET_PREFIX + "Basic Comical Regular NC.ttf";

    RenderWindow window(sf::VideoMode(LENGTH, HEIGHT), "Warehouse");

    Texture fon_texture;
    fon_texture.loadFromFile(ASSET_PREFIX + "Fon7.1.jpg");
    Sprite fon;
    fon.setTexture(fon_texture);
    fon.setPosition(0, 0);
    fon.setScale(1.5, 1.5);


    Button exit(BLength, BHeight);
    exit.setPosition(XButton, YButton);
    exit.setImage(ASSET_PREFIX + "Button.jpg", 0, 0);
    exit.setNCImage(ASSET_PREFIX + "NCButton.jpg", 0, 0);
    exit.setFont(s_font);
    exit.setString(L"Завершить");
    exit.setCharacterSize(Ch_sz);

    Button start(BLength, BHeight);
    start.setPosition(XButton + StepButton, YButton);
    start.setImage(ASSET_PREFIX + "Button.jpg", 0, 0);
    start.setNCImage(ASSET_PREFIX + "NCButton.jpg", 0, 0);
    start.setFont(s_font);
    start.setString(L"Начать");
    start.setCharacterSize(Ch_sz);

    Button b_fon(WLenght, WHeight);
    b_fon.setPosition((LENGTH - WLenght) / 2.0, 150);
    b_fon.setImage(ASSET_PREFIX + "Button11.jpg");
    b_fon.setNCImage(ASSET_PREFIX + "Button11.jpg", 0, 0);
    b_fon.setFont(s_font);
    b_fon.setString(L"Система управления\n   оптовым складом");
    b_fon.setCharacterSize(60);

    RectangleShape outline(Vector2f(WLenght, WHeight));
    outline.setPosition((LENGTH - WLenght) / 2.0, 150);
    outline.setOutlineThickness(10);
    outline.setOutlineColor(Color::Black);


    Texture t_text;
    t_text.loadFromFile(ASSET_PREFIX + "Button11.jpg", IntRect(200, 200,
                                                       WLenght + 200, WHeight + 200));

    Sprite text;
    text.setTexture(t_text);
    //text.setPosition();

    Text s_text;
    s_text.setFont(font);
    s_text.setPosition((LENGTH - WLenght) / 2.0 + 20, 50);
    s_text.setCharacterSize(65);
    s_text.setFillColor(Color::Black);
    s_text.setString(L"Система управления\nоптовым складом");


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                result.status = 0;
                window.close();
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    double x = event.mouseButton.x;
                    double y = event.mouseButton.y;

                    if (exit.In(x, y)) {
                        result.status = 0;
                        window.close();

                    }
                    if (start.In(x, y)) {
                        result.status = 1;
                        window.close();

                    }



                }

            }

        }

        window.clear();


        window.draw(fon);
        exit.draw(window);
        start.draw(window);
//        window.draw(text);
//        window.draw(s_text);
        window.draw(outline);
        b_fon.draw(window);


        window.display();
    }


    return result;
}
