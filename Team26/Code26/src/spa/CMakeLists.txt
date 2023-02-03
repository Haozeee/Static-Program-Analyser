file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} src/program_knowledge_base/relationship/RelationshipManager.cpp src/program_knowledge_base/relationship/RelationshipManager.h src/program_knowledge_base/relationship/FollowsManager.h src/program_knowledge_base/relationship/FollowsTManager.h src/program_knowledge_base/relationship/ModifiesSManager.h src/program_knowledge_base/relationship/ModifiesPManager.h src/program_knowledge_base/relationship/ParentManager.h src/program_knowledge_base/relationship/ParentTManager.h src/program_knowledge_base/relationship/UsesSManager.h src/program_knowledge_base/relationship/UsesPManager.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
