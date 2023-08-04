cmake_minimum_required(VERSION 3.20)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if(NOT DEFINED CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
    set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings.")
endif()

project(NodeProcessingV2 CXX)

### cmake module ###
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/thirdparty/cmake/sdl2)

### imgui ###
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/thirdparty/imgui)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends)
set(IMGUI_SOURCES
	${IMGUI_DIR}/imgui.cpp
	${IMGUI_DIR}/imgui_demo.cpp
	${IMGUI_DIR}/imgui_draw.cpp
	${IMGUI_DIR}/imgui_tables.cpp
	${IMGUI_DIR}/imgui_widgets.cpp
	${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
	${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

### imnodes ###
set(IMNODES_DIR ${CMAKE_SOURCE_DIR}/thirdparty/imnodes)
include_directories(${IMNODES_DIR})
set(IMNODES_SOURCES ${IMNODES_DIR}/imnodes.cpp)

### ImGuiFileDialog ###
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/ImGuiFileDialog)
set(IMGUI_FILE_DIALOG_SOURCES ${CMAKE_SOURCE_DIR}/thirdparty/ImGuiFileDialog/ImGuiFileDialog.cpp)

### implot ###
set(IMPLOT_DIR ${CMAKE_SOURCE_DIR}/thirdparty/implot)
include_directories(${IMPLOT_DIR})
set(IMPLOT_SOURCES ${IMPLOT_DIR}/implot.cpp ${IMPLOT_DIR}/implot_items.cpp)

### OpenGL ###
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})

### OpenCV ###
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

### SDL2 ###
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

### stb ###
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/stb)

### NodeProcessingV2 ###
set(MAIN_SRC_DIR ${CMAKE_SOURCE_DIR}/src/)
include_directories(${MAIN_SRC_DIR})
include_directories((${MAIN_SRC_DIR}/node) ${MAIN_SRC_DIR}/profiler)
set(NP_SOURCES
	${MAIN_SRC_DIR}/main.cpp
	${MAIN_SRC_DIR}/MenuBar.cpp
	${MAIN_SRC_DIR}/MenuItem_Audio.cpp
	${MAIN_SRC_DIR}/MenuItem_File.cpp
	${MAIN_SRC_DIR}/MenuItem_ImageVideo.cpp
	${MAIN_SRC_DIR}/NodeGui.cpp
	${MAIN_SRC_DIR}/NodeManager.cpp
	${MAIN_SRC_DIR}/Pin.cpp
	${MAIN_SRC_DIR}/PinManager.cpp
	${MAIN_SRC_DIR}/FileDialog.cpp

	${MAIN_SRC_DIR}/node/BinarizationNode.cpp
	${MAIN_SRC_DIR}/node/EdgeDetectionNode.cpp
	${MAIN_SRC_DIR}/node/GrayScallingNode.cpp
	${MAIN_SRC_DIR}/node/HistogramNode.cpp
	${MAIN_SRC_DIR}/node/ImageNode.cpp
	${MAIN_SRC_DIR}/node/Node.cpp
)

if(WIN32)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
	set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	set(_src_root_path "${CMAKE_SOURCE_DIR}/src/")

	file(GLOB_RECURSE _header_list "${_src_root_path}/*.h")
	add_executable(${PROJECT_NAME} ${NP_SOURCES} ${IMGUI_SOURCES} ${IMNODES_SOURCES} ${IMGUI_FILE_DIALOG_SOURCES} ${IMPLOT_SOURCES} ${_header_list})

	file(GLOB_RECURSE _source_list 
		LIST_DIRECTORIES false
		"${_src_root_path}/*.cpp"
		"${_src_root_path}/*.h"
	)
	foreach(_source IN ITEMS ${_source_list})
		get_filename_component(_source_path "${_source}" PATH)
		file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
		string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
		source_group("${_group_path}" FILES "${_source}")
	endforeach()

	source_group("imgui" FILES ${IMGUI_SOURCES} ${IMNODES_SOURCES} ${IMGUI_FILE_DIALOG_SOURCES} ${IMPLOT_SOURCES})
else()
	add_executable(${PROJECT_NAME} ${NP_SOURCES} ${IMGUI_SOURCES} ${IMNODES_SOURCES} ${IMGUI_FILE_DIALOG_SOURCES} ${IMPLOT_SOURCES})
endif()

target_link_libraries(${PROJECT_NAME} OpenGL::GL ${OpenCV_LIBRARIES} ${SDL2_LIBRARIES})
