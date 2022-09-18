add_library(
    PokerSolver
    Cards.cpp
    Pattern.cpp
)

# set C++ minimum standard to 20
target_compile_features(PokerSolver PRIVATE cxx_std_20) # we need three way comparison operator
set_target_properties(PokerSolver PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(
    PokerSolver
    PRIVATE ../include/PokerSolver
)

# add SSE support (SSE2 is so old that I assume it should have been already supported)
target_compile_options(PokerSolver PRIVATE $<IF:$<BOOL:${MSVC}>,/arch:SSE4.1,-msse4.1>)