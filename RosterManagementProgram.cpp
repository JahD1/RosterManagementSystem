//
//  StudentApp.cpp
//  Management of Roster System
//
//  Created by Nadjah Duke on 9/17/25.
//

//
#include <iostream>
#include"Student.h"
#include "Roster.h"
#include "Date.h"
#include <fstream>
#include <sstream>

// removes whitespace from beginning and end of a string
std::string removeWhiteSpace(const std::string str)
{
    long start = 0;
    long end = str.size() -1;
    
    while(start <= end && std::isspace(str[start]))
    {
        start++;
    }
    
    while(end >= start && std::isspace(str[end]))
    {
        end--;
    }
    
    return str.substr(start, end-start+1);
}
// reads file and populates each roster and studuents information
void readRosterFile(std:: vector<Roster>& rosters)
{
    std::ifstream inStream("/Users/nadjahduke/Developer/XcodeProjects/Management of Roster System/Management of Roster System/roster.txt");
    
    if(inStream.fail())
    {
        std::cerr << "Input file opening failed \n";
        exit(1);
    }
    else
    {
        std::cout <<"Loading File... ";
    }
    
    std::string line;
    Roster currentRoster;
    bool isRosterHeading = true;
    
    while(std::getline(inStream, line))
    {
        line = removeWhiteSpace(line);
        
        if(line.empty())continue;
        
        if(line == "end_roster|")
        {
            rosters.push_back(currentRoster);
            currentRoster = Roster();
            
            isRosterHeading = true;
            continue;
        }
        
        std::stringstream ss(line);
        
        if(isRosterHeading)
        {
            // std:: cout <<"First line \n" << line<<std::endl;
            std::string courseName, courseCode, instructor, tempCredits;
            int numberOfCredits;
            
            getline(ss,courseName, '|');
            courseName = removeWhiteSpace(courseName);
            getline(ss,courseCode, '|');
            courseCode = removeWhiteSpace(courseCode);
            getline(ss,tempCredits,'|');
            getline(ss,instructor, '|');
            instructor = removeWhiteSpace(instructor);
            
            
            numberOfCredits = std::stoi(tempCredits);
            currentRoster = Roster(courseName,courseCode,numberOfCredits,instructor);
            isRosterHeading = false;
            
        }
        else
        {
            Student currentStudent;
            std::string firstName, lastName, standing, tempStudentID, tempCredits, tempDOB, tempMADate, tempGpa;
            int studentId, credits;
            double gpa;
            
            
            getline(ss,firstName, '|');
            getline(ss,lastName, '|');
            getline(ss,tempStudentID, '|');
            //std::cout << "Debug: "<< tempStudentID<<std::endl;
            studentId = std::stoi(tempStudentID);
            getline(ss,standing, '|');
            getline(ss,tempCredits, '|');
            credits = std::stoi(tempCredits);
            getline(ss,tempGpa,'|');
            gpa = std::stod(tempGpa);
            
            getline(ss,tempDOB, '|');
            getline(ss,tempMADate, '|');
            
            std::stringstream dOB(tempDOB);
            std::stringstream maDate(tempMADate);
            std::string tempMonth, tempDay, tempYear;
            int month, day, year;
            
            getline(dOB, tempMonth, '/');
            month = std::stoi(tempMonth);
            getline(dOB, tempDay, '/');
            day = std::stoi(tempDay);
            getline(dOB, tempYear,'/');
            year = std::stoi(tempYear);
            
            Date dateOfBirth(month,day,year);
            
            getline(maDate,tempMonth,'/');
            month = std::stoi(tempMonth);
            getline(maDate,tempDay,'/');
            day = std::stoi(tempDay);
            getline(maDate,tempYear,'/');
            year = std::stoi(tempYear);
            
            Date matriculationDate(month,day, year);
            
            
            currentStudent = Student(studentId,lastName,firstName,standing,credits,gpa,dateOfBirth,matriculationDate);
            
            currentRoster.addStudent(currentStudent);
        }
    }
}

//writes back to file with changes made
void writeRosterFile(const std::vector<Roster> & rosters)
{
    std::ofstream outStream("/Users/nadjahduke/Developer/XcodeProjects/Management of Roster System/Management of Roster System/roster.txt");
    
    if(outStream.fail())
    {
        std::cerr<< "Ouput file writing failed \n";
        exit(1);
    }
    else
    {
        std::cout << "Writing File... \n";
    }
    
    
    for(int i = 0; i < rosters.size(); i++)
    {
        const Roster& roster = rosters[i];
        
        outStream << roster.getCourseName() << '|'
        << roster.getCourseCode() << '|'
        << roster.getNumberOfCredits() << '|'
        <<roster.getInstructorName() << '\n';
        
        
        
        for(int j = 0; j < roster.getFilledSlots(); j++)
        {
            const Student* student = roster[j];
            
            outStream << student->getFirstName() << '|'
            << student->getLastName() << '|'
            << student->getStudentId() << '|'
            << student->getStanding() << '|'
            << student->getCredits() << '|'
            << student->getGpa() << '|'
            << student->getDateOfBirth().getMonthNum()<< '/'
            << student->getDateOfBirth().getDay()<< '/'
            << student->getDateOfBirth().getYear()<< '|'
            << student->getMatriculationDate().getMonthNum() << '/'
            << student->getMatriculationDate().getDay() << '/'
            << student->getMatriculationDate().getYear() << '|';
            
            outStream << '\n';
        }
        
        outStream <<"end_roster|\n";
        
    }
    outStream.close();
}
//Helper Function To Enter Student Information (used to insert new student to a roster)
Student enterStudentInfo()
{
    int tempNumberOfCredits;
    double tempGpa;
    std:: string tempFirstName, tempLastName, tempStanding;
    Date tempMatriculationDate, tempDateOfBirth;
    
    Student temp;
    
    std::cin.ignore(std::numeric_limits<std::streamsize>:: max(),'\n');
    
    std::cout<< "Enter the Last Name of The Student You Want To Add To The Roster : \n";
    std::getline(std::cin, tempLastName);
    
    temp.setLastname(tempLastName);
    
    std::cout<< "Enter the First Name of The Student You Want To Add To The Roster : \n";
    std::getline(std::cin, tempFirstName);
    
    temp.setFirstName(tempFirstName);
    
    
    std::cout<< "Enter the Number Of Credits of The Student You Want To Add To The Roster : \n";
    std::cin >> tempNumberOfCredits;
    
    std::cin.ignore(std::numeric_limits<std::streamsize>:: max(),'\n');
    
    temp.setCredits(tempNumberOfCredits);
    
    std::cout<< "Enter the Standing of The Student You Want To Add To The Roster : \n";
    std::getline(std::cin, tempStanding);
    
    temp.setStanding(tempStanding);
    
    std::cout<< "Enter the GPA of The Student You Want To Add To The Roster : \n";
    std::cin >> tempGpa;
    
    std::cin.ignore(std::numeric_limits<std::streamsize>:: max(),'\n');
    
    temp.setGpa(tempGpa);
    
    std::cout<< "Enter the Matriculation Date of The Student You Want To Add To The Roster : \n";
    std::cin >> tempMatriculationDate;
    
    std::cin.ignore(std::numeric_limits<std::streamsize>:: max(),'\n');
    
    temp.setMatriculationDate(tempMatriculationDate);
    
    std::cout<< "Enter the Date of Birth of The Student You Want To Add To The Roster : \n";
    
    std::cin >> tempDateOfBirth;
    std::cin.ignore(std::numeric_limits<std::streamsize>:: max(),'\n');
    
    temp.setDateOfBirth(tempDateOfBirth);
    
    return temp;
}
//Supervior Mode
void SupervisorMode(std::vector<Roster> &rosters)
{
    int answer;
    
    do
    {
        std::cout<< "Enter one the following options. Entering any other number will end the program: \n";
        std::cout << "1) Create a new roster \n";
        std::cout << "2) Drop a roster \n";
        std::cout << "3) Display roster information \n";
        std::cout << "4) Display all rosters \n";
        std::cout << "5) Select a roster to perform the following operations \n";
        std::cout << "    a) Insert a new student to a roster \n";
        std::cout << "    b) Remove a student from a roster  \n";
        std::cout << "    c) Update a student in a roster \n";
        std::cout << "    d) List all student in one roster in sorted order \n";
        
        std::cin >> answer;
        std::cin.ignore(std::numeric_limits<std::streamsize>:: max(),'\n');
        
        
        switch (answer) {
            case 1:
            {
                Roster newRoster;
                
                std::string courseName, courseCode, instructorName;
                int numberOfCredits;
                
                std::cout << "You have chosen to create a new roster \n";
                
                std::cout << "Enter The Course Name: ";
                std::getline(std::cin, courseName);
                std::cout << std::endl;
                
                std::cout << "Enter The Course Code: ";
                std::getline(std::cin, courseCode);
                std::cout << std::endl;
                
                std::cout << "Enter Number Of Credits For The Course: ";
                std::cin >> numberOfCredits;
                std::cout << std::endl;
                
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                std::cout << "Enter The Instructor's Name: ";
                std::getline(std::cin, instructorName);
                std::cout << std::endl;
                
                newRoster = Roster(courseName, courseCode,numberOfCredits,instructorName);
                rosters.push_back(newRoster);
            }
                break;
            case 2:
            {
                std::string courseCode;
                bool foundCourse = false;
                
                std::cout << "You Have Chosen to Drop A Roster \n";
                
                std::cout << "Enter the Course Code of The Roster You Would Like To Drop : ";
                std::getline(std::cin, courseCode);
                
                for(int i = 0; i < rosters.size(); i++)
                {
                    if(rosters[i].getCourseCode() == courseCode)
                    {
                        rosters.erase(rosters.begin()+i);
                        std::cout << "Roster " << courseCode << " Has Been Dropped. \n";
                        
                        foundCourse = true;
                        break;
                    }
                }
                
                if(!foundCourse)
                {
                    std::cerr << "Unable To Find Course With The Course Code: " << courseCode;
                    std::cout << std::endl;
                }
            }
                break;
            case 3:
            {
                std::string courseCode;
                bool foundCourse = false;
                
                
                std::cout << "You Have Chosen To Display A Roster \n";
                std::cout << "Enter the Course Code of The Roster You Would Like To Display : ";
                
                std::getline(std::cin, courseCode);
                
                for(int i = 0; i < rosters.size(); i++)
                {
                    if(rosters[i].getCourseCode() == courseCode)
                    {
                        std:: cout << rosters[i];
                        foundCourse = true;
                        break;
                    }
                }
                
                if(!foundCourse)
                {
                    std::cerr << "Unable To Find Course With The Course Code: " << courseCode <<"\n";
                }
            }
                break;
            case 4:
            {
                std::cout << "You Have Chosen To Display All Rosters \n";
                
                for(int i = 0; i < rosters.size(); i++)
                {
                    std::cout<<rosters[i];
                }
            }
                break;
                
            case 5:
            {
                char option;
                std::string courseCode;
                
                do {
                    std::cout << "Chosen One  Perform The Following Operations On A Roster. Enter Any Other Key To Stop Editting Roster \n";
                    std::cout << "    a) Insert a new student to a roster \n";
                    std::cout << "    b) Remove a student from a roster  \n";
                    std::cout << "    c) Update a student in a roster \n";
                    std::cout << "    d) List all student in one roster in sorted order \n";
                    
                    std::cin >> option;
                    option = std::tolower(option);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    
                    std::cout << "Enter The Course Code Of The Roster You Want To Edit: ";
                    getline(std::cin, courseCode);
                    std::cout << std::endl;
                    
                    bool foundCourse = false;
                    int rosterIndex = -1;
                    
                    for(int i = 0; i < rosters.size();i++)
                    {
                        if(rosters[i].getCourseCode() == courseCode)
                        {
                            //std::cout << "DEBUG: " << rosters[i].getCourseCode();
                            
                            std::cout << courseCode;
                            
                            rosterIndex = i;
                            foundCourse = true;
                            break;
                        }
                    }
                    
                    if(foundCourse)
                    {
                        int studentId;
                        switch(option)
                        {
                            case 'a':
                            {
                                Student temp;
                                std::cout << "Enter The Student Id Of The Student You Want To Add: ";
                                std::cin >> studentId;
                                
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                
                                temp.setStudentId(studentId);
                                
                                if(rosters[rosterIndex].findStudent(temp) != -1)
                                {
                                    std::cerr << "Student Already Exist \n";
                                }
                                else
                                {
                                    temp = enterStudentInfo();
                                    
                                    rosters[rosterIndex].addStudent(temp);
                                }
                            }
                                break;
                                
                            case 'b':
                            {
                                Student temp;
                                std::cout << "Enter The Student Id Of The Student You Want To Remove: ";
                                std::cin >> studentId;
                                
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                
                                temp.setStudentId(studentId);
                                
                                int studentIndex = rosters[rosterIndex].findStudent(temp);
                                
                                if(studentIndex != -1)
                                {
                                    
                                    const StudentPtr student = rosters[rosterIndex][studentIndex];
                                    rosters[rosterIndex].removeStudent(*student);
                                }
                                else
                                {
                                    std::cerr << "Student Does Not Exist On Roster \n";
                                }
                            }
                                break;
                                
                            case 'c':
                            {
                                Student temp;
                                std::cout << "Enter The Student Id Of The Student You Want To Update: ";
                                std::cin >> studentId;
                                
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                
                                temp.setStudentId(studentId);
                                
                                int studentIndex = rosters[rosterIndex].findStudent(temp);
                                
                                if(studentIndex != -1)
                                {
                                    std::cin >> *(rosters[rosterIndex][studentIndex]);
                                    
                                    std::cout << "Student Updated \n";
                                }
                                else
                                {
                                    std::cerr << "Student Does Not Exist On Roster \n";
                                }
                                
                            }
                                break;
                                
                            case 'd':
                            {
                                std::cout << "Listing all Students On the Roster In Sorted Order: \n";
                                
                                Roster& roster = rosters[rosterIndex];
                                StudentPtr* sortOrdStudents = roster.getStudents();
                                int filledSlots = rosters[rosterIndex].getFilledSlots();
                                
                                
                                roster.sortRoster(sortOrdStudents, filledSlots);
                                
                                for(int i = 0; i < filledSlots; i++)
                                {
                                    std::cout << *(sortOrdStudents[i]);
                                }
                            }
                                break;
                                
                            default:
                            {
                                std::cout << "You Have Choosen To Stop Edits To Roster With Course Code: " << courseCode << '\n';
                                
                                option = 'n';
                            }
                        }
                    }
                    else
                    {
                        std::cerr << "No Roster With Exist With Course Code: " << courseCode << '\n';
                    }
                    
                } while (option != 'n');
                
            }
                break;
                
            default:
            {
                std:: cout << "You have chosen to end the program \n";
            }
                break;
        }
        
        
    }while(answer >=1 && answer<=5);
    
}
//User Mode
void UserMode(std::vector<Roster>& rosters)
{
    char option ;
    std::string courseCode;
    
    do {
        std::cout << "Chosen One  Perform The Following Operations On A Roster. Enter Any Other Key To Stop Editting Roster \n";
        std::cout << "    a) Insert a new student to a roster \n";
        std::cout << "    b) Remove a student from a roster  \n";
        std::cout << "    c) Update a student in a roster \n";
        
        std::cin >> option;
        option = std::tolower(option);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if(option != 'a' && option != 'b' && option != 'c')
        {
            std::cout<< "You Have Chosen To End The Program \n";
            break;
        }
        
        std::cout << "Enter The Course Code Of The Roster You Want To Edit: ";
        getline(std::cin, courseCode);
        
        bool foundCourse = false;
        int rosterIndex = -1;
        
        for(int i = 0; i < rosters.size(); i++)
        {
            if(rosters[i].getCourseCode() == courseCode)
            {
                rosterIndex = i;
                foundCourse = true;
                break;
            }
        }
        
        if(!foundCourse)
        {
            std::cout << "No Roster Found With Course Code: " << courseCode << '\n';
            break;
        }
        
        int studentId = 0;
        switch(option)
        {
            case 'a':
            {
                Student temp;
                std::cout << "Enter The Student Id Of The Student You Want To Add: ";
                std::cin >> studentId;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                temp.setStudentId(studentId);
                
                if(rosters[rosterIndex].findStudent(temp) != -1)
                {
                    std::cerr << "Student Already Exist \n";
                }
                else
                {
                    temp = enterStudentInfo();
                    rosters[rosterIndex].addStudent(temp);
                }
            }
                break;
                
            case 'b':
            {
                Student temp;
                std::cout << "Enter The Student Id Of The Student You Want To Remove: ";
                std::cin >> studentId;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                temp.setStudentId(studentId);
                
                int studentIndex = rosters[rosterIndex].findStudent(temp);
                
                if(studentIndex != -1)
                {
                    const StudentPtr student = rosters[rosterIndex][studentIndex];
                    rosters[rosterIndex].removeStudent(*student);
                }
                else
                {
                    std::cerr << "Student Does Not Exist On Roster \n";
                }
            }
                break;
                
            case 'c':
            {
                Student temp;
                std::cout << "Enter The Student Id Of The Student You Want To Update: ";
                std::cin >> studentId;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                temp.setStudentId(studentId);
                
                int studentIndex = rosters[rosterIndex].findStudent(temp);
                
                if(studentIndex != -1)
                {
                    std::cin >> *(rosters[rosterIndex][studentIndex]);
                    std::cout << "Student Updated \n";
                }
                else
                {
                    std::cerr << "Student Does Not Exist On Roster \n";
                }
            }
                break;
        }
        
    } while(true);
}



int main(int argc, const char * argv[]) {
    
    //creates vector of rosters
    std::vector<Roster> rosters;
    
    //Prompt User
    char choice;
    std::cout << "Choose Your Mode: \n";
    std::cout << "A. Supervisor \n"
    << "B. User \n"
    << "C. Exit \n";
    
    std::cin >> choice;
    choice = std::tolower(choice);
    
    //reads file given and populates rosters and students info
    readRosterFile(rosters);
    
    switch (choice) {
        case 'a':
        {
            //Supervisor Authentication Check
            std::string userName, password, usernameEntered, passwordEntered;
            
            std::ifstream inStream("/Users/nadjahduke/Developer/XcodeProjects/Management of Roster System/Management of Roster System/database.txt");
            if(inStream.fail())
            {
                std::cerr << "Cannot Authenticate Due to File Error \n";
                exit(1);
            }
            else
            {
                std::cout << "Authenticating... \n";
            }
            
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            std::getline(inStream,userName);
            std::getline(inStream,password);
            
            userName = removeWhiteSpace(userName);
            password = removeWhiteSpace(password);
            
            std::cout<< "Enter UserName: ";
            std::getline(std::cin,usernameEntered);
            
            std::cout << "Enter Password: ";
            std::getline(std::cin, passwordEntered);
            
            
            if(usernameEntered == userName && passwordEntered == password)
            {
                std::cout<< "Entering Supervisor Menu \n";
                //Gives access the supervisor menu
                SupervisorMode(rosters);
            }
            else
            {
                std::cout << "Incorrect Login \n";
            }
            break;
        }
        case 'b':
        {
            //Gives access to User Menu
            UserMode(rosters);
            break;;
        }
        default:
        {
            std::cout << "You Have Choosen To Exit The Menu \n";
            break;
        }
            
    }
    
    //write file with changes to the rosters vector
    writeRosterFile(rosters);
}

