file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/program_knowledge_base/relationship/ReadOnlyRelationshipManager.cpp src/program_knowledge_base/relationship/ReadOnlyRelationshipManager.h src/program_knowledge_base/relationship/WriteOnlyRelationshipManager.cpp src/program_knowledge_base/relationship/WriteOnlyRelationshipManager.h src/program_knowledge_base/pattern/ReadOnlyPatternManager.cpp src/program_knowledge_base/entity/EntityManager.cpp src/program_knowledge_base/ReadOnlyStorage.h src/program_knowledge_base/WriteOnlyStorage.cpp src/program_knowledge_base/WriteOnlyStorage.h src/program_knowledge_base/entity/EntityManager.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
