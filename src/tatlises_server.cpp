#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <actionlib_tutorials/TatlisesAction.h>

class TatlisesAction
{
protected:
  ros::NodeHandle nh_;
  
  actionlib::SimpleActionServer<actionlib_tutorials::TatlisesAction> as_;
  std::string action_name_;
  actionlib_tutorials::TatlisesFeedback feedback_;
  actionlib_tutorials::TatlisesResult result_;
  bool cancel=false;

public:
  ros::Subscriber cancel_sub;
  
  TatlisesAction(std::string name) :
    as_(nh_,name,boost::bind(&TatlisesAction::callBack,this,_1),false),
    action_name_(name){
      as_.start();
      cancel_sub=nh_.subscribe<actionlib_msgs::GoalID>("tatlises/cancel",1,boost::bind(&TatlisesAction::cancelCallback,this,_1));
    }
    
	~TatlisesAction(void){}

  void cancelCallback(const actionlib_msgs::GoalID::ConstPtr &msg){
    ROS_INFO("%s hop",msg->id.c_str());
    if(msg->id=="1"){
      this->cancel=true;
    }
    else
      this->cancel=false;
  }  

	void callBack(const actionlib_tutorials::TatlisesGoalConstPtr &goal){
		ros::Rate(1);

		if(!goal->kursundan_kacis){
		feedback_.damage= rand() % 100 +1;
		ROS_INFO("%s Damage: %d",action_name_.c_str(),feedback_.damage);
		}
		else
		feedback_.damage=50;
	
		if (feedback_.damage<50){
			result_.kac_cigkofte=feedback_.damage/2;
			ROS_INFO("%d kadar cig köfte yerim daha",result_.kac_cigkofte);
			as_.setSucceeded(result_);
		}
		else if(feedback_.damage>50){
			result_.kac_cigkofte=feedback_.damage;
			ROS_INFO("%d kursuna kafa atmam lazim",result_.kac_cigkofte);
			as_.setSucceeded(result_);
		}
		else
			for(int i=0;i<200;i++){
				ROS_INFO("herkese benden cigkofte");
				ros::Duration(0.5).sleep();
        ROS_INFO("cancel %i",cancel);
        if (this->cancel==true||!ros::ok()){
      		ROS_INFO("%s: Preempted", action_name_.c_str());
   	  		as_.setPreempted();
	    		break;
    		}
			}
			as_.setSucceeded(result_);
	}
};

int main(int argc, char** argv){
	ros::init(argc,argv,"tatlises");
	TatlisesAction tatlises("tatlises");
	ros::spin();
	return 0;
}

