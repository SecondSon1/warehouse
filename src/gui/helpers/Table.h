#pragma once
#include <stdexcept>
#include "Element.h"
#include "HelpString.h"
#include <iostream>

using namespace std;
using namespace sf;


class Table {

 public:

    Table(){}
    Table(int num_columns, int num_lines, float step_ver, float step_hor,
          Vector2f size_h, Vector2f size_v):

          num_columns_(num_columns), num_lines_(num_lines),
          step_ver_(step_ver), step_hor_(step_hor),
          size_h_(size_h), size_v_(size_v) {

                up_.setSize(Vector2f(num_columns_ * step_ver_ + board_, step_hor_ + board_));
                up_.setFillColor(Color::White);

                down_.setSize(Vector2f(num_columns_ * step_ver_ + board_,  step_hor_+ board_));
                down_.setFillColor(Color::White);


                for (int i = 0; i < num_columns_ + 1; i++) {
                    RectangleShape temp(size_v_);
                    temp.setFillColor(contur_);
                    vertical_.push_back(temp);
                }

                for (int i = 0; i < num_columns_; i++) {
                    RectangleShape temp(size_h_);
                    temp.setFillColor(contur_);
                    horizontal_.push_back(temp);
                }
                for (int i = 0; i < 3; i++) {
                    RectangleShape temp(size_h_);
                    temp.setFillColor(contur_);
                    st_horizontal_.push_back(temp);
                }


           }


    void setPosition(double x, double y) {
        x_ = x;
        y_ = y;
        for (int i = 0; i < vertical_.size(); i++) {
            vertical_[i].setPosition(x_ + step_ver_ * i, y_);
        }

        for (int i = 0; i < horizontal_.size(); i++) {
            horizontal_[i].setPosition(x_, y_ + (i + 2) * step_hor_);
        }
        st_horizontal_[0].setPosition(x_, y_);
        st_horizontal_[1].setPosition(x_, y_ + step_hor_);
        st_horizontal_[2].setPosition(x_, y_ + step_hor_ * 5);

        up_.setPosition(x_, y_);
        down_.setPosition(x_, y_ + step_hor_ * 5);



        for (int i = 0; i < all_line_.size(); i++) {
            for (int j = 0; j < all_line_[i].size(); j++) {
                all_line_[i][j] -> setPosition(x_ + board_ + j * step_ver_, y_ + board_ + step_hor_ * (i + 1));
            }

        }

        for (int i = 0; i < name_colums_.size(); i++) {
            name_colums_[i].setPosition(x_ + (step_ver_ - name_colums_[i].getLocalBounds().width) / 2.0 + step_ver_ * i,
                          y_ + (step_hor_ - name_colums_[i].getLocalBounds().height) / 4.0);
        }

    }

    void Move(float d_y) {
        d_y *= -1;
        //wcout << d_y << endl;
        d_ += d_y;
        //wcout << "+++++++ " << d_ << endl;
        start_ = -1;
        for (int i = 0; i < all_line_.size(); i++) {
            for (int j = 0; j < all_line_[i].size(); j++) {
                all_line_[i][j] -> setPosition(x_ + board_ + j * step_ver_, y_ + board_ + step_hor_ * (i + 1) + d_);
                if (y_ + board_ + step_hor_ * (i + 1) + d_ + step_hor_ - board_ >= y_ + step_hor_ && start_ == -1) {
                    start_ = i;
                }
                if (y_ + board_ + step_hor_ * (i + 1) + d_ < y_ + 5 * step_hor_) {
                    end_ = i;
                }
            }

        }
        for (int i = 0; i < horizontal_.size(); i++) {
            horizontal_[i].setPosition(x_, y_ + step_hor_ * (i + 2) + d_);
        }


    }
    void setHead(vector<wstring> head) {
        //name_colums_.clear();
        for (int i = 0; i < head.size(); i++) {
            Text temp;
            temp.setFont(font_);
            temp.setFillColor(Color::Black);
            temp.setCharacterSize(25);
            temp.setString(head[i]);
            name_colums_.push_back(temp);
        }
    }


    void setFont(string font) {
        font_.loadFromFile(font);
    }
    void setItems(vector<Element *> temp) {
        line_ = temp;
    }

    void addLine() {
        num_lines_ += 1;
        vector<Element *> temp;
        for (int i = 0; i < line_.size(); i++) {
            temp.push_back(line_[i] -> copy());
            temp[i] -> setPosition(x_ + board_ + i * step_ver_, y_ + board_ + step_hor_ * (all_line_.size() + 1));
            temp[i] -> setCharacterSize(30);
        }
        if (horizontal_.size() == 0) {
            RectangleShape line(size_h_);
            line.setFillColor(contur_);
            line.setPosition(Vector2f(x_, y_ + 2 * step_hor_));
            horizontal_.push_back(line);
        } else {
            Vector2f coord = horizontal_.back().getPosition();
            RectangleShape line(size_h_);
            line.setFillColor(contur_);
            line.setPosition(Vector2f(coord.x, coord.y + step_hor_));
            horizontal_.push_back(line);
        }

        all_line_.push_back(temp);
        for (int i = 0; i < all_line_.size(); i++) {
            if ((all_line_[i][0] -> getPosition()).second >= y_ + step_hor_ && start_ == -1) {
                start_ = i;
            }
            if ((all_line_[i][0] -> getPosition()).second < y_ + 5 * step_hor_) {
                end_ = i;
            }

        }

    }

    bool In(float x, float y) {
        bool ans = false;
        for (int i = start_; i <= end_; i++) {
            for (int j = 0; j < all_line_[i].size(); j++) {
                if (all_line_[i][j] -> IsWrite()) {
                    ans |= all_line_[i][j] -> In(x, y);
                } else if (all_line_[i][j] -> IsActive()) {
                    ans |= all_line_[i][j] -> In(x, y);
                    ans |= all_line_[i][j] -> InChoice(x, y);
                    //wcout << all_line_[i][j] -> InChoice(x, y) << " " << all_line_[i][j] -> In(x, y) << " " << i << endl;
                } else {
                    ans |= all_line_[i][j] -> In(x, y);
                }

            }
        }
        return ans;
    }

    void Click(float x, float y) {
        int f_i = -1, f_j = -1, is_choice = 0;
        for (int i = start_; i <= end_; i++) {
            for (int j = 0; j < all_line_[i].size(); j++) {
                if (all_line_[i][j] -> IsWrite()) {
                    if (all_line_[i][j] -> In(x, y)) {
                        f_i = i;
                        f_j = j;
                        break;
                    }
                } else {
                    if (all_line_[i][j] -> IsActive()) {
                        if (all_line_[i][j] -> In(x, y)) {
                            f_i = i;
                            f_j = j;
                            break;
                        } else if (all_line_[i][j] -> InChoice(x, y)) {
                            f_i = i;
                            f_j = j;
                            is_choice = 1;
                            break;
                        }

                    } else {
                        if (all_line_[i][j] -> In(x, y)) {
                            f_i = i;
                            f_j = j;
                            break;
                        }
                    }

                }

            }
            if (f_i != -1) {
                break;
            }
        }
        if (f_i == -1) return;

        for (int i = 0; i < all_line_.size(); i++) {
            for (int j = 0; j < all_line_[i].size(); j++) {
                if (f_i == i && f_j == j) {
                    continue;
                }
                all_line_[i][j] -> Off();

            }

        }

        if (is_choice == 1) {
            all_line_[f_i][f_j] -> setString(all_line_[f_i][f_j] -> NameChoice( all_line_[f_i][f_j] -> CountChoice(x, y)));
            all_line_[f_i][f_j] -> Off();
        } else {
            all_line_[f_i][f_j] -> Switch();
        }


    }

    void setString(wstring text) {
        for (int i = 0; i < all_line_.size(); i++) {
            for (int j = 0; j < all_line_[i].size(); j++) {
                if (all_line_[i][j] -> Status() && all_line_[i][j] -> IsWrite()) {
                    if (all_line_[i][j] -> Checker(text)) {
                        all_line_[i][j] -> setString(text);
                    }
                }
            }
        }

    }

    void draw(RenderWindow & window) {

        for (int i = start_ - 1; i >= 0; i--) {
            for (int j = 0; j < all_line_[i].size(); j++) {


                if (!(all_line_[i][j] -> IsWrite())) {
                    //wcout << "+++++++++++++++++++++++\n";
                    all_line_[i][j] -> Off();
                    all_line_[i][j] -> Off();


                }
                //cout << all_line_[i][j] -> getPosition().first <<" " << all_line_[i][j] -> getPosition().second<< endl;
            }
        }

        for (int i = end_; i >= start_; i--) {
            for (int j = 0; j < all_line_[i].size(); j++) {


                if (!(all_line_[i][j] -> IsWrite())) {
                    //wcout << "+++++++++++++++++++++++\n";
                    if (all_line_[i][j] -> getPosition().second + step_hor_ - 5 > y_ + 5 * step_hor_) {
                        all_line_[i][j] -> Off();

                    }
                }
                all_line_[i][j] -> draw(window);
                //cout << all_line_[i][j] -> getPosition().first <<" " << all_line_[i][j] -> getPosition().second<< endl;
            }
        }


        for (int i = start_; i <= end_; i++) {
            window.draw(horizontal_[i]);
        }
        window.draw(up_);
        window.draw(down_);
        for (int i = 0; i < vertical_.size(); i++) {
            window.draw(vertical_[i]);
        }
        for (int i = 0; i < st_horizontal_.size(); i++) {
            window.draw(st_horizontal_[i]);
        }

        //cout << horizontal_.size() << endl;

        //cout << start_ << " " << end_ << endl;

        for (int i = 0; i < name_colums_.size(); i++) {
            window.draw(name_colums_[i]);
        }
        for (int i = end_; i >= start_; i--) {
            for (int j = 0; j < all_line_[i].size(); j++) {
                if (!(all_line_[i][j] -> IsWrite())) {
                    all_line_[i][j] -> drawOnlyChoice(window);
                }
                //cout << all_line_[i][j] -> getPosition().first <<" " << all_line_[i][j] -> getPosition().second<< endl;
            }
        }
        //cout << name_colums_[0].getPosition().y << endl;


    }
    bool IsActive() {
        bool ans = false;
        for (int i = 0; i < all_line_.size(); i++) {
            for (int j = 0; j < all_line_[i].size(); j++) {
                ans |= all_line_[i][j] -> IsActive();
            }
        }
        return ans;
    }
    wstring getString() {
        wstring ans;
        for (int i = 0; i < all_line_.size(); i++) {
            for (int j = 0; j < all_line_[i].size(); j++) {
                if (all_line_[i][j] -> IsActive() && all_line_[i][j] -> IsWrite()) {
                    ans = all_line_[i][j] -> getString();
                }
            }
        }
        return ans;
    }
    void Off() {

        for (int i = 0; i < all_line_.size(); i++) {
            for (int j = 0; j < all_line_[i].size(); j++) {
                all_line_[i][j] -> Off();
            }
        }
    }
    void Clear() {
        for (int i = 0; i < all_line_.size(); i++) {
            for (int j = 0; j < all_line_[i].size(); j++) {
                all_line_[i][j] -> Clear();
            }
        }

    }

    int Count() {
        int ans = 0;
        for (int i = 0; i < all_line_.size(); i++) {
            bool flag = true;
            for (int j = 0; j < all_line_[i].size(); j++) {
                if (all_line_[i][j] -> IsWrite()) {
                    if (all_line_[i][j] -> getString() == L"") {
                        cout << i << "//dcsdcsdc***/////\n";
                        flag = false;
                        break;
                    }
                } else {
                    if (all_line_[i][j] -> getChoice() == -1) {
                        flag = false;
                        cout << i << "//***/////\n";
                        break;
                    }
                }
            }
            if (flag) {
                ans += 1;
            }
        }
        return ans;
    }

    vector<vector<wstring>> Result() {
        vector<vector<wstring>> ans;
        for (int i = 0; i < all_line_.size(); i++) {
            bool flag = true;
            vector<wstring> temp;
            for (int j = 0; j < all_line_[i].size(); j++) {
                if (all_line_[i][j] -> IsWrite() && all_line_[i][j] -> getString() == L"" ||
                    !all_line_[i][j] -> IsWrite() && all_line_[i][j] -> getChoice() == -1) {
                    flag = false;
                    break;
                }
                if (all_line_[i][j] -> IsWrite()) {
                    temp.push_back(all_line_[i][j] -> getString());
                } else {
                    temp.push_back(i_to_s(all_line_[i][j] -> getChoice()));
                }

            }
            if (flag) {
                ans.push_back(temp);
            }
        }
        return ans;
    }

 private:
     float x_, y_;
     int k_ = 4;
     float d_ = 0;
     int start_ = 0, end_ = 5;
     int num_columns_, num_lines_ = 0;
     float board_ = 5;
     Vector2f size_h_, size_v_;
     vector<Element *> line_;
     vector<vector<Element *>> all_line_;
     vector<Text> name_colums_;
     Font font_;
     Color contur_ = Color(54, 51, 58);
     float step_ver_, step_hor_;
     RectangleShape up_, down_;
     vector<RectangleShape> vertical_, st_horizontal_, horizontal_;

};
