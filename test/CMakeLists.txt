cmake_minimum_required (VERSION 3.5)


set(SOURCES 
	TokenTest.cpp
)

add_executable(TokenTest ${SOURCES})


target_link_libraries(TokenTest PRIVATE
	cpplox
	gtest_main
)


add_test(
	TokenGTest TokenTest
)
