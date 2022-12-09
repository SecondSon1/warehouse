cmake_minimum_required(VERSION 3.21)
project(Warehouse)

set(CMAKE_CXX_STANDARD 17)

add_executable(Warehouse
        src/main.cpp
        src/interface/system.cpp
        src/interface/system.hpp
        src/interface/product.cpp
        src/interface/product.hpp
        src/interface/storage/package.cpp
        src/interface/storage/package.hpp
        src/interface/storage/storage.cpp
        src/interface/storage/storage.hpp
        src/interface/managers/manager.cpp
        src/interface/managers/manager.hpp
        src/interface/managers/accepting_manager.cpp
        src/interface/managers/accepting_manager.hpp
        src/interface/outlets/outlet.cpp
        src/interface/outlets/outlet.hpp
        src/interface/outlets/types/cafe.cpp
        src/interface/outlets/types/cafe.hpp
        src/interface/outlets/types/school.cpp
        src/interface/outlets/types/school.hpp
        src/interface/outlets/types/market.cpp
        src/interface/outlets/types/market.hpp
        src/interface/outlets/request.cpp src/interface/outlets/request.hpp src/interface/suppliers/request.cpp src/interface/suppliers/request.hpp src/interface/suppliers/supplier.cpp src/interface/suppliers/supplier.hpp)
