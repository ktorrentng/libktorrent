set(datacheckertest_SRCS datacheckertest.cpp)

add_executable(datacheckertest ${datacheckertest_SRCS})
add_test(datacheckertest datacheckertest)
ecm_mark_as_test(datacheckertest)
target_link_libraries(datacheckertest Qt5::Test testlib KF5::Torrent)
