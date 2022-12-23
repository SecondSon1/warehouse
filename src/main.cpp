#include <SFML/Graphics.hpp>
#include <iostream>
#include "gui/helpers/Helpers.h"
#include <random>

#include "gui/Preview.h"
#include "gui/StartPage.h"
#include "gui/MainPage.h"
#include "gui/EndPage.h"

#include "simplifier.hpp"
#include "interface/managers/accepting_manager.hpp"

using namespace std;
using namespace sf;

vector<shared_ptr<Product>> getProduct(info result) {
  vector<shared_ptr<Product>> ans;
  for (int i = 0; i < result.product.size(); i++) {
    uint32_t package_amount = s_to_i(result.product[i][4]);
    uint32_t price = s_to_i(result.product[i][2]) * package_amount;
    ans.push_back(shared_ptr<Product>(new Product(i, result.product[i][0],
                              s_to_i(result.product[i][1]),
                              s_to_i(result.product[i][1]) / 2,
                              price,
                              price * 3 / 2,
                              price * 3 / 4,
                              package_amount,
                              result.package)));
  }

  return ans;
}

vector<double> Cafe(vector<vector<wstring>> result) {
  vector<double> ans;
  for (int i = 0; i < result.size(); i++) {
    if (s_to_i(result[i][3]) == 0) {
      ans.push_back(10);
    } else if (s_to_i(result[i][3]) == 1) {
      ans.push_back(9);
    } else if (s_to_i(result[i][3]) == 2) {
      ans.push_back(6);
    } else if (s_to_i(result[i][3]) == 3) {
      ans.push_back(10);
    } else if (s_to_i(result[i][3]) == 4) {
      ans.push_back(5);
    }
  }
  return ans;
}
vector<double> Shop(vector<vector<wstring>> result) {
  vector<double> ans;
  for (int i = 0; i < result.size(); i++) {
    if (s_to_i(result[i][3]) == 0) {
      ans.push_back(10);
    } else if (s_to_i(result[i][3]) == 1) {
      ans.push_back(10);
    } else if (s_to_i(result[i][3]) == 2) {
      ans.push_back(10);
    } else if (s_to_i(result[i][3]) == 3) {
      ans.push_back(4);
    } else if (s_to_i(result[i][3]) == 4) {
      ans.push_back(6);
    }
  }
  return ans;
}
vector<double> Hospital(vector<vector<wstring>> result) {
  vector<double> ans;
  for (int i = 0; i < result.size(); i++) {
    if (s_to_i(result[i][3]) == 0) {
      ans.push_back(10);
    } else if (s_to_i(result[i][3]) == 1) {
      ans.push_back(2);
    } else if (s_to_i(result[i][3]) == 2) {
      ans.push_back(10);
    } else if (s_to_i(result[i][3]) == 3) {
      ans.push_back(1);
    } else if (s_to_i(result[i][3]) == 4) {
      ans.push_back(10);
    }
  }
  return ans;
}
vector<double> School(vector<vector<wstring>> result) {
  vector<double> ans;
  for (int i = 0; i < result.size(); i++) {
    if (s_to_i(result[i][3]) == 0) {
      ans.push_back(10);
    } else if (s_to_i(result[i][3]) == 1) {
      ans.push_back(3);
    } else if (s_to_i(result[i][3]) == 2) {
      ans.push_back(9);
    } else if (s_to_i(result[i][3]) == 3) {
      ans.push_back(4);
    } else if (s_to_i(result[i][3]) == 4) {
      ans.push_back(5);
    }
  }
  return ans;
}

vector<double> Prof (int n){
  vector<double> ans(n, 1.0);
  return ans;
}

vector<shared_ptr<Outlet>> getOutlet(info result) {
  vector<shared_ptr<Outlet>> ans;
  for (int i = 0; i < result.outlets; i++) {

    if (result.area == 0) {
      int n = rand();
      if (n % 3 == 0) {
        ans.push_back(shared_ptr<Outlet>(new Outlet(i, "Cafe_" + i_to_s(i + 1), Cafe(result.product), Prof(result.product.size()))));
      } else if (n % 3 == 1) {
        ans.push_back(shared_ptr<Outlet>(new Outlet(i, "Shop_" + i_to_s(i + 1), Shop(result.product), Prof(result.product.size()))));
      } else {
        ans.push_back(shared_ptr<Outlet>(new Outlet(i, "School_" + i_to_s(i + 1), School(result.product), Prof(result.product.size()))));
      }
    } else if (result.area == 1) {
      int n = rand();
      if (n % 3 == 0) {
        ans.push_back(shared_ptr<Outlet>(new Outlet(i, "Hospital_" + i_to_s(i + 1), Hospital(result.product), Prof(result.product.size()))));
      } else if (n % 3 == 1) {
        ans.push_back(shared_ptr<Outlet>(new Outlet(i, "Shop_" + i_to_s(i + 1), Shop(result.product), Prof(result.product.size()))));
      } else {
        ans.push_back(shared_ptr<Outlet>(new Outlet(i, "School_" + i_to_s(i + 1), School(result.product), Prof(result.product.size()))));
      }
    } else if (result.area == 2) {
      int n = rand();
      if (n % 3 == 0) {
        ans.push_back(shared_ptr<Outlet>(new Outlet(i, "Hospital_" + i_to_s(i + 1), Hospital(result.product), Prof(result.product.size()))));
      } else if (n % 3 == 1) {
        ans.push_back(shared_ptr<Outlet>(new Outlet(i, "Shop_" + i_to_s(i + 1), Shop(result.product), Prof(result.product.size()))));
      } else {
        ans.push_back(shared_ptr<Outlet>(new Outlet(i, "Cafe_" + i_to_s(i + 1), Cafe(result.product), Prof(result.product.size()))));
      }
    }

  }

  return ans;
}

int main() {



  while (true) {
      vector<info> result;
//        result.push_back(Preview());
//
//        if (result.back().status == 0) {
//            break;
//        }
        result.push_back(StartPage());
        if (result.back().status == 0) {
            continue;
        }
//
//        wcout << result[0].area << " " <<result[0].day << " " << result[0].packege << endl;
//        wcout << endl;
//        for (int i = 0; i < result[0].product.size(); i++) {
//            for (int j = 0; j < result[0].product[i].size(); j++){
//                wcout << result[0].product[i][j] << endl;
//        }
//        }
//        wcout << "///////////////" << endl;
//    info temp;
//    temp.day = 365;
//    temp.area = 0;
//    temp.manager = 0;
//    temp.outlets = 2;
//    temp.status = 1;
//    temp.package = 70;
//    temp.product.push_back({L"Хлеб", L"14", L"150", L"0", L"15"});
    //temp.product.push_back({L"aaaaaaa", L"14", L"123", L"0", L"12"});
//    result.push_back(temp);

    vector<shared_ptr<Product>> product = getProduct(result.back());
    shared_ptr<AcceptingManager> manager = shared_ptr<AcceptingManager>( new AcceptingManager);
    shared_ptr<Supplier> supplier = shared_ptr<Supplier>(new Supplier);
    vector<shared_ptr<Outlet>> outlet = getOutlet(result.back());
    WarehouseSystem warehouse(move(product), manager, outlet, supplier);


    result.push_back(MainPage(result.back(), warehouse));
    result.push_back(EndPage(result.back(), warehouse));
    if (result.back().status == 0) {
      break;
    }
  }

  return 0;
}
