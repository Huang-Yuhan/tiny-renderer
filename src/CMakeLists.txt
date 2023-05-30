

set(LINE_DRAWING line-drawing.cpp tgaimage.cpp)

add_executable(line_drawing ${LINE_DRAWING})

target_include_directories(line_drawing PUBLIC ${PROJECT_SOURCE_DIR}/include)