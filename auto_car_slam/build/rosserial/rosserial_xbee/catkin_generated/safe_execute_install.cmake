execute_process(COMMAND "/home/zhili/hector_slam_tutorial/auto_car_slam/build/rosserial/rosserial_xbee/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/zhili/hector_slam_tutorial/auto_car_slam/build/rosserial/rosserial_xbee/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
