//
//  Roster.h
//  Management of Roster System
//
//  Created by Nadjah Duke on 9/30/25.
//
/*Homework 3
 Due date: October 21
 Write a class Roster that is identified by the course name, course code, number of credits,
 instructor name, and contains a list of students stored in an array. For now, you can use
 stack allocated array of MAX_CAPACITY=10 (define MAX_CAPACITY as a macro in
 the .h file). Later we will make this array dynamic to allow it to grow. Provide necessary
 constructors, accessor functions for each member, and mutator functions for each
 member. Provide a function to add a student to a Roster, delete student from a Roster,
 and search for a student. Provide a function to output all Students from a roster to console
 in a nice format.
 For now, you should not worry about the order of Students in your Roster. They do not
 need to be sorted
 Write a driver program to test your Roster class.
 Use declare/define/use approach
 Submit the assignment to your lab instructor.*/

#pragma once
#define ROSTER_H
#include "Student.h"

//Declare a alias for a pointer
typedef Student* StudentPtr;

class Roster
{
    //variable declaration
private:
    std::string courseName;
    std::string courseCode;
    int numberOfCredits;
    std::string instructorName;
    int capacity;
    int filledSlots;
    
    //Declares a dynamic array of pointers to student objects
    StudentPtr *students;
    
    // used to grow the dynamic array
    void resize();
    
    
    //public methods
public:
    
    //default constuctor
    Roster():courseName("no name yet"), courseCode("no code yet"),numberOfCredits(0),instructorName("no name yet"), filledSlots(0),capacity(10)
    {
        //all pointers in the dynamic array points to a null pointer
        students = new StudentPtr[capacity];
        
        for(int i = 0; i < capacity; i++)
        {
            students[i] = nullptr;
        }
    }
    
    //parameterized constructor
    Roster(std::string cName, std::string cCode, int numOfCreds, std::string instructor): courseName(cName), courseCode(cCode), numberOfCredits(numOfCreds), instructorName(instructor),filledSlots(0),capacity(10){
        
        // all pointers in the dynamic array points to anull pointer
        students = new StudentPtr[capacity];
        for(int i = 0; i < capacity; i++)
        {
            students[i] = nullptr;
        }
    }
    
    //copy constuctor declaration
    
    Roster(const Roster& rosterObject);
    
    //overload assignment declaration
    
    Roster& operator = (const Roster& roster);
    
    //destuctor declaration
    
    ~Roster();
    
    
    //overload[] operator declaration
    
    const StudentPtr operator [] (int index) const;
    
    
    //setter method declarations
    void setCourseName(std::string cName);
    void setCourseCode(std::string cCode);
    void setNumberOfCredits(int creds);
    void setInstructorName(std::string instructor);
    
    //getter method declartions
    std::string getCourseName() const;
    std::string getCourseCode() const;
    int getNumberOfCredits() const;
    std::string getInstructorName() const;
    int getCapacity() const;
    int getFilledSlots() const;
    
    //array access method declarations(add, search and delete)
    int findStudent(const Student& student);
    void addStudent(const Student& student);
    int removeStudent(const Student& student);
    
    //print roster info metho declation
    void getRosterInfo()const;
    StudentPtr* getStudents() const; 
    void sortRoster(StudentPtr* arr,int filledSlots);
    
    
    
    
    friend std::ostream& operator << (std::ostream& outputStream, Roster& r);
    friend std::istream& operator >> (std::istream& inputStream, Roster& r);
    
    
};
