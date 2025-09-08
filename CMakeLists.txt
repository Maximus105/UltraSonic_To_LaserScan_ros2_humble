cmake_minimum_required(VERSION 3.8)
project(sensor_us_random_gen)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

add_executable(ultrasonic_sensor_data src/random_val_sensor.cpp)
ament_target_dependencies(ultrasonic_sensor_data rclcpp sensor_msgs)

add_executable(array_ultrasonic_sensor_data src/random_val_ensor_array.cpp)
ament_target_dependencies(array_ultrasonic_sensor_data rclcpp sensor_msgs)

add_executable(laser_scan_node src/random_val_laser.cpp)
ament_target_dependencies(laser_scan_node rclcpp sensor_msgs)

add_executable(lidar_array src/lidar_sensor_array_random.cpp)
ament_target_dependencies(lidar_array rclcpp sensor_msgs)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS
  lidar_array
  array_ultrasonic_sensor_data
  laser_scan_node
  ultrasonic_sensor_data
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
