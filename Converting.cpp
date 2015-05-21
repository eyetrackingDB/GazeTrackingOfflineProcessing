#include <string>

using namespace std;

void convert_fps(const string folder, const string postProcFolderName, const string videoInputFile, const string videoOutputFile){
	string ffmpegCall = "FFMPEG/ffmpeg";
	ffmpegCall += " -y";

	//The input file	
	ffmpegCall += " -i";
	ffmpegCall += (" "+folder + videoInputFile);

	// The frame rate which we want to achieve
	ffmpegCall += " -r";
	ffmpegCall += " 30";
	
	// The codec which we want to achieve
	ffmpegCall += " -vcodec";
	ffmpegCall += " libx264";

	// The profile 
	ffmpegCall += " -profile:v";
	ffmpegCall += " baseline";

	// The level of the profile
	ffmpegCall += " -level";
	ffmpegCall += " 3.1";

	// The wanted quality
	ffmpegCall += " -crf";
	ffmpegCall += " -1";

	// Removing of the audio
	ffmpegCall += " -an";

	// The outputfile
	ffmpegCall += (" "+folder + postProcFolderName + videoOutputFile);
	
	system(ffmpegCall.c_str());
}
