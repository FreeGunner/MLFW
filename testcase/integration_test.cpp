#include <iostream>

#include "mlfw/math/matrix.h"
#include "mlfw/cuda/memory.h"
#include "mlfw/cuda/device.h"

using namespace std;
using namespace mlfw;

int main()
{
    cout << "========================================\n";
    cout << "MLFW Integration Test\n";
    cout << "========================================\n\n";

    //----------------------------------------------------
    // STEP 1 : Load Matrix
    //----------------------------------------------------

    Matrix A =
        Matrix::fromCSV(
            "testcase/TS.csv"
        );

    cout << "Matrix Loaded\n";

    cout
        << "Rows : "
        << A.getRows()
        << endl;

    cout
        << "Cols : "
        << A.getCols()
        << endl;

    cout << endl;

    //----------------------------------------------------
    // STEP 2 : Print Matrix
    //----------------------------------------------------

    cout
        << "Original Matrix\n";

    for(index_t r = 0; r < A.getRows(); r++)
    {
        for(index_t c = 0; c < A.getCols(); c++)
        {
            cout
                << A(r,c)
                << " ";
        }

        cout << endl;
    }

    cout << endl;

    //----------------------------------------------------
    // STEP 3 : Allocate GPU Memory
    //----------------------------------------------------

    size_t bytes =
        sizeof(double) *
        A.getRows() *
        A.getCols();

    void* gpu =
        CudaMemory::allocate(
            bytes
        );

    cout
        << "GPU Memory Allocated\n\n";

    //----------------------------------------------------
    // STEP 4 : Copy Matrix to GPU
    //----------------------------------------------------

    CudaMemory::copyHostToDevice(
        gpu,
        A.raw(),
        bytes
    );

    cout
        << "Copied Matrix -> GPU\n\n";

    //----------------------------------------------------
    // STEP 5 : Clear Matrix
    //----------------------------------------------------

    A.fill(0);

    cout
        << "CPU Matrix Cleared\n";

    for(index_t r = 0; r < A.getRows(); r++)
    {
        for(index_t c = 0; c < A.getCols(); c++)
        {
            cout
                << A(r,c)
                << " ";
        }

        cout << endl;
    }

    cout << endl;

    //----------------------------------------------------
    // STEP 6 : Copy Back
    //----------------------------------------------------

    CudaMemory::copyDeviceToHost(
        A.raw(),
        gpu,
        bytes
    );

    cout
        << "Copied GPU -> CPU\n\n";

    //----------------------------------------------------
    // STEP 7 : Verify
    //----------------------------------------------------

    cout
        << "Recovered Matrix\n";

    for(index_t r = 0; r < A.getRows(); r++)
    {
        for(index_t c = 0; c < A.getCols(); c++)
        {
            cout
                << A(r,c)
                << " ";
        }

        cout << endl;
    }

    cout << endl;

    //----------------------------------------------------
    // STEP 8 : GPU Information
    //----------------------------------------------------

    CudaDevice::printInfo();

    //----------------------------------------------------
    // STEP 9 : Free GPU Memory
    //----------------------------------------------------

    CudaMemory::free(gpu);

    cout
        << "GPU Memory Released\n\n";

    cout
        << "Integration Test Passed\n";

    return 0;
}