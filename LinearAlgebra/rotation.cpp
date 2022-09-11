// compile "$ g++ file_name.cpp -I /usr/local/include/eigen3"

#include <iostream>
#include <Eigen/Core>
#include <Eigen/LU>
#include <Eigen/Dense>

const int jacobi_row = 3;
const int jacobi_column = 6;

const int Coordinate_DOF = 3, Joint_DOF = 6;

Eigen::Matrix<double, jacobi_column, jacobi_row> getGeneralezedInverse(Eigen::Matrix<double, jacobi_row, jacobi_column> M);
void rotationX(Eigen::Matrix<double, 3, 3> &rotation, Eigen::Matrix<double, Joint_DOF, 1> &theta, int joint_number);

int main()
{
    Eigen::Matrix<double, 3, 3> rotation[6];
    Eigen::Matrix<double, Joint_DOF, 1> theta;
    theta << M_PI/6, 0.0, 0.0, 0.0, 0.0, 0.0;
    
    rotationX(rotation[0], theta, 0);

    std::cout << rotation[0] << std::endl;

    return 0;
}

void rotationX(Eigen::Matrix<double, 3, 3> &rotation, Eigen::Matrix<double, Joint_DOF, 1> &theta, int joint_number)
{
    rotation << 1.0, 0.0                       ,  0.0                       ,
                0.0, cos(theta(joint_number,0)), -sin(theta(joint_number,0)),
                0.0, sin(theta(joint_number,0)),  cos(theta(joint_number,0));
}

Eigen::Matrix<double, jacobi_column, jacobi_row> getGeneralezedInverse(Eigen::Matrix<double, jacobi_row, jacobi_column> M)
{
    Eigen::Matrix<double, jacobi_column, jacobi_row> M_transpose = M.transpose();
    Eigen::Matrix<double, jacobi_column, jacobi_column> M_holomorphic = M_transpose*M;
    if(M_holomorphic.determinant() < 10e-10)
    {
        std::cout << "Not holomorphic" << std::endl;
    }
    Eigen::Matrix<double, jacobi_column, jacobi_column> M_inverse = M_holomorphic.inverse();
    return M_inverse*M_transpose;
}