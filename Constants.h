#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

using namespace std;

// The files which are available in the main directory
const string RAW_INPUT_VIDEO = "video_recording_raw_vfr.mp4";
const string RAW_INPUT_SCREEN = "screen_recording_raw_vfr.mp4";
const string SETTINGS_FILE = "GazeTrackingSettings.txt";

// The files which are produced during post processing
const string RAW_INPUT_VIDEO_CFR = "video_recording_raw_cfr.mp4";
const string RAW_INPUT_SCREEN_CFR = "screen_recording_raw_cfr.mp4";
const string PROC_VIDEO_RECORDING_VFR = "video_recording_proc_vfr.avi";
const string PROC_VIDEO_RECORDING_CFR = "video_recording_proc_cfr.avi";
const string PROC_SCREEN_RECORDING_CFR = "screen_recording_proc_cfr.avi";
const string TEXT_GAZE_POINTS_VFR = "gaze_points_vfr.txt";
const string TEXT_GAZE_POINTS_CFR = "gaze_points_cfr.txt";

#endif
