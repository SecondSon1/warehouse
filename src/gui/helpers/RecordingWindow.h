#pragma once
#include <stdexcept>
#include "Element.h"
#include <iostream>
using namespace std;
using namespace sf;

bool default_f(wstring text) {
    return true;
}

class RecordingWindow: public Element {

 public:

    RecordingWindow(): is_active_(1), type_(2), checker_(default_f){}
    RecordingWindow(float length, float width, bool is_active = 1, int type = 2): length_(length),
                                                                                  width_(width),
                                                                                  is_active_(is_active),
                                                                                  type_(type), checker_(default_f)  {}

    virtual Element * copy() {

        RecordingWindow * now = new RecordingWindow;
        now -> length_ = length_;
        now -> width_ = width_;
        now -> setFont(s_font_);
        now -> setImage(linkImg_, Img_d_x_, Img_d_y_);
        now -> setNCImage(linkImgNc_, ImgNc_d_x_, ImgNc_d_y_);
        now -> start_ = start_;
        now -> is_active_ = is_active_;
        now -> setChecker(checker_);
        //wcout << now -> Checker(L"sdfghj") << endl;

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
        NCimg_.setPosition(x_, y_);

        text_.setPosition(x_ + bound_,
                          y_ );

    }

    void setNoneClick() {
        is_active_ = 0;
    }

    void setClick() {
        is_active_ = 1;
    }

    void setImage(string link, int d_x = 0, int d_y = 0) {
        if (!texture_.loadFromFile(link, IntRect(d_x, d_y, length_, width_)))
          cout << "-\n";
        linkImg_ = link;
        Img_d_x_ = d_x;
        Img_d_y_ = d_y;

        img_.setTexture(texture_);
    }


    void setNCImage(string link, int d_x = 0, int d_y = 0) {
        if (!NCtexture_.loadFromFile(link, IntRect(d_x, d_y, length_, width_)))
          cout << "-\n";
        linkImgNc_ = link;
        ImgNc_d_x_ = d_x;
        ImgNc_d_y_ = d_y;
        NCimg_.setTexture(NCtexture_);
    }

    void setChecker(function<bool(wstring)> checker) {
        checker_ = checker;
    }

    void setFont(string font) {
        s_font_ = font;
        font_.loadFromFile(font);
        text_.setFont(font_);
        text_.setColor(Color::Black);
        text_.setCharacterSize(50);
    }

    void setCharacterSize(int num) {
        text_.setCharacterSize(num);
    }

    void setString(wstring text) {
        text_.setString(text);
        tstring_ = text;
        start_ = FindStart(length_, text);



    }

    wstring getString() {
        return tstring_;
    }
    void Switch() {
        is_active_ = (is_active_ + 1) % 2;
    }

    void draw(RenderWindow & window) {
        if (is_active_) {
            window.draw(img_);
        } else {
            window.draw(NCimg_);
        }
        wstring tmp;

        for (int i = start_; i < tstring_.size(); i++) {
            tmp += tstring_[i];
            text_.setString(tmp);
            if (text_.getLocalBounds().width + bound_ > length_) {
                tmp.pop_back();
                text_.setString(tmp);
                break;
            } else if (text_.getLocalBounds().width + bound_ == length_) {
                break;
            }
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

    bool Checker(wstring text) {
        return checker_(text);
    }

    bool IsActive() {
        return is_active_;
    }

    bool Status() {
        return is_active_;
    }
    void On() {
        //cout << "on\n";
        is_active_ = 1;
    }

    void Off() {
        //cout << "off\n";
        is_active_ = 0;
    }


    pair<float,float> getPosition() {
        return {img_.getPosition().x, img_.getPosition().y};
    }

    void Clear() {
        text_.setString(L"");
        tstring_ = L"";
    }
    virtual ~RecordingWindow() {}


    bool IsWrite() {
        return true;
    }


 private:
    wstring tstring_;
    string s_texture;
    string linkImg_, linkImgNc_;
    string s_font_;
    int Img_d_x_, Img_d_y_, ImgNc_d_x_, ImgNc_d_y_;
    int type_;
    float length_, width_;
    float bound_ = 5;
    float x_, y_;
    Font font_;
    Text text_;
    Texture texture_;
    Sprite img_;
    Texture NCtexture_;
    Sprite NCimg_;
    function<bool(wstring)> checker_;
    bool is_active_;
    int start_;

    int FindStart(float length, wstring tstring) {


        wstring tmp2;


        int ans = 0;

        for (int i = tstring.size() - 1; i >= 0; i--) {
            tmp2 += tstring[i];
            text_.setString(tmp2);
            ans += 1;
            if (text_.getLocalBounds().width + bound_ > length) {
                ans -= 1;
                break;
            } else if (text_.getLocalBounds().width + bound_ == length) {
                break;
            }
        }
        text_.setString(tstring_);
        return max(int(0), int(tstring.size() - ans));
    }

};
