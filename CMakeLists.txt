project(CppMonolith)
find_package(cpprestsdk REQUIRED)
add_executable(CppMonolith main.cpp BasicController.cpp BFSResult.cpp BFSService.cpp EdmondsKarpService.cpp Graph.cpp GraphController.cpp GraphRepository.cpp GraphService.cpp DirectedGraph.cpp PushRelabelService.cpp KeyboardInterruptHandler.cpp)
target_link_libraries(CppMonolith PUBLIC cpprestsdk::cpprest ssl crypto)