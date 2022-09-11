/**
* @file open_manipulator_control.cpp
* @brief 
* @author Akiro Harada
* @date 2022.8.13
* @details 
*/

#include <ros/ros.h>

#include <std_msgs/Bool.h>
#include <geometry_msgs/Pose.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <Eigen/Core>
#include <Eigen/LU>
#include <Eigen/Dense>

#include <dynamixel_sdk/dynamixel_sdk.h>
#include <dynamixel-wrapper/dynamixel_wrapper.h>

geometry_msgs::Pose init_pose;

ros::Time start_time;

geometry_msgs::Pose now_pose;
geometry_msgs::Pose target_pose;
geometry_msgs::Pose target_pose_old;
double duration_time = 0.0f;



const int Coordinate_DOF = 6, Joint_DOF = 6, Limited_DOF = 3;

// Prototype Declaration
Eigen::Matrix3d rotationX(double theta);
Eigen::Matrix3d rotationY(double theta);
Eigen::Matrix3d rotationZ(double theta);
Eigen::Matrix<double, Joint_DOF, Limited_DOF> getGeneralezedInverse(Eigen::Matrix<double, Limited_DOF, Joint_DOF> M);

Eigen::Matrix<double, 3, 3> rotation[6];
Eigen::Matrix<double, Joint_DOF, 1> theta, theta_target, theta_dot;
Eigen::Matrix<double, 3, 1>  link0, link1, link2, link3, link4, link5, now_position, target_position;
Eigen::Matrix<double, Coordinate_DOF, 1> position_orientation;
Eigen::Matrix<double, Limited_DOF, Joint_DOF> jacobian;
Eigen::Matrix<double, Joint_DOF, Limited_DOF> jacobian_inverse; 

double l1, l2, l3, l4, l5, l6;
double t1, t2, t3, t4, t5, t6;
double td1, td2, td3, td4, td5, td6;

double kp = 0.01;

ros::Publisher state_pub;
void pose_cb(geometry_msgs::Pose::ConstPtr pose)
{
    if(*pose == target_pose) return;
    target_position(0,0) = pose->position.x;
    target_position(1,0) = pose->position.y;
    target_position(2,0) = pose->position.z;
    
    std_msgs::Bool msg;
    msg.data = false;
    state_pub.publish(msg);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "dynamixel_wrapper_example_node");
    ros::NodeHandle nh;

    ros::Subscriber pose_sub = nh.subscribe<geometry_msgs::Pose>("target_pose", 1, pose_cb);

    state_pub = nh.advertise<std_msgs::Bool>("open_manipulator_controller/isGoaled", 1);

    double rate = 10.0f;
    ros::Rate loop_rate(rate);

    std::string port_name("/dev/ttyUSB0");
    int baudrate=1000000;

    dynamixel_wrapper::dynamixel_wrapper_base dxl_base(port_name, baudrate);
    dynamixel_wrapper::dynamixel_wrapper motor1(1, dxl_base, dynamixel_wrapper::PH54_200_S500_R, 4);
    dynamixel_wrapper::dynamixel_wrapper motor2(2, dxl_base, dynamixel_wrapper::PH54_200_S500_R, 4);
    dynamixel_wrapper::dynamixel_wrapper motor3(3, dxl_base, dynamixel_wrapper::PH54_100_S500_R, 4);
    dynamixel_wrapper::dynamixel_wrapper motor4(4, dxl_base, dynamixel_wrapper::PH54_100_S500_R, 4);
    dynamixel_wrapper::dynamixel_wrapper motor5(5, dxl_base, dynamixel_wrapper::PH42_020_S300_R, 4);
    dynamixel_wrapper::dynamixel_wrapper motor6(6, dxl_base, dynamixel_wrapper::PH42_020_S300_R, 4);

    motor1.setTorqueEnable(false);
    motor1.setVelocityLimit(15);
    motor1.setHomingOffset(0);
    motor1.setPositionGain(15, 0, 0);
    motor1.setTorqueEnable(true);

    motor2.setTorqueEnable(false);
    motor2.setVelocityLimit(15);
    motor2.setHomingOffset(6.383073693);
    motor2.setPositionGain(15, 0, 0);
    motor2.setTorqueEnable(true);

    motor3.setTorqueEnable(false);
    motor3.setVelocityLimit(15);
    motor3.setHomingOffset(45-6.383073693-6.632514615);
    motor3.setPositionGain(15, 0, 0);
    motor3.setTorqueEnable(true);

    motor4.setTorqueEnable(false);
    motor4.setVelocityLimit(15);
    motor4.setHomingOffset(0);
    motor4.setPositionGain(15, 0, 0);
    motor4.setTorqueEnable(true);

    motor5.setTorqueEnable(false);
    motor5.setVelocityLimit(15);
    motor5.setHomingOffset(6.632514615);
    motor5.setPositionGain(15, 0, 0);
    motor5.setTorqueEnable(true);

    motor6.setTorqueEnable(false);
    motor6.setVelocityLimit(15);
    motor6.setHomingOffset(0);
    motor4.setPositionGain(15, 0, 0);
    motor6.setTorqueEnable(true);

    link0 << 0.0, 0.0, 0.0;
    link1 << 0.0, 0.0, sqrt(pow(264.0,2.0)+pow(30.0,2.0));
    link2 << 0.0, 0.0, sqrt(pow(258.0,2.0)+pow(30.0,2.0));
    link3 << 0.0, 0.0, 0.0;
    link4 << 0.0, 0.0, 123.0;    // Without End Effector
    link5 << 0.0, 0.0, 0.0;
    l1 = 0.0, l2 = sqrt(pow(264.0,2.0)+pow(30.0,2.0)), l3 = sqrt(pow(258.0,2.0)+pow(30.0,2.0)), l4 = 0.0, l5 = 123.0, l6 = 0.0;

    bool isValid_old = true;

    // Initialize
    init_pose.position.x = 200.0;
    init_pose.position.y = 0.0;
    init_pose.position.z = 100.0;
    init_pose.orientation.x = 0.0;
    init_pose.orientation.y = 90.0;
    init_pose.orientation.z = 0.0;
    init_pose.orientation.w = 5.0;

    target_pose = target_pose_old = init_pose; 

    int operating_mode = 4;
    int operating_mode_old;
    bool have_finished_initilization  = false;

    while(nh.ok())
    {
        t1 = (M_PI/180.0)*motor1.getPresentPosition(),
        t2 = (M_PI/180.0)*motor2.getPresentPosition(),
        t3 = (M_PI/180.0)*motor3.getPresentPosition(),
        t4 = (M_PI/180.0)*motor4.getPresentPosition(),
        t5 = (M_PI/180.0)*motor5.getPresentPosition(),
        t6 = (M_PI/180.0)*motor6.getPresentPosition();

        theta << t1, t2, t3, t4, t5, t6; 
        
        rotation[0] = rotationZ(t1);
        rotation[1] = rotationY(t2);
        rotation[2] = rotationY(t3);
        rotation[3] = rotationZ(t4);
        rotation[4] = rotationY(t5);
        rotation[5] = rotationZ(t6);

        now_position = rotation[0]*(link0+rotation[1]*(link1+rotation[2]*(link2+rotation[3]*(link3+rotation[4]*(link4+rotation[5]*link5)))));

        // Jacobian
        jacobian(0,0) = cos(t1)*sin(t2)*l2 + cos(t1)*sin(t2+t3)*(l3+l4) + (cos(t1)*cos(t2+t3)*cos(t4)*sin(t5)-sin(t1)*sin(t4)*sin(t5)+cos(t1)*sin(t2+t3)*cos(t5))*(l5+l6),
        jacobian(0,1) = sin(t1)*cos(t2)*l2 + sin(t1)*cos(t2+t3)*(l3+l4) + (sin(t1)*cos(t2+t3)*cos(t5)-sin(t1)*sin(t2+t3)*cos(t4)*sin(t5))*(l5+l6),
        jacobian(0,2) = sin(t1)*cos(t2+t3)*(l3+l4) + (sin(t1)*cos(t2+t3)*cos(t5)-sin(t1)*sin(t2+t3)*cos(t4)*sin(t5))*(l5+l6),
        jacobian(0,3) = (cos(t1)*cos(t4)*sin(t5)-sin(t1)*cos(t2+t3)*sin(t4)*sin(t5))*(l5+l6),
        jacobian(0,4) = (cos(t1)*sin(t4)*cos(t5)+sin(t1)*cos(t2+t3)*cos(t4)*cos(t5)-sin(t1)*sin(t2+t3)*sin(t5))*(l5+l6),
        jacobian(0,5) = 0.0,

        jacobian(1,0) = sin(t1)*cos(t2)*l2 + sin(t1)*sin(t2+t3)*(l3+l4) + (cos(t1)*sin(t4)*sin(t5)+sin(t1)*cos(t2+t3)*cos(t4)*sin(t5)+sin(t1)*sin(t2+t3)*cos(t5))*(l5+l6),
        jacobian(1,1) = cos(t1)*sin(t2)*l2-cos(t1)*cos(t2+t3)*(l3+l4) + (cos(t1)*sin(t2+t3)*cos(t4)*sin(t5)-cos(t1)*cos(t2+t3)*cos(t5))*(l5+l6),
        jacobian(1,2) = -cos(t1)*cos(t2+t3)*(l3+l4) + (cos(t1)*sin(t2+t3)*cos(t4)*sin(t5)-cos(t1)*cos(t2+t3)*cos(t5))*(l5+l6),
        jacobian(1,3) = (sin(t1)*cos(t4)*sin(t5)+cos(t1)*cos(t2+t3)*sin(t4)*sin(t5))*(l5+l6),
        jacobian(1,4) = (sin(t1)*sin(t4)*cos(t5)-cos(t1)*cos(t2+t3)*cos(t4)*cos(t5)+cos(t1)*sin(t2+t3)*sin(t5))*(l5+l6),
        jacobian(1,5) = 0.0,

        jacobian(2,0) = 0.0,
        jacobian(2,1) = -sin(t2)*l2 -sin(t2+t3)*(l3+l4) - (sin(t2+t3)*cos(t5)+cos(t2+t3)*cos(t4)*sin(t5))*(l5+l6),
        jacobian(2,2) = -sin(t2+t3)*(l3+l4) - (sin(t2+t3)*cos(t5)+cos(t2+t3)*cos(t4)*sin(t5))*(l5+l6),
        jacobian(2,3) = sin(t2+t3)*sin(t4)*sin(t5)*(l5+l6),
        jacobian(2,4) = -(cos(t2+t3)*sin(t5)+sin(t2+t3)*cos(t4)*cos(t5))*(l5+t6),
        jacobian(2,5) = 0.0;
        
        jacobian_inverse = getGeneralezedInverse(jacobian);

        theta_dot = kp*jacobian_inverse*(target_position-now_position);

        td1 = theta_dot(0,0);
        td2 = theta_dot(1,0);
        td3 = theta_dot(2,0);
        td4 = theta_dot(3,0);
        td5 = theta_dot(4,0);
        td6 = theta_dot(5,0);

        
        bool isValid = true;
        for(int i = 0; i < 6; i++)
        {
            if(isnan(theta(i,0)) || isnan(theta_dot(i,0)))
            {
                isValid = false;
                break;
            }
        }

        if(isValid)
        {
            motor1.setGoalVelocity(td1);
            motor2.setGoalVelocity(td2);
            motor3.setGoalVelocity(td3);
            motor4.setGoalVelocity(td4);
            motor5.setGoalVelocity(td5);
            motor6.setGoalVelocity(td6);
        }
        if(isValid != isValid_old)
        {
            motor1.setLED(isValid?0:255, isValid?255:0, 0);
            motor2.setLED(isValid?0:255, isValid?255:0, 0);
            motor3.setLED(isValid?0:255, isValid?255:0, 0);
            motor4.setLED(isValid?0:255, isValid?255:0, 0);
            motor5.setLED(isValid?0:255, isValid?255:0, 0);
            motor6.setLED(isValid?0:255, isValid?255:0, 0);
        }

        if(have_finished_initilization)
        {
            operating_mode = 1;
        }
        if(operating_mode != operating_mode_old)
        {
            motor1.setOperatingMode(operating_mode);
            motor2.setOperatingMode(operating_mode);
            motor3.setOperatingMode(operating_mode);
            motor4.setOperatingMode(operating_mode);
            motor5.setOperatingMode(operating_mode);
            motor6.setOperatingMode(operating_mode);
        }

        std_msgs::Bool msg;
        if(motor1.getIsInPosition() && motor2.getIsInPosition() && motor3.getIsInPosition() && motor4.getIsInPosition() && motor5.getIsInPosition() && motor6.getIsInPosition())
        {
            msg.data = true;
            have_finished_initilization = true;
        }
        else
        {
            msg.data = false;
        }
        state_pub.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();

        isValid_old = isValid;
        operating_mode_old = operating_mode;
    }
    motor1.setTorqueEnable(false);
    motor2.setTorqueEnable(false);
    motor3.setTorqueEnable(false);
    motor4.setTorqueEnable(false);
    motor5.setTorqueEnable(false);
    motor6.setTorqueEnable(false);
    return 0;
}

// Basic Rotation
Eigen::Matrix3d rotationX(double theta)
{
    Eigen::Matrix3d rotation;
    rotation << 1.0, 0.0       ,  0.0       ,
                0.0, cos(theta), -sin(theta),
                0.0, sin(theta),  cos(theta);
    return rotation;
}
Eigen::Matrix3d rotationY(double theta)
{
    Eigen::Matrix3d rotation;
    rotation <<  cos(theta), 0.0, sin(theta),
                 0.0       , 1.0, 0.0,
                -sin(theta), 0.0, cos(theta);
    return rotation;
}
Eigen::Matrix3d rotationZ(double theta)
{
    Eigen::Matrix3d rotation;
    rotation << cos(theta), -sin(theta), 0.0,
                sin(theta),  cos(theta), 0.0,
                0.0       , 0.0        , 1.0;
    return rotation;
}

// Inverse
Eigen::Matrix<double, Joint_DOF, Limited_DOF> getGeneralezedInverse(Eigen::Matrix<double, Limited_DOF, Joint_DOF> M)
{
    Eigen::Matrix<double, Joint_DOF, Limited_DOF> M_transpose = M.transpose();
    Eigen::Matrix<double, Joint_DOF, Joint_DOF> M_holomorphic = M_transpose*M;
    if(M_holomorphic.determinant() < 10e-10)
    {
        std::cout << "Not holomorphic" << std::endl;
    }
    Eigen::Matrix<double, Joint_DOF, Joint_DOF> M_inverse = M_holomorphic.inverse();
    return M_inverse*M_transpose;
}