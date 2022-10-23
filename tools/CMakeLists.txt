cmake_minimum_required (VERSION 3.8)

set(SOURCES 
	"GenerateAst.cpp"
)

add_executable(generateast ${SOURCES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET generateast PROPERTY CXX_STANDARD 20)
endif()
