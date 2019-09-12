/**
回调函数中的传入msg是根据发出的消息不同而自行定义的
可以用rostopic list 命令查看
rosrun rqt_graph rqt_graph查看订阅关系
*/

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <turtlesim/Pose.h>
//#include <turtle_actionlib/Velocity.h>

std::string turtle_name;

void poseCallback(const turtlesim::PoseConstPtr& msg){
  static tf::TransformBroadcaster br;
  tf::Transform transform;
  transform.setOrigin( tf::Vector3(msg->x, msg->y, 0.0) );
  tf::Quaternion q;
  q.setRPY(0, 0, msg->theta);
  transform.setRotation(q);
  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", turtle_name));
  ROS_INFO_STREAM(turtle_name << "the turtle name is " << std::endl);
}

void vel_callback(const geometry_msgs::TwistPtr& msg)
{
    std::cout << msg->linear << std::endl;
    std::cout << msg->angular<< std::endl;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "my_tf_broadcaster");//name of this node
  if (argc != 2){ROS_ERROR("need turtle name as argument"); return -1;};
  turtle_name = argv[1];
  ROS_INFO_STREAM(turtle_name << "the turtle name is " << std::endl);

  ros::NodeHandle node;
//  ros::Subscriber sub = node.subscribe(turtle_name+"/pose", 10, &poseCallback);
  ros::Subscriber sub = node.subscribe(turtle_name+"/cmd_vel", 10, &vel_callback);

  std::cout << "time a" << std::endl;
  ros::spin();//the call back function works here!!!!!
  return 0;
};
