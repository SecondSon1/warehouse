#pragma once
#include <stdexcept>
#include "Element.h"
#include <iostream>
using namespace std;
using namespace sf;


class List: public Element {
 public:
     List(): is_active_(0) {}
     List(float length, float width): length_(length), width_(width), is_active_(0) {}

     virtual Element * copy() {

        List * now = new List;
        now -> length_ = length_;
        now -> width_ = width_;
        now -> font_ = font_;
        now -> texture_ = texture_;
        now -> img_ = img_;
        now -> step_ = step_;
        now -> text_ = text_;
        (now -> text_).setCharacterSize(Ch_size_);
        now -> Ch_size_ = Ch_size_;
        now -> text_choice_ = text_choice_;
        now -> choice_ = choice_;
        now -> now_choice_ = now_choice_;
        now -> choice_length_ = choice_length_;

        return now;

    }

    void setSize(float length, float width) {
        length_ = length;
        width_ = width;
    }


     void setPosition(double x, double y) {
        x_ = x;
        y_ = y;
        img_.setPosition(x_, y_);
        text_.setPosition(x_ + (length_ - text_.getLocalBounds().width) / 2.0,
                          y_ + (width_ - text_.getLocalBounds().height) / 4.0);
        for (int i = 0; i < text_choice_.size(); i++) {
            text_choice_[i].setPosition(x_ + 3, y_ + width_ + step_ * i);
        }
        choice_.setPosition(x_ + 2, y_ + width_);
        now_choice_.setPosition(x_ + 2, y_ + width_);
     }

     void setImage(string link, int d_x = 0, int d_y = 0) {
        if (!texture_.loadFromFile(link, IntRect(d_x, d_y, length_, width_)))
          cout << "-\n";
        img_.setTexture(texture_);
    }

    void setFont(string font) {
        font_.loadFromFile(font);
        text_.setFont(font_);
        text_.setColor(Color::Black);
        text_.setCharacterSize(Ch_size_);


    }

    void setCharacterSize(int num) {
        text_.setCharacterSize(num);
        Ch_size_ = num;
    }

    void setString(wstring text) {
        now_ = text;
        text_.setString(now_);
        if (text_.getLocalBounds().width + 5> length_) {
            wstring tmp2;
            for (int i = 0; i < text.size(); i++) {
                tmp2 += text[i];
                text_.setString(tmp2);
                if (text_.getLocalBounds().width + 5 > length_) {
                    tmp2.pop_back();
                    break;
                } else if (text_.getLocalBounds().width + 5 == length_) {
                    break;
                }
            }
            text_.setString(tmp2);
            text_.setPosition(x_ + 5, y_ + (width_ - text_.getLocalBounds().height) / 4.0);
        } else {
            text_.setPosition(x_ + (length_ - text_.getLocalBounds().width) / 2.0,
                              y_ + (width_ - text_.getLocalBounds().height) / 4.0);
        }

        //wcout << text_.getLocalBounds().height << " " << text_.getLocalBounds().width << endl;
    }

    void setStep(float step) {
        step_ = step;
    }

    void setList(vector<wstring> t_list, float length = -1) {
        if (length == -1) {
            choice_length_ = length_ - 4;
            length = length_ - 4;
        } else {
            choice_length_ = length;
        }
        for (int i = 0; i < t_list.size(); i++) {
            Text temp;
            temp.setFont(font_);
            temp.setColor(Color::Black);
            temp.setCharacterSize(30);
            temp.setPosition(x_ + 3, y_ + width_ + step_ * i);
            temp.setString(t_list[i]);
            text_choice_.push_back(temp);
        }

        choice_.setSize(Vector2f(length, step_ * t_list.size()));
        choice_.setPosition(x_ + 2, y_ + width_);
        choice_.setFillColor(Color::White);
        choice_.setOutlineThickness(2);
        choice_.setOutlineColor(Color(54, 51, 58));

        now_choice_.setSize(Vector2f(length, step_));
        now_choice_.setPosition(x_ + 2, y_ + width_);
        now_choice_.setFillColor(Color(15, 15, 15, 60));


    }

    void draw(RenderWindow & window) {
        window.draw(img_);
        window.draw(text_);

        if (is_active_) {
            window.draw(choice_);
            window.draw(now_choice_);
            for (int i = 0; i < text_choice_.size(); i++) {
                window.draw(text_choice_[i]);
            }
        }
    }
    void drawOnlyChoice(RenderWindow & window) {
        if (is_active_) {
            window.draw(choice_);
            window.draw(now_choice_);
            for (int i = 0; i < text_choice_.size(); i++) {
                window.draw(text_choice_[i]);
            }
        }
    }


    bool In(double x, double y) {
        if (x_ <= x && x <= x_ + length_ && y_ <= y && y <= y_ + width_) {
            return true;
        } else {
            return false;
        }
    }

    bool InChoice(double x, double y) {
        //wcout << x << " " << x_ + choice_length_ << endl;
        if (x >= x_ && x <= x_ + choice_length_ && y > y_ + width_ && y <= y_ + width_ + step_ * text_choice_.size()) {
            return true;
        }
        return false;
    }

    wstring NameChoice(int num) {
        if (num < 0) return L"Не выбрано";
        return text_choice_[num].getString();
    }


    int CountChoice(double x, double y) {
        for (int i = 0; i < text_choice_.size(); i++) {
            if (x >= x_ && x <= x_ + choice_length_ && y >= y_ + width_ + step_ * i && y <= y_ + width_ + step_ * (i + 1)) {
                return i;
            }
        }
        return -1;
    }

    void setChoice(int num) {
        if (num < 0) return;
        now_choice_.setPosition(x_ + 2, y_ + width_ + step_ * num);
        return;
    }

    int getChoice() {
        for (int i = 0; i < text_choice_.size(); i++) {
            if (now_ == text_choice_[i].getString()) {
                return i;
            }
        }
        return -1;
    }


    void On() {
        //wcout << "on\n";
        is_active_ = 1;
    }

    void Off() {
        //wcout << "off\n";
        is_active_ = 0;
        for (int i = 0; i < text_choice_.size(); i++) {
            if (text_choice_[i].getString() == text_.getString()) {
                setChoice(i);
                break;
            }
        }
    }

    pair<float,float> getPosition() {
        return {x_, y_};
    };

    void Switch() {
        if (is_active_ == 1) Off();
        else On();
    }

    bool IsActive() {
       return is_active_;
    }

    void Clear() {
        text_.setString(L"Не выбрано");
        text_.setPosition(x_ + (length_ - text_.getLocalBounds().width) / 2.0,
                          y_ + (width_ - text_.getLocalBounds().height) / 4.0);
    }

    bool IsWrite() {
        return false;
    }


 private:
    float length_, width_;
    float choice_length_;
    float bound_ = 10;
    float x_ = 0, y_ = 0;
    int Ch_size_ = 50;
    Font font_;
    Text text_;
    float step_;
    wstring now_;
    vector<Text> text_choice_;
    Texture texture_;
    Sprite img_;
    bool is_active_;
    RectangleShape choice_, now_choice_;





};
