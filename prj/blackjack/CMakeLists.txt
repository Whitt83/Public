cmake_minimum_required (VERSION 3.5.0)
project(blackjack_sim)

SET (PRJ_SRC
	main.cpp
	card.cpp
	shoe.cpp
	lucky_lady_score_keeper.cpp
	top_three_score_keeper.cpp
)

set (PRJ_INC
	card.hpp
	shoe.hpp
	lucky_lady_score_keeper.hpp
	top_three_score_keeper.hpp
)

ADD_DEFINITIONS(-std=c++0x)
INCLUDE_DIRECTORIES(./)
ADD_EXECUTABLE(${PROJECT_NAME} ${PRJ_SRC} ${PRJ_INC})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX) 
