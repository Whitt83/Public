cmake_minimum_required (VERSION 3.5.0)
project(codekata18)

SET (PRJ_SRC
	kata18.c
)

set (PRJ_INC
	#None
)

ADD_LIBRARY(${PROJECT_NAME} ${PRJ_SRC} ${PRJ_INC})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C) 
