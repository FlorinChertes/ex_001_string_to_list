cmake_minimum_required (VERSION 3.7)
project (ex_001_string_to_list_prj)

IF (MSVC) 
	# Activate C++ exception handling 
	IF (NOT CMAKE_CXX_FLAGS MATCHES "/EHsc") 
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc") 
	ENDIF ()
ELSE ()
	SET(GCC_STD_CPP_11_COMPILE_FLAGS "-std=c++11")
	SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_STD_CPP_11_COMPILE_FLAGS}")
ENDIF () 

# add the executable
add_executable(
    ex_001_string_to_list_prj
	
    src/ex_001_string_to_list.cpp

)

