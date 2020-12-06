CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(hzx_stl_learn VERSION 0.1.0)

SET(SOURCES ./src/main.cpp ./src/chrono.cpp ./src/myRegex.cpp ./src/myIterator.cpp )


ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)