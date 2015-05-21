# GazeTrackingOfflineProcessing

Copyright (C) 2014-2015, André Pomp <andre.pomp@rwth-aachen.de>

Copyright (C) 2014-2015, Jó Ágila Bitsch <jo.bitsch@comsys.rwth-aachen.de>

Copyright (C) 2014-2015, Oliver Hohlfeld <oliver.hohlfeld@comsys.rwth-aachen.de>

Copyright (C) 2014-2015, Chair of Computer Science 4, RWTH Aachen University, <klaus@comsys.rwth-aachen.de>

#### ABOUT
The GazeTrackingOfflineProcessing Framework is an extension to the [GazeTrackingFramework](https://github.com/apomp/GazeTrackingFramework). It allows to evaluate videos that were created with the GazeTrackingFramework offline on a Computer that has much more computation power than the mobile devices. Hence, the processing is much faster. As gaze tracking algorithm, we use the same modified version of [EyeTab](https://github.com/errollw/EyeTab/) as in the GazeTrackingFramework including, e.g., the pupil detection of [EyeLike](https://github.com/trishume/eyeLike). Therefore, the code that was used in this framework is build on the same code as the one of the GazeTrackingFramework. If you extend the GazeTrackingFramework with an additional eye tracking algorithm, you can also extend this framework so that you can do offline processing as well. For more information, we relate to the master thesis [(download)](https://docs.google.com/uc?export=download&id=0B729EHEvlyiUNXdBNVFXUzB2MWM) during which this frame work was developed.  

#### FREE SOFTWARE

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.

#### IF YOU NEED ANOTHER LICENSE

If you are planning to integrate NormMaker into a commercial product, please contact us for licensing options via email at:

  jo.bitsch@comsys.rwth-aachen.de
  
#### Requirements
 This project requires:
  * OpenCV [click](http://opencv.org/) 
  * TBB Library [click](https://www.threadingbuildingblocks.org/)
  * CMake for building the project [click](http://www.cmake.org/)
   
  All other libraries are included.
 
#### Used Libraries
 This project bases on different OpenSource libraries. Please respect their license if you use it. You can find copies of their licenses in the "licenses" folder. 
  * EyeTab GazeTracking  [click](https://github.com/errollw/EyeTab/)
  * EyeLike Pupil Detection [click](https://github.com/trishume/eyeLike)
  * OpenCV [click](http://opencv.org/) 
  * TBB Library [click](https://www.threadingbuildingblocks.org/)
  * Eigen [click](http://eigen.tuxfamily.org/index.php?title=Main_Page)
  * FFMPEG [click](https://www.ffmpeg.org/)

#### HOW TO USE THIS SOFTWARE
* Download the tools that are listed under requirements and install them
* Clone the git repository
* Build the project using CMake (build script included in the build folder)
* Load recorded gaze tracking data folders either from the gaze tracking database or from the device where you recorded them
* Start the post-processing by specifying the following attributes
			<< "\t--input <filepath> \t The filepath to the folder where the video files and settings are located\n"
			<< "\t--output <foldername> \t The folder name for the output (will be created inside the input folder) \n"
			<< "\t--eyealg <algorithm>\t The algorithm that is used for detecting the eye center. Possible Values: grad, isoph, comb \n"
			<< "\t--gazealg <algorithm>\t The algorithm that is used for detecting the gaze. Possible Values: approx, geo \n"
			<< "\t--fastwidth \t The window size of the scaled window that is used for detecting the eye center. (optional) Default: 50 for grad, 80 for isoph algo\n"
			<< "\t--convertfps \t Indicates that we want to convert FPS (optional) Default: off\n"
			<< "\t--drawonvideo \t Indicates that we want to draw the gaze points on the recorded video (optional) Default: off\n"
			<< "\t--drawonscreen \t Indicates that we want to draw the gaze points on the recorded screen (optional but requires --convertfps) Default: off\n"

For more information, we relate to the master thesis [(download)](https://docs.google.com/uc?export=download&id=0B729EHEvlyiUNXdBNVFXUzB2MWM) during which this frame work was developed.  
