set(GTEST_SHUFFLE 1)

find_package(OpenCV REQUIRED)

add_executable(
cpp-test 
main.cpp 
StereoTest.cpp 
HumanDetectorTest.cpp
../app/Stereo.cpp
../app/Scene.cpp
../app/HumanDetector.cpp
)

target_include_directories(cpp-test PUBLIC ../vendor/googletest/googletest/include 
                                           ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(cpp-test PUBLIC gtest ${OpenCV_LIBS})
