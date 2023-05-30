

set(LINE_DRAWING line-drawing.cpp tgaimage.cpp)

add_executable(line_drawing ${LINE_DRAWING})

target_include_directories(line_drawing PUBLIC ${PROJECT_SOURCE_DIR}/include)

set(TRIANGLE_DRAWING triangle-drawing.cpp tgaimage.cpp)

add_executable(triangle_drawing ${TRIANGLE_DRAWING})

target_include_directories(triangle_drawing PUBLIC ${PROJECT_SOURCE_DIR}/include)