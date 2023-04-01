file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(unit_testing ${srcs} src/query_processing_system/evaluator/TestQueryDb.cpp src/query_processing_system/evaluator/TestUnionFind.cpp src/query_processing_system/evaluator/mock_storage/MockStorageReader.h src/query_processing_system/evaluator/query_evaluator/MockIntStringClause.cpp src/query_processing_system/evaluator/query_evaluator/MockIntStringClause.cpp src/query_processing_system/evaluator/query_evaluator/MockIntIntClause.cpp)
target_link_libraries(unit_testing spa)
