cmake_minimum_required (VERSION 3.8)

project ("sinlang" CXX)

set(SOURCES
	"main.cpp"
)

# SETTING TOOLS to be true will build 
# GenerateAst.cpp
set(TOOLS 1)

if(TOOLS)
	message("building tools")
	add_subdirectory(tools)
endif()

add_executable (${PROJECT_NAME} ${SOURCES})

enable_testing()

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


add_subdirectory(external/googletest)
add_subdirectory(cpplox)
add_subdirectory(test)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

target_link_libraries(${PROJECT_NAME} cpplox)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET sinlang PROPERTY CXX_STANDARD 20)
  set_property(TARGET cpplox PROPERTY CXX_STANDARD 20)
  set_property(TARGET TokenTest PROPERTY CXX_STANDARD 20)
endif()
