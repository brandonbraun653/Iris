
# Add project dependencies to this target interface
add_library(iris_prj_dependencies INTERFACE)
export(TARGETS iris_prj_dependencies FILE "Iris/iris_prj_dependencies.cmake")

# Use this target for include headers
add_library(iris_intf_inc INTERFACE)
export(TARGETS iris_intf_inc FILE "Iris/iris_intf_inc.cmake")
target_include_directories(iris_intf_inc INTERFACE
  ./..
  ./include
)
target_link_libraries(iris_intf_inc INTERFACE
  iris_prj_dependencies
)

# Use this target for linking
add_library(iris_lib STATIC
  src/session/session_mngr.cpp
  src/transport/transport_packet.cpp
)
export(TARGETS iris_lib FILE "Iris/iris_lib.cmake")

target_link_libraries(iris_lib PRIVATE
  iris_prj_dependencies
  iris_intf_inc
)
