cmake_minimum_required (VERSION 3.5.0)
project(euler)

SET (PRJ_SRC
    main.cpp
    p45.cpp
)

set (PRJ_INC
    p45.hpp
)

ADD_DEFINITIONS(-std=c++11)
ADD_EXECUTABLE(${PROJECT_NAME} ${PRJ_SRC} ${PRJ_INC})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX) 
