cmake_minimum_required(VERSION 3.10)

project(run_dachshund VERSION 0.1)

add_subdirectory(SDL)

# path to src folder with .c files and inc folder with .h files
set(PATH_SRC ${PROJECT_SOURCE_DIR}/src)
set(PATH_INC ${PROJECT_SOURCE_DIR}/inc)

# EXEC list with all of sources to add by "add_executable" 
list(APPEND EXEC ${PATH_SRC}/main.c)
list(APPEND EXEC ${PATH_SRC}/encoder_decoder.c)
list(APPEND EXEC ${PATH_SRC}/engine.c)

if (WIN32)
    list(APPEND EXEC ${PATH_SRC}/client_win.c)
    list(APPEND EXEC ${PATH_SRC}/server_win.c)
else()
    list(APPEND EXEC ${PATH_SRC}/client_mac.c)
    list(APPEND EXEC ${PATH_SRC}/server_mac.c)
endif()



# add all executables from EXEC list
add_executable(run_dachshund ${EXEC})

# link winsock
if (WIN32)
    target_link_libraries(run_dachshund wsock32 ws2_32)
endif()

# link SDL
target_link_libraries(run_dachshund SDL2)

# copy sdl dll file into build folder; it does not do it by default
# taken from https://github.com/libsdl-org/SDL/issues/6399
add_custom_command(TARGET run_dachshund POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE_DIR:run_dachshund>" VERBATIM)

# includes
target_include_directories(run_dachshund PUBLIC ${PATH_INC})

