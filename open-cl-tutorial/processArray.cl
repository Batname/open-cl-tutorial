kernel void processArray(global int* data, global int* outData)
{
    outData[get_global_id(0)] = data[get_global_id(0)] * 2;
}


kernel void processArray1(global char * data)
{
    
}
