#GUI OBJECT lib to include  name is == gui_peer_lib

cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Network Gui Widgets Qml Concurrent Sql REQUIRED)

#Common
include_directories(../Common)
add_subdirectory(../Common/ BUILD_COMMON)

#DAL
include_directories(../DAL)
add_subdirectory(../DAL/ BUILD_DAL)

#Parser
include_directories(../Parser&Structs)
add_subdirectory(../Parser&Structs/ BUILD_PARSER)

#GUI
include_directories(GUI)
#add_subdirectory(GUI)


add_library(overall_peer_static_lib STATIC

      abstractstrategy.h
      abstractstrategy.cpp
      delete_request_response_strategy.h
      delete_request_response_strategy.cpp

      friendsupdatemanager.h
      friendsupdatemanager.cpp

      dataaccessor.h
      dataaccessor.cpp

      cachedata.h
      cachedata.cpp

      add_friend_request_strategy.h
      add_friend_request_strategy.cpp

      clientcontroller.h 
      clientcontroller.cpp

      register_response_strategy.h
      register_response_strategy.cpp
                   
      friend_update_strategy.h
      friend_update_strategy.cpp

      messagestrategy.cpp
      messagestrategy.h
      
      servermanager.cpp
      servermanager.h

      new_friend_response_strategy.h
      new_friend_response_strategy.cpp

      friend_request_response_strategy.h
      friend_request_response_strategy.cpp
      
      clientlogger.h
      clientlogger.cpp

      signalredirector.h
      signalredirector.cpp

      localserver.h
      localserver.cpp

      friendsmanager.h
      friendsmanager.cpp
      
      
      
      blockreader.h
      blockreader.cpp

      login_response_strategy.h
      login_response_strategy.cpp

      recieve_mesage_strategy.cpp
      recieve_mesage_strategy.h 

      blockwriter.cpp
      blockwriter.h
      
      worker.h
      worker.cpp

      ui_mainwindow.h
      application_info.h
      config.h


      GUI/friendmodel.h
      GUI/friendmodel.cpp
      GUI/friendrequestitem.h
      GUI/friendrequestitem.cpp
      GUI/frienditem.h
      GUI/frienditem.cpp
      GUI/friendrequestmodel.h
      GUI/friendrequestmodel.cpp
      GUI/messageitem.h
      GUI/messageitem.cpp
      GUI/messagemodel.h
      GUI/messagemodel.cpp
      GUI/guimanager.h
      GUI/guimanager.cpp
      GUI/rolesenum.h

)


add_executable(MesXMessenger.out main.cpp)
#target_link_libraries(overall_peer_static_lib gui_peer_lib)
target_link_libraries(overall_peer_static_lib common_lib)
target_link_libraries(overall_peer_static_lib dal_overall_static_lib)
target_link_libraries(overall_peer_static_lib parser_and_structs_stat)

target_link_libraries(overall_peer_static_lib Qt5::Core Qt5::Network Qt5::Gui Qt5::Widgets Qt5::Qml Qt5::Concurrent Qt5::Sql)
target_link_libraries(MesXMessenger.out overall_peer_static_lib)