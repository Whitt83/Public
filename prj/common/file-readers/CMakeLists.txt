cmake_minimum_required (VERSION 3.5.0)
project(filereaders)

SET (PRJ_SRC
	src/csv_reader.cpp
)

set (PRJ_INC
	src/csv_reader.hpp
)



ADD_LIBRARY(${PROJECT_NAME} ${PRJ_SRC} ${PRJ_INC})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX) 
