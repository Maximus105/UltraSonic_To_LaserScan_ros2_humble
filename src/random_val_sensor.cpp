#include<chrono>
#include<functional>
#include<memory>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/range.hpp"
#include<random>

class random_sensor:public rclcpp::Node{
    public:
        random_sensor():Node("ultrasonic_sensor"),mt(rd()){
            min=1.0;
            max=4.0;
            pub_=this->create_publisher<sensor_msgs::msg::Range>("/ultrasonic",10);
            timer_=this->create_wall_timer(
                std::chrono::milliseconds(100),
                std::bind(&random_sensor::callback,this)
            );
        }

    private:
        void callback(){
            std::uniform_real_distribution<double> dist(1.2, 4.0);
            msg.range=dist(mt);
            msg.field_of_view=0.261799;
            msg.radiation_type=sensor_msgs::msg::Range::ULTRASOUND;
            msg.min_range=min;
            msg.max_range=max;
            msg.header.stamp=this->now();
            msg.header.frame_id="ultrasonic_0";
            pub_->publish(msg);
            RCLCPP_INFO(this->get_logger(),"Sensor MSG PUBLISHED...!!");
        }
        float min ,max;
        rclcpp::Publisher<sensor_msgs::msg::Range>::SharedPtr pub_;
        rclcpp::TimerBase::SharedPtr timer_;
        sensor_msgs::msg::Range msg;
        std::random_device rd;
        std::mt19937 mt;
};

int main(int argc,char ** argv){
    srand(time(0));
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<random_sensor>());
    rclcpp::shutdown();
}