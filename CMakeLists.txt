cmake_minimum_required (VERSION 3.25.1)
project (minu)
include(GNUInstallDirs)

include_directories(.)

add_executable (minu minu.cpp)

if(NOT WIN32)
	install(CODE "execute_process(COMMAND mkdir -p /opt/minu/days)")
	install(CODE "execute_process(COMMAND chown -R $ENV{USER}:$ENV{USER} /opt/minu)")
    install(CODE "execute_process(COMMAND chmod -R 755 /opt/minu)")
endif()

install(TARGETS minu
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
