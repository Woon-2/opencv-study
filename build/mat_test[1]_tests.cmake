add_test([=[MatTest.assign]=]  [==[C:/Users/USER/Desktop/footprint of soilder/opencv/opencv-study/build/Release/mat_test.exe]==] [==[--gtest_filter=MatTest.assign]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatTest.assign]=]  PROPERTIES WORKING_DIRECTORY [==[C:/Users/USER/Desktop/footprint of soilder/opencv/opencv-study/build]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[Terminate.Terminate]=]  [==[C:/Users/USER/Desktop/footprint of soilder/opencv/opencv-study/build/Release/mat_test.exe]==] [==[--gtest_filter=Terminate.Terminate]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Terminate.Terminate]=]  PROPERTIES WORKING_DIRECTORY [==[C:/Users/USER/Desktop/footprint of soilder/opencv/opencv-study/build]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  mat_test_TESTS MatTest.assign Terminate.Terminate)
