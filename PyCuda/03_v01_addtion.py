%%writefile cpu_gpu_time_pycuda.py
import numpy as np
import pycuda.driver as cuda
import pycuda.autoinit
from pycuda.compiler import SourceModule
import time

# CUDA kernel code for array addition
cuda_code = """
__global__ void add_arrays(int *a, int *b, int *c, int size) {
    int tid = threadIdx.x + blockIdx.x * blockDim.x;

    if (tid < size) {
        c[tid] = a[tid] + b[tid];
    }
}
"""


# CPU array addition
def cpu_add_arrays(a, b):
    return a + b

# GPU array addition
def gpu_add_arrays(a_gpu, b_gpu, result_gpu, size):
    block_size = 256
    grid_size = (size + block_size - 1) // block_size

    add_arrays_cuda(a_gpu, b_gpu, result_gpu, np.int32(size), block=(block_size, 1, 1), grid=(grid_size, 1))

# Generate random arrays
size = 25000 * 25000
a_cpu = np.random.rand(size).astype(np.float32)
b_cpu = np.random.rand(size).astype(np.float32)
result_cpu = np.zeros_like(a_cpu)

# Allocate GPU memory
a_gpu = cuda.mem_alloc(a_cpu.nbytes)
b_gpu = cuda.mem_alloc(b_cpu.nbytes)
result_gpu = cuda.mem_alloc(result_cpu.nbytes)

# Copy data to GPU
cuda.memcpy_htod(a_gpu, a_cpu)
cuda.memcpy_htod(b_gpu, b_cpu)

# Compile the CUDA code
mod = SourceModule(cuda_code)
add_arrays_cuda = mod.get_function("add_arrays")

# Perform CPU array addition and measure time
start_time_cpu = time.time()
result_cpu = cpu_add_arrays(a_cpu, b_cpu)
end_time_cpu = time.time()
time_cpu = end_time_cpu - start_time_cpu

# Perform GPU array addition and measure time
start_time_gpu = time.time()
gpu_add_arrays(a_gpu, b_gpu, result_gpu, size)
cuda.Context.synchronize()
end_time_gpu = time.time()
time_gpu = end_time_gpu - start_time_gpu

# Copy result from GPU to host
cuda.memcpy_dtoh(result_cpu, result_gpu)

# Display results and time taken
print(f"Time taken on CPU: {time_cpu} seconds")
print(f"Time taken on GPU: {time_cpu} seconds")



