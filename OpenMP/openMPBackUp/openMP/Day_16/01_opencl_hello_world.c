#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#define CL_USE_DEPRECATED_OPENCL_1_1_APIS

// OpenCL kernel code
const char *kernelSource = 
"__kernel void helloWorld() {\n"
"    printf(\"Hello, World!\\n\");\n"
"}\n"; 

int main() {
    cl_platform_id platform;
    cl_device_id device;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;


    // Step 1 : Discover Platforms and Devices
    clGetPlatformIDs(1, &platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);

    // Step 2 : Create Context and Command Queue
    context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
    queue = clCreateCommandQueue(context, device, 0, NULL);

    // Step 3 : Create and Build Program
    program = clCreateProgramWithSource(context, 1, (const char**)&kernelSource, NULL, NULL);
    clBuildProgram(program, 1, &device, NULL, NULL, NULL);

    // Step 4 : Create kernel
    kernel = clCreateKernel(program, "helloWorld", NULL);

    // Step 5 : Enqueue Kernel for Execution
    clEnqueueTask(queue, kernel, 0, NULL, NULL);

    // Step 6 : Release Resources
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);


    return 0;

}