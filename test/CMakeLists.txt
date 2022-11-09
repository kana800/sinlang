cmake_minimum_required (VERSION 3.5)


set(SOURCES 
	TokenTest.cpp
	ParserTest.cpp
)

add_executable(SinLangTest ${SOURCES})


target_link_libraries(SinLangTest PRIVATE
	cpplox
	gtest_main
)


add_test(
	TokenGTest TokenTest
)
