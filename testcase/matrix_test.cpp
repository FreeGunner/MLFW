#include <iostream>

#include "mlfw/math/matrix.h"

using namespace std;
using namespace mlfw;

int main()
{
    cout << "========================\n";
    cout << "Constructor Test\n";
    cout << "========================\n";

    Matrix A(3,4);

    cout << "Rows : "
         << A.getRows()
         << endl;

    cout << "Cols : "
         << A.getCols()
         << endl;

    cout << "\n";


    cout << "========================\n";
    cout << "set/get Test\n";
    cout << "========================\n";

    A.set(0,0,10);
    A.set(0,1,20);
    A.set(1,2,30);

    cout << A.get(0,0) << endl;
    cout << A.get(0,1) << endl;
    cout << A.get(1,2) << endl;

    cout << "\n";


    cout << "========================\n";
    cout << "operator() Test\n";
    cout << "========================\n";

    A(2,3)=99;

    cout << A(2,3)
         << endl;

    cout << "\n";


    cout << "========================\n";
    cout << "fill Test\n";
    cout << "========================\n";

    A.fill(5.0);

    for(index_t r=0;
        r<A.getRows();
        r++)
    {
        for(index_t c=0;
            c<A.getCols();
            c++)
        {
            cout
            << A(r,c)
            << " ";
        }

        cout << endl;
    }

    cout << "\n";


    cout << "========================\n";
    cout << "Raw Pointer Test\n";
    cout << "========================\n";

    double *ptr = A.raw();

    ptr[0]=100;
    ptr[1]=200;

    cout
    << A(0,0)
    << " "
    << A(0,1)
    << endl;

    cout << "\n";


    cout << "========================\n";
    cout << "Copy Constructor Test\n";
    cout << "========================\n";

    Matrix B = A;

    B(0,0)=999;

    cout
    << "A(0,0) = "
    << A(0,0)
    << endl;

    cout
    << "B(0,0) = "
    << B(0,0)
    << endl;

    cout << "\n";


    cout << "========================\n";
    cout << "Copy Assignment Test\n";
    cout << "========================\n";

    Matrix C(2,2);

    C = A;

    C(0,1)=777;

    cout
    << "A(0,1) = "
    << A(0,1)
    << endl;

    cout
    << "C(0,1) = "
    << C(0,1)
    << endl;

    cout << "\n";


    cout << "========================\n";
    cout << "CSV Test\n";
    cout << "========================\n";

    Matrix D =
    Matrix::fromCSV(
        "testcase/TS.csv"
    );

    cout
    << "Rows : "
    << D.getRows()
    << endl;

    cout
    << "Cols : "
    << D.getCols()
    << endl;

    for(index_t r=0;
        r<D.getRows();
        r++)
    {
        for(index_t c=0;
            c<D.getCols();
            c++)
        {
            cout
            << D(r,c)
            << " ";
        }

        cout << endl;
    }

    cout << "\n";


    cout << "========================\n";
    cout << "ALL TESTS PASSED\n";
    cout << "========================\n";

    return 0;
}