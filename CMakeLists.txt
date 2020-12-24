CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(hzx_stl_learn VERSION 0.1.0)

SET(SOURCES ./src/main.cpp ./src/mychrono.cpp ./src/myRegex.cpp ./src/myIterator.cpp ./src/myAsync.cpp ./src/cmd_parser.cpp )


IF (WIN32)
	MESSAGE(STATUS "Now is windows")
ELSEIF (APPLE)
	MESSAGE(STATUS "Now is Apple systens.")
ELSEIF (UNIX)
	MESSAGE(STATUS "Now is UNIX-like OS's.")
ENDIF ()


ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}//include
)