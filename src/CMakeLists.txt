add_library(
    PokerSolver
    Cards.cpp
    Pattern.cpp
)

# set C++ minimum standard to 17
target_compile_features(PokerSolver PRIVATE cxx_std_17)
set_target_properties(PokerSolver PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(
    PokerSolver
    PRIVATE ../include/PokerSolver
)

# add SSE support (SSE2 is so old that I assume it should have been already supported)
if (NOT MSVC)
    target_compile_options(PokerSolver PUBLIC -msse4.1)
endif()