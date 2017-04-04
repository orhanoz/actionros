#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <actionlib_tutorials/WaitAction.h>
#include <actionlib_msgs/GoalID.h>

int main(int argc,char** argv){
  ros::init(argc,argv,"test_wait");
  actionlib::SimpleActionClient<actionlib_tutorials::WaitAction> ac("waitaction",true);
  ROS_INFO("Waiting for action server to start");
  ac.waitForServer();
  ROS_INFO("Action server started.. sending goal");
  actionlib_tutorials::WaitGoal goal;
  
  goal.wait=10;
  ac.sendGoal(goal);

  bool result = ac.waitForResult(ros::Duration(goal.wait+2));
  if(result){
    actionlib::SimpleClientGoalState state=ac.getState();
    ROS_INFO("Action finished: %s",state.toString().c_str());
  }
  else
    ROS_INFO("Action did NOT finish before the duration.");

  return 0;
}
