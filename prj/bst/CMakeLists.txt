cmake_minimum_required (VERSION 3.5.0)
project(bst)

SET (PRJ_SRC
	src/bst.c
)

set (PRJ_INC
	src/bst.h
)



ADD_LIBRARY(${PROJECT_NAME} ${PRJ_SRC} ${PRJ_INC})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C) 






project(test_bst)

SET (PRJ_SRC
	test/test-bst.cpp
)

set (PRJ_INC
	#None
)

INCLUDE_DIRECTORIES(./src)
ADD_EXECUTABLE(${PROJECT_NAME} ${PRJ_SRC} ${PRJ_INC})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} bst)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX) 
