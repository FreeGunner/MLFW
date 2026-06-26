#include "mlfw/cuda/device.h"

#include <cuda_runtime.h>

#include <iostream>
#include <stdexcept>

namespace mlfw
{

int CudaDevice::deviceCount()
{
    int count = 0;

    cudaError_t error =
        cudaGetDeviceCount(&count);

    if(error != cudaSuccess)
    {
        throw std::runtime_error(
            cudaGetErrorString(error)
        );
    }

    return count;
}

int CudaDevice::currentDevice()
{
    int device = 0;

    cudaError_t error =
        cudaGetDevice(&device);

    if(error != cudaSuccess)
    {
        throw std::runtime_error(
            cudaGetErrorString(error)
        );
    }

    return device;
}

void CudaDevice::setDevice(
    int device_id
)
{
    cudaError_t error =
        cudaSetDevice(device_id);

    if(error != cudaSuccess)
    {
        throw std::runtime_error(
            cudaGetErrorString(error)
        );
    }
}

void CudaDevice::printInfo()
{
    int count =
        deviceCount();

    std::cout
    << "=====================================\n";

    std::cout
    << "CUDA DEVICE INFORMATION\n";

    std::cout
    << "=====================================\n";

    std::cout
    << "Device Count : "
    << count
    << "\n\n";

    for(int device = 0;
        device < count;
        device++)
    {
        cudaDeviceProp prop;

        cudaError_t error =
            cudaGetDeviceProperties(
                &prop,
                device
            );

        if(error != cudaSuccess)
        {
            throw std::runtime_error(
                cudaGetErrorString(error)
            );
        }

        std::cout
        << "Device "
        << device
        << "\n";

        std::cout
        << "-------------------------------------\n";

        std::cout
        << "Name                    : "
        << prop.name
        << "\n";

        std::cout
        << "Compute Capability      : "
        << prop.major
        << "."
        << prop.minor
        << "\n";

        std::cout
        << "Global Memory           : "
        << prop.totalGlobalMem / (1024 * 1024)
        << " MB\n";

        std::cout
        << "Shared Memory / Block   : "
        << prop.sharedMemPerBlock
        << " Bytes\n";

        std::cout
        << "Registers / Block       : "
        << prop.regsPerBlock
        << "\n";

        std::cout
        << "Warp Size               : "
        << prop.warpSize
        << "\n";

        std::cout
        << "Max Threads / Block     : "
        << prop.maxThreadsPerBlock
        << "\n";

        std::cout
        << "Max Threads Dimension   : "
        << prop.maxThreadsDim[0]
        << " x "
        << prop.maxThreadsDim[1]
        << " x "
        << prop.maxThreadsDim[2]
        << "\n";

        std::cout
        << "Max Grid Size           : "
        << prop.maxGridSize[0]
        << " x "
        << prop.maxGridSize[1]
        << " x "
        << prop.maxGridSize[2]
        << "\n";

        std::cout
        << "Multiprocessor Count    : "
        << prop.multiProcessorCount
        << "\n";

        std::cout
        << "Clock Rate              : "
        << prop.clockRate / 1000
        << " MHz\n";

        std::cout
        << "Memory Clock Rate       : "
        << prop.memoryClockRate / 1000
        << " MHz\n";

        std::cout
        << "Memory Bus Width        : "
        << prop.memoryBusWidth
        << " Bits\n";

        std::cout
        << "L2 Cache Size           : "
        << prop.l2CacheSize / 1024
        << " KB\n";

        std::cout
        << "Concurrent Kernels      : "
        << (prop.concurrentKernels ? "Yes" : "No")
        << "\n";

        std::cout
        << "Unified Addressing      : "
        << (prop.unifiedAddressing ? "Yes" : "No")
        << "\n";

        std::cout
        << "\n";
    }
}

}