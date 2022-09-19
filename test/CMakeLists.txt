add_executable(SolverTest SolverTest.cpp)

target_compile_features(SolverTest PRIVATE cxx_std_20)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

target_include_directories(
    SolverTest
    PRIVATE $<TARGET_PROPERTY:PokerSolver,INCLUDE_DIRECTORIES> # include library's private headers
)

target_link_libraries(
    SolverTest
    PRIVATE PokerSolver
    PRIVATE GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(SolverTest)