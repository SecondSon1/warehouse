#include <SFML/Graphics.hpp>
#include <iostream>
#include "helpers/Helpers.h"

#include <chrono>
#include "../simplifier.hpp"
#include "asset_manager.hpp"

using namespace std;
using namespace sf;




vector<wstring> text_for_first_page = {L"Длительность моделирования",
                                      L"Количество торговых точек",
                                      L"Максимальное количество упаковок",
                                      L"Район моделирования",
                                      L"Стратегия моделирования"};
vector<wstring> text_for_second_page = {L"Товары",};

vector<wstring> str_area = {L"Жилой район", L"Бизнес-центр", L"Туристический центр"};

vector<wstring> str_manager = {L"Добрый"};

vector<wstring> str_type = {L"Постоянного спроса",
                            L"Импульсивной покупки",
                            L"Экстренных случаев",
                            L"Особого спроса",
                            L"Пассивного спроса"};


wstring not_selected = L"Не выбрано";

vector<wstring> head = {L"Наименование",
                        L"    Срок\nгодности",
                        L"Закупочная\n      цена",
                        L"Товар",
                        L"Количество\nв упаковке"};
vector<wstring> hints_page_one_str = {L"*Обязательное поле. Значение в диапозоне от 7 до 100.",
                                      L"*Обязательное поле. Значение в диапозоне от 3 до 9.",
                                      L"*Обязательное поле. Ненулевое значение.",
                                      L"*Обязательный выбор.",
                                      L"*Обязательный выбор.",
                                      };
vector<wstring> hints_page_two_str = {L"*В таблице должна быть полностью заполнена хотя бы одна строка."
                                      };

bool is_num(wstring text) {
    for (int i = 0; i < text.size(); i++) {
        if (int(text[i]) < 48 || int(text[i]) > 57) {
            return false;
        }
    }
    return true;
}


info StartPage() {

    int LENGTH = 1500, HEIGHT = 800;
    float XNotepad = 20, YNotpad = 50;
    float XText = XNotepad + 100, YText = YNotpad + 50, StepText = 120;
    float BLength = 250, BHeight = 100;
    float XButton = 1200, YButton = 30, StepButton = BHeight + 50;
    float XRec = 900, YRec = YText + 10, StepRec = StepText;
    float XList = 800;
    float XHint = XText, YHint = YText + 50, StepHint = StepText;
    float RLenght = 100, RHeight = 70;
    int PAGE = 1;
    Color Color_for_text = Color::Black;
    Font font;
    font.loadFromFile(ASSET_PREFIX + "Basic Comical Italic NC.ttf");
    font.loadFromFile(ASSET_PREFIX + "Basic Comical Italic NC.ttf");
    string s_font = ASSET_PREFIX + "Basic Comical Regular NC.ttf";
    string s_i_font = ASSET_PREFIX + "Basic Comical Italic NC.ttf";
    vector<Element *> itemes;
    bool TRY = false;

    RecordingWindow * r_temp = new RecordingWindow;

    r_temp -> setSize(180, 75);
    r_temp -> setFont(s_font);
    r_temp -> setImage(ASSET_PREFIX + "Rec2.png");
    r_temp -> setNCImage(ASSET_PREFIX + "Rec2.png", 0, 75);

    r_temp -> Off();

    itemes.push_back(r_temp);
    r_temp = dynamic_cast<RecordingWindow *>(r_temp -> copy());
    r_temp -> setChecker(is_num);
    itemes.push_back(r_temp);
    itemes.push_back(r_temp -> copy());

    vector<Text> hints_page_one;
    for (int i = 0; i < hints_page_one_str.size(); i++) {
        Text tmp;
        tmp.setFont(font);
        tmp.setCharacterSize(20);
        tmp.setFillColor(Color::Black);
        tmp.setString(hints_page_one_str[i]);
        tmp.setPosition(XHint, YHint + StepHint * i);
        hints_page_one.push_back(tmp);
    }

    vector<Text> hints_page_two;
    for (int i = 0; i < hints_page_two_str.size(); i++) {
        Text tmp;
        tmp.setFont(font);
        tmp.setCharacterSize(20);
        tmp.setPosition(110, 155);
        tmp.setFillColor(Color::Black);
        tmp.setString(hints_page_two_str[i]);
        hints_page_two.push_back(tmp);
    }



    List * l_temp = new List;
    l_temp -> setSize(180, 75);
    l_temp -> setFont(s_font);
    l_temp -> setString(not_selected);
    l_temp -> setCharacterSize(30);
    l_temp -> setStep(40);
    l_temp -> setList(str_type, 320);
    l_temp -> setImage(ASSET_PREFIX + "List2.png");
    l_temp -> setString(not_selected);
    itemes.push_back(l_temp);
    itemes.push_back(r_temp -> copy());


    RenderWindow window(sf::VideoMode(LENGTH, HEIGHT), "Warehouse");


    RectangleShape notepad(Vector2f(1080, 680));
    notepad.setPosition(XNotepad + 30, YNotpad);
    notepad.setFillColor(Color::White);
    notepad.setOutlineColor(Color::Black);
    notepad.setOutlineThickness(10);
    /*Texture notepad_texture;
    notepad_texture.loadFromFile("Notepad4.png");
    Sprite notepad;
    notepad.setTexture(notepad_texture);
    notepad.setPosition(XNotepad, HEIGHT - YNotpad);
    notepad.setScale(1.25, 1.4);
    notepad.setRotation(-90);*/


    Texture fon_texture;
    fon_texture.loadFromFile(ASSET_PREFIX + "Fon7.1.jpg");
    Sprite fon;
    fon.setTexture(fon_texture);
    fon.setPosition(0, 0);
    fon.setScale(1.5, 1.5);


    Button next(BLength, BHeight);
    next.setPosition(XButton, YButton);
    next.setImage(ASSET_PREFIX + "Button.jpg", 0, 0);
    next.setNCImage(ASSET_PREFIX + "NCButton.jpg", 0, 0);
    next.setFont(s_font);
    next.setString(L"Next");

    Button prev(BLength, BHeight, false);
    prev.setPosition(XButton, YButton + StepButton);
    prev.setImage(ASSET_PREFIX + "Button.jpg", 0, 0);
    prev.setNCImage(ASSET_PREFIX + "NCButton.jpg", 0, 0);
    prev.setFont(s_font);
    prev.setString(L"Prev");

    Button clear(BLength, BHeight);
    clear.setPosition(XButton, YButton + StepButton * 2);
    clear.setImage(ASSET_PREFIX + "Button.jpg", 0, 0);
    clear.setFont(s_font);
    clear.setString(L"Clear");

    Button start(BLength, BHeight, true);
    start.setPosition(XButton, YButton + StepButton * 3);
    start.setImage(ASSET_PREFIX + "Button.jpg", 0, 0);
    start.setNCImage(ASSET_PREFIX + "NCButton.jpg", 0, 0);
    start.setFont(s_font);
    start.setString(L"Start");

    Button exit(BLength, BHeight);
    exit.setPosition(XButton, YButton + StepButton * 4);
    exit.setImage(ASSET_PREFIX + "Button.jpg", 0, 0);
    exit.setFont(s_font);
    exit.setString(L"Exit");


    vector<Text> first_page;

    for (int i = 0; i < text_for_first_page.size(); i++) {
        Text temp;
        temp.setFont(font);
        temp.setString(text_for_first_page[i]);
        temp.setPosition(XText, YText + StepText * i);
        temp.setColor(Color_for_text);
        temp.setCharacterSize(40);
        first_page.push_back(temp);
    }

    vector<Text> second_page;

    for (int i = 0; i < text_for_second_page.size(); i++) {
        Text temp;
        temp.setFont(font);
        temp.setString(text_for_second_page[i]);
        temp.setPosition(XText, YText + (530) * (i != 0));
        temp.setColor(Color_for_text);
        temp.setCharacterSize(40);
        second_page.push_back(temp);
    }

    RecordingWindow day(RLenght, RHeight, 0);

    day.setPosition(XRec, YRec);
    day.setFont(s_i_font);
    day.setImage(ASSET_PREFIX + "Rec.png");
    day.setNCImage(ASSET_PREFIX + "Rec.png", 0, RHeight + 2);


    RecordingWindow outlets(RLenght, RHeight, 0);

    outlets.setPosition(XRec, YRec + StepRec);
    outlets.setFont(s_i_font);
    outlets.setImage(ASSET_PREFIX + "Rec.png");
    outlets.setNCImage(ASSET_PREFIX + "Rec.png", 0, RHeight + 2);

    RecordingWindow package(RLenght, RHeight, 0);

    package.setPosition(XRec, YRec + StepRec * 2);
    package.setFont(s_i_font);
    package.setImage(ASSET_PREFIX + "Rec.png");
    package.setNCImage(ASSET_PREFIX + "Rec.png", 0, RHeight + 2);

    List area(200, 50);
    area.setPosition(XList, YRec + StepRec * 3);
    area.setStep(50);
    area.setFont(s_font);
    area.setCharacterSize(30);
    area.setList(str_area, 300);
    area.setImage(ASSET_PREFIX + "List.png");
    area.setString(not_selected);

    List manager(200, 50);
    manager.setPosition(XList, YRec + StepRec * 4);
    manager.setStep(50);
    manager.setFont(s_font);
    manager.setCharacterSize(30);
    manager.setList(str_manager);
    manager.setImage(ASSET_PREFIX + "List.png");
    manager.setString(not_selected);


    Table table(5, 0, 185, 80, Vector2f(925, 5),
                Vector2f(5, 400));
    table.setFont(s_font);
    table.setHead(head);
    table.setItems(itemes);
    table.setPosition(XText, 190);
    for (int i = 0; i < 17; i++) {
        table.addLine();
    }

    Scroll scroll(30, 395, 1360, 320, 4);
    scroll.setPosition(XText + 925, 195);

    info result;

    chrono::steady_clock::time_point start_t, end_t;
    bool flag = false;
    float prev_x, prev_y;

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

                if (PAGE == 1 && area.IsActive()) {
                    if (area.InChoice(x, y)) {

                        area.setChoice(area.CountChoice(x, y));
                    }
                }
                if (PAGE == 1 && manager.IsActive()) {
                    if (manager.InChoice(x, y)) {
                        manager.setChoice(manager.CountChoice(x, y));
                    }
                }

                if (PAGE == 2 && scroll.Status()) {
                    end_t = chrono::steady_clock::now();
                    auto t = chrono::duration_cast<chrono::nanoseconds>(end_t - start_t);
                    scroll.Move((y - prev_y) / t.count(), t.count());
                    table.Move(scroll.dH());
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
                    if (clear.In(x, y)) {
                        table.Clear();
                        package.Clear();
                        outlets.Clear();
                        day.Clear();
                        manager.Clear();
                        area.Clear();

                    }

                    if (next.In(x, y) && next.IsActive()) {
                        PAGE = 2;
                        next.setNoneClick();
                        prev.setClick();
                    }

                    if (prev.In(x, y) && prev.IsActive()) {
                        PAGE = 1;
                        prev.setNoneClick();
                        next.setClick();

                    }

                    if (start.In(x, y) && start.IsActive()) {
                        TRY = true;
                        if (day.getString() != L"") {
                            result.day = s_to_i(day.getString());
                        } else {
                            TRY = false;
                            continue;
                        }
                        if (result.day < 7 || result.day > 100) {
                            TRY = false;
                        }
                        if (outlets.getString() != L"") {
                            result.outlets = s_to_i(outlets.getString());
                        } else {
                            TRY = false;
                            continue;
                        }
                        if (result.outlets < 3 || result.outlets > 9) {
                            TRY = false;
                        }
                        if (package.getString() != L"") {
                            result.package = s_to_i(package.getString());
                        } else {
                            TRY = false;
                            continue;
                        }
//                        if (result.packege < 1 || result.packege > 15) {
//                            TRY = false;
//                        }

                        result.area = area.getChoice();
                        result.manager = manager.getChoice();
                        cout << endl << table.Count() << endl;
                        if (table.Count() > 0) {
                            result.product = table.Result();

                        } else {
                            TRY = false;
                        }
                        if (TRY == true) {
                            result.status = 1;
                            window.close();
                        }
                    }
                    if (day.In(x, y) && PAGE == 1) {
                        day.Switch();
                        package.setNoneClick();
                        outlets.setNoneClick();
                    }

                    if (outlets.In(x, y) && PAGE == 1) {
                        outlets.Switch();
                        package.setNoneClick();
                        day.setNoneClick();
                    }

                    if (package.In(x, y) && PAGE == 1) {
                        package.Switch();
                        outlets.setNoneClick();
                        day.setNoneClick();

                    }
                    if (table.In(x, y) && PAGE == 2) {
                        table.Click(x, y);
                    }

                    if (PAGE == 1 && area.In(x, y)) {
                        if (manager.IsActive()) {
                            manager.Off();
                        }
                        if (area.IsActive()) {
                            area.Off();
                        } else {
                            area.On();
                        }
                    }
                    if (PAGE == 1 && area.IsActive() && area.InChoice(x, y)) {
                        ////////////////////////
                        area.setString(area.NameChoice(area.CountChoice(x, y)));
                        area.Off();
                        break;
                    }

                    if (PAGE == 1 && manager.In(x, y)) {
                        if (area.IsActive()) {
                            area.Off();
                        }
                        if (manager.IsActive()) {
                            manager.Off();
                        } else {
                            manager.On();
                        }

                    }
                    if (PAGE == 1 && manager.IsActive() && manager.InChoice(x, y)) {
                        ////////////////////////
                        manager.setString(manager.NameChoice(manager.CountChoice(x, y)));
                        manager.Off();
                    }

                    if (PAGE == 2 && scroll.In(x, y)) {
                        scroll.On();
                        start_t = chrono::steady_clock::now();
                        flag = true;
                        prev_y = y;
                    }

                }
            }

            if (event.type == Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (PAGE == 2) {
                        scroll.Off();
                    }
                }
            }
            if (event.type == sf::Event::TextEntered) {

                wchar_t symbol = static_cast<wchar_t>(event.text.unicode);
                if (day.IsActive() && PAGE == 1) {
                    wstring tmp = day.getString();
                    if (symbol == 8) {
                        if (tmp.size() > 0) {
                            tmp.pop_back();
                        }
                    } else if (symbol >= 48 && symbol <= 57) {
                        tmp += symbol;
                    }
                    day.setString(tmp);
                }
                if (outlets.IsActive() && PAGE == 1) {
                    wstring tmp = outlets.getString();
                    if (symbol == 8) {
                        if (tmp.size() > 0) {
                            tmp.pop_back();
                        }
                    } else if (symbol >= 48 && symbol <= 57) {
                        tmp += symbol;
                    }
                    outlets.setString(tmp);
                }
                if (package.IsActive() && PAGE == 1) {
                    wstring tmp = package.getString();
                    if (symbol == 8) {
                        if (tmp.size() > 0) {
                            tmp.pop_back();
                        }
                    } else if (symbol >= 48 && symbol <= 57) {
                        tmp += symbol;
                    }
                    package.setString(tmp);
                }
                if (table.IsActive() && PAGE == 2) {
                    // wcout << "***\n";
                    // wcout << event.text.unicode << endl;
                    wstring tmp = table.getString();
                    // wcout << tmp << endl;
                    if (symbol == 8) {
                        if (tmp.size() > 0) {
                            tmp.pop_back();
                        }
                    } else if (symbol >= 32) {
                        tmp += symbol;
                        // wcout << int(symbol) << endl;
                        // wcout << symbol << endl;
                    }
                    table.setString(tmp);
                }


            }


        }

        window.clear();
        window.draw(fon);
        window.draw(notepad);
        if (PAGE == 1) {
            for (int i = 0; i < first_page.size(); i++) {
                window.draw(first_page[i]);
            }
            for (int i = 0; i < hints_page_one.size(); i++) {
                window.draw(hints_page_one[i]);
            }

            day.draw(window);
            outlets.draw(window);
            package.draw(window);
            manager.draw(window);
            area.draw(window);

        } else if (PAGE == 2) {

            for (int i = 0; i < second_page.size(); i++) {
                window.draw(second_page[i]);
            }
            table.draw(window);
            scroll.draw(window);
            for (int i = 0; i < hints_page_two.size(); i++) {
                window.draw(hints_page_two[i]);
            }






        }
        next.draw(window);
        prev.draw(window);
        start.draw(window);
        clear.draw(window);
        exit.draw(window);



        window.display();
    }


    return result;

}
