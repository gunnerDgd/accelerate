__kernel void CLSimpleKernel(__global int* Input1, __global int* Input2, __global int* Output1)
{
    int i = 0;
    for(i = 0 ; i < 16 ; i++)
        Output1[i] = Input1[i] + Input2[i];
}