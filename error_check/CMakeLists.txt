file(GLOB_RECURSE error_check ./  *.cpp)
add_library(error_check_lib ${error_check} )