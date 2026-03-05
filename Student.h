//
//  Student.h
//  Management of Roster System
//
//  Created by Nadjah Duke on 9/18/25.
//

#pragma once
#define STUDENT_H
#include "Date.h"

class Student
{
    //variable declaration
private:
    int studentId;
    std::string lastName;
    std::string firstName;
    int credits;
    std::string standing;
    double gpa;
    Date dateOfBirth;
    Date matriculationDate;
    
    
    //public methods
public:
    
    //Default Constructor * now uses date object for date of birth and matriculation date instead of a string
    Student():studentId(0),lastName("No Last Name"), firstName("No First Name") ,standing("Unknown Standing"),credits(0) ,gpa(0.0){}
    
    //Parameterized Constructor used to give values to private variablesnow uses date object for date of birth and matriculation date instead of a string
    Student(int idNum, std::string lastN,std::string firstN,std::string standingClass,int creds, double gradePoint, Date& DOB,Date& maDate): studentId(idNum),lastName(lastN), firstName(firstN),standing(standingClass),credits(creds),gpa(gradePoint),dateOfBirth(DOB),matriculationDate(maDate){}
    
    //setter method declarations
    void setStudentId(int idNum);
    void setLastname(std::string lName);
    void setFirstName(std::string fName);
    void setStanding(std::string standingClass);
    void setCredits(int creds);
    void setGpa(double gradePoint);
    
    //take a Date object for the Date of Birth instead of a string
    void setDateOfBirth(const Date& dOB);
    
    //take a Date object for the matriculation date instead of a string
    void setMatriculationDate(const Date& maDate);
    
    
    //getter method declarations
    int getStudentId ()const;
    std::string getLastName()const;
    std::string getFirstName()const;
    std::string getStanding()const;
    int getCredits()const;
    double getGpa()const;
    
    //returns Date object as Date of Birth instead of string
    Date getDateOfBirth()const;
    
    //returns Date onject as matriculation date instead of a string
    Date getMatriculationDate()const;
    
    
    //print students info
    void printStudentInfo()const;
    
    //overloaded operator non member function declaration
    bool operator == (const Student& s) const;
    bool operator != (const Student& s) const;
    bool operator >= (const Student& s) const;
    bool operator <= (const Student& s) const;
    
    //friend function declaration
    friend std::ostream& operator << (std::ostream& outputStream, const Student& s);
    friend std::istream& operator >>(std::istream& inputStream, Student& s);
};
