# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "rosserial_msgs: 2 messages, 3 services")

set(MSG_I_FLAGS "-Irosserial_msgs:/home/zhili/hector_slam_tutorial/auto_car_slam/src/rosserial/rosserial_msgs/msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(rosserial_msgs_generate_messages ALL)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(rosserial_msgs
  "/home/zhili/hector_slam_tutorial/auto_car_slam/src/rosserial/rosserial_msgs/msg/TopicInfo.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rosserial_msgs
)
_generate_msg_cpp(rosserial_msgs
  "/home/zhili/hector_slam_tutorial/auto_car_slam/src/rosserial/rosserial_msgs/msg/Log.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rosserial_msgs
)

### Generating Services
_generate_srv_cpp(rosserial_msgs
  "/home/zhili/hector_slam_tutorial/auto_car_slam/src/rosserial/rosserial_msgs/srv/RequestMessageInfo.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rosserial_msgs
)
_generate_srv_cpp(rosserial_msgs
  "/home/zhili/hector_slam_tutorial/auto_car_slam/src/rosserial/rosserial_msgs/srv/RequestServiceInfo.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rosserial_msgs
)
_generate_srv_cpp(rosserial_msgs
  "/home/zhili/hector_slam_tutorial/auto_car_slam/src/rosserial/rosserial_msgs/srv/RequestParam.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rosserial_msgs
)

### Generating Module File
_generate_module_cpp(rosserial_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rosserial_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(rosserial_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(rosserial_msgs_generate_messages rosserial_msgs_generate_messages_cpp)

# target for backward compatibility
add_custom_target(rosserial_msgs_gencpp)
add_dependencies(rosserial_msgs_gencpp rosserial_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS rosserial_msgs_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(rosserial_msgs
  "/home/zhili/hector_slam_tutorial/auto_car_slam/src/rosserial/rosserial_msgs/msg/TopicInfo.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rosserial_msgs
)
_generate_msg_lisp(rosserial_msgs
  "/home/zhili/hector_slam_tutorial/auto_car_slam/src/rosserial/rosserial_msgs/msg/Log.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rosserial_msgs
)

### Generating Services
_generate_srv_lisp(rosserial_msgs
  "/home/zhili/hector_slam_tutorial/auto_car_slam/src/rosserial/rosserial_msgs/srv/RequestMessageInfo.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rosserial_msgs
)
_generate_srv_lisp(rosserial_msgs
  "/home/zhili/hector_slam_tutorial/auto_car_slam/src/rosserial/rosserial_msgs/srv/RequestServiceInfo.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rosserial_msgs
)
_generate_srv_lisp(rosserial_msgs
  "/home/zhili/hector_slam_tutorial/auto_car_slam/src/rosserial/rosserial_msgs/srv/RequestParam.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rosserial_msgs
)

### Generating Module File
_generate_module_lisp(rosserial_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rosserial_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(rosserial_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(rosserial_msgs_generate_messages rosserial_msgs_generate_messages_lisp)

# target for backward compatibility
add_custom_target(rosserial_msgs_genlisp)
add_dependencies(rosserial_msgs_genlisp rosserial_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS rosserial_msgs_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(rosserial_msgs
  "/home/zhili/hector_slam_tutorial/auto_car_slam/src/rosserial/rosserial_msgs/msg/TopicInfo.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rosserial_msgs
)
_generate_msg_py(rosserial_msgs
  "/home/zhili/hector_slam_tutorial/auto_car_slam/src/rosserial/rosserial_msgs/msg/Log.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rosserial_msgs
)

### Generating Services
_generate_srv_py(rosserial_msgs
  "/home/zhili/hector_slam_tutorial/auto_car_slam/src/rosserial/rosserial_msgs/srv/RequestMessageInfo.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rosserial_msgs
)
_generate_srv_py(rosserial_msgs
  "/home/zhili/hector_slam_tutorial/auto_car_slam/src/rosserial/rosserial_msgs/srv/RequestServiceInfo.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rosserial_msgs
)
_generate_srv_py(rosserial_msgs
  "/home/zhili/hector_slam_tutorial/auto_car_slam/src/rosserial/rosserial_msgs/srv/RequestParam.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rosserial_msgs
)

### Generating Module File
_generate_module_py(rosserial_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rosserial_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(rosserial_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(rosserial_msgs_generate_messages rosserial_msgs_generate_messages_py)

# target for backward compatibility
add_custom_target(rosserial_msgs_genpy)
add_dependencies(rosserial_msgs_genpy rosserial_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS rosserial_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rosserial_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rosserial_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rosserial_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rosserial_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rosserial_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rosserial_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rosserial_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
