#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <actionlib_tutorials/TatlisesAction.h>

int main(int argc,char** argv){
  ros::init(argc,argv,"test_tatlises");

  actionlib::SimpleActionClient<actionlib_tutorials::TatlisesAction> ac("tatlises",true);

  ROS_INFO("Waiting for action server to start.");
  ac.waitForServer();
  ROS_INFO("Action server started, sending goal.");
  actionlib_tutorials::TatlisesGoal goal;
  
  goal.kursundan_kacis=true;
  
  ac.sendGoal(goal);



  return 0;
}
