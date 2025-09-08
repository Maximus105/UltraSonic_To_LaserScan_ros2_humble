#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include <random>
#include <chrono>
#include <memory>
#include <functional>
#include <string>

class lidar_random_pub:public rclcpp::Node{
    public:
        lidar_random_pub():Node("Lidar_Pub_Node"),mt_(rd_()),dist_(0.02,4.0){
            std::vector<float> def_val ={0,40,80,-40,-80};
            for(int i=0;i<5;i++){
                std::string para ="us_node_"+std::to_string(i);
                this->declare_parameter(para,def_val[i]);
                pub_[i]=this->create_publisher<sensor_msgs::msg::LaserScan>(
                    "/laser_scan",
                    10);
            }
            timer_=this->create_wall_timer(
                std::chrono::milliseconds(200),
                std::bind(&lidar_random_pub::callback,this)
            );
        }
    private:
        void callback(){
            float range=(dist_(mt_)+0.35);
            for(int i=0;i<5;i++){
                msg[i].header.frame_id="base_footprint";
                msg[i].header.stamp=this->now();
                msg[i].range_max=4.35;
                msg[i].range_min=0.37;
                msg[i].angle_increment=((30.0*M_PI)/180)/99;
                msg[i].scan_time=0.1;
                msg[i].time_increment=0;

                float offset_deg=0;
                std::string para="us_node_"+std::to_string(i);
                offset_deg = (this->get_parameter(para)).as_double();
                float offset_rad = offset_deg*M_PI/180;
                msg[i].angle_max=0.261799+offset_rad;
                msg[i].angle_min=-0.261799+offset_rad;


                float sizeV = (msg[i].angle_max-msg[i].angle_min)/msg[i].angle_increment;
                msg[i].ranges.resize(sizeV);
                std::fill(msg[i].ranges.begin(),msg[i].ranges.end(),range);
            }
            for(int i=0;i<5;i++){
                pub_[i]->publish(msg[i]);
            }
        }
        std::mt19937 mt_;
        std::random_device rd_;
        std::uniform_real_distribution<float> dist_;
        sensor_msgs::msg::LaserScan msg[5];
        rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr pub_[5];
        rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc,char **argv){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<lidar_random_pub>());
    rclcpp::shutdown();
}