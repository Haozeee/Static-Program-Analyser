file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/query_processing_system/evaluator/clause_evaluator/ClauseResult.cpp src/query_processing_system/evaluator/clause_evaluator/ClauseResult.h src/query_processing_system/evaluator/Result.cpp src/query_processing_system/evaluator/Result.h src/query_processing_system/evaluator/PkbUtil.cpp src/query_processing_system/evaluator/PkbUtil.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
