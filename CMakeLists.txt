cmake_minimum_required(VERSION 3.8)
project(test_domain_bridge_app)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(composition_interfaces REQUIRED)
find_package(domain_bridge REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(lifecycle_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rcl_interfaces REQUIRED)

add_executable(service_bridge src/service_bridge.cpp)
ament_target_dependencies(service_bridge
  composition_interfaces
  domain_bridge
  example_interfaces
  lifecycle_msgs
  rclcpp
  rcl_interfaces
)

install(TARGETS
  service_bridge
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
