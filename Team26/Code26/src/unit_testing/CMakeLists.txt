file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(unit_testing ${srcs} src/query_processing_system/parser/TestQueryParser.cpp src/query_processing_system/evaluator/TestQueryEvaluator.cpp)

target_link_libraries(unit_testing spa)

