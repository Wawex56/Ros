#include "ros/ros.h"
#include <image_transport/image_transport.h> 
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h> 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

static const std::string OPENCV_WINDOW = "camera image";

class camera {
   ros::NodeHandle nh;

   image_transport::ImageTransport imtr;
   image_transport::Subscriber image_sub;
   image_transport::Publisher image_pub;

   public:
      camera() : imtr(nh){
          image_sub = imtr.subscribe("/usb_cam/image_raw", 1, &camera::func, this);
          image_pub = imtr.advertise("/camera_cpp",1);

          cv::namedWindow(OPENCV_WINDOW);
       }
       
       ~camera(){
           cv::destroyWindow(OPENCV_WINDOW);
       }

       void func(const sensor_msgs::ImageConstPtr& msg){
           cv_bridge::CvImagePtr cv_ptr;

           try{
               cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
           }

           catch(cv_bridge::Exception& e){
               ROS_ERROR("cv bridge error: %s", e.what());
               return;
           }
 
           cv::imshow(OPENCV_WINDOW, cv_ptr->image);
           cv::waitKey(3);

           image_pub.publish(cv_ptr->toImageMsg());
       }
};

int main(int argc, char** argv){
   ros::init(argc, argv, "camera");
    
    camera object;
    //ros::spin();

    return 0;
}
