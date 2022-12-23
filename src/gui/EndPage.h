#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

#include "helpers/Helpers.h"
#include "asset_manager.hpp"

#include "../simplifier.hpp"


using namespace std;
using namespace sf;

wstring get2() {
    return L"12345";
}

vector<wstring> str = {L"Количество дней:  ",
                       L"Количество выполненых заказов:  ",
                       L"Денеждые потери:  ",
                       L"Выручка:  ",
                       L"Поставленные продукты:  "};

wstring Formed(pair<int, wstring> t, int i) {
    wstring ans =  i_to_s(i) + L". " + t.second + L":  " + i_to_s(t.first);
    return ans;

}

vector <pair<int, wstring>> getProducts() {
    vector <pair<int, wstring>> ans = { make_pair(155, L"Сыр"),
                                        make_pair(156, L"Капуста"),
                                        make_pair(176, L"Веревка"),
                                        make_pair(1105, L"Конфеты"),
                                        make_pair(900, L"Газировка"),
                                        make_pair(1, L"Мыло")};
    return ans;
}

vector <pair<int, wstring>> FormedGetProduct(vector<std::pair<std::shared_ptr<const Product>, uint32_t>> vec) {

    vector <pair<int, wstring>> ans;
    for (int i = 0; i < vec.size(); i++) {
        ans.push_back(make_pair(vec[i].second, vec[i].first -> GetName()));
    }
    return ans;
}

info EndPage(info result, WarehouseSystem & warehouse) {
    int LENGTH = 1500, HEIGHT = 800;
    int MLENGTH = 500, MHEIGHT = 600;
    float BLength = 250, BHeight = 100, StepButton = BHeight + 50;
    float XButton = 1200, YButton = 300;
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

    Texture help_texture;
    help_texture.loadFromFile(ASSET_PREFIX + "FonHelpEndPage.png");
    Sprite help_fon;
    help_fon.setTexture(help_texture);
    help_fon.setPosition(0, 710);


    Button exit(BLength, BHeight);
    exit.setPosition(XButton, YButton);
    exit.setImage(ASSET_PREFIX + "Button.jpg", 0, 0);
    exit.setNCImage(ASSET_PREFIX + "NCButton.jpg", 0, 0);
    exit.setFont(s_font);
    exit.setString(L"Завершить");
    exit.setCharacterSize(Ch_sz);

    Button again(BLength, BHeight);
    again.setPosition(XButton, YButton + StepButton);
    again.setImage(ASSET_PREFIX + "Button.jpg", 0, 0);
    again.setNCImage(ASSET_PREFIX + "NCButton.jpg", 0, 0);
    again.setFont(s_font);
    again.setString(L"Заново");
    again.setCharacterSize(Ch_sz);

    Screen screen(1000, 650, 80);
    screen.setNormal();
    screen.setPosition(XScreen, YScreen);
    screen.setFont(s_font);
    screen.setHead(L"Итоги");
    screen.setPositionText(20, 20, 70, 40);

    Statistics statistic = warehouse.GetStatistics();

    screen.addLine(str[0] + i_to_s(warehouse.GetCurrentDay()));
    screen.addLine(str[1] + i_to_s(statistic.GetAmountOfOrders()));
    screen.addLine(str[2] + i_to_s(statistic.GetBurnt()));
    screen.addLine(str[3] + i_to_s(statistic.GetProfit()));
    screen.addLine(str[4]);

    screen.setPositionText(20, 20, 70, 30);

    vector<pair<int, wstring>> products = FormedGetProduct(GetProducts(warehouse));

    sort(products.rbegin(), products.rend());
    for (int i = 0; i < products.size(); i++) {

        screen.addLine(Formed(products[i], i + 1));
        if (i == 0) {
            //screen.setPositionText(20, 20, 60, 30);
        }
    }
    RectangleShape help_rect(Vector2f(30, 650));
    help_rect.setPosition(XScreen + 1010, YScreen - 10);
    help_rect.setFillColor(Color::Black);

    RectangleShape help_rect_white(Vector2f(30, 80));
    help_rect_white.setPosition(XScreen + 1000, YScreen);
    help_rect_white.setFillColor(Color::White);

    Scroll scroll(30, 560, screen.Height(), 570, 4);
    scroll.setPosition(1055, 80 + 50 + 15);

    chrono::steady_clock::time_point start_t, end_t;
    float prev_x, prev_y;
    bool flag = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                result.status = 0;
                window.close();
            }
            if (event.type == sf::Event::MouseMoved) {
                double x = Mouse::getPosition(window).x;
                double y = Mouse::getPosition(window).y;
                if (scroll.Status()) {
                    end_t = chrono::steady_clock::now();
                    auto t = chrono::duration_cast<chrono::nanoseconds>(end_t - start_t);
                    scroll.Move((y - prev_y) / t.count(), t.count());
                    screen.Move(scroll.dH());
                    prev_y = y;
                    start_t = chrono::steady_clock::now();
                }
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    double x = event.mouseButton.x;
                    double y = event.mouseButton.y;

                    if (exit.In(x, y)) {
                        result.status = 0;
                        window.close();

                    }
                    if (again.In(x, y)) {
                        result.status = 1;
                        window.close();

                    }
                    if (scroll.In(x, y)) {
                        scroll.On();
                        start_t = chrono::steady_clock::now();
                        flag = true;
                        prev_y = y;
                    }



                }

            }

            if (event.type == Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    scroll.Off();
                }
            }



        }

        window.clear();


        window.draw(fon);
        exit.draw(window);
        again.draw(window);
        window.draw(help_rect);
        screen.draw(window);
        window.draw(help_rect_white);

        scroll.draw(window);
        window.draw(help_fon);





        window.display();
    }


    return result;
}
