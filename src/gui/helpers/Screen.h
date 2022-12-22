#pragma once
#include <stdexcept>
#include "Element.h"

using namespace std;
using namespace sf;

class Screen {
 public:
     Screen() {};
     Screen(float length, float height, float up_height, bool is_table = true) {
        status_ = true;
        setSize(length, height, up_height, is_table);
     }

     void setSize(float length, float height, float up_height, float is_table = true) {
        is_table_ = is_table;
        length_ = length;
        height_ = height;
        up_length_ = length;
        up_height_ = up_height;
        screen_.setSize(Vector2f(length_, height_));
        screen_.setOutlineColor(Color::Black);
        screen_.setOutlineThickness(10);
        screen_.setFillColor(Color::White);

        up_.setSize(Vector2f(up_length_, up_height_));
        up_.setOutlineColor(Color::Black);
        up_.setOutlineThickness(10);
        up_.setFillColor(Color::White);



     }
     void setFont(string font) {
        font_.loadFromFile(font);
        name_.setFont(font_);

     }
     void setHead(wstring head) {
        name_.setString(head);
        name_.setColor(Color::Black);
        name_b_ = 50 * 15 / 45.0;
        name_.setCharacterSize(50);
        name_.setPosition(x_ + (up_length_ - name_.getLocalBounds().width) / 2.0,
                          y_ + (up_height_ - name_.getLocalBounds().height) / 2.0 - name_b_);


     }
     void setHeadChracterSize(int num) {
        name_b_ = num * 15 / 45.0;
        name_.setCharacterSize(num);
        name_.setPosition(x_ + (up_length_ - name_.getLocalBounds().width) / 2.0,
                          y_ + (up_height_ - name_.getLocalBounds().height) / 2.0 - name_b_);

     }
     void setPosition(float x, float y) {
        x_ = x;
        y_ = y;

        screen_.setPosition(x_, y_);
        up_.setPosition(x_, y_);

        name_.setPosition(x_ + (up_length_ - name_.getLocalBounds().width) / 2.0,
                          y_ + (up_height_ - name_.getLocalBounds().height) / 2.0 - name_b_);

     }
     void setNormal() {
        is_table_ = false;
     }

     void setTable(float hor_s, float ver_s, float board_s) {
        hor_s_ = hor_s;
        ver_s_ = ver_s;
        board_s_ = board_s;

     }
     void setPositionText(float x, float y, float tstep, float text_sz, float txstep = 0) {
        tx_ = x_ + x;
        ty_ = y_ + y + up_height_;
        tstep_ = tstep;
        text_sz_ = text_sz;
        txstep_ = txstep;
     }
    void addLine(vector<wstring> str) {
         vector<Text> text;

         for (int i = 0; i < str.size(); i++) {
             Text tmp;
             tmp.setFont(font_);
             tmp.setPosition(tx_ + txstep_ * i, ty_ + tstep_ * t_info_.size());
             tmp.setCharacterSize(text_sz_);
             tmp.setString(str[i]);
             tmp.setFillColor(Color::Black);
             text.push_back(tmp);
         }

         t_info_.push_back(text);
         t_len_ = t_info_[t_info_.size() - 1][0].getPosition().y - t_info_[0][0].getPosition().y +
                  t_info_[0][0].getLocalBounds().height +  t_info_[t_info_.size() - 1][0].getLocalBounds().height + 20;
         for (int i = 0; i < t_info_.size(); i++) {
            if (t_info_[i][0].getPosition().y < 700) {
                end_ = i + 1;

            }

         }
         for (int i = t_info_.size() - 1; i >= 0; i--) {
            if (t_info_[i][0].getPosition().y + 5 > 80 + 10 + 50) {
                start_ = i;

            }

         }
         end_ = min(end_, int(t_info_.size() - 1));
         //wcout << endl;
         //wcout << start_ << " " << end_ << endl;

     }
     void addLine(wstring str) {
         Text tmp;
         tmp.setFont(font_);
         tmp.setPosition(tx_, ty_ + tstep_ * t_info_.size());
         tmp.setCharacterSize(text_sz_);
         tmp.setString(str);
         tmp.setFillColor(Color::Black);
         t_info_.push_back({tmp});
         t_len_ = t_info_[t_info_.size() - 1][0].getPosition().y - t_info_[0][0].getPosition().y +
                  t_info_[0][0].getLocalBounds().height +  t_info_[t_info_.size() - 1][0].getLocalBounds().height + 20;
         for (int i = 0; i < t_info_.size(); i++) {
            if (t_info_[i][0].getPosition().y < 700) {
                end_ = i + 1;

            }

         }
         for (int i = t_info_.size() - 1; i >= 0; i--) {
            if (t_info_[i][0].getPosition().y + 5 > 80 + 10 + 50) {
                start_ = i;

            }

         }
         end_ = min(end_, int(t_info_.size() - 1));
         //wcout << endl;
         //wcout << start_ << " " << end_ << endl;

     }
     void addLine(pair<float, vector<Text>> line) {
        vector<float> temp;
        for (int i = 0; i < line.second.size(); i++) {
            if (t_info_.size() == 0 && i > 0 && is_table_) {
                ver_.push_back(RectangleShape(Vector2f(board_s_, ver_s_)));
                ver_[i - 1].setPosition(line.second[i].getPosition().x - 10, line.second[i].getPosition().y);
                ver_[i - 1].setFillColor(Color::Black);
                ty_ = line.second[i].getPosition().y;
            }
            line.second[i].move(0, prev_ + 15);
            temp.push_back(line.second[i].getLocalBounds().height);
        }

        prev_ += line.first + 35;
        H_.push_back(temp);
        t_info_.push_back(line.second);
        if (is_table_) {
            hor_.push_back(RectangleShape(Vector2f(hor_s_, board_s_)));
            hor_[hor_.size() - 1].setPosition(x_, ty_ + prev_ - 5);

            if(hor_.size() == 1) {
                //hor_[hor_.size() - 1].setPosition(line.second[0].getPosition().x, ty_ + prev_);
//                prev_ += 10;
                ty_ += 15;
            }
            hor_[hor_.size() - 1].setFillColor(Color::Black);
        }


        t_len_ = hor_[hor_.size() - 1].getPosition().y - y_;
                 for (int i = 0; i < hor_.size(); i++) {
            if (hor_[i].getPosition().y < 700) {
                end_ = i + 1;

            }

        }
        for (int i = hor_.size() - 1; i >= 0; i--) {
            if (hor_[i].getPosition().y + 5 > 80 + 10 + 50) {
                start_ = i;

            }

        }
        end_ = min(end_, int(t_info_.size() - 1));



    }

     void draw(RenderWindow & window) {

        window.draw(screen_);
//        wcout << "first1" << endl;
//        cout << start_ << " " << end_ << endl;
        if (t_info_.size() != 0) {
            for (int i = start_; i <= end_; i++) {
                for (int j = 0; j < t_info_[i].size(); j++) {
                    window.draw(t_info_[i][j]);
                }
            }
        }

//wcout << "first2" << endl;
        if (is_table_) {
//            wcout << "first4" << endl;
            //wcout << "******";
            for (int i = start_; i <= end_; i++) {
                window.draw(hor_[i]);
            }

            for (int i = 0; i < ver_.size(); i++) {
                window.draw(ver_[i]);
            }
        }
//    wcout << "first3" << endl;
        window.draw(up_);
        window.draw(name_);



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
     void Clear() {
          while(t_info_.size() > 1) {
            t_info_.pop_back();
            if (is_table_) {
                H_.pop_back();
                hor_.pop_back();
            }

          }
          if (!is_table_) {
            if (t_info_.size() == 1) {
                t_info_.pop_back();
            }
          }
          prev_ = 0;
          if (is_table_) {
              if (H_.size() == 1) {
                for (int i = 0; i < t_info_[0].size(); i++) {
                    prev_ = max(H_[0][i], prev_);
                }
              }
          }
          prev_ += 10 + 35;
          //wcout << prev_ << endl;
     }

     float Height() {
        //wcout << t_len_ << endl << endl;
        return t_len_;
     }

     void Move(float y) {
        y *= -1;
        for (int i = 0; i < t_info_.size(); i++) {
            for (int j = 0; j < t_info_[i].size(); j++) {
                t_info_[i][j].move(0, y);
            }
        }
        for (int i = 0; i < hor_.size(); i++) {
            hor_[i].move(0, y);
        }
        if (is_table_) {
            for (int i = 0; i < hor_.size(); i++) {
                if (hor_[i].getPosition().y < 700) {
                    end_ = i + 1;

                }

            }
            for (int i = hor_.size() - 1; i >= 0; i--) {
                if (hor_[i].getPosition().y + 5 > 80 + 10 + 50) {
                    start_ = i;

                }

            }
            end_ = min(end_, int(t_info_.size() - 1));
        } else {
            for (int i = 0; i < t_info_.size(); i++) {
                if (t_info_[i][0].getPosition().y < 700) {
                    end_ = i + 1;

                }

             }
             for (int i = t_info_.size() - 1; i >= 0; i--) {
                if (t_info_[i][0].getPosition().y + t_info_[i][0].getLocalBounds().height > 80 + 10 + 50) {
                    start_ = i;

                }

             }
             end_ = min(end_, int(t_info_.size() - 1));
        }

     }

 private:
     float x_, y_;
     float tx_, ty_, tstep_, txstep_;
     float name_b_;
     float t_len_;
     float text_sz_;

     float length_, height_;
     float up_length_, up_height_;

     float prev_ = 10;
     vector<vector<float>> H_;

     RectangleShape up_;
     vector<RectangleShape> hor_, ver_;
     float hor_s_ = 800, ver_s_ = 500, board_s_ = 5;
     bool is_table_;
     Font font_;
     Text name_;
     int start_ = 0, end_ = 0;

     RectangleShape screen_;
     vector<wstring> info_;
     vector<vector<Text>> t_info_;

     bool status_;


};
