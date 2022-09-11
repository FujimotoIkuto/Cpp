// compile "$ g++ file_name.cpp -I eigen"

#include <iostream>
#include <Eigen/Core>
#include <Eigen/LU>
#include <Eigen/Dense>

const int jacobi_row = 3;
const int jacobi_column = 6;

Eigen::Matrix<double, jacobi_column, jacobi_row> getGeneralezedInverse(Eigen::Matrix<double, jacobi_row, jacobi_column> M);

int main()
{
    Eigen::Matrix<float, 3, 3> A, B, C, D;
    // Eigen::Matrix<float, 3, 1> B, C;
    Eigen::Matrix<double, jacobi_row, jacobi_column> J;
    Eigen::Matrix<double, jacobi_column, jacobi_row> Jinv;
    Eigen::Matrix<double, jacobi_column, jacobi_column> I;
    Eigen::Matrix<int, 3, 3> array[6];
    float kp = 2;


    // A(0,0) =  1;    A(0,1) =  0;    A(0,2) =  1;
    // A(1,0) = -2;    A(1,1) =  1;    A(1,2) =  0;
    // A(2,0) =  2;    A(2,1) = -1;    A(2,2) =  1;

    // B(0,0) =  2;    B(0,1) =  5;    B(0,2) =  4;
    // B(1,0) =  1;    B(1,1) =  1;    B(1,2) =  7;
    // B(2,0) =  6;    B(2,1) =  3;    B(2,2) =  6;

    // J(0,0) =  1;    J(0,1) =  0;    J(0,2) =  1;    J(0,3) =  2;    J(0,4) =  2;    J(0,5) =  2;
    // J(1,0) = -2;    J(1,1) =  1;    J(1,2) =  0;    J(1,3) =  2;    J(1,4) =  2;    J(1,5) =  2;
    // J(2,0) =  2;    J(2,1) = -1;    J(2,2) =  1;    J(2,3) =  2;    J(2,4) =  2;    J(2,5) =  2;

    // J <<  1, -1,
    //      -1,  2,
    //       2, -1;

    // I << 1, 0, 0, 0, 0, 0,
    //      0, 1, 0, 0, 0, 0,
    //      0, 0, 1, 0, 0, 0,
    //      0, 0, 0, 1, 0, 0,
    //      0, 0, 0, 0, 1, 0,
    //      0, 0, 0, 0, 0, 1;

    A << 
    1,0,0,
    0,1,0,
    0,0,1;

    B << 
    2,2,2,
    2,2,2,
    2,2,2;

    C << 
    1,2,2,
    2,1,2,
    2,2,1;

    D = kp*A*(B-C);
    // D = A.inverse();

    Jinv = getGeneralezedInverse(J);

    // Jinv = getGeneralezedInverse(J);

    // Jinv = J.inverse();
    I = Jinv*J;

    std::cout << "A:" << std::endl << A << std::endl << std::endl;
    std::cout << "B:" << std::endl << B << std::endl << std::endl;
    std::cout << "C:" << std::endl << C << std::endl << std::endl;
    std::cout << "D:" << std::endl << D << std::endl << std::endl;
    // std::cout << "J:" << std::endl << J << std::endl << std::endl;
    // std::cout << "Jinv:" << std::endl << Jinv << std::endl << std::endl;
    // std::cout << "I:" << std::endl << I << std::endl << std::endl;

    return 0;
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