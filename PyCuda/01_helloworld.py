
import pycuda.driver as cuda
import pycuda.autoinit
from pycuda.compiler import SourceModule

#CUDA Kernel code for priting "Hello ,World !"

cuda_code ="""
    #include<stdio.h>
    
    __global__ void hello_world(){
        printf("Hello , World! \\n");
    }
"""


#load the cuda module
cuda_module=SourceModule(cuda_code)
hello_world_kernel=cuda_module.get_function("hello_world")

#set up block and grid dimensions
block_dim =(1,1,1)
grid_dim=(1,1)

#Launch the CUDA kernel
hello_world_kernel(block=block_dim,grid=grid_dim)
