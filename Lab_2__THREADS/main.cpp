#include <iostream>
#include <Windows.h>
#include<algorithm>
#include<thread>

void min_max(int& min, int& max,int *arr, int arr_size)
{
    min=*(std::min_element(arr,arr+arr_size,[](int a, int b){bool res(a<b);Sleep(7);return res;} ));
    max=*(std::max_element(arr,arr+arr_size,[](int a,int b){bool res(a<b);Sleep(7);return res;}));
}

int main()
{

    int arrSize(0);
    int min(0);
    int max(0);

    std::cin>>arrSize;

    int* arr =new int [arrSize];
    for(int i=0;i<arrSize;++i)
        std::cin>>arr[i];

    std::thread minmaxThr(min_max,std::ref(min),std::ref(max),arr,arrSize);


    minmaxThr.join();
    
    std::cout<<min<<"\n";
    std::cout<<max;

    delete [] arr;

}
