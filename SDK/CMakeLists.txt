cmake_minimum_required(VERSION 3.17) 
set(TARGET_NAME DEMO)
project(${TARGET_NAME})
add_definitions(-D SDK_EXPORT)

set(SDK_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SDK_3RD_PARTY ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty)


include_directories (${SDK_3RD_PARTY})
include_directories (${SDK_DIR})

#Qt
file(GLOB SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	)

file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h 
				  )
add_library(${TARGET_NAME} SHARED ${SOURCES} ${HEADERS})

#set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "SDK")

install(TARGETS ${TARGET_NAME} RUNTIME  DESTINATION bin)
install(FILES ${TARGET_NAME} DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/DEMO)