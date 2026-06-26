#ifndef MLFW_CUDA_DEVICE_H
#define MLFW_CUDA_DEVICE_H

namespace mlfw
{

class CudaDevice
{
public:

    // Number of CUDA GPUs installed
    static int deviceCount();

    // Current active GPU
    static int currentDevice();

    // Select GPU
    static void setDevice(int device_id);

    // Print complete device information
    static void printInfo();
};

}

#endif