#pragma once
#include <SFML/Graphics.hpp>
#include <stdexcept>
using namespace std;
using namespace sf;

class Element {
public:

    virtual Element * copy() = 0;
    virtual bool IsActive() = 0;
    virtual bool In(double x, double y) = 0;
    virtual void On() = 0;
    virtual void Off() = 0;
    virtual void setPosition(double x, double y) = 0;
    virtual void setString(wstring text) = 0;
    virtual void draw(RenderWindow & window) = 0;
    virtual void setCharacterSize(int num) = 0;
    virtual void Clear() = 0;
    virtual bool IsWrite() = 0;
    virtual pair<float,float> getPosition() = 0;


    virtual bool Checker(wstring text) { return false; }
    virtual wstring getString() { return {}; }
    virtual bool Status() { return false; }
    virtual void Switch() {}

    virtual int CountChoice(double x, double y) { return 0; }
    virtual bool InChoice(double x, double y) { return false; }
    virtual wstring NameChoice(int num) { return {}; }
    virtual int getChoice() { return 0; }
    virtual void drawOnlyChoice(RenderWindow & window) {}
    virtual void setChoice(int num) {}

};

struct line{
    wstring name;
    int date;
    int price;
    int num;
    int type;
};

struct info{
    int day;
    int outlets;
    int package;
    int area;
    int manager;
    vector<vector<wstring>> product;
    int status;

};

