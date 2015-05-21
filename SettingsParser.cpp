#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Device Model
const string KEY_DEVICE_MODEL = "DEVICE_MODEL";

// Device Parameters that depend on the orientation
const string KEY_ORIENTATION = "ORIENTATION";
const string KEY_SCREEN_HEIGHT_PX = "SCREEN_HEIGHT_PX";
const string KEY_SCREEN_WIDTH_PX = "SCREEN_WIDTH_PX";
const string KEY_SCREEN_HEIGHT_MM = "SCREEN_HEIGHT_MM";
const string KEY_SCREEN_WIDTH_MM = "SCREEN_WIDTH_MM";

// Camera parameters that depend on camera/setting and orientation
const string KEY_CAMERA_RES_WIDTH = "CAMERA_RES_WIDTH";
const string KEY_CAMERA_RES_HEIGHT = "CAMERA_RES_HEIGHT";

// Camera parameters that depend on orientation and device
const string KEY_CAMERA_OFFSET_X = "CAMERA_OFFSET_X";
const string KEY_CAMERA_OFFSET_Y = "CAMERA_OFFSET_Y";

// Camera parameters (intrinsic) - requires calibration
const string KEY_CAMERA_FOCAL_LEN_X = "CAMERA_FOCAL_LEN_X";
const string KEY_CAMERA_FOCAL_LEN_Y = "CAMERA_FOCAL_LEN_Y";
const string KEY_CAMERA_PRIN_POINT_X = "CAMERA_PRIN_POINT_X";
const string KEY_CAMERA_PRIN_POINT_Y = "CAMERA_PRIN_POINT_Y";

// Camera parameters extrinsic - requires calibration
const string KEY_CAMERA_DISTORT_0 = "CAMERA_DISTORT_0";
const string KEY_CAMERA_DISTORT_1 = "CAMERA_DISTORT_1";
const string KEY_CAMERA_DISTORT_2 = "CAMERA_DISTORT_2";
const string KEY_CAMERA_DISTORT_3 = "CAMERA_DISTORT_3";
const string KEY_CAMERA_DISTORT_4 = "CAMERA_DISTORT_4";

// The type def for the current settings mapping
typedef map<const string,string> SettingsMap;

static SettingsMap currentSettings;
static void parseSettings(const string filePath){
	// The settings file	
	ifstream f(filePath.c_str());

	//Parse the settings
	string line;
	while (getline(f, line)){
		currentSettings[line.substr(0,line.find('='))]=line.substr(line.find('=')+1);
	}
}

static string getOrientation(){
	return currentSettings[KEY_ORIENTATION];
}

static int getScreenWidthPX(){
	return stoi(currentSettings[KEY_SCREEN_WIDTH_PX]);
}

static int getScreenHeightPX(){
	return stoi(currentSettings[KEY_SCREEN_HEIGHT_PX]);
}

static int getScreenWidthMM(){
	return stoi(currentSettings[KEY_SCREEN_WIDTH_MM]);
}

static int getScreenHeightMM(){
	return stoi(currentSettings[KEY_SCREEN_HEIGHT_MM]);
}

static int getCameraResWidth(){
	return stoi(currentSettings[KEY_CAMERA_RES_WIDTH]);
}

static int getCameraResHeight(){
	return stoi(currentSettings[KEY_CAMERA_RES_HEIGHT]);
}

static int getCameraOffsetX(){
	return stoi(currentSettings[KEY_CAMERA_OFFSET_X]);
}

static int getCameraOffsetY(){
	return stoi(currentSettings[KEY_CAMERA_OFFSET_Y]);
}

static float getFocalLenX(){
	return stof(currentSettings[KEY_CAMERA_FOCAL_LEN_X]);
}

static float getFocalLenY(){
	return stof(currentSettings[KEY_CAMERA_FOCAL_LEN_Y]);
}

static float getFocalLenZ(){
	return (stof(currentSettings[KEY_CAMERA_FOCAL_LEN_X]) + stof(currentSettings[KEY_CAMERA_FOCAL_LEN_Y]))/2.0f;
}

static float getPrinPointX(){
	return stof(currentSettings[KEY_CAMERA_PRIN_POINT_X]);
}

static float getPrinPointY(){
	return stof(currentSettings[KEY_CAMERA_PRIN_POINT_Y]);
}
