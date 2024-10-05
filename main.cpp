#include <windows.h>
#include<iostream>
#include<fstream>


int main()
{
    std::string fileName_Bin;
    std::string fileName_Report;
    std::string payment_hour;
    std::string numNotes("");
    std::string strCreator="Creator.exe";
    std::string strReporter="Reporter.exe";

    STARTUPINFO sui;
    PROCESS_INFORMATION pri;

    std::cout<<"Enter binary file name: ";
    std::cin>>fileName_Bin;
    std::cout<<"Enter number of emloyees:";
    std::cin>>numNotes;
    std::cout<<"Enter notes \n";

    std::string strCommandLine=strCreator+" "+numNotes+" "+fileName_Bin;

    ZeroMemory(&sui,sizeof(STARTUPINFO));
    sui.cb=sizeof(STARTUPINFO);

    if(!CreateProcess(NULL,&strCommandLine[0],NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL,&sui,&pri))
    {

        std::cout<<"Creator was not started \n";
        return -1;

    }
    WaitForSingleObject(pri.hProcess,INFINITE);

    CloseHandle(pri.hProcess);
    CloseHandle(pri.hThread);

    std::cout<<"Enter report file name: ";
    std::cin>>fileName_Report;
    std::cout<<"Enter payment for hour: ";
    std::cin>>payment_hour;

    strCommandLine=strReporter+" "+fileName_Bin+" "+fileName_Report+" "+payment_hour;    
    
    if(!CreateProcess(NULL,&strCommandLine[0],NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL,&sui,&pri))
    {
        std::cout<<"Reporter was not started \n";
        return -1;
    }

    WaitForSingleObject(pri.hProcess,INFINITE);

    CloseHandle(pri.hProcess);
    CloseHandle(pri.hThread);

    std::ifstream fileReport(fileName_Report);
    if(!fileReport.is_open())
        return -1;

    while(!fileReport.eof())
    {
        std::string tmp;
        getline(fileReport,tmp);
        std::cout<<tmp<<"\n";
    }
    fileReport.close();
    return 0;

}


