#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#define CL_USE_DEPRECATED_OPENCL_1_1_APIS

const char *kernelSource = 
    "_kernel void arrayAdd(_global int *a, __global int *b, __global int *c) {\n"
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
    int *a = (int *)malloc(sizeof(int));
    int *b = (int *)malloc(sizeof(int));
    int *c = (int *)malloc(sizeof(int));
    

    *a=222;
    *b=333;
    
    //step 1:Create OpenCL context and command queue
    clGetPlatformIDs(1,&platform,NULL);
    clGetDeviceIDs(platform,CL_DEVICE_TYPE_GPU,1,&device,NULL);
    context=clCreateContext(NULL,1,&device,NULL,NULL,NULL);
    queue=clCreateCommandQueue(context,device,CL_QUEUE_PROFILING_ENABLE,NULL);

    //step 2: create and build OpenCL program
    program=clCreateProgramWithSource(context,1,(const char **)&kernelSource,NULL,NULL);

    clBuildProgram(program,1,&device,NULL,NULL,NULL);

    //step 3: create kernel
    kernel=clCreateKernel(program,"arrayAdd",NULL);

    //step 4: Create Memory buffers
    bufferA=clCreateBuffer(context,CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,sizeof(int),a,NULL);

    bufferB=clCreateBuffer(context,CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,sizeof(int ),b,NULL);

    bufferC=clCreateBuffer(context,CL_MEM_WRITE_ONLY,sizeof(int),NULL,NULL);

    //step 5: set kernel arguments
    clSetKernelArg(kernel,0,sizeof(cl_mem),&bufferA);
    clSetKernelArg(kernel,1,sizeof(cl_mem),&bufferB);
    clSetKernelArg(kernel,2,sizeof(cl_mem),&bufferC);

    //step 6 : Enqueue kernal for execution and measure time size_t global Size = N;

    //clEnqueueNDRangeKernel(queue,kernel,1,NULL.&globalSize,NULL,0,NULL,&event);

    err=clEnqueueNDRangeKernel(queue,kernel,1,NULL,&globalSize,NULL,0,NULL,&event);

    if(err !=CL_SUCCESS)
    {
        //Handle the error here , e.g print and erroe message and exit

        printf("Error enqueueing kernel : %d\n",err);
        return 1;
    }

    clWaitForEvents(1,&event);

    //Get kernel execution time
    cl_ulong startTime, endTime;
    clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_START(cl_ulong),&startTime,NULL);

    double  executionTime=(double)(endTime -startTime)/1000000.0;//convert nanoseconds to milliseconds

    //step 7 " Reat the result from the device"
    clSetKernelArg(kernel,0,sizeof(cl_mem),&bufferA);
    clEnqueueReadBuffer(queue,bufferC,CL_TRUE,sizeof(int),c,0,NULL,NULL);


    //step 8 : print the result and execution time 
    printf("Enxecution Time L %d.6f milliseconds\n",executionTime);
    printf("Result : ");
    printf("%d  ",*c);
    printf("\n");


//Step 9 :Release resources
clReleaseMemObject(bufferC);
clReleaseMemObject(bufferC);
clReleaseMemObject(bufferC);
clReleaseKernel(kernel);
clReleaseProgram(program);
clReleaseCommandQueue(queue);
clReleaseContext(context);

//Free allocated memory
free(a);
free(b);
free(c);

return 0;








}