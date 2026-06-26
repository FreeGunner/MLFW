#include <iostream>

#include "mlfw/cuda/device.h"

using namespace std;
using namespace mlfw;

int main()
{
    cout
    << "Current Device : "
    << CudaDevice::currentDevice()
    << endl;

    cout
    << "Total Devices  : "
    << CudaDevice::deviceCount()
    << endl
    << endl;

    CudaDevice::printInfo();

    return 0;
}