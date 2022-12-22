#pragma once
#include <stdexcept>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int s_to_i(wstring text) {
    return std::stoi(text);
}

wstring i_to_s(int x) {
    //return L"1";
    return std::to_wstring(x);
}
