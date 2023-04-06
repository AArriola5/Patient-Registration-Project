#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ios>
#include "include/patient.h"

void displayMenu(Hospital& h1, std::vector<Patient>& patientList);
void registerPatient(Hospital&, std::vector<Patient>&);
void viewPatient(Hospital&, std::vector<Patient>&);
void updatePatient(Hospital&, std::vector<Patient>&);
void checkHospital(Hospital&, std::vector<Patient>&);
bool stringCompare(std::string s1, std::string s2);
void saveHospitalDB(Hospital&);
void loadHospitalDB(Hospital&);
void read_record(Hospital&, std::vector<Patient>&);
void saveHospital(Hospital&);
void loadHospital(Hospital&);

int main() {

  //Setup Hospital
  Hospital H1;
  H1.set_hospitalName("Thompson Center");
  H1.set_hospitalAddress("124 Main Road, Union City, CA 90000");
  H1.set_hospitalCapacity(10);
  
  std::vector<Patient> patientList;
  read_record(H1, patientList);

  //function to display Menu
  
  int Yourchoice;
  std::string confirm ="";
  do
  { 
    displayMenu(H1, patientList);
    std::cout<<"Enter Your choice(1-4) : ";
    std::cin>>Yourchoice;
    
   switch (Yourchoice)
   {
      case 1: registerPatient(H1, patientList); break;
      case 2: viewPatient(H1, patientList); break;
      case 3: updatePatient(H1, patientList); break;
      case 4: checkHospital(H1, patientList); break;
      default: std::cout <<"Invalid Choice" << std::endl; break;
    }
    std::cout<< std::endl << "Press y to Quit" << std::endl << "Press any other key to Continue: ";
    std::cin.clear();
    std::cin>>confirm;
  } while (confirm != "y");
  
  saveHospitalDB(H1); //save patients DB
  saveHospital(H1); //save hospital config
  return 0;

}

// **************************** Display Menu Function *************************************
void displayMenu(Hospital& h1, std::vector<Patient>& patientList)
{ 
  std::cout<<"\n===================================================== \n";
  std::cout<<" \t\t MENU  \n";
  std::cout<<"===================================================== \n";
  std::cout<<" 1. Register Patient\n";
  std::cout<<" 2. View Patient\n";
  std::cout<<" 3. Edit Patient\n";
  std::cout<<" 4. View Hospital Occupancy (" << h1.count_free_bed() << " bed available with the capacity of " << h1.get_hospitalCapacity() << " )\n";
}

// **************************** Register Patient Menu Function *************************************
void registerPatient(Hospital& h1, std::vector<Patient>& patientList)
{
  std::cout<< "\nRegister Patient\n";
  std::cout<< "================\n";
  Patient temp;
  std::string stemp;
  std::cout<< "Enter Patient Name : ";
  std::cin.ignore();
  std::cin.clear();
  std::getline(std::cin, stemp);
  temp.set_patient(stemp);

  // check Hospital availabiltiy
  int bedNumber = 0;

  if(h1.check_bed_available())
  {
    bedNumber = h1.reserve_bed(temp);
    temp.set_admission(true);
    std::cout << "\n\t" << temp.get_patientName() << " is admitted with bed number ( " << bedNumber << " )\n";
  }
  else
  {
    std::cout << "\n\tHospital is fully reserved";
    std::cout << "\n\t" << stemp << " is registered in the patient list without bed.";
  }
  patientList.push_back(temp);
}

// **************************** View Patient Menu Function *************************************
void viewPatient(Hospital& h1, std::vector<Patient>& patientList)
{
  std::cout<< "\nView Patient\n";
  std::cout<< "============\n";

  std::cout << std::setw(20) << "Name" << " | " <<std::setw(10) << "Admitted" << " | "  << std::setw(10) << "Critical condition" << std::endl;
  for(int i = 0; i < patientList.size(); i++)
  {
    std::cout << std::setw(20) << patientList[i].get_patientName() << " | " << std::setw(10) << patientList[i].get_admissionStatus() << " | "  << std::setw(10) << patientList[i].get_criticalnStatus() << std::endl;
  }
}

// **************************** Update Patient Menu Function *************************************
void updatePatient(Hospital& h1, std::vector<Patient>& patientList)
{
  std::cout<< "\nUpdate Patient\n";
  std::cout<< "==============\n";

  std::cout << std::setw(20) << "Name" << " | " <<std::setw(10) << "Admitted" << " | "  << std::setw(10) << "Critical condition" << std::endl;
  for(int i = 0; i < patientList.size(); i++)
  {
    std::cout << std::setw(20) << patientList[i].get_patientName() << " | " << std::setw(10) << patientList[i].get_admissionStatus() << " | "  << std::setw(10) << patientList[i].get_criticalnStatus() << std::endl;
  }

  std::string stemp;

  std::cout<< "Enter the name of patient name to update : ";
  std::cin.ignore();
  std::cin.clear();
  std::getline(std::cin, stemp);

  std::vector<int> searchResult_index;
  
  std::cout << "\n\t Search Result \n";
  std::cout << "\t ----------------";
  std::cout << std::setw(20) << "Name" << " | " <<std::setw(10) << "Admitted" << " | "  << std::setw(10) << "Critical condition" << std::endl;
  for(int i = 0; i < patientList.size(); i++)
  {
    if(patientList[i].check_patientName(stemp))
    {
      std::cout << std::setw(20) << patientList[i].get_patientName() << " | " << std::setw(10) << patientList[i].get_admissionStatus() << " | "  << std::setw(10) << patientList[i].get_criticalnStatus() << std::endl;
      searchResult_index.push_back(i);
    }
  }

  std::cout << std::endl;

  for(int i = 0; i < searchResult_index.size(); i++)
  {
    std::cout << "\t Patient Name : " << patientList[searchResult_index[i]].get_patientName() << std::endl;
    std::cout << "\t Admitted : " << patientList[searchResult_index[i]].get_admissionStatus() << std::endl;
    std::cout << "\t Critical Condition : " << patientList[searchResult_index[i]].get_criticalnStatus() << std::endl;

    std::string stemp_name = "";
    std::cout << "Enter Patient Name : " ;
    std::cin.clear();
    std::getline(std::cin, stemp_name);

    std::string admission_status = "";
    
    std::cout << "Update Admission Status (0 - Not Admitted, 1 - Admitted) : " ;
    std::cin.clear();
    std::getline(std::cin,admission_status);

    if(stringCompare(admission_status,"0"))
    {
      patientList[searchResult_index[i]].set_admission(0);
      h1.unreserve_bed(patientList[searchResult_index[i]]);
    }
    else if(stringCompare(admission_status,"1"))
    {
      patientList[searchResult_index[i]].set_admission(1);
    }
    
    else
      std::cout << "\n\t *** Invalid Input ***";

    stemp = "";

    std::cout << "Update Critical Status (0 - Not Critical, 1 - Critical) : " ;
    std::cin.clear();
    std::getline(std::cin,stemp);
    
    if(stringCompare(stemp,"0"))
      patientList[searchResult_index[i]].set_patient_condition(0);
    else if(stringCompare(stemp,"1"))
      patientList[searchResult_index[i]].set_patient_condition(1);
    else
      std::cout << "\n\t *** Invalid Input ***";

  if (admission_status != "0")
  {
    for(int k = 0; k < h1.get_hospitalCapacity(); k++)
    {
      //Update patient
      if (stringCompare(patientList[searchResult_index[i]].get_patientName(), h1.h_bed[k].bedOccupant))
      {
        h1.h_bed[k].bedOccupant = stemp_name;
        break;
      }
    }
  }
  patientList[searchResult_index[i]].set_patient(stemp_name);
  }
}


void checkHospital(Hospital& h1, std::vector<Patient>& patientList)
{
  std::cout<< "Hospital Overview" << std::endl << std::endl;

  std::cout << " Hospital Name     : " << h1.get_hospitalName() << std::endl;
  std::cout << " Hospital Capacity : " << h1.get_hospitalCapacity() << std::endl;
  std::cout << std::setw(10) << "Bed Number" << " | " <<std::setw(10) << "Available" << " | "  << std::setw(10) << "Patient Name" << std::endl;
  for(int i = 0; i < h1.get_hospitalCapacity(); i++ )
  {
    std::cout << std::setw(10) << i+1 << " | " << std::setw(10) << std::boolalpha << h1.h_bed[i].available << " | "  << std::setw(10) << h1.h_bed[i].bedOccupant << std::endl;
  }
}

bool stringCompare(std::string s1, std::string s2)
{
  size_t found = s1.find(s2);
  if (found!=std::string::npos)
    return true;
  else
    return false;
}

void saveHospitalDB(Hospital& H1)
{
  std::ofstream fout;
  fout.open("hospitalDB.csv");

  //patient data export
  for(int i = 0; i < H1.get_hospitalCapacity(); i++)
  {
    fout << i+1 << ", " << H1.h_bed[i].available << "," << H1.h_bed[i].bedOccupant <<  "\n"; //new row

  }
     
  fout.close();
}

void saveHospital(Hospital& H1)
{
    std::ofstream fout;
    fout.open("hospital.cfg");

    //patient column headers
    fout << "Name=" << H1.get_hospitalName() << "\n"
        << "Address=" << H1.get_hospitalAddress() << "\n"
        << "Capacity=" << H1.get_hospitalCapacity() << "\n"
        << "Address=" << H1.get_hospitalAddress() << "\n";
    fout.close();
}

void loadHospital(Hospital& H1)
{
    std::ifstream fin;
    char str[256];
    std::string input;
    fin.open("hospital.cfg");
    if(!fin.good()) return;

    fin.ignore(100,'=');
    fin.getline(str,256);
    H1.set_hospitalName(str);

    fin.ignore(100,'=');
    fin.getline(str,256);
    H1.set_hospitalAddress(str);

    fin.ignore(100,'=');
    fin.getline(str,256);
    H1.set_hospitalCapacity(atoi(str));

    fin.close();
}

void loadHospitalDB(Hospital& H1)
{
    std::ifstream fin;
    std::string stemp;
    bool btemp;

    fin.open("hospitalDB.csv");

    fin.ignore(256,'\n'); //ignore column headers

    //patient data import
    for(int i = 0; i < H1.get_hospitalCapacity(); i++)
    {
      std::getline(fin, stemp, ',');
      if(stemp=="0") break;
    
      Patient temp;
      temp.set_patient(stemp);

      std::getline(fin, stemp, ',');
      btemp = atoi(stemp.c_str());
      temp.set_admission(btemp);
      if(btemp)
      {
        H1.reserve_bed_with_Name(stemp);
      }

      std::getline(fin, stemp, ',');
      btemp = atoi(stemp.c_str());
      temp.set_patient_condition(btemp);  
    }

   fin.close();
}


void read_record(Hospital& h1, std::vector<Patient>& patientList)
{
    // File pointer
    std::fstream fin;
  
    // Open an existing file
    fin.open("hospitalDB.csv", std::ios::in);

    std::vector<std::string> row;
    std::string line, word, temp, stemp;
    bool temp_status, btemp;
    Patient temp_Patient;
    int bed_number = 0;

    for(int i = 0; i < h1.get_hospitalCapacity(); i++)
    {
          
      Patient temp;
      temp.set_patient(stemp);

      //Get Bed number from csv
      std::getline(fin, stemp, ',');

      //Get Admission status from csv
      std::getline(fin, stemp, ',');
      btemp = atoi(stemp.c_str());
      temp.set_admission(btemp);

      //Get Name of patient from csv
      std::getline(fin, stemp, '\n');

      if(!btemp)
      {
        h1.reserve_bed_with_Name(stemp);
        temp.set_patient_condition(false);
        temp.set_admission(!btemp);
        temp.set_patient(stemp);
        patientList.push_back(temp);     
      }
    }
}
