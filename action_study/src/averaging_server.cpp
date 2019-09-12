#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <actionlib/server/simple_action_server.h>
#include <action_study/averagingAction.h>

class averagingAction
{
public:

    averagingAction(std::string name):
//        as_(nh_, name, false),
        nh_("test"),
        as_(nh_, name, false),
        action_name_(name)
    {
        ROS_INFO_STREAM("the namespace is " << nh_.getNamespace() << std::endl);
//        std::cout << "the namespace is "<< nh_.getNamespace().c_str()<< std::endl;
        as_.registerGoalCallback(boost::bind(&averagingAction::goalCB, this));//this means as_;
        as_.registerPreemptCallback(boost::bind(&averagingAction::preemptCB, this));

        sub_ = nh_.subscribe("/random_number", 1, &averagingAction::analysisCB, this);//this means nh_
        as_.start();
    }

    ~averagingAction()
    {

    }

    void goalCB()
    {
        data_count_ = 0;
        sum_ = 0;
        sum_sq_ = 0;
        goal_ = as_.acceptNewGoal()->samples;
    }

    void preemptCB()
    {
        ROS_INFO("%s: preempted", action_name_.c_str());
        as_.setPreempted();
    }

    void analysisCB(const std_msgs::Float32::ConstPtr& msg)
    {
        if (!as_.isActive())
            return;
        data_count_++;
        feedback_.sample = data_count_;
        feedback_.data = msg->data;

        sum_ += msg->data;
        feedback_.mean = sum_ / data_count_;
        sum_sq_ += pow(msg->data, 2);
        feedback_.std_dev = sqrt(fabs((sum_sq_ / data_count_) - pow(feedback_.mean, 2)));
        as_.publishFeedback(feedback_);

        if(data_count_ > goal_)
        {
            result_.mean = feedback_.mean;
            result_.std_dev = feedback_.std_dev;

            if(result_.mean > 5.0)
            {
                ROS_INFO("%s: Aborted", action_name_.c_str());
                as_.setAborted(result_);
            }
            else {
                ROS_INFO("%s: succeed", action_name_.c_str());
                as_.setSucceeded(result_);
            }
        }
    }

protected:
    ros::NodeHandle nh_;
    actionlib::SimpleActionServer<action_study::averagingAction> as_;
    std::string action_name_;
    int data_count_, goal_;
    float sum_, sum_sq_;
    action_study::averagingFeedback feedback_;
    action_study::averagingResult result_;
    ros::Subscriber sub_;
};

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "averaging");

    averagingAction averaging(ros::this_node::getName());
    ros::spin();
    return 0;
}
