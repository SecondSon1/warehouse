cmake_minimum_required(VERSION 3.21)
project(Warehouse)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWAREHOUSE_DEBUG")

add_executable(Warehouse
        src/main.cpp
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
        src/interface/product_table.hpp src/interface/report.cpp src/interface/report.hpp)
