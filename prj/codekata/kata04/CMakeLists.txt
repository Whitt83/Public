cmake_minimum_required (VERSION 3.5.0)
project(codekata04)

SET (PRJ_SRC
	src/kata04.cpp
)

set (PRJ_INC
	src/kata04.hpp
)

ADD_DEFINITIONS(-std=c++0x)
INCLUDE_DIRECTORIES(../../common/file-readers/src)
ADD_LIBRARY(${PROJECT_NAME} ${PRJ_SRC} ${PRJ_INC})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX) 







project(test_codekata04)

SET (PRJ_SRC
	test/main.cpp
)

set (PRJ_INC
	#None
)

ADD_DEFINITIONS(-std=c++0x)
INCLUDE_DIRECTORIES(./src)
ADD_EXECUTABLE(${PROJECT_NAME} ${PRJ_SRC} ${PRJ_INC})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} codekata04 filereaders)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX) 
