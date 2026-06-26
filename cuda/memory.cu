#include <mlfw/cuda/memory.h>

#include <cuda_runtime.h>

#include <stdexcept>

namespace mlfw
{

void* CudaMemory::allocate(size_t bytes){
    void* ptr = nullptr;
    cudaError_t error = cudaMalloc(&ptr,bytes);
    if(error != cudaSuccess){
        throw std::runtime_error(
            cudaGetErrorString(error)
        );
    }
    return ptr;
}

void CudaMemory::free(void* ptr){
    if(ptr == nullptr){
        return;
    }
    cudaFree(ptr);
}

void CudaMemory::copyHostToDevice(void* device,const void* host,size_t bytes){
    cudaMemcpy(device,host,bytes,cudaMemcpyHostToDevice);
}

void CudaMemory::copyDeviceToHost(void* host,const void* device,size_t bytes){
    cudaMemcpy(host,device,bytes,cudaMemcpyDeviceToHost);
}

void CudaMemory::copyDeviceToDevice(void* dst,const void* src,size_t bytes){
    cudaMemcpy(dst,src,bytes,cudaMemcpyDeviceToDevice);
}

}