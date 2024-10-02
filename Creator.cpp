#include<string>
#include<iostream>
#include<fstream>


class Creator
{
 private:

     struct Employee;
     std::string fileName;
     int numNotes;
     std::string forRead;
     std::ofstream binf;
     Employee *emp_arr;

     struct Employee
     {
         int Id;
         char name[10];
         double hours;
         friend std::istream& operator>>(std::istream& in,Employee &obj)
         {
         std::string tmp("");
         std::string tmp2("");
         in>>tmp>>obj.name>>tmp2;
         obj.Id=std::stoi(tmp);
         obj.hours=std::stod(tmp2);
         return in;
         }

     };

 public:
     Creator():fileName(""),numNotes(0),forRead("")
     {

         ReadInfo();
     }
     ~Creator()
     {
         if(emp_arr!=NULL)
             delete[] emp_arr;
     }

     void ReadInfo()
     {
         std::cin>>forRead;
         numNotes=std::stoi(forRead);
         emp_arr=new Employee[numNotes];
         std::cin>>fileName;
         for(int i=0;i<numNotes;++i)
         {
             std::cin>>emp_arr[i];
         }
         binf.open(fileName ,std::ios::binary|std::ios::out); 
     }
     void WriteOnBinf()
     {
        
         if(!binf)
         {
             std::cout<<"File is not opened"<<"\n";
             return;
         }
         binf.write(reinterpret_cast<char*>(&numNotes),sizeof(int));
         for(int i=0;i<numNotes;++i)
         {
             binf.write(reinterpret_cast<char*>(&emp_arr[i].Id),sizeof(int));
             binf.write(reinterpret_cast<char*>(&emp_arr[i].name),sizeof(char[10]));
             binf.write(reinterpret_cast<char*>(&emp_arr[i].hours),sizeof(double));

         }
         binf.close();
     }


};



int main()
{

    Creator cr1;
    cr1.WriteOnBinf();
    return 0;
}
