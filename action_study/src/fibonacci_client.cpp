#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <actionlib_tutorials/FibonacciAction.h>

int main (int argc, char **argv)
{
    ros::init(argc, argv, "test_fibonacci");

    // create the action client
    // true causes the client to spin its own thread
    /**
     * @brief template, action message
     * fibonacci, action name
     * true,automatically spin a thread
     */
    actionlib::SimpleActionClient<actionlib_tutorials::FibonacciAction> ac("fibonacci", true);


    ROS_INFO("Waiting for action server to start.");
    // wait for the action server to start
    ac.waitForServer(); //will wait for infinite time

    ROS_INFO("Action server started, sending goal.");
    // send a goal to the action
    actionlib_tutorials::FibonacciGoal goal;//goal message is created
    goal.order = 20;//goal.value is set
    ac.sendGoal(goal);//goal's value is sent to action server

    //wait for the action to return
    // The timeout on the wait is set to 30 seconds,
    //this means after 30 seconds the function will return with false if the goal has not finished.
    bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));

    if (finished_before_timeout)
    {
        actionlib::SimpleClientGoalState state = ac.getState();
        ROS_INFO("Action finished: %s",state.toString().c_str());
    }
    else
        ROS_INFO("Action did not finish before the time out.");

    //exit
    return 0;
}
