cmake_minimum_required(VERSION 3.21)
project(Warehouse)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWAREHOUSE_DEBUG")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Warehouse
        src/interface_test.cpp
        src/interface/system.cpp
        src/interface/system.hpp
        src/interface/product.cpp
        src/interface/product.hpp
        src/interface/storage/package.cpp
        src/interface/storage/package.hpp
        src/interface/storage/storage.hpp
        src/interface/managers/manager.hpp
        src/interface/managers/accepting_manager.hpp
        src/interface/outlets/outlet.cpp
        src/interface/outlets/outlet.hpp
        src/interface/outlets/order.hpp
        src/interface/supplier/request.hpp
        src/interface/supplier/supplier.cpp
        src/interface/supplier/supplier.hpp
        src/interface/debug.hpp
        src/interface/exceptions.hpp
        src/interface/supplier/order.hpp
        src/interface/product_table.hpp
        src/interface/statistics.cpp
        src/interface/statistics.hpp
        src/interface/storage/storage.cpp
        src/interface/debug.cpp
        src/simplifier.hpp

        src/main.cpp
        src/gui/helpers/Button.h
        src/gui/helpers/Element.h
        src/gui/helpers/HelpString.h
        src/gui/helpers/List.h
        src/gui/helpers/RecordingWindow.h
        src/gui/helpers/Table.h
        src/gui/helpers/Scroll.h
        src/gui/helpers/Screen.h
        src/gui/EndPage.h
        src/gui/Preview.h
        src/gui/start_page.h src/simplifier.cpp src/gui/asset_manager.hpp)

target_link_libraries(Warehouse sfml-graphics sfml-audio)