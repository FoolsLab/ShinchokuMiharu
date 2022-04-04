# CMakeList.txt : ShinchokuMiharu の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#
cmake_minimum_required (VERSION 3.16)

set (SRC_FILES 
	"ShinchokuMiharu.cpp"
	"ShinchokuMiharu.h"
)

# ソースをこのプロジェクトの実行可能ファイルに追加します。

add_executable (ShinchokuMiharu ${SRC_FILES})

if(WIN32)
	# show console if debug
	set_property(TARGET ShinchokuMiharu PROPERTY WIN32_EXECUTABLE $<NOT:$<CONFIG:Debug>>)
	set_property(TARGET myproject PROPERTY VS_DPI_AWARE "PerMonitor")
endif()

find_package(OpenGL REQUIRED)
target_link_libraries(ShinchokuMiharu PRIVATE ${OPENGL_LIBRARIES})
include_directories(${OPENGL_INCLUDE_DIRS})

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(ShinchokuMiharu PRIVATE glfw)
include_directories(${GLFW_INCLUDE_DIRS})

find_path(STB_INCLUDE_DIRS "stb.h" REQUIRED)
target_include_directories(ShinchokuMiharu PRIVATE ${STB_INCLUDE_DIRS})

# TODO: テストを追加し、必要な場合は、ターゲットをインストールします。
