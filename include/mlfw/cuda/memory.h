#ifndef MLFW_CUDA_MEMORY_H
#define MLFW_CUDA_MEMORY_H

#include <cstddef>

namespace mlfw
{

class CudaMemory
{
public:

    static void* allocate(size_t bytes);

    static void free(void* ptr);

    static void copyHostToDevice(void* device,const void* host,size_t bytes);

    static void copyDeviceToHost(void* host,const void* device,size_t bytes);

    static void copyDeviceToDevice(void* dst,const void* src,size_t bytes);
};

}

#endif