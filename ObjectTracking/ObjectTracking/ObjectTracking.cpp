// ObjectTracking.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "people_counter.h"
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

const char* keys =
"{help h ?|| usage examples: peoplecounter.exe --dev=0 }"
"{mov     |mov.mp4| video file name                     }"
"{dev     |0| input device id                          }"
"{ct      |0.5| confidence threshold                   }"
"{st      |0.4| non-maximum suppression threshold      }"
"{iw      |320| width of network's input image         }"
"{ih      |320| height of network's input image        }"
"{cfg     |net.cfg| network configuration              }"
"{wts     |net.wts| network weights                    }"
"{nms     |net.nms| network object classes             }"
"{zsf     |0.01| zooming speed factor                  }"
;

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	char szEXEPath[2048];
	GetModuleFileName(NULL, szEXEPath, 2048);
	PathRemoveFileSpec(szEXEPath);

	std::string strExePath = szEXEPath;
	strExePath += "\\";

	std::cout << "step 1 - " << strExePath << std::endl;

	cv::CommandLineParser parser(argc, argv, keys);

	cv::VideoCapture cap;

	try {
		// Open the video file
		if (parser.has("mov")) {
			std::string str_name = strExePath + parser.get<std::string>("mov");
			std::cout << "step 2 - " << str_name << std::endl;
			bool b = cap.open(str_name);

			int a = 0;
		}
		else {
			// Open the cam
			cap.open(parser.get<int>("dev"));
		}
	}
	catch (...) {
		std::cout << "Could not open the input video stream" << std::endl;
		return 0;
	}

	std::cout << "step 3 - " << strExePath << std::endl;
	if (cap.isOpened()) {
		std::cout << "step 4 - " << strExePath << std::endl;
		PeopleCounter peopleCounter(cap,
			strExePath + parser.get<std::string>("cfg"), strExePath + parser.get<std::string>("wts"), strExePath + parser.get<std::string>("nms"),
			parser.get<float>("ct"), parser.get<float>("st"),
			parser.get<int>("iw"), parser.get<int>("ih"), parser.get<float>("zsf"));

		peopleCounter.runThreads();
	}

	cv::waitKey(1000);

    return 0;
}

