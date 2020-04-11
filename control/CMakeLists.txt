cmake_minimum_required(VERSION 2.8.3)
project(control)



catkin_package()


find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
  geometry_msgs
)





include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(height_control src/height_loop.cpp)
add_dependencies(height_control ${abc_node_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(height_control ${catkin_LIBRARIES})

add_executable(stabilisation src/stabilisation.cpp)
add_dependencies(stabilisation ${abc_node_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(stabilisation ${catkin_LIBRARIES})

add_executable(collector src/collector.cpp)
add_dependencies(collector ${abc_node_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(collector ${catkin_LIBRARIES})


