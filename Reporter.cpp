#include<algorithm>
#include<iostream>
#include<fstream>

class Reporter
{
 private:

    struct Employee;
    std::string fileName_Bin;
    std::string fileName_Report;
    double payment_hour;
    int numEmp;
    Employee * emp_arr;
    std::ifstream binf;
    std::ofstream reportf;

    struct Employee
    {
        int Id;
        std::string name;
        double hours;
        bool operator<(const Employee& obj1)
        {
            return Id<obj1.Id;
        }
    };
    
 public:
    Reporter():fileName_Bin(""),fileName_Report(""),payment_hour(0.0),numEmp(0)
    {
        GetInfo();
    }
    ~Reporter()
    {
        if(emp_arr!=NULL)
            delete []emp_arr; 
    }
    void GetInfo()
    {
        std::string tmp("");
        std::cin>>fileName_Bin;
        std::cin>>fileName_Report;
        std::cin>>tmp;
        payment_hour=std::stod(tmp);

        binf.open(fileName_Bin,std::ios::binary|std::ios::out);
        if(!binf)
        {
            std::cout<<"File is not found\n";
            return;
        }
        binf.read(reinterpret_cast<char*>(&numEmp), sizeof(int));
        emp_arr=new Employee[numEmp];

        for(int  i=0; i<numEmp;++i)
        {
            binf.read(reinterpret_cast<char*>(&emp_arr[i].Id), sizeof(int));
            binf.read(reinterpret_cast<char*>(&emp_arr[i].name),sizeof(char[10]));
            binf.read(reinterpret_cast<char*>(&emp_arr[i].hours),sizeof(double));
        }
    }
    void Write()
    {
        reportf.open(fileName_Report);      
        if(!reportf)
        {
            std::cout<<"File is not found";
            return;
        }
        std::sort(emp_arr,emp_arr+numEmp);
        reportf<<"          Отчёт по файлу"<<fileName_Bin;    
        for(int i=0;i<numEmp;++i)
        {
            reportf<<emp_arr[i].Id<<" "<<emp_arr[i].name<<" "<<emp_arr[i].hours<<" "<<emp_arr[i].hours*payment_hour<<"\n";
        }
        reportf.close();

    }

};


int main()
{
    Reporter rp1;
    rp1.Write();
    return 0;
}
