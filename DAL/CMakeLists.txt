cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 11)

set(IsSampleApp 1)

if(${IsSampleApp})
    set(CMAKE_AUTOMOC ON)
    find_package(Qt5 COMPONENTS Core Sql REQUIRED)

    add_executable(DAL_sample_app.out main.cpp)
    #target_link_libraries(DAL_sample_app.out Qt5::Core Qt5::Sql)
endif()

#if(FALSE)
include_directories(Connection)
add_subdirectory(Connection)


add_library(dal_overall_static_lib STATIC
    deletefriendnotification.h
    deletefriendnotification.cpp
    friend.h
    friend.cpp
    friendrequest.h
    friendrequest.cpp
    notificationinfo.h
    notificationinfo.cpp
    requestinfo.h
    requestinfo.cpp
    sqldal.h 
    unitofwork.cpp
    unitofwork.h 
    user.h
    user.cpp
    friendinfo.h
    friendinfo.cpp
    info.h
    message.h
    message.cpp 
 #   serverdal.h
 #   serverdal.cpp
    statement.h
    statement.cpp
#    $<TARGET_OBJECTS:dal_connect_obj_lib>
)

#endif()
target_link_libraries(dal_overall_static_lib Qt5::Core Qt5::Sql)
target_link_libraries(dal_overall_static_lib dal_connect_static_lib)

if(${IsSampleApp})
   target_link_libraries(DAL_sample_app.out dal_overall_static_lib)
endif()