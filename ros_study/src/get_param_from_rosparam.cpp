/**
  load param from ros_parameters server with the launch file.
  */

#include "ros/ros.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "get_param_from_rosparam");
    ros::NodeHandle n;
    std::string node_name;
    std::cout << "the number of input is " << argc << std::endl;
    for (unsigned int i = 0; i < argc; i++) {
        node_name = argv[i];
        std::cout << "the input" << i << "-th of argv is " << node_name <<std::endl;
    }
    std::cout << "End" << std::endl;
    int demon_param_int;
    n.getParam("demon_param",demon_param_int);
    std::cout << "the demon_param_int is " << demon_param_int << std::endl;
    return 0;
}
