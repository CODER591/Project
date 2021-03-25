cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)

include_directories(Exceptions DAL Logger RequestProcessing)

#DAL
include_directories(../DAL)
add_subdirectory(../DAL/ BUILD_DAL)

#Parser
include_directories(../Parser&Structs)
add_subdirectory(../Parser&Structs/ BUILD_PARSER)


find_package(Qt5 COMPONENTS Core Network Concurrent Sql REQUIRED)

add_library(server_binary_lib_stat STATIC

            async_server.h
            async_server.cpp
            server_thread.h
            server_thread.cpp

            Exceptions/user_not_found.h

            Logger/logger.h
            Logger/logger.cpp

            DAL/Client.h
            DAL/client.cpp
            DAL/dal.h
            DAL/dal.cpp

            RequestProcessing/abstract_request.h
            RequestProcessing/abstract_request.cpp
            RequestProcessing/add_friend_request.h
            RequestProcessing/add_friend_request.cpp
            RequestProcessing/delete_friend_request.h
            RequestProcessing/delete__friend_request.cpp
            RequestProcessing/friendship_request.h
            RequestProcessing/friendship_request.cpp
            RequestProcessing/login_request.h
            RequestProcessing/login_request.cpp
            RequestProcessing/new_user_request.h
            RequestProcessing/new_user_request.cpp

)

add_executable(MesXServer.out main.cpp)

target_link_libraries(server_binary_lib_stat dal_overall_static_lib)
target_link_libraries(server_binary_lib_stat parser_and_structs_stat)

target_link_libraries(server_binary_lib_stat Qt5::Core Qt5::Network Qt5::Concurrent Qt5::Sql)

target_link_libraries(MesXServer.out server_binary_lib_stat)
target_link_libraries(MesXServer.out Qt5::Core Qt5::Network Qt5::Concurrent Qt5::Sql)
#target_link_libraries(MesXServer.out $<TARGET_OBJECTS:server_binary_lib_obj>)