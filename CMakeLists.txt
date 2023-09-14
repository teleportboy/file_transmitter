cmake_minimum_required(VERSION 3.14)

project(sender LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

add_executable(sender
  main.cpp
  Packet.cpp Packet.h PacketReceiver.cpp PacketReceiver.h PacketsContainer.cpp PacketsContainer.h PacketsSender.cpp PacketsSender.h   types.h
  FileBuilder.h FileBuilder.cpp
  Settings.h Settings.cpp
  constants.h

)
target_link_libraries(sender Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)

include(GNUInstallDirs)
install(TARGETS sender
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
