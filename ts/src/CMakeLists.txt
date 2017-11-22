cmake_minimum_required(VERSION 3.0.2)
project(task_force_radio)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    ../include/clunk/buffer.cpp
    ../include/clunk/clunk_ex.cpp
    ../include/clunk/context.cpp
    ../include/clunk/distance_model.cpp
    ../include/clunk/hrtf.cpp
    ../include/clunk/kemar.c
    ../include/clunk/clunk_logger.cpp
    ../include/clunk/object.cpp
    ../include/clunk/sample.cpp
    ../include/clunk/source.cpp
    ../include/clunk/sse_fft_context.cpp
    ../include/clunk/stream.cpp
    ../include/clunk/wav_file.cpp
    ../include/dspfilters/source/Bessel.cpp
    ../include/dspfilters/source/Biquad.cpp
    ../include/dspfilters/source/Butterworth.cpp
    ../include/dspfilters/source/Cascade.cpp
    ../include/dspfilters/source/ChebyshevI.cpp
    ../include/dspfilters/source/ChebyshevII.cpp
    ../include/dspfilters/source/Custom.cpp
    ../include/dspfilters/source/Design.cpp
    ../include/dspfilters/source/Documentation.cpp
    ../include/dspfilters/source/Elliptic.cpp
    ../include/dspfilters/source/Filter.cpp
    ../include/dspfilters/source/Legendre.cpp
    ../include/dspfilters/source/Param.cpp
    ../include/dspfilters/source/PoleFilter.cpp
    ../include/dspfilters/source/RBJ.cpp
    ../include/dspfilters/source/RootFinder.cpp
    ../include/dspfilters/source/State.cpp
    ../include/simpleSource/SimpleComp.cpp
    ../include/simpleSource/SimpleEnvelope.cpp
    ../include/simpleSource/SimpleGate.cpp
    ../include/simpleSource/SimpleLimit.cpp
    ../include/sqlite3/sqlite3.c

    antennaManager.cpp
    clientData.cpp
    CommandProcessor.cpp
    datatypes.cpp
    # debugExecutable.cpp
    helpers.cpp
    Logger.cpp
    MacFunctions.cpp
    pipe_handler.cpp
    pipe_handler_mac.cpp
    PlaybackHandler.cpp
    plugin.cpp
    profilers.cpp
    serverData.cpp
    # SharedMemoryHandler.cpp
    task_force_radio.cpp
    Teamspeak.cpp
)

set(INCLUDE_DIRS
    .
	../include
	/usr/local/include
)

set(LIBRARY_DIRS
    /usr/local/lib
)

list(APPEND LIBRARIES
	
)

add_definitions(-DCLUNKAPI=)
add_definitions(-DCLUNK_USES_SSE)
add_definitions(-DX64BUILD)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_LIST_DIR})

include_directories(${INCLUDE_DIRS})
link_directories(${LIBRARY_DIRS})

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME} "-framework CoreFoundation")
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_compile_options(${PROJECT_NAME} PUBLIC
	-Wno-nonportable-include-path
)