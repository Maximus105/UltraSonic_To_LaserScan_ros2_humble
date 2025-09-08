#include<memory>
#include<functional>
#include<chrono>
#include"rclcpp/rclcpp.hpp"
#include"sensor_msgs/msg/laser_scan.hpp"
#include<random>
#include<vector>

class random_scan_laser:public rclcpp::Node{
    public:
        random_scan_laser():Node("Random_Scan_Laser"),mt(rd()),dist(0.02,4){
            pub_=this->create_publisher<sensor_msgs::msg::LaserScan>("/model/vehicle_blue/scan",10);
            timer_=this->create_wall_timer(
                std::chrono::milliseconds(100),
                std::bind(&random_scan_laser::callback,this)
            );
        }
    private:
        void callback(){
            // std::vector<float>v;
            msg.header.frame_id="lidar";
            msg.header.stamp=this->now();
            msg.range_min=0.00;
            msg.range_max=4.00;
            msg.angle_min=-3.14;
            msg.angle_max=3.14;
            msg.angle_increment=6.28/100;
            msg.scan_time=0.1;
            msg.time_increment=0.0;
            msg.ranges.resize(200);
            float r=dist(rd);
            for(int i=0;i<200;i++){
                msg.ranges[i]=r;
            }
            pub_->publish(msg);
            RCLCPP_INFO(this->get_logger(),"LIDAR MSG PUBLISHED...");
        }
        rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr pub_;
        rclcpp::TimerBase::SharedPtr timer_;
        sensor_msgs::msg::LaserScan msg;
        std::random_device rd;
        std::mt19937 mt;
        std::uniform_real_distribution<float> dist;
};

int main(int argc,char **argv){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<random_scan_laser>());
    rclcpp::shutdown();
}
