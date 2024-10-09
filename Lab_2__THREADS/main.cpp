#include <iostream>
#include <Windows.h>
#include<algorithm>
#include<thread>
#include<numeric>


void average(int*arr,int arr_size,int& result)
{
    if(!arr_size)
    {
        return;
    }
    result=std::accumulate(arr,arr+arr_size,0,[](int a, int b){int res(a+b);Sleep(12);return res;});
    result/=arr_size;
    
}

void min_max(int& minIndex, int& maxIndex,int *arr, int arr_size)
{
    minIndex=(std::min_element(arr,arr+arr_size,[](int a, int b){bool res(a<b);Sleep(7);return res;} ))-arr;
    maxIndex=(std::max_element(arr,arr+arr_size,[](int a,int b){bool res(a<b);Sleep(7);return res;}))-arr;
}

int main()
{

    int arrSize(0);
    int minIndex(0);
    int maxIndex(0);
    int result(0);

    std::cout<<"Enter array size\n";
    std::cin>>arrSize;
    std::cout<<"Enter elements\n";

    int* arr =new int [arrSize];
    for(int i=0;i<arrSize;++i)
        std::cin>>arr[i];

    std::thread minmaxThr(min_max,std::ref(minIndex),std::ref(maxIndex),arr,arrSize);
    std::thread averageThr(average,arr,arrSize,std::ref(result));

    minmaxThr.join();
    averageThr.join();
    
    std::cout<<"Min: "<<arr[minIndex]<<"\n";
    std::cout<<"Max: "<<arr[maxIndex]<<"\n";
    std::cout<<"Average: "<<result<<"\n";

    arr[minIndex]=result;
    arr[maxIndex]=result;

    std::cout<<"Array: \n";
    for(int i=0;i<arrSize;++i)
        std::cout<<arr[i]<<" ";

    delete [] arr;

}
