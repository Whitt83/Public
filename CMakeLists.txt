cmake_minimum_required (VERSION 3.5.0)

if (TARGETPLATFORM  STREQUAL "vocore2")
	ADD_SUBDIRECTORY(prj/common)
	ADD_SUBDIRECTORY(prj/hello_world)
endif()

if (TARGETPLATFORM  STREQUAL "x64linux")
	ADD_SUBDIRECTORY(prj/common)
	ADD_SUBDIRECTORY(prj/hello_world)
	ADD_SUBDIRECTORY(prj/codekata)
	ADD_SUBDIRECTORY(prj/destiny)
	ADD_SUBDIRECTORY(prj/blackjack)
	ADD_SUBDIRECTORY(prj/singleton)
  ADD_SUBDIRECTORY(prj/euler)
endif()


