//
//  Roster.cpp
//  Management of Roster System
//
//  Created by Nadjah Duke on 10/20/25.
//

#include <iostream>
#include"Roster.h"

//copy constructor implentation makes a deep copy of student obects in dynamic array of pinters
Roster::Roster(const Roster& rosterObject)
{
    courseName = rosterObject.courseName;
    courseCode = rosterObject.courseCode;
    numberOfCredits = rosterObject.numberOfCredits;
    instructorName = rosterObject.instructorName;
    capacity = rosterObject.getCapacity();
    filledSlots = rosterObject.getFilledSlots();
    
    students = new StudentPtr[capacity];
    
    for(int i = 0; i < filledSlots; i++)
    {
        students[i] = new Student(*rosterObject.students[i]);
    }
    
    for(int i = filledSlots; i < capacity; i++)
    {
        students [i] = nullptr;
    }
    
}

// = operator implementation copies roster infor fron right side and overrights roster on left side
Roster& Roster:: operator = (const Roster& roster)
{
    if(this == &roster)
    {
        return *this;
    }
    
    if(capacity!= roster.capacity)
    {
        delete [] students;
        
        students = new StudentPtr[roster.capacity];
    }
    
    courseName = roster.courseName;
    courseCode = roster.courseCode;
    numberOfCredits = roster.numberOfCredits;
    instructorName = roster.instructorName;
    capacity = roster.capacity;
    filledSlots = roster.filledSlots;
    
    for(int i = 0; i < filledSlots; i++)
    {
        students[i] = new Student(*roster.students[i]);
    }
    
    for(int i = filledSlots; i < capacity; i++)
    {
        students[i] =nullptr;
    }
    
    courseCode = roster.courseCode;
    courseName = roster.courseName;
    instructorName = roster.instructorName;
    numberOfCredits = roster.numberOfCredits;
    
    return *this;
}

//destuctor implementation
Roster::~Roster()
{
    delete [] students;
}
const StudentPtr Roster:: operator [] (int index) const
{
    if(index < 0 || index >= filledSlots)
    {
        return nullptr;
    }
    
    return students[index];
}
//setter method implementations
void Roster:: setCourseName(std::string cName)
{
    courseName = cName;
}
void Roster:: setCourseCode(std::string cCode)
{
    courseCode = cCode;
}
void Roster:: setNumberOfCredits(int creds)
{
    numberOfCredits = creds;
}
void Roster:: setInstructorName(std::string instructor)
{
    instructorName = instructor;
}

//getter method implementations
std::string Roster:: getCourseName() const
{
    return courseName;
}
std::string Roster:: getCourseCode() const
{
    return courseCode;
}
int Roster:: getNumberOfCredits() const
{
    return numberOfCredits;
}
std::string Roster:: getInstructorName() const
{
    return instructorName;
}
int Roster:: getFilledSlots()const
{
    return filledSlots;
}
int Roster:: getCapacity()const
{
    return capacity;
}
StudentPtr* Roster::getStudents()const
{
    return students;
}

void Roster::resize()
{
    StudentPtr * newArray = new StudentPtr[2*capacity];
    
    StudentPtr * oldArray;
    
    
    for(int i = 0; i < filledSlots; i++)
    {
        newArray[i] = students[i];
    }
    
    for(int i = filledSlots; i < 2*capacity; i++)
    {
        newArray[i] = nullptr;
    }
    
    capacity = 2* capacity;
    
    oldArray = students;
    
    students = newArray;
    
    delete [] oldArray;
    
    oldArray = nullptr;
}

//implementation of method to find student in roster
int Roster:: findStudent(const Student& stud)
{
    for(int i = 0; i < filledSlots; i++)
    {
        if (students[i] != nullptr && (students[i]->getStudentId() == stud.getStudentId()))
        {
            return i;
        }
    }
    return -1;
}

//implementation of method to add student to the roster
void Roster::addStudent(const Student& student)
{
    if(filledSlots == capacity)
    {
        resize();
    }
    
    if (findStudent(student) != -1)
    {
        std:: cout << "Student exist on roster already \n";
    }
    else
    {
        students[filledSlots] = new Student(student);
        
        filledSlots++;
        
        std::cout << "Student added \n";
    }
}

// implementation of method to remove student from the roster
int Roster::removeStudent(const Student& student)
{
    int index = findStudent(student);
    
    if(index != -1)
    {
        
        std::cout << "Student Removed: " << students[index]->getFirstName()<< ", " << students[index]->getLastName()<< "---> Students' ID: " << students[index]->getStudentId()<< std::endl;
        
        delete students[index];
        for (int i = index; i <= filledSlots-1; i++)
        {
            students[i] = students[i+1];
        }
        
        students[filledSlots - 1] = nullptr;
        filledSlots--;
        
        return index;
    }
    else
    {
        std::cout << "Student not on Roster " << std::endl;
    }
    return -1;
}

//print roster info implementation
void Roster:: getRosterInfo()const
{
    std::cout << "Course Name: " << courseName << std::endl;
    std::cout << "Course Code: " << courseCode << std::endl;
    std::cout << "Number Of Credits: " << numberOfCredits << std::endl;
    std::cout << "Instructor Name: "<< instructorName << std::endl;
    std::cout << "Filled Slots : " << filledSlots << "/" << capacity << std::endl;
    
    
    for(int i = 0; i < filledSlots; i++)
    {
        std::cout << (i+1) << ". Full Name: " << students[i]->getLastName() << ", " << students[i]->getFirstName();
        std::cout << " --->  Student ID: " << students[i]->getStudentId()<< std::endl;
    }
    
    std::cout<< std::endl;
}
//function takes dynamic array of pointers to student objects and sorts the students
void Roster:: sortRoster(StudentPtr* arr,int filledSlots)
{
    //simple sort implementation
    for(int i = 0; i < filledSlots-1; i++)
    {
        int minIndex = i;
        
        for(int j = i+1; j < filledSlots; j++)
        {
            
            if(arr[j]->getLastName()!= arr[minIndex]->getLastName())
            {
                if(arr[j]->getLastName() < arr[minIndex]->getLastName())
                {
                    minIndex = j ;
                }
            }
            else if (arr[j]->getFirstName() != arr[minIndex]->getFirstName())
            {
                if(arr[j]->getFirstName() < arr[minIndex]->getFirstName())
                {
                    minIndex = j;
                }
            }
            else
            {
                if(arr[j]->getStudentId() < arr[minIndex]->getStudentId())
                {
                    minIndex =j;
                }
            }
            
        }
        
        if(minIndex != i)
        {
            StudentPtr temp = arr[i];
            arr[i]=arr[minIndex];
            arr[minIndex] = temp;
        }
    }
    
}

//friend function prints roster info
std::ostream& operator << (std::ostream& outputStream, Roster& r)
{
    r.sortRoster(r.students,r.filledSlots);
    
    r.getRosterInfo();
    
    return outputStream;
}

//friend function used to allow user to input data. Aloows changes and searches to roster
std::istream& operator >> (std::istream& inputStream, Roster& r)
{
   char userInput;
    
    std::cout << "To Change Roster Info Follow Directions Below. To Stop Editting The Roster Press Any Key \n";
    do
    {
        std::cout << "Enter 'n' to change Course Name \n";
        std::cout << "Enter 'p' to change Course Code/Pin \n";
        std::cout << "Enter 'c' to change the Number of Credits \n";
        std::cout << "Enter 'i' to change the Instructors Name \n";
        std::cout << "Enter 'a' to add a student \n";
        std::cout << "Enter 'f' to find a student \n";
        std::cout << "Enter 'd' to delete a student \n";
        
        inputStream >> userInput;
        userInput =std::tolower(userInput);
        
        //reads input until it finds a new line character
        inputStream.ignore(std::numeric_limits<std::streamsize>:: max(),'\n');
        
        switch(userInput)
        {
            case 'n':
            {
                std::string courseName;
                std::cout<< "Enter Course Name: \n";
                std::getline(inputStream, courseName);
                
                r.setCourseName(courseName);
                
                break;
            }
            case 'p':
            {
                std::string courseCode;
                std::cout<< "Enter Course Code/Pin: \n";
                std::getline(inputStream,courseCode);
                
                r.setCourseCode(courseCode);
                break;
            }
            case 'c':
            {
                int numOfCreds;
                std::cout<< "Enter Number Of Credits: \n";
                inputStream >> numOfCreds;
                inputStream.ignore(std::numeric_limits<std::streamsize>:: max(),'\n');
                
                r.setNumberOfCredits(numOfCreds);
                
                break;
            }
            case 'i':
            {
                std::string instructorName;
                std::cout<< "Enter Instructor Name: \n";
                std::getline(inputStream,instructorName);
                
                r.setInstructorName(instructorName);
                
                break;
            }
            case 'a':
            {
                int tempStudentId,tempNumberOfCredits;
                double tempGpa;
                std:: string tempFirstName, tempLastName, tempStanding;
                Date tempMatriculationDate, tempDateOfBirth;
                
                Student temp;
                
                std::cout<< "Enter the Student ID of The Student You Want To Add To The Roster : \n";
                inputStream >> tempStudentId;
                
                inputStream.ignore(std::numeric_limits<std::streamsize>:: max(),'\n');
                
                temp.setStudentId(tempStudentId);
                
                std::cout<< "Enter the Last Name of The Student You Want To Add To The Roster : \n";
                std::getline(inputStream, tempLastName);
                
                temp.setLastname(tempLastName);
                
                std::cout<< "Enter the First Name of The Student You Want To Add To The Roster : \n";
                std::getline(inputStream, tempFirstName);
                
                temp.setFirstName(tempFirstName);
                
                
                std::cout<< "Enter the Number Of Credits of The Student You Want To Add To The Roster : \n";
                inputStream >> tempNumberOfCredits;
                
                inputStream.ignore(std::numeric_limits<std::streamsize>:: max(),'\n');
                
                temp.setCredits(tempNumberOfCredits);
                
                std::cout<< "Enter the Standing of The Student You Want To Add To The Roster : \n";
                std::getline(inputStream, tempStanding);
                
                temp.setStanding(tempStanding);
                
                std::cout<< "Enter the GPA of The Student You Want To Add To The Roster : \n";
                inputStream >> tempGpa;
                
                inputStream.ignore(std::numeric_limits<std::streamsize>:: max(),'\n');
                
                temp.setGpa(tempGpa);
                
                std::cout<< "Enter the Matriculation Date of The Student You Want To Add To The Roster : \n";
                std::cin >> tempMatriculationDate;
                
                inputStream.ignore(std::numeric_limits<std::streamsize>:: max(),'\n');
                
                temp.setMatriculationDate(tempMatriculationDate);
                
                std::cout<< "Enter the Date of Birth of The Student You Want To Add To The Roster : \n";
                
                std::cin >> tempDateOfBirth;
                inputStream.ignore(std::numeric_limits<std::streamsize>:: max(),'\n');
                
                temp.setDateOfBirth(tempDateOfBirth);
                
                
                r.addStudent(temp);
                break;
            }
            case 'f':
            {
                int StudentId;
                Student temp;
                
                std::cout<< "Enter the Student ID of The Student You Want To Find On The Roster : \n";
                inputStream >> StudentId;
                temp.setStudentId(StudentId);
                
                int found = r.findStudent(temp);
                
                if(found != -1)
                {
                    std::cout << "Student found at number " << (found + 1) << " on the roster \n";
                }
                else
                {
                    std:: cout <<"Student not found \n";
                }
                break;
            }
            case 'd':
            {
                int StudentId;
                Student temp;
                
                std::cout<< "Enter the Student ID of The Student You Want To Remove From The Roster : \n";
                inputStream >> StudentId;
                temp.setStudentId(StudentId);
                
                r.removeStudent(temp);
                break;
            }
            default:
            {
                userInput = 'q';
                break;
            }
        }
    }while(userInput != 'q');
    
    return inputStream;
}
