cmake_minimum_required (VERSION 3.5.0)
project(destiny)

SET (PRJ_SRC
	main.cpp
)

set (PRJ_INC
	data_file_format.hpp
	base64.hpp
)

ADD_DEFINITIONS(-std=c++0x)
INCLUDE_DIRECTORIES(../common/file-readers/src)
ADD_EXECUTABLE(${PROJECT_NAME} ${PRJ_SRC} ${PRJ_INC})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX) 
TARGET_LINK_LIBRARIES(${PROJECT_NAME} filereaders ssl crypto)
