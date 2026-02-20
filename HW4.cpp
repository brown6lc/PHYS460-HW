#include <iostream>
#include <cmath>
#include <complex>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
using namespace std;
using namespace Eigen;

int main(){
     const complex<double> i(0.0, 1.0);
     MatrixXcd A(3,3);
     MatrixXcd B(3,3);
     MatrixXcd C(2,2);
     MatrixXcd S(2,2);

     VectorXcd a(3);
     VectorXcd b(3);

     A << 1, -1, i,
         2, 0, 3,
         -2.0*i, 2.0*i, 2;
     B << 2, 0, -i,
         0, 1, 0,
         i, 4, 2;
     C << 1, 1.0-i,
         1.0+i, 0;
     S << (1.0-i)/sqrt(3), -(1.0-i)/sqrt(6),
          1/sqrt(3), 2/sqrt(6);
     a << i, 2.0*i, 2;
     b << 2, (1.0-i), 0;

     // problem 2
     cout << "A + B =\n" << A + B << endl;
     cout << "A * B =\n" << A * B << endl;
     cout << "A~ =\n" << A.transpose() << endl;
     cout << "A* =\n" << A.conjugate() << endl;
     cout << "A† =\n" << A.adjoint() << endl;
     cout << "det(B) =\n" << B.determinant() << endl;
     cout << "B inverse =\n" << B.inverse() << endl;
     cout << "B * B inverse =\n" << B * B.inverse() << endl;
     cout << "A inverse =\n" << A.inverse() << endl;
     cout << "A * a =\n" << A * a << endl;
     cout << "a† * b =\n" << a.adjoint() * b << endl;
     cout << "a~ * B * b =\n" << a.transpose() * B * b << endl;
     cout << "b† * a =\n" << b.adjoint() * a << endl;

     // problem 3
     ComplexEigenSolver<MatrixXcd> solver(C);
     cout << "Eigenvalues of C:\n" << solver.eigenvalues() << endl;
     cout << "Eigenvectors of C:\n" << solver.eigenvectors() << endl;
     cout << "S inverse =\n" << S.inverse() << endl;
 

     return 0;
}