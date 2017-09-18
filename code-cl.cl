__kernel void hello(__global char* string)
{

}

// > gcc -I /path-to-NVIDIA/OpenCL/common/inc -L /path-to-NVIDIA/OpenCL/common/lib/Linux64 -o hello hello.c -lOpenCL (64-bit Linux)
