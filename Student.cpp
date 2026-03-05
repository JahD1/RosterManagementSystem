//
//  Student.cpp
//  Management of Roster System
//
//  Created by Nadjah Duke on 9/17/25.
//

#include <iostream>
#include <string>
#include"Student.h"
#include "Date.h"


// implentation of setters
void Student::setStudentId(int idNum)
{
    studentId = idNum;
}
void Student::setLastname(std::string lName)
{
    lastName = lName;
}
void Student::setFirstName(std::string fName)
{
    firstName = fName;
}
void Student::setStanding(std::string standingClass)
{
    standing = standingClass;
}
void Student::setCredits(int creds)
{
    if(creds >= 0)
    {
        credits = creds;
    }
    else
    {
        throw std::invalid_argument("cannot enter negative credits");
    }
    
    
    if(creds < 15)
    {
        standing = "Lower Freshman";
    }
    else if(creds < 30)
    {
        standing = "Upper Freshman";
    }
    else if(creds < 45)
    {
        standing = "Lower Sophmore";
    }
    else if(creds < 60)
    {
        standing = "Upper Sophmore";
    }
    else if(creds< 75)
    {
        standing = "Lower Junior";
    }
    else if(creds < 90)
    {
        standing = "Upper Junior";
    }
    else if(creds < 105)
    {
        standing = "Lower Senior";
    }
    else
        standing = "Upper Senior";
}

void Student::setGpa(double gradePoint)
{
    gpa = gradePoint;
}

//take a Date object for the Date of Birth instead of a string 
void Student::setDateOfBirth(const Date& dob)
{
    dateOfBirth = dob;
}

//take a Date object for the matriculation date instead of a string
void Student::setMatriculationDate(const Date& maDate)
{
    matriculationDate = maDate;
}

//implementation of getters
int Student::getStudentId()const
{
    return studentId;
}
std::string Student::getLastName()const
{
    return lastName;
}
std::string Student::getFirstName()const
{
    return firstName;
}
std::string Student::getStanding()const
{
    return standing;
}
int Student::getCredits()const
{
    return credits;
}
double Student::getGpa()const
{
    return gpa;
}
Date Student::getDateOfBirth()const
{
    return dateOfBirth;
}
Date Student::getMatriculationDate()const
{
    return matriculationDate;
}
//print student info
void Student::printStudentInfo()const
{
    std::cout << "Student ID: " << studentId << std::endl;
    std::cout << "Last Name: " << lastName << std::endl;
    std::cout << "First Name: " << firstName << std::endl;
    std::cout << "Standing: " << standing << std::endl;
    std::cout << "Credits: " << credits << std::endl;
    std::cout << "Gpa: " << gpa << std::endl;
    std::cout << "Date Of Birth: " << dateOfBirth << std::endl;
    std:: cout << "Matriculation Date: " << matriculationDate <<std::endl;
}

//uses == overloaded operator to compare 2 students
bool Student:: operator ==(const Student& s) const
{
    bool check = true;
    
    if(lastName != s.lastName)
    {
        check = false;
    }
    
    if(firstName != s.firstName)
    {
        check = false;
    }
    
    if (studentId != s.studentId)
    {
        check = false;
    }
    
    return check;
}

//uses != overloaded operator to compare 2 students
bool Student:: operator != (const Student& s) const
{
    bool check = false;
    
    if(lastName != s.lastName)
    {
        check = true;
    }
    if(firstName != s.firstName)
    {
        check = true;
    }
    
    if(studentId != s.studentId)
    {
        check = true;
    }
    
    return check;
}

//uses >= overloaded operator to compare 2 students
bool Student::operator >= (const Student& s) const
{
    long minSize = 0;
    
    if(lastName.length() != s.lastName.length())
    {
        if(lastName.length() <  s.lastName.length())
        {
            minSize = lastName.length();
        }
        else
        {
            minSize = s.lastName.length();
        }
        
        for(int i = 0; i < minSize; i++)
        {
            if (lastName[i] < s.lastName[i])
            {
                return false;
            }
        }
        if(lastName.length() > s.lastName.length())
        {
            return  true;
        }
        else
        {
            return false;
        }
    }
    else if(firstName.length() != s.firstName.length())
    {
        if(firstName.length() <  s.firstName.length())
        {
            minSize = firstName.length();
        }
        else
        {
            minSize = s.firstName.length();
        }
        
        for(int i = 0; i < minSize; i++)
        {
            if (firstName[i] < s.firstName[i])
            {
                return false;
            }
        }
        if(firstName.length() > s.firstName.length())
        {
            return  true;
        }
        else
        {
            return false;
        }
    }
    else if (studentId != s.studentId)
    {
        if(studentId > s.studentId)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return true;
}

// uses <= overloaded operator to compare 2 students
bool Student::operator <= (const Student& s) const
{
    long minSize = 0;
    
    if(lastName.length() != s.lastName.length())
    {
        if(lastName.length() < s.lastName.length())
        {
            minSize = lastName.length();
        }
        else
        {
            minSize = s.lastName.length();
        }
        
        for(int i = 0; i < minSize; i++)
        {
            if (lastName[i] > s.lastName[i])
            {
                return false;
            }
        }
        if(lastName.length() < s.lastName.length())
        {
            return  true;
        }
        else
        {
            return false;
        }
    }
    else if(firstName.length() != s.firstName.length())
    {
        if(firstName.length() <  s.firstName.length())
        {
            minSize = firstName.length();
        }
        else
        {
            minSize = s.firstName.length();
        }
        
        for(int i = 0; i < minSize; i++)
        {
            if (firstName[i] > s.firstName[i])
            {
                return false;
            }
        }
        if(firstName.length() < s.firstName.length())
        {
            return  true;
        }
        else
        {
            return false;
        }
    }
    else if (studentId != s.studentId)
    {
        if(studentId < s.studentId)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return true;
}

//friend function ised to out students info
std::ostream& operator << (std::ostream& outputStream, const Student& s)
{
    s.printStudentInfo();
    return outputStream;
}

//uses friend function to edit student info based on user input
std::istream& operator >>(std::istream& inputStream, Student& s)
{
    char userInput;
    
    do
    {
        std:: cout << "Enter 'i' for Stduent Id: \n ";
        std:: cout << "Enter 'f' for First Name: \n ";
        std:: cout << "Enter 'l' for Last Name: \n ";
        std:: cout << "Enter 's' for Standing: \n ";
        std:: cout << "Enter 'c' for Credits: \n ";
        std:: cout << "Enter 'g' for Gpa \n: ";
        std:: cout << "Enter 'd' for Date Of Birth: \n ";
        std:: cout << "Enter 'm' for Matriculation Date: \n ";
        
        std:: cin >> userInput;
        userInput = std::tolower(userInput);
        
        switch (userInput) {
            case 'i':
            {
                int StudentId;
                std:: cout<< "Enter Student Id \n ";
                inputStream >> StudentId;
                
                s.setStudentId(StudentId);
                break;
            }
            case 'f':
            {
                std:: string firstName;
                std:: cout<< "Enter Student's First Name \n ";
                inputStream >> firstName;
                
                s.setFirstName(firstName);
                break;
            }
            case 'l':
            {
                std::string lastName;
                std:: cout<< "Enter Student's Last Name \n ";
                inputStream >> lastName;
                
                s.setLastname(lastName);
                break;
            }
            case 's':
            {
                std::string standing;
                std:: cout<< "Enter Student's Standing \n ";
                inputStream >> standing;
                
                s.setStanding(standing);
                break;
            }
            case 'c':
            {
                int credits;
                std:: cout<< "Enter Student's Credits \n ";
                inputStream >> credits;
                
                s.setCredits(credits);
                break;
            }
            case 'g':
            {
                double gpa;
                std:: cout<< "Enter Student's Gpa \n ";
                inputStream >> gpa;
                
                s.setGpa(gpa);
            }
                break;
            case 'd':
            {
                Date dob;
                std:: cout<< "Enter Student's Date of Birth \n ";
                inputStream >> dob;
                
                s.setDateOfBirth(dob);
                break;
            }
            case 'm':
            {
                Date matriculaton;
                std:: cout<< "Enter Student's Matriculation Date \n ";
                inputStream >> matriculaton;
                
                s.setMatriculationDate(matriculaton);
                break;
            }
            default:
                userInput = 'q';
                break;
        }
        
        
    }while(userInput != 'q');
    
    return inputStream;
}































