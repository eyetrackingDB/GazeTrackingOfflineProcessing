#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

#include "Constants.h"
#include "Converting.cpp"
#include "ProcessVideoRecording.cpp"
#include "ProcessScreenRecording.cpp"

using namespace std;

static void show_usage(string name)
{
	cerr << "Usage: " << name << " Options:\n"
			<< "\t--input <filepath> \t The filepath to the folder where the video files and settings are located\n"
			<< "\t--output <foldername> \t The folder name for the output (will be created inside the input folder) \n"
			<< "\t--eyealg <algorithm>\t The algorithm that is used for detecting the eye center. Possible Values: grad, isoph, comb \n"
			<< "\t--gazealg <algorithm>\t The algorithm that is used for detecting the gaze. Possible Values: approx, geo \n"
			<< "\t--fastwidth \t The window size of the scaled window that is used for detecting the eye center. (optional) Default: 50 for grad, 80 for isoph algo\n"
			<< "\t--convertfps \t Indicates that we want to convert FPS (optional) Default: off\n"
			<< "\t--drawonvideo \t Indicates that we want to draw the gaze points on the recorded video (optional) Default: off\n"
			<< "\t--drawonscreen \t Indicates that we want to draw the gaze points on the recorded screen (optional but requires --convertfps) Default: off\n"
			<< endl;
}

static bool existsFile (const string& name) {
	ifstream f(name.c_str());
	if (f.good()) {
		f.close();
		return true;
	} else {
		f.close();
		return false;
	}   
}

int main (int argc, char *argv[]){
	// Check if we have at least 7 arguments
	if (argc < 7){
		show_usage(argv[0]);
		return 1;
	}

	// Check the arguments itself
	string folderFilePath;
	string outputFolderName;
	string eyeCenterDetectAlgo;
	string gazeTrackingAlgo; 
	bool convertFPS = false;
	bool drawOnVideo = false;
	bool drawOnScreen = false;
	int fastEyeWidth = 0;

	for (int i = 1; i < argc; ++i) { 
		// **** required parameters *****
		//Check the video input option		
		if (string(argv[i]) == "--input") {
			if (i + 1 < argc) { 
				folderFilePath = argv[++i]; 
			} else { 
				cerr << "--input option requires one argument." << endl;
				show_usage(argv[0]);
				return 1;
			}  
		}
		//Check the output video option
		if (string(argv[i]) == "--output") {
			if (i + 1 < argc) { 
				outputFolderName = argv[++i]; 
				outputFolderName += "/";
			} else { 
				cerr << "--output option requires one argument." << endl;
				show_usage(argv[0]);
				return 1;
			}  
		}
		//Check the eye algorithm option	
		if (string(argv[i]) == "--eyealg") {
			if (i + 1 < argc) { 
				eyeCenterDetectAlgo = argv[++i]; 
			} else { 
				cerr << "--eyealg option requires one argument." << endl;
				show_usage(argv[0]);
				return 1;
			}  
		}
		//Check the gaze algorithm option	
		if (string(argv[i]) == "--gazealg") {
			if (i + 1 < argc) { 
				gazeTrackingAlgo = argv[++i]; 
			} else { 
				cerr << "--gazealg option requires one argument." << endl;
				show_usage(argv[0]);
				return 1;
			}  
		}
	
		// **** optional parameters *****
		//Check the convertFPS option		
		if (string(argv[i]) == "--convertfps") {
			convertFPS = true;
		}
		//Check the drawOnVideo option		
		if (string(argv[i]) == "--drawonvideo") {
			drawOnVideo = true;
		}
		//Check the drawOnScreen option		
		if (string(argv[i]) == "--drawonscreen") {
			drawOnScreen = true;
		}
		//Check the fastSizeWidth Argument		
		if (string(argv[i]) == "--fastwidth") {
			if (i + 1 < argc) { //it must be one available
				istringstream ss(argv[++i]);
				if(!(ss >> fastEyeWidth)){ //it must be a valid number
					cerr << "Invalid Number for argument --fastwidth" << endl;
					show_usage(argv[0]);
					return 1;
				}
			} else {
				cerr << "--fastwidth option requires one argument." << endl;
				show_usage(argv[0]);
				return 1;
			}
		}
	}

	// **** check all argument requirements **** 
	// Check if the required files are available within the folder
	if(!existsFile(folderFilePath+SETTINGS_FILE)){
		cerr << "Missing file in folder: GazeTrackingSettings.txt" << endl;
		return 1;
	}

	if(!existsFile(folderFilePath+RAW_INPUT_VIDEO)){
		cerr << "Missing file in folder: video_recording_raw_vfr.mp4" << endl;
		return 1;
	}
	if(outputFolderName.empty()){
		cerr << "Invalid output folder. Either missing or empty/invalid string!" << endl;
		return 1;
	}
	if(drawOnScreen){ //must only be available if we want to draw on the screen
		if(!existsFile(folderFilePath+RAW_INPUT_SCREEN)){
			cerr << "Missing file in folder: screen_recording_raw_vfr.txt" << endl;
			return 1;
		}
	}

	// Check if the eye center algorithm was specified correctly
	if(eyeCenterDetectAlgo == "grad"){
		eyeCenterDetectAlgo = "EYE_CENTER_ALGO_GRADIENTS";
		//Set the default fast size if no fast size was specified
		if(fastEyeWidth <= 0){
			fastEyeWidth = 50;
		}
	} else if (eyeCenterDetectAlgo == "isoph"){
		eyeCenterDetectAlgo = "EYE_CENTER_ALGO_ISOPHOTES";
		if(fastEyeWidth <= 0){
			fastEyeWidth = 80;
		}
	} else if (eyeCenterDetectAlgo == "comb"){
		eyeCenterDetectAlgo = "EYE_CENTER_ALGO_COMBINED";
		fastEyeWidth = 0; //we do not need this setting as we cannot specify it for the combined version (always uses 50/80)
	} else {
			cerr << "Invalid Eye Center Algorithm" << endl;
			show_usage(argv[0]);
			return 1;
	}

	// Check if the gaze tracking algorithm was specified correctly
	if(gazeTrackingAlgo == "approx"){
		gazeTrackingAlgo = "GAZE_TRACKING_ALGO_APPROX";
	} else if (gazeTrackingAlgo == "geo"){
		gazeTrackingAlgo = "GAZE_TRACKING_ALGO_GEO";
	} else {
			cerr << "Invalid Gaze Tracking Algorithm" << endl;
			show_usage(argv[0]);
			return 1;
	}

	// Create the post proc folder
	mkdir((folderFilePath+outputFolderName).c_str(),0777);

	//Depending on the availability start the corresponding steps
	// Step1 => Check if we have to do a video conversion	
	if(convertFPS){
		convert_fps(folderFilePath, outputFolderName, RAW_INPUT_VIDEO, RAW_INPUT_VIDEO_CFR);
		if(drawOnScreen){
			convert_fps(folderFilePath, outputFolderName, RAW_INPUT_SCREEN, RAW_INPUT_SCREEN_CFR);
		}
	}

	// Step2 => Convert the video file (consider the different type of input files)
	if(convertFPS){
		string postProcFolder = folderFilePath+outputFolderName;
		process_video(postProcFolder+RAW_INPUT_VIDEO_CFR, postProcFolder+PROC_VIDEO_RECORDING_CFR, folderFilePath+SETTINGS_FILE, postProcFolder+TEXT_GAZE_POINTS_CFR, drawOnVideo, eyeCenterDetectAlgo,gazeTrackingAlgo, fastEyeWidth);
	} else {
		string postProcFolder = folderFilePath+outputFolderName;
		process_video(folderFilePath+RAW_INPUT_VIDEO, postProcFolder+PROC_VIDEO_RECORDING_VFR, folderFilePath+SETTINGS_FILE, postProcFolder+TEXT_GAZE_POINTS_VFR, drawOnVideo, eyeCenterDetectAlgo,gazeTrackingAlgo, fastEyeWidth);
	}

	// Step3 => Draw GazePoints on the Screen Recording file
	if(drawOnScreen && convertFPS){
		string postProcFolder = folderFilePath+outputFolderName;
		process_screen(postProcFolder+RAW_INPUT_SCREEN_CFR, postProcFolder+PROC_SCREEN_RECORDING_CFR, postProcFolder+TEXT_GAZE_POINTS_CFR);
	}
	return 0;
}
