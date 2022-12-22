#pragma once
#include <stdexcept>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Scroll {

 public:
     Scroll(){};

     Scroll(float length, float hight, float t_len, float sz_window, float w = -1): length_(length), hight_(hight),
                                                                      t_len_(t_len), sz_window_(sz_window){
        in_.setSize(Vector2f(length_, hight_));
        in_.setFillColor(Color(181, 185, 198));
        in_.setOutlineThickness(5);
        in_.setOutlineColor(Color(54, 51, 58));
        float tmp = (t_len_ - sz_window_) / k_;

        w_ = (t_len_ - sz_window_) / (hight - tmp);
        if (w != -1) {

            w_ = w;
            tmp = hight - (t_len_ - sz_window_) / w_;
            if (t_len_ <= sz_window_) {
                w_ = 0;
                tmp = hight;
            }
        }
        //wcout << w_ << endl << "/////";
        move_.setSize(Vector2f(length - board_, tmp));
        move_.setFillColor(Color(112, 113, 114));
        status_ = false;
     }

     void setPosition(float x, float y) {
        x_ = x;
        y_ = y;
        prev_y_ = y_;
        in_.setPosition(x_, y_);
        move_.setPosition(x_ + board_ / 2.0, y_);
        //wcout << move_.getPosition().y << " " << in_.getPosition().y << endl;
     }

     void setPositionScroll(float x, float y) {
        if (y + move_.getSize().y > y_ + in_.getSize().y) return;
        if (y < y_) return;
        move_.setPosition(x_ + board_ / 2.0, y);
     }

     void Move(float a, float t) {
        float y = move_.getPosition().y + a * t;

        if (y + move_.getSize().y > y_ + in_.getSize().y) {
            a_ = 0;
            return;
        }
        if (y < y_) {
            a_ = 0;
            return;
        }
        a_ = a * t;
        prev_y_ = move_.getPosition().y;
        move_.setPosition(x_ + board_ / 2.0, y);

     }

     bool In(float x, float y) {
        if (x >= move_.getPosition().x && x <= move_.getPosition().x + move_.getSize().x) {
            if (y >= move_.getPosition().y && y <= move_.getPosition().y + move_.getSize().y) {
                return true;
            }
        }
        return false;
     }

     float dH() {
        return a_ * w_;
     }

     void draw(RenderWindow & window) {
        window.draw(in_);
        window.draw(move_);
     }
     void On() {
        status_ = true;
     }

     void Off() {
        status_ = false;
     }

     bool Status() {
        return status_;
     }



 private:
    float x_, y_;
    float a_ = 0;
    float w_ = 1;
    float prev_y_;
    float length_, hight_;
    float step_ = 1.5;
    float t_len_, sz_window_;
    float k_= 20.8, board_ = 6;
    bool status_;
    RectangleShape in_, move_;


};
