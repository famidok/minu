cmake_minimum_required (VERSION 3.25.1)
project (minu)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(GNUInstallDirs)

include_directories(.)

add_executable (minu minu.cpp)

if(NOT WIN32)
	install(CODE "execute_process(COMMAND mkdir -p ~/.local/minu/day)")
endif()

install(TARGETS minu
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
