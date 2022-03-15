# CMakeList.txt : ShinchokuMiharu の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#
cmake_minimum_required (VERSION 3.8)

# ソースをこのプロジェクトの実行可能ファイルに追加します。
add_executable (ShinchokuMiharu "ShinchokuMiharu.cpp" "ShinchokuMiharu.h")

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})

find_package(glfw3 3.3 CONFIG REQUIRED)

target_link_libraries(ShinchokuMiharu PRIVATE glfw)

# TODO: テストを追加し、必要な場合は、ターゲットをインストールします。
