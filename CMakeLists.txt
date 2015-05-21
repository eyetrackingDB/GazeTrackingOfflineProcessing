cmake_minimum_required (VERSION 2.8)
PROJECT(PostProcessing) 

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(EyeTabTracker)
include_directories(GazeTrackerEyeTab/lib_eigen)
include_directories(GazeTrackerEyeTab/src_eyetab)
include_directories(GazeTrackerEyeTab/src_eyelike)

find_package(OpenCV REQUIRED)

add_executable(PostProcessing 
	PostProcessing.cpp
	EyeTabTracker/GazeSettingsEyeTab.cpp 
	EyeTabTracker/GazeTrackerEyeTab.cpp 
	EyeTabTracker/src_eyetab/erase_specular.cpp 
	EyeTabTracker/src_eyetab/eye_center_isophotes.cpp 
	EyeTabTracker/src_eyetab/eye_center_combined.cpp 
	EyeTabTracker/src_eyetab/fit_ellipse.cpp 
	EyeTabTracker/src_eyetab/utils.cpp 
	EyeTabTracker/src_eyetab/gaze_geometry.cpp 
	EyeTabTracker/src_eyetab/gaze_smoothing.cpp 
	EyeTabTracker/src_eyetab/get_poss_limb_pts.cpp 
	EyeTabTracker/src_eyetab/get_eyelids.cpp 
	EyeTabTracker/src_eyetab/gaze_system.cpp 
	EyeTabTracker/src_eyetab/eye_detect.cpp 
	EyeTabTracker/src_eyelike/findEyeCenter.cpp 
	EyeTabTracker/src_eyelike/helpers.cpp 					
)

target_link_libraries(PostProcessing ${OpenCV_LIBS}) 
