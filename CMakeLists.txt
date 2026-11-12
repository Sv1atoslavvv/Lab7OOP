cmake_minimum_required(VERSION 3.16)
project(profspilka_oop_lab7 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(profspilka_oop_lab7
  src/main.cpp
  src/voucher_cost.cpp
  src/domain.cpp
  src/voucher.cpp
  src/services.cpp
  src/inheritance_demo.cpp
  src/voucher_record.cpp
  src/voucher_containers.cpp
  src/stl_iterators.cpp
  src/stl_algorithms.cpp
  src/stl_demo.cpp
)
target_include_directories(profspilka_oop_lab7 PRIVATE include)
