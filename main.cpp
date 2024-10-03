#include <windows.h>
#include <fstream>
#include<conio.h>

const std::string CREATOR = "Creator.exe";
const std::string REPORTER = "Reporter.exe";

int main()
{
     	std::string fileName_bin;
	int numNotes;
	std::string tmp;
	std::string msgCreator;
		
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	
	std::cout << "Enter binary file name: ";
	std::cin >> fileName_bin;
	std::cout << "Enter a number of notes in this file: ";
	std::cin >> tmp;
	numNotes=std::stoi(tmp);

	msgCreator=CREATOR+" "+ fileName_bin+" "+numNotes;
	std::wstring w_msgCreator(msgCreator.begin(),msgCreator.end());
	LPWSTR lp_msgCreator=&w_msgCreator;

	ZeroMemory(&si,sizeof(si);
	si.cb=sizeof(STARTUPINFO);

	if(!CreateProcess(NULL,lp_msgCreator,NULL,NULL,TRUE,CREATE_NEW_CONSOLE,NULL,NULL,&si,&pi)
{
	system("cls");
	std::cout<<" There is an error in Creator";
return GetLastError();
}

	std::string fileName_report;
	std::string payment_hour;
	std::string msgReporter;
	
	std::cout<<"Enter file name for report";
	std::cin>>fileName_report;
	std::cout<<"Enter payment for hour";
	std::cin>>payment_hour;
	
	msgReporter=REPORTER+" "+fileName_report+" "+payment_hour;
	std::wstring w_msgReporter(msgReporter.begin(),msgReporter.end());
	LPWSTR lp_msgReporter=&w_msgReporter;

if (!CreateProcess(NULL, lp_msgReporter, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		system("cls");
		std::cout << "Something Wrong with Reporter process";
		return GetLastError();
	}
	WaitForSingleObject(pi.hProcess, INFINITE);

	std::ifstream reportInput(fileName_report);

	if (reportInput.is_open())
	{
		while (!reportInput.eof())
		{
			std::string temp;
			getline(reportInput, temp);
			std::cout << temp << "\n";
		}
	}
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

}


