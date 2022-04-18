cmake_minimum_required (VERSION 3.16)

set (SRC_FILES 
	"main.cpp"
	"app/Charactor.cpp"
	"app/Texture.cpp"
	"app/Text.cpp"
	"sys/Monitor.cpp"
	"extra/stb_impl.cpp"
)

add_executable (Miharu ${SRC_FILES})

if(WIN32)
	# show console if debug
	set_property(TARGET Miharu PROPERTY WIN32_EXECUTABLE $<NOT:$<CONFIG:Debug>>)
	set_property(TARGET Miharu PROPERTY VS_DPI_AWARE "PerMonitor")
endif()

if(MSVC)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
endif()

set_property(TARGET Miharu PROPERTY CXX_STANDARD 20)
set_property(TARGET Miharu PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET Miharu PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/dist")
set_property(TARGET Miharu PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/dist_d")

find_package(OpenGL REQUIRED)
target_link_libraries(Miharu PRIVATE ${OPENGL_LIBRARIES})
include_directories(${OPENGL_INCLUDE_DIRS})

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(Miharu PRIVATE glfw)
include_directories(${GLFW_INCLUDE_DIRS})

find_path(STB_INCLUDE_DIRS "stb.h" REQUIRED)
target_include_directories(Miharu PRIVATE ${STB_INCLUDE_DIRS})

# TODO: テストを追加し、必要な場合は、ターゲットをインストールします。
