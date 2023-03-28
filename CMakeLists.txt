cmake_minimum_required(VERSION 3.10)

project(run_dashund VERSION 0.1)

# path to src folder with .c files and inc folder with .h files
set(PATH_SRC ${PROJECT_SOURCE_DIR}/src)
set(PATH_INC ${PROJECT_SOURCE_DIR}/inc)

# EXEC list with all of sources to add by "add_executable" 
list(APPEND EXEC ${PATH_SRC}/main.c)

if (WIN32)
    list(APPEND EXEC ${PATH_SRC}/client_win.c)
    list(APPEND EXEC ${PATH_SRC}/server_win.c)
else()
    list(APPEND EXEC ${PATH_SRC}/client_mac.c)
    list(APPEND EXEC ${PATH_SRC}/server_mac.c)
endif()

# add all executables from EXEC list
add_executable(run_dashund ${EXEC})

# link winsock
if (WIN32)
    target_link_libraries(run_dashund wsock32 ws2_32)
endif()

# includes
target_include_directories(run_dashund PUBLIC ${PATH_INC})