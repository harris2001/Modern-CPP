set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB CPP_FILES "*.cpp")

foreach(CPP_FILE ${CPP_FILES})
    get_filename_component(TARGET_NAME ${CPP_FILE} NAME_WE)

    add_executable(${TARGET_NAME} ${CPP_FILE})

    add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
endforeach()

