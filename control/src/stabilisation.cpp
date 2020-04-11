#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>


std_msgs::Float64 currentRoll;
std_msgs::Float64 currentPitch;
std_msgs::Float64 currentYaw;
std_msgs::Float64 desired;




void callback(const sensor_msgs::Imu& msg){
	
		currentRoll.data = msg.angular_velocity.x;
		currentPitch.data = msg.angular_velocity.y;
		currentYaw.data = msg.angular_velocity.z;
}		


int main(int argc, char **argv){
	
	
	
	ros::init(argc, argv, "stabilisation");
	
	ros::NodeHandle nodeHandle;
	ros::Subscriber subscriber = nodeHandle.subscribe("quadrotor/imu", 1, callback);
	ros::Publisher publisher = nodeHandle.advertise<geometry_msgs::Twist>("quadrotor/vel_cmd_stability", 1);

	ros::Rate naptime(100);
	double gain = 1.0;
	double error = 0.0;
	
	currentRoll.data = 0.0;
	currentPitch.data = 0.0;
	currentYaw.data = 0.0;
	
	geometry_msgs::Twist output;
	desired.data = 0.0;
	output.linear.x = 0.0;
	output.linear.y = 0.0;
	output.linear.z = 0.0;
	output.angular.x = 0.0;
	output.angular.y = 0.0;
	output.angular.z = 0.0;


while(ros::ok()){
		
		error = desired.data - currentRoll.data;
		output.angular.x = error*gain;
		error = desired.data - currentPitch.data;
		output.angular.y = error*gain;
		error = desired.data - currentYaw.data;
		output.angular.z = error*gain;
		publisher.publish(output);

		ros::spinOnce();
		naptime.sleep();
		}

return 0;

}

	

