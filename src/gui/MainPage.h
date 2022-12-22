#include <SFML/Graphics.hpp>
#include <iostream>
#include "helpers/Helpers.h"

#include "../simplifier.hpp"
#include "asset_manager.hpp"

using namespace std;
using namespace sf;

bool NextDay() {
    return true;
}

int get3() {
    return 10006565;
}
struct my_data {
    wstring name;
    int count_in_package;
    int count_package;
    vector<tuple<int, int, int>> info;
};

vector<my_data> func() {
    vector<my_data> vec;
    for (int i = 0; i < 5; i++) {
        my_data temp;
        temp.name = L"Butter";
        temp.count_in_package = 15;
        temp.count_package = 3;
        temp.info.push_back(make_tuple(1, 4, 1200));
        temp.info.push_back(make_tuple(1, 3, 1100));
        temp.info.push_back(make_tuple(1, 2, 1000));
        vec.push_back(temp);
    }
    return vec;

}

vector<vector<wstring>> get() {
    vector<vector<wstring>> ans = {{L"1", L"Чтоdsdsd\nssdfsf т\nо", L"Что то", L"Что то", L"Что то", L"Что то"},
                                   {L"2", L"Что то", L"Что то", L"Что то", L"Что то", L"Что то"},
                                   {L"3", L"Что то", L"Что то", L"Что то", L"Что то", L"Что то"},
                                   {L"4", L"Что то", L"Что то", L"Чтdadadadо то", L"Что то", L"Что то"},
                                   {L"5", L"Что то", L"Что то", L"Что то", L"Что то", L"Что то"},
                                   {L"6", L"Что то", L"Что то", L"Что то", L"Что то", L"Чтadsadsadsadо то"},
                                   {L"7", L"Что то", L"Что то", L"Что то", L"Что то", L"Что то"},
                                   {L"8", L"Что то", L"asdadadaЧто то", L"Что то", L"Что то", L"Что то"}};
    return ans;
}

float sum(vector<float> t) {
    float ans = 0;
    for (int i = 0; i < t.size(); i++) {
        ans += t[i];
    }
    return ans;
}

vector<wstring> w_button_string = {L"Продажа",
                                   L"Закупка",
                                   L"Привоз",
                                   L"Списание",
                                   L"Торговые\n   точки",
                                   L"Склад"};
vector<wstring> screen_head_string = {L"Список проданных продуктов",
                                      L"Список закупленных продуктов",
                                      L"Список поставленных в склад продуктов",
                                      L"Список списанных продуктов",
                                      L"Список запросов от торговых точек",
                                      L"Склад"};

vector<vector<float>> table = {{100, 215, 215, 215, 215},
                               {100, 215, 215, 215, 215},
                               {100, 300, 300, 300},
                               {100, 450, 450},
                               {100, 300, 300, 300},
                               {}};
vector<vector<wstring>> head_table = {{L"Номер", L"Торг. точка", L"Товар", L"Количество", L"Выручка"},
                               {L"Номер", L"Товар", L"Количество", L"Цена", L"Дата"},
                               {L"Номер", L"Товар", L"Количество", L"Дата заказа"},
                               {L"Номер", L"Товар", L"Количество"},
                               {L"Номер", L"Торг. точка", L"Товар", L"Количество"},
                               {}};

vector<float> table_size = { sum(table[0]),
                             sum(table[1]),
                             sum(table[2]),
                             sum(table[3]),
                             sum(table[4]),
                             sum(table[5])};



pair<float, vector<Text>> ToTable(int n, Font & font, vector<float> column, float board, vector<wstring> str, float x = 0, float y = 0, int ch_sz = 30) {

    vector<Text> ans;


    float sum = 0;


    for (int i = 0; i < n; i++) {
        Text temp;
        temp.setFont(font);
        temp.setCharacterSize(ch_sz);
        temp.setFillColor(Color::Black);
        temp.setPosition(x + sum + board * i, y);
        wstring t;
        temp.setString(t);
        for (int j = 0; j < str[i].size(); j++) {
            t += str[i][j];
            temp.setString(t);
            if (temp.getLocalBounds().width == column[i]) {
                t += '\n';
                temp.setString(t);
            } else if (temp.getLocalBounds().width > column[i]) {
                t.pop_back();
                t += '\n';
                t += str[i][j];
                temp.setString(t);
            }
        }
        sum += column[i];
        ans.push_back(temp);

    }
    float height = 0;

    for (int i = 0; i < n; i++) {

        height = max(height, ans[i].getLocalBounds().height);
    }

    return make_pair(height, ans);

}



void FillAll(vector<Screen *> & screen, vector<Scroll *> & scroll, Font & font, float XText, float YText, WarehouseSystem & warehouse, vector<std::vector<std::pair<uint32_t, uint32_t>>> next_day) {
    // wcout << "w0" << endl;
    vector<vector<wstring>> tmp = GetListOfProductSold(warehouse);
    // wcout << "w1\n" << endl;
    screen[0] -> Clear();
     // wcout << "w10" << endl;
    for (int i = 0; i < scroll.size(); i++) {
        delete scroll[i];
    }
    // wcout << "w11" << endl;

    for (int i = 0; i < tmp.size(); i++) {
             // wcout << "w12 " << i << endl;
            for (int j = 0; j < tmp[i].size(); j++) {
                // wcout << tmp[i][j] << endl;
            }
        screen[0] -> addLine(ToTable(5, font, table[0], 10, tmp[i], XText, YText));
    }
    // wcout << "w13 "<< endl;
    scroll[0] = new Scroll(30, 550, screen[0] -> Height(), 570, 4);
    // wcout << "w14 " <<endl;
    scroll[0] -> setPosition(1055, 80 + 50 + 15);
    // wcout << "w2\n";
    tmp.clear();
    // wcout << "w21" << endl;
    tmp = GetListOfPurchasedProduct(warehouse);
    // wcout << "w22" << endl;
    screen[1] -> Clear();
    // wcout << "w23" << endl;
    for (int i = 0; i < tmp.size(); i++) {
        for (int j = 0; j < tmp[i].size(); j++) {
            // wcout << "w235 " << tmp[i][j] << endl;
        }

        screen[1] -> addLine(ToTable(5, font, table[1], 10, tmp[i], XText, YText));
    }
    // wcout << "w24" << endl;
    scroll[1] = new Scroll(30, 550, screen[1] -> Height(), 570, 4);
    // wcout << "w25" << endl;
    scroll[1] -> setPosition(1055, 80 + 50 + 15);
// wcout << "w3\n";
    tmp.clear();
    tmp = GetProductsThatCame(warehouse);
    screen[2] -> Clear();
    for (int i = 0; i < tmp.size(); i++) {
        screen[2] -> addLine(ToTable(4, font, table[2], 10, tmp[i], XText, YText));
    }
    scroll[2] = new Scroll(30, 550, screen[2] -> Height(), 570, 4);
    scroll[2] -> setPosition(1055, 80 + 50 + 15);

// wcout << "w4\n";
    tmp.clear();
    tmp = GetListOfDecommissionedProducts(warehouse);
    // wcout << "w41" << endl;
    screen[3] -> Clear();
    // wcout << "w42" << endl;
    for (int i = 0; i < tmp.size(); i++) {
        for (int j = 0; j < tmp[i].size(); j++) {
            // wcout << "w435 " << tmp[i][j] << endl;
        }

        screen[3] -> addLine(ToTable(3, font, table[3], 10, tmp[i], XText, YText));
    }
    // wcout << "w43" << endl;
    scroll[3] = new Scroll(30, 550, screen[3] -> Height(), 570, 4);
    // wcout << "w44" << endl;
    scroll[3] -> setPosition(1055, 80 + 50 + 15);

// wcout << "w5\n";
    tmp.clear();
    tmp = GetListOfRequestsFromOutlets(warehouse, next_day);
    screen[4] -> Clear();
    for (int i = 0; i < tmp.size(); i++) {
        screen[4] -> addLine(ToTable(4, font, table[4], 10, tmp[i], XText, YText));
    }
    scroll[4] = new Scroll(30, 550, screen[4] -> Height(), 570, 4);
    scroll[4] -> setPosition(1055, 80 + 50 + 15);
// wcout << "w6\n";
    tmp.clear();
    tmp = GetStorage(warehouse);
    // wcout << "w61\n";
    screen[5] -> Clear();
    screen[5] -> setNormal();
    screen[5] -> setPositionText(20, 20, 60, 35, 400);
    int last = 0;
    // wcout << "w62\n";
    for (int i = 0; i < tmp.size(); i++) {
        // wcout << "w63\n";
        if (i != tmp.size() - 1 && tmp[i][0] == tmp[i + 1][0]) {
            continue;
        }
        int count_package = 0;
        for (int j = last; j <= i; j++) {
            count_package += s_to_i(tmp[i][2]);

        }
        // wcout << "w64\n";
        screen[5] -> addLine(i_to_s(i + 1) + L". " + tmp[i][0]);
        screen[5] -> addLine(L"Количество упаковок: " + i_to_s(count_package));
        screen[5] -> addLine(L"Количество в одной упаковоке: " + tmp[i][1]);
        screen[5] -> addLine(L"Подробнее: ");
        screen[5] -> addLine({L"Количество упаковок", L"Срок годности", L"Цена"});
        // wcout << "w65\n";
        for (int j = last; j <= i; j++) {
            vector<wstring> temp = {tmp[j][2], tmp[j][3], tmp[j][4]};
            screen[5] -> addLine(temp);

        }
        // wcout << "w66\n";
        last = i + 1;
    }
    // wcout << "w67\n";
    scroll[5] = new Scroll(30, 550, screen[5] -> Height(), 570, 4);
    scroll[5] -> setPosition(1055, 80 + 50 + 15);
}



info MainPage(info prev, WarehouseSystem & warehouse) {
    info result = prev;
    int LENGTH = 1500, HEIGHT = 800;
    int MLENGTH = 500, MHEIGHT = 600;
    float BLength = 250, BHeight = 100, StepButton = BHeight + 50;
    float XButton = 1170, YButton = 300;
    float SLength = 1000, SHeight = 650, SUpHeight = 80;
    float XScreen = 50, YScreen = 50;
    float WLength = 170, WHeight = 80, WStep = WLength;
    float XWindow = XScreen - 10, YWindow = YScreen + SHeight;
    float XText = 60, YText = YScreen + SUpHeight + 10;
    int Ch_sz = 45, Ch_sz_w = 30;
    int PAGE = 0;
    Color Color_for_text = Color::Black;
    Font font;
    font.loadFromFile(ASSET_PREFIX + "Basic Comical Italic NC.ttf");
    string s_font = ASSET_PREFIX + "Basic Comical Regular NC.ttf";

    RenderWindow window(sf::VideoMode(LENGTH, HEIGHT), "Warehouse");

    Texture fon_texture;
    fon_texture.loadFromFile(ASSET_PREFIX + "Fon7.1.jpg");
    Sprite fon;
    fon.setTexture(fon_texture);
    fon.setPosition(0, 0);
    fon.setScale(1.5, 1.5);

    vector<Button *> b_window;
   for (int i = 0; i < 6; i++) {
        Button * temp = new Button(WLength, WHeight);
        temp -> setPosition(XWindow + WStep * i, YWindow);
        if (i == 0) {
            temp -> setImage(ASSET_PREFIX + "Button.jpg", 0, BHeight + WHeight * 2);
            temp -> setNCImage(ASSET_PREFIX + "Button.jpg", 0, BHeight + WHeight * 3);
        } else if (i + 1 == 6) {
            temp -> setImage(ASSET_PREFIX + "Button.jpg", 0, BHeight + WHeight * 4);
            temp -> setNCImage(ASSET_PREFIX + "Button.jpg", 0, BHeight + WHeight * 5);
        } else {
            temp -> setImage(ASSET_PREFIX + "Button.jpg", 0, BHeight);
            temp -> setNCImage(ASSET_PREFIX + "Button.jpg", 0, BHeight + WHeight);
        }

        temp -> setFont(s_font);
        temp -> setCharacterSize(Ch_sz_w);
        temp -> setString(w_button_string[i]);
        b_window.push_back(temp);
    }
    b_window[PAGE] -> setNoneClick();
    vector<Screen *> screen;
    for (int i = 0; i < 6; i++) {
        Screen * temp = new Screen (SLength, SHeight, SUpHeight);
        temp -> setPosition(XScreen, YScreen);
        temp -> setFont(s_font);
        temp -> setHead(screen_head_string[i]);
        temp -> Off();
        screen.push_back(temp);

    }
    screen[PAGE] -> On();

    vector<Scroll *> scroll(6);

    Button next(BLength, BHeight);
    next.setPosition(XButton, YButton);
    next.setImage(ASSET_PREFIX + "Button.jpg", 0, 0);
    next.setNCImage(ASSET_PREFIX + "NCButton.jpg", 0, 0);
    next.setFont(s_font);
    next.setString(L"Далее");
    next.setCharacterSize(Ch_sz);


    Button exit(BLength, BHeight);
    exit.setPosition(XButton, YButton + StepButton);
    exit.setImage(ASSET_PREFIX + "Button.jpg", 0, 0);
    exit.setNCImage(ASSET_PREFIX + "NCButton.jpg", 0, 0);
    exit.setFont(s_font);
    exit.setString(L"Выход");
    exit.setCharacterSize(Ch_sz);

    Button complete(BLength, BHeight, false);
    complete.setPosition(XButton, YButton + StepButton * 2);
    complete.setImage(ASSET_PREFIX + "Button.jpg", 0, 0);
    complete.setNCImage(ASSET_PREFIX + "NCButton.jpg", 0, 0);
    complete.setFont(s_font);
    complete.setString(L"Итог");
    complete.setCharacterSize(Ch_sz);

    screen[0] -> setTable(table_size[0] + 10 * 5, 600, 5);
    screen[1] -> setTable(table_size[1] + 10 * 5, 600, 5);
    screen[2] -> setTable(table_size[2] + 10 * 4, 600, 5);
    screen[3] -> setTable(table_size[3] + 10 * 3, 600, 5);
    screen[4] -> setTable(table_size[4] + 10 * 4, 600, 5);

    screen[0] -> addLine(ToTable(5, font, table[0], 10, head_table[0], XText, YText));
    screen[1] -> addLine(ToTable(5, font, table[1], 10, head_table[1], XText, YText));
    screen[2] -> addLine(ToTable(4, font, table[2], 10, head_table[2], XText, YText));
    screen[3] -> addLine(ToTable(3, font, table[3], 10, head_table[3], XText, YText));
    screen[4] -> addLine(ToTable(4, font, table[4], 10, head_table[4], XText, YText));


    int now_day = 1;
    Text t_now_day;
    t_now_day.setFont(font);
    t_now_day.setCharacterSize(35);
    t_now_day.setPosition(1135, 70);
    t_now_day.setFillColor(Color::Black);
    t_now_day.setString(L"День: " + i_to_s(now_day));


    Text t_now_profit;
    t_now_profit.setFont(font);
    t_now_profit.setCharacterSize(35);
    t_now_profit.setPosition(1135, 120);
    t_now_profit.setFillColor(Color::Black);


    RectangleShape desk(Vector2f(330, 150));
    desk.setPosition(1130, 50);
    desk.setFillColor(Color::White);
    desk.setOutlineColor(Color::Black);
    desk.setOutlineThickness(5);


    Texture help_t;
    help_t.loadFromFile(ASSET_PREFIX + "FonHelp.png", IntRect(0, 0, 1500, 90));
    Sprite help_s;
    help_s.setTexture(help_t);
    help_s.setPosition(0, 710);
    // wcout << "q8\n";
    vector<std::vector<std::pair<uint32_t, uint32_t>>> next_day = warehouse.NextDay();
    t_now_profit.setString(L"Прибыль: " + i_to_s(warehouse.GetStatistics().GetProfit()));
    // wcout << "q9\n";
    FillAll(screen, scroll, font, XText, YText, warehouse, next_day);
    // wcout << "q10\n";
    chrono::steady_clock::time_point start_t, end_t;
    float prev_x, prev_y;
    bool flag = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                if (now_day == prev.day) {
                    result.status = 1;
                } else {
                    result.status = -1;
                }
                window.close();
            }

            if (event.type == sf::Event::MouseMoved) {
                double x = Mouse::getPosition(window).x;
                double y = Mouse::getPosition(window).y;
                for (int i = 0; i < 6; i++) {
                    if (PAGE == i && scroll[i] -> Status()) {
                        end_t = chrono::steady_clock::now();
                        auto t = chrono::duration_cast<chrono::nanoseconds>(end_t - start_t);
                        scroll[i] -> Move((y - prev_y) / t.count(), t.count());
                        screen[i] -> Move(scroll[i] -> dH());
                        prev_y = y;
                        start_t = chrono::steady_clock::now();
                    }

                }
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    double x = event.mouseButton.x;
                    double y = event.mouseButton.y;

                    if (exit.In(x, y)) {
                        if (complete.Status()) result.status = 1;
                        else result.status = -1;
                        window.close();
                        //
                    }
                    if (complete.In(x, y) && complete.IsActive()) {
                        result.status = 1;
                        window.close();
                        //
                    }

                    if (next.In(x, y) && next.IsActive()) {
                        // wcout << "e1" << endl;
                        next_day = warehouse.NextDay();
                    // wcout << "e2" << endl;
                        FillAll(screen, scroll, font, XText, YText, warehouse, next_day);
                        now_day = warehouse.GetCurrentDay();
                        t_now_day.setString(L"День: " + i_to_s(now_day));
                        t_now_profit.setString(L"Прибыль: " + i_to_s(warehouse.GetStatistics().GetProfit()));
                        if (now_day == prev.day) {
                            complete.setClick();
                            next.setNoneClick();
                        }
                    }

                    for (int i = 0; i < 6; i++) {
                        if (b_window[i] -> In(x, y)) {
                            PAGE = i;
                        }
                    }
                    for (int i = 0; i < 6; i++) {
                        if (PAGE != i) {
                            b_window[i] -> setClick();
                            screen[i] -> Off();
                        } else {
                            b_window[i] -> setNoneClick();
                            screen[i] -> On();
                        }
                    }

                    for (int i = 0; i < 6; i++) {
                        if (PAGE == i && scroll[i] -> In(x, y)) {
                            scroll[i] -> On();
                            start_t = chrono::steady_clock::now();
                            flag = true;
                            prev_y = y;
                        }

                    }
                }

            }

            if (event.type == Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    for (int i = 0; i < 6; i++) {
                        scroll[i] -> Off();
                    }
                }
            }



        }

        window.clear();


        window.draw(fon);
        next.draw(window);
        exit.draw(window);
        complete.draw(window);
        window.draw(desk);
        window.draw(t_now_day);
        window.draw(t_now_profit);
        screen[PAGE] -> draw(window);
        scroll[PAGE] -> draw(window);

        window.draw(help_s);
        for (int i = 0; i < 6; i++) {
            b_window[i] -> draw(window);

        }



        window.display();
    }
    return result;
}
