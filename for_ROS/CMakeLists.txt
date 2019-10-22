file(GLOB_RECURSE scratches  ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)


set(DONT_BUILD
        )

find_package(rospy REQUIRED)
find_package(roscpp REQUIRED)

foreach(scratch_src ${scratches})
    get_filename_component(scratch_name ${scratch_src} NAME)
    string(REGEX REPLACE "\\.[^.]*$" "" scratch_name ${scratch_name})

    string(FIND "${DONT_BUILD}" "${scratch_name}" res)

    if(res LESS 0)
        add_executable(${scratch_name} "${scratch_src}")
    target_link_libraries(${scratch_name} "${ns3-libs}" ${ns3-contrib-libs})
    endif()
endforeach()

add_executable(for_ROS simple_pub.cpp)
target_link_libraries(for_ROS ${catkin_LIBRARIES})
