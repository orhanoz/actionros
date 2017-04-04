#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <actionlib_tutorials/WaitAction.h>

class WaitAction{

  protected:
    ros::NodeHandle nh_;
    actionlib::SimpleActionServer<actionlib_tutorials::WaitAction> as_;
    std::string action_name_;
    actionlib_tutorials::WaitFeedback feedback_;
    actionlib_tutorials::WaitResult result_;
    bool cancel=false;

  public:
    ros::Subscriber cancel_sub;
    
    WaitAction(std::string name):
      as_(nh_,name,boost::bind(&WaitAction::callback,this,_1),false),action_name_(name){
        as_.start();
        cancel_sub=nh_.subscribe<actionlib_msgs::GoalID>("/waitaction/cancel",1,boost::bind(&WaitAction::cancelCallback,this,_1));
            }
            
    ~WaitAction(void){}

    void cancelCallback(const actionlib_msgs::GoalID::ConstPtr &msg){
      if(msg->id=="1"){
        ROS_INFO("Sleep action interrupted. Canceling..");
        this->cancel=true;
      }
      else if(msg->id=="0")
        this->cancel=false;
    }

    void callback(const actionlib_tutorials::WaitGoalConstPtr &goal){
      ros::Rate(1);
      if(goal->wait!=0){
        ROS_INFO("Sleep state.. Duration:%d",goal->wait);
        for(int i=0;i<goal->wait;i++){
          if(this->cancel==true){
            ROS_INFO("break");
            break;
          }
          ros::Duration(1).sleep();
          ROS_INFO("loop");
      }
        ROS_INFO("Sleep state finished");
        if(this->cancel==false)
          as_.setSucceeded(result_);
        else if(this->cancel==true)
          as_.setAborted();
      }
    }
};

int main(int argc, char** argv){
  ros::init(argc,argv,"waitaction");
  WaitAction waitaction("waitaction");
  ros::spin();

  return 0;
}
