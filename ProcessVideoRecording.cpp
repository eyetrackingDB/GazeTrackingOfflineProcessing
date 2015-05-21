#include <iostream>
#include <string>

#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 

#include "SettingsParser.cpp"
#include "EyeTabTracker/GazeTrackerEyeTab.h"

using namespace cv;
using namespace std;

const string CASCADE_FILE_EYE_PAIR = "raw/haarcascade_mcs_eyepair_big.xml";
const string CASCADE_FILE_EYE_LEFT = "raw/haarcascade_mcs_lefteye.xml";
const string CASCADE_FILE_EYE_RIGHT = "raw/haarcascade_mcs_righteye.xml";

void process_video(const string inputVideoFile, const string outputVideoFile, const string settingsFile, const string gazePointsFile, bool drawOnVideo, const string eyeCenterDetectAlgo, const string gazeTrackingAlgo, int fastEyeWidth) {
	// Read in the settings
	parseSettings(settingsFile);
	
	//The input video file
	VideoCapture inputVideo(inputVideoFile);
	inputVideo.set(CV_CAP_PROP_CONVERT_RGB, true);

	//The output video file
	VideoWriter outputVideo;
	if(drawOnVideo){
		Size size;	
		// The input video is always in landscape mode => width/height must be exchanged for portrait/reverse portrait
		if (getOrientation() == "LANDSCAPE" || getOrientation() == "LANDSCAPE_REVERSE"){
			size = Size((int) inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), 
					  (int) inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));
		} else {
			size = Size((int) inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT),
					  (int) inputVideo.get(CV_CAP_PROP_FRAME_WIDTH));
		}
		outputVideo.open(outputVideoFile , CV_FOURCC('X','V','I','D'), inputVideo.get(CV_CAP_PROP_FPS),size, true);
	}

	//Check if the video file is loaded
	if (!inputVideo.isOpened()){
		cout << "Error: Video Recording File not found!!" << endl;
		return;
	}

	//Create the text file to store the gaze points in
	ofstream gazeFile;
	gazeFile.open(gazePointsFile);

	//Processing the video recording
	Mat frame;
	int framecounter = 0;
	float timestamp = 0;

	// Create and init the GazeTracker
	GazeTrackerEyeTab gazeTracker;
	gazeTracker.init(CASCADE_FILE_EYE_PAIR, CASCADE_FILE_EYE_LEFT, CASCADE_FILE_EYE_RIGHT, 
		getOrientation(), getScreenWidthPX(), getScreenHeightPX(), getScreenWidthMM(), getScreenHeightMM(),
		getCameraOffsetX(), getCameraOffsetY(), getCameraResWidth(), getCameraResHeight(), getFocalLenX(), getFocalLenY(), 
		getFocalLenZ(), getPrinPointX(), getPrinPointY(), eyeCenterDetectAlgo, gazeTrackingAlgo, fastEyeWidth);

	while(true) {
		// read a new frame from video
        bool success = inputVideo.read(frame); 
		if (!success) {
			break; //no frames left, we can stop
		}
		
		//obtain the timestamp of the current frame!
		timestamp = inputVideo.get(CV_CAP_PROP_POS_MSEC);

		//Processing of the frame
		//Change color as the gaze tracker expects RGBA
		cvtColor(frame, frame, COLOR_BGRA2RGBA);

		//Track the gaze
		string errorMessage;
		int* result = gazeTracker.detect(frame, errorMessage);
		if(result != NULL){
			// Store the gaze points in a text file
			gazeFile << framecounter << ";" << timestamp << ";" << result[0] << ";" << result[1] << ";" << result[2] << ";" << result[3] << endl;
		} else {
			// Store the null in the text file
			gazeFile << framecounter << ";" << timestamp << ";" << "NULL;" << errorMessage << endl;
		}

		//Change the color back to BGR (gaze tracker returns RGB) 
		cvtColor(frame, frame, COLOR_RGBA2BGR);

		// write the frame to the output video file
		if(drawOnVideo){
			outputVideo.write(frame);
		}
		framecounter++;
	}

	//Close the gaze file
	gazeFile.close();
}
