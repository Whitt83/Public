cmake_minimum_required (VERSION 3.5.0)
project(HelloWorld)

SET (PRJ_SRC
	main.cpp
)

set (PRJ_INC
	#None
)

ADD_EXECUTABLE(${PROJECT_NAME} ${PRJ_SRC} ${PRJ_INC})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX) 

