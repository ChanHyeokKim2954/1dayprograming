#include "ros/ros.h"
#include "std_msgs/Bool.h"

void chatterCallback(const std_msgs::Bool::ConstPtr& msg)
{
	if(msg->data == true)	ROS_INFO("AEB_Activation!!");
	else if(msg->data == false)	ROS_INFO("NO_AEB_Activation!!");
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "bool_pub");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("/BOOL", 1000, chatterCallback);
	ros::Rate loop_rate(1); //10
	
	while(ros::ok())
	{	
		loop_rate.sleep();
		ros::spinOnce();
	}
	return 0;
}
