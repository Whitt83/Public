cmake_minimum_required (VERSION 3.5.0)
project (LibrarySingleton)
SET (PRJ_SRC
	library_function.cpp
)

set (PRJ_INC
	library_function.hpp
)

set(CMAKE_CXX_FLAGS "-g --std=c++11 -O0" )
ADD_LIBRARY(${PROJECT_NAME} ${PRJ_SRC} ${PRJ_INC})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX) 


project(Singleton)

SET (PRJ_SRC
	main.cpp
    OtherClass.cpp
    OtherCompilationUnit.cpp
)

set (PRJ_INC
	singleton.hpp
    OtherClass.hpp
    OtherCompilationUnit.hpp
)

set(CMAKE_CXX_FLAGS "-g --std=c++11 -O0" )
ADD_EXECUTABLE(${PROJECT_NAME} ${PRJ_SRC} ${PRJ_INC})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} LibrarySingleton)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

