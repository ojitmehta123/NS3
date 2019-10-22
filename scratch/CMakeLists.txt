file(GLOB_RECURSE scratches  ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

find_package(rospy REQUIRED)
find_package(roscpp REQUIRED)

set(DONT_BUILD
           )

foreach(scratch_src ${scratches})
    get_filename_component(scratch_name ${scratch_src} NAME)
    string(REGEX REPLACE "\\.[^.]*$" "" scratch_name ${scratch_name})

    string(FIND "${DONT_BUILD}" "${scratch_name}" res)

    if(res LESS 0)
        add_executable(${scratch_name} "${scratch_src}")
    target_link_libraries(${scratch_name} "${ns3-libs}" ${ns3-contrib-libs} ${catkin_LIBRARIES})
    endif()
endforeach()
add_executable(simpub simple_pub.cpp)
target_link_libraries(simpub "${ns3-libs}" ${ns3-contrib-libs} ${catkin_LIBRARIES})

add_executable(simsub simsub.cpp)
target_link_libraries(simsub "${ns3-libs}" ${ns3-contrib-libs} ${catkin_LIBRARIES})


