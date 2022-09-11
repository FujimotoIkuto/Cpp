#include <iostream>
#include <Eigen/Core>
#include <Eigen/LU>
#include <Eigen/Dense>

const int Coordinate_DOF = 6, Joint_DOF = 6, Limited_DOF = 3;

// Prototype Declaration
Eigen::Matrix3d rotationX(double theta);
Eigen::Matrix3d rotationY(double theta);
Eigen::Matrix3d rotationZ(double theta);
Eigen::Matrix<double, Joint_DOF, Limited_DOF> getGeneralezedInverse(Eigen::Matrix<double, Limited_DOF, Joint_DOF> M);

Eigen::Matrix<double, 3, 3> rotation[6];
Eigen::Matrix<double, Joint_DOF, 1> theta, theta_target, theta_dot;
Eigen::Matrix<double, 3, 1>  link[6], now_position, target_position;
Eigen::Matrix<double, Coordinate_DOF, 1> position_orientation;
Eigen::Matrix<double, Limited_DOF, Joint_DOF> jacobian;
Eigen::Matrix<double, Joint_DOF, Limited_DOF> jacobian_inverse; 


double t1, t2, t3, t4, t5, t6;
double td1, td2, td3, td4, td5, td6;

double kp = 0.01;

int main()
{
    double l1 = 0.0, l2 = sqrt(pow(264.0,2.0)+pow(30.0,2.0)), l3 = sqrt(pow(258.0,2.0)+pow(30.0,2.0)), l4 = 0.0, l5 = 123.0, l6 = 0.0;
    
    // t1 = (M_PI/180.0)*motor1.getPresentPosition(),
    // t2 = (M_PI/180.0)*motor2.getPresentPosition(),
    // t3 = (M_PI/180.0)*motor3.getPresentPosition(),
    // t4 = (M_PI/180.0)*motor4.getPresentPosition(),
    // t5 = (M_PI/180.0)*motor5.getPresentPosition(),
    // t6 = (M_PI/180.0)*motor6.getPresentPosition();
    while(1)
    {
        t1 = 0.0;
        t2 = 0.0;
        t3 = 0.0;
        t4 = 0.0;
        t5 = 0.0;
        t6 = 0.0;

        theta << t1, t2, t3, t4, t5, t6; 
        
        rotation[0] = rotationZ(t1);
        rotation[1] = rotationY(t2);
        rotation[2] = rotationY(t3);
        rotation[3] = rotationZ(t4);
        rotation[4] = rotationY(t5);
        rotation[5] = rotationZ(t6);

        now_position = rotation[0]*(l1+rotation[1]*(l2+rotation[2]*(link2+rotation[3]*(link3+rotation[4]*(link4+rotation[5]*link5)))));

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
    }
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