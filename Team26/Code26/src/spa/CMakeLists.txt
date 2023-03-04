file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/query_processing_system/evaluator/Result.cpp src/query_processing_system/evaluator/Result.h src/common/parser/ShuntNode.cpp src/query_processing_system/evaluator/clause_evaluator/such_that_clause_evaluator/StringStringClauseEvaluator.cpp)
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)