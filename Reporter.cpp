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
        char name[10];
        double hours;
        bool operator<(const Employee& obj1)
        {
            return Id<obj1.Id;
        }
    };
    
 public:
    Reporter(char ** arg):fileName_Bin(arg[1]),fileName_Report(arg[2]),payment_hour(std::stod(arg[3])),numEmp(0)
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
        reportf<<"          Report on the file "<<fileName_Bin<<"\n";    
        for(int i=0;i<numEmp;++i)
        {
            reportf<<emp_arr[i].Id<<" "<<emp_arr[i].name<<" "<<emp_arr[i].hours<<" "<<emp_arr[i].hours*payment_hour<<"\n";
        }
        reportf.close();

    }

};


int main(int argc, char ** argv)
{
    Reporter rp1(argv);
    rp1.Write();
    return 0;
}
