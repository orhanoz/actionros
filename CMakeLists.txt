cmake_minimum_required(VERSION 2.8.3)
project(actionlib_tutorials)

find_package(catkin REQUIRED COMPONENTS roscpp actionlib actionlib_msgs)
find_package(Boost REQUIRED COMPONENTS system)

add_action_files(
  DIRECTORY action
  FILES Tatlises.action
        Wait.action
  )

generate_messages(
  DEPENDENCIES actionlib_msgs std_msgs
)

catkin_package(
  CATKIN_DEPENDS actionlib_msgs
)

include_directories(include ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

add_executable(tatlises_server src/tatlises_server.cpp)
target_link_libraries(
  tatlises_server
  ${catkin_LIBRARIES}
)
add_dependencies(
  tatlises_server
  ${actionlib_tutorials_EXPORTED_TARGETS}
)

add_executable(wait_server src/wait_server.cpp)
target_link_libraries(
  wait_server
  ${catkin_LIBRARIES}
)
add_dependencies(
  wait_server
  ${actionlib_tutorials_EXPORTED_TARGETS}
)

add_executable(tatlises_client src/tatlises_client.cpp)
target_link_libraries(
  tatlises_client
  ${catkin_LIBRARIES}
)
add_dependencies(
  tatlises_client
  wait_client
  ${actionlib_tutorials_EXPORTED_TARGETS}
)

add_executable(wait_client src/wait_client.cpp)
target_link_libraries(
  wait_client
  ${catkin_LIBRARIES}
)
add_dependencies(
  wait_client
  ${actionlib_tutorials_EXPORTED_TARGETS}
)



