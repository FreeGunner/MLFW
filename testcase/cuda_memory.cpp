#include <iostream>

#include "mlfw/cuda/memory.h"

using namespace std;
using namespace mlfw;

int main()
{
    constexpr size_t N = 10;

    double host[N];

    for(size_t i=0;i<N;i++)
    {
        host[i]=i+1;
    }

    cout<<"Host Memory"<<endl;

    for(size_t i=0;i<N;i++)
    {
        cout<<host[i]<<" ";
    }

    cout<<endl<<endl;

    //-------------------------------------------------

    void *device =
        CudaMemory::allocate(
            sizeof(host)
        );

    cout<<"GPU Memory Allocated"<<endl;

    //-------------------------------------------------

    CudaMemory::copyHostToDevice(
        device,
        host,
        sizeof(host)
    );

    cout<<"Copied Host -> Device"<<endl;

    //-------------------------------------------------

    for(size_t i=0;i<N;i++)
    {
        host[i]=0;
    }

    cout<<endl;

    cout<<"Host Cleared"<<endl;

    for(size_t i=0;i<N;i++)
    {
        cout<<host[i]<<" ";
    }

    cout<<endl<<endl;

    //-------------------------------------------------

    CudaMemory::copyDeviceToHost(
        host,
        device,
        sizeof(host)
    );

    cout<<"Copied Device -> Host"<<endl<<endl;

    cout<<"Host Memory"<<endl;

    for(size_t i=0;i<N;i++)
    {
        cout<<host[i]<<" ";
    }

    cout<<endl<<endl;

    //-------------------------------------------------

    CudaMemory::free(device);

    cout<<"GPU Memory Freed"<<endl;

    return 0;
}