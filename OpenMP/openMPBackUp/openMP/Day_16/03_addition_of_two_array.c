// %%writefile addition_of_two_array.c
// !gcc -o array_addition addition_of_two_array.c -I "usr/include/CL" -L "/usr/include/CL" -lOpenCL

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#define N 100

#define CL_USE_DEPRECATED_OPENCL_1_1_APIS

const char *kernelSource =
    "__kernel void arrayAdd(__global int *a, __global int *b, __global int *c) {\n"
    "   int i = get_global_id(0);\n"
    "   c[i] = a[i] + b[i];\n"
    "}\n";

int main() {
    cl_platform_id platform;
    cl_device_id device;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;
    cl_mem bufferA, bufferB, bufferC;
    cl_event event;
    cl_int err;

    // Initialize inputs
    int *a = (int *)malloc(N * sizeof(int));
    int *b = (int *)malloc(N * sizeof(int));
    int *c = (int *)malloc(N * sizeof(int));

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i ;
    }

    // Step 1: Create OpenCL context and command queue
    clGetPlatformIDs(1, &platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
    queue = clCreateCommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE, NULL);

    // Step 2: Create and build OpenCL program
    program = clCreateProgramWithSource(context, 1, (const char **)&kernelSource, NULL, NULL);
    clBuildProgram(program, 1, &device, NULL, NULL, NULL);

    // Step 3: Create kernel
    kernel = clCreateKernel(program, "arrayAdd", NULL);

    // Step 4: Create memory buffer
    bufferA = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, N * sizeof(int), a, NULL);
    bufferB = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, N * sizeof(int), b, NULL);
    bufferC = clCreateBuffer(context, CL_MEM_WRITE_ONLY, N * sizeof(int), NULL, NULL);

    // Step 5: Set kernel arguments
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &bufferA);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &bufferB);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &bufferC);

    // Step 6: Enqueue kernel for execution and measure time
    size_t globalSize = N;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, &event);
    if (err != CL_SUCCESS) {
        // Handle the error here, e.g., print an error message and exit
        printf("Error enqueueing kernel: %d\n", err);
        return 1;
    }

    clWaitForEvents(1, &event);

    // Get kernel execution time
    cl_ulong startTime, endTime;
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &startTime, NULL);
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &endTime, NULL);
    double executionTime = (double)(endTime - startTime) / 1000000.0;   // Convert nanoseconds to milliseconds

    // Step 7: Read the result from the device
    clEnqueueReadBuffer(queue, bufferC, CL_TRUE, 0, N * sizeof(int), c, 0, NULL, NULL);

    // Step 8: Print the result and execution time
    printf("Execution Time: %.6f milliseconds\n", executionTime);
    printf("Result: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", c[i]);
    }
    printf("\n");

    // Step 9: Release resources
    clReleaseMemObject(bufferA);
    clReleaseMemObject(bufferB);
    clReleaseMemObject(bufferC);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);

    // Free allocated memory
    free(a);
    free(b);
    free(c);

    return 0;
}