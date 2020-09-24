cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(RtspAccess)

add_library(RtspAccess SHARED
        RtspFF.cpp
        RtspFF.h)

target_link_libraries(RtspAccess
		avformat avdevice avcodec avutil avfilter swresample swscale pthread)

# install(TARGETS detection_task DESTINATION ${INSTALL_ROOT_DIR}/lib/)

