cmake_minimum_required(VERSION 3.8.0)
project(ChinesePokerGameSolver VERSION 1.0.0
                               DESCRIPTION "A Chinese poker game solver"
                               LANGUAGES CXX)

# include(CTest)
# enable_testing()

aux_source_directory(src source_dir)
add_executable(chinese_poker_game_solver ${source_dir})
target_compile_features(chinese_poker_game_solver PUBLIC cxx_std_20)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
