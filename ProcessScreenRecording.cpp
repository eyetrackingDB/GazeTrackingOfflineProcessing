#include <iostream>
#include <string>

#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

void process_screen(const string inputScreenFile, const string outputScreenFile, const string gazePointsFile) {
	//The input video file
	VideoCapture inputVideo(inputScreenFile);

	//The output video file
	VideoWriter outputVideo;
	//The screen recording is always processed as it is
	Size size = Size((int) inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int) inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));
	outputVideo.open(outputScreenFile , CV_FOURCC('X','V','I','D'), inputVideo.get(CV_CAP_PROP_FPS),size, true);

	//Check if the video file is loaded
	if (!inputVideo.isOpened()){
		cout << "Error: Screen Recording File not found!!" << endl;
		return;
	}

	//Open the text file with the gaze points
	ifstream gazeFile; // out file stream
	gazeFile.open(gazePointsFile);

	//Processing the video recording
	Mat frame;
	while(true) {
		// Check if we have a frame left
		bool success = inputVideo.read(frame); 
		if (!success) {
			break; //no frames left, we can stop
		}

		// Check if we have a gaze point left
		String line;
		if(!getline(gazeFile, line)){
			break;
		}

		if (line.find("NULL") != std::string::npos) {
			//The line contains NULL => we do nothing
		} else {
			//The line contains valid coordinates
			// Get the coordinates of the line
			stringstream ssin(line);
			string frameString;	
			getline(ssin, frameString, ';');
			string timeString;
			getline(ssin, timeString, ';');
			string xCoordinateString;	
			getline(ssin, xCoordinateString, ';');
			string yCoordinateString;	
			getline(ssin, yCoordinateString, ';');

			// Convert coordinates to integer
			int xCoord = stoi(xCoordinateString);
			int yCoord = stoi(yCoordinateString);

			// Draw the point on the frame
			Point2i point(xCoord, yCoord);
			circle(frame, point, 20, Scalar(0, 255, 255), -1); //img is in BGR format
		}
		// Write the frame into the output file
		outputVideo.write(frame);
	}		
 	//Close the gaze file
	gazeFile.close();
}
