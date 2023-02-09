file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(unit_testing ${srcs} src/program_knowledge_base/TestEntityManager.cpp src/program_knowledge_base/TestRelationshipManager.cpp "src/source_processor/TestParser.cpp")

target_link_libraries(unit_testing spa)

