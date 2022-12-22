#pragma once
#include <stdexcept>
#include "Element.h"
#include <iostream>
using namespace std;
using namespace sf;


class Button{
 public:

    Button(): status_(0), is_active_(1) {}

    Button(int length, int width, bool is_active = 1): length_(length),
                                                       width_(width),
                                                       status_(0),
                                                       is_active_(is_active)  {}
    /*virtual Element * copy() {

        Button * now = new Button;
        now -> length_ = length_;
        now -> width_ = width_;
        now -> font_ = font_;
        now -> texture_ = texture_;
        now -> img_ = img_;
        now -> NCtexture_ = NCtexture_;
        now -> NCimg_ = NCimg_;
        now -> is_active_ = is_active_;

        return now;

    }*/

    void setSize(int length, int width) {
        length_ = length;
        width_ = width;
    }

    void setPosition(double x, double y) {
        x_ = x;
        y_ = y;
        img_.setPosition(x_, y_);
        NCimg_.setPosition(x_, y_);
        text_.setPosition(x_ /*+ (length_ - text_.getLocalBounds().width) / 2.0*/,
                          y_);// + (width_ - text_.getLocalBounds().height) / 4.0);

    }

    void setNoneClick() {
        is_active_ = 0;
    }

    void setClick() {
        is_active_ = 1;
    }

    void setImage(string link, int d_x = 0, int d_y = 0) {
        if (!texture_.loadFromFile(link, IntRect(d_x, d_y, length_, width_))) cout << "-\n";
        img_.setTexture(texture_);
    }

    void setNCImage(string link, int d_x = 0, int d_y = 0) {
        if (!NCtexture_.loadFromFile(link, IntRect(d_x, d_y, length_, width_))) cout << "-\n";
        NCimg_.setTexture(NCtexture_);
    }


    void setFont(string font) {
        font_.loadFromFile(font);
        text_.setFont(font_);
        text_.setColor(Color::Black);
        text_.setCharacterSize(50);
    }

    void setString(wstring text) {
        text_.setString(text);
        text_.setPosition(x_ + (length_ - text_.getLocalBounds().width) / 2.0,
                          y_ + (width_ - text_.getLocalBounds().height) / 4.0);
    }

    void setCharacterSize(int num) {
        text_.setCharacterSize(num);
        text_.setPosition(x_  + (length_ - text_.getLocalBounds().width) / 2.0,
                          y_ + (width_ - text_.getLocalBounds().height) / 2.0 - 15);
        wcout << text_.getPosition().x << " " << text_.getPosition().y << " " << img_.getPosition().x << " " << img_.getPosition().y << endl;
    }
    void draw(RenderWindow & window) {
        if (is_active_) {
            window.draw(img_);
        } else {
            window.draw(NCimg_);
        }

        window.draw(text_);
    }

    bool In(double x, double y) {
        if (x_ <= x && x <= x_ + length_ && y_ <= y && y <= y_ + width_) {
            return true;
        } else {
            return false;
        }
    }
    void On() {
        cout << "on\n";
        status_ = 1;
    }

    void Off() {
        cout << "off\n";
        status_ = 0;
    }

    bool Status() {
       return status_;
    }
    bool IsActive() {
        return is_active_;
    }


    pair<float,float> getPosition() {
        return {x_, y_};
    }
    virtual ~Button() {}

 protected:
    int length_, width_;
    double x_, y_;
    Font font_;
    Text text_;
    Texture texture_;
    Sprite img_;
    Texture NCtexture_;
    Sprite NCimg_;
    bool status_;
    bool is_active_;
};



