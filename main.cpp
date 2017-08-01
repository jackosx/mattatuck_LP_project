#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <alpr.h>
#include <vector>
#include <string>
#include <time.h>
#include <sstream>
#include <thread>
#include "src/db.h"
#include "src/server.h"

std::string takePicture(int count)
{
  cv::VideoCapture stream1("picture/lp.png"); //cap

  if(!stream1.isOpened())
  {
    std::cout << "Cannot open camera" << std::endl;
  }
  cv::Mat cameraFrame; //frame
  stream1.read(cameraFrame);
  
  std::vector<uchar> buff;
  std::vector<char> convert;
  std::vector<int> cp;

  cp.push_back(CV_IMWRITE_PNG_COMPRESSION);
  
  cv::imencode(".png",cameraFrame,buff,cp);

  alpr::Alpr openalpr("us","openalpr.conf");

  for(int i = 0; i < buff.size(); i++)
  {
    convert.push_back(buff[i]);
  }
  
  alpr::AlprResults results = openalpr.recognize(convert);

  if(results.plates.size() > 0)
  {
    std::ostringstream convert;
    convert << count;
    std::string id = convert.str();
    std::string f = "picture/lp"+id+".png";
    cv::imwrite(f,cameraFrame);
  }else{
    return "";
  }
  
  alpr::AlprPlateResult plate = results.plates[0];
  alpr::AlprPlate candidate = plate.topNPlates[0];
  std::string t = candidate.characters;
  
  return t;
}

double elapsedTime(double tt)
{
  return(clock() - tt) / CLOCKS_PER_SEC;
}

void runLPDetect()
{
  std::vector<Data> lpDataVec;
  int i = 0;
  int last = 0;
  double tt;

  std::string lp;
  bool trigger = false;
  int count = 0;
  tt = clock();
  while(i < 1)
  {
    if(elapsedTime(tt) >= .3)
    {
      i++;
      tt = clock();

      if(trigger == true && last == 4)
      {
	last = 0;
	trigger = false;
	std::cout << "false" << std::endl;
      }else if(trigger == true && last < 4){
	last++;
	std::cout << "false" << std::endl;
      }else if(trigger == false){
	lp = takePicture(i);
	if(lp != "")
	{
	  lpDataVec.push_back(Data(count,lp));
	  count++;
	  writeData(lpDataVec);
	  std::cout << lp << std::endl;
	  trigger = true;
	}else{
	  //std::cout << "No lp" << std::endl;
	}
      }
    }
  }

  std::cout << "-------------" << std::endl;
  for(int e = 0; e < lpDataVec.size(); ++e)
  {
    std::cout << lpDataVec[e].getLP() << std::endl;
  }

  //writeData(lpDataVec);
}

int main()
{
  std::thread tlp(runLPDetect);
  std::thread tserver(server);

  tlp.join();
  tserver.join();
}
