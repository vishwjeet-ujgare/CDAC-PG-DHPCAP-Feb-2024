import numpy as nu
import pycuda.driver as cuda
import pycuda.autoinit
from pycuda.compiler import SourceModule

#CUDA kernel code for array addition
cuda_code="""
    __global__ void add_arrays(int *a ,int *b,int size){
        int tid=threadIdx.x + blockIdx.x * blockDim.x;
        
        if(tid < size){
            c[tid]=a[tid]+b[tid];
        }
    }
"""

#Host data
a_host=np.array([1,2,3],dtype=np.int32)
b_host=np.array([4,5,6],dtype=np.int32)

size=len(a_host)

#Device Data
a_device=cuda.mem_alloc(a_host.nbytes)
b_device=cuda.mem_alloc(b_host.nbytes)
c_device=cuda.mem_alloc(a_host.nbytes)


#Copy data to device
cuda.memcpy_htod(a_device,a_host)
cuda.memcpy_htod(b_device,b_host)

#Load the CUDA module
cuda_module=SourceModule(cuda_code)
add_arrays_kernel=cuda_module.get_function("add_arrays")

#Set up block grid demensions
block_dim=(size,1,1)
grid_dim=(1,1)

#Launch the CUDA kernel
add_arrays_kernel(a_device,b_device,c_device,np.int32(size),block=block_dim,grid_dim=grid_dim)

#Copy the result back to the host
c_host=np.empty_like(a_host)
cuda.memcpy_dtoh=(c_host,c_device)

#Display the resulte
print("Array A : ",a_host)
print("Array a : ",b_host)
print("Array Array C : ",c_host)






