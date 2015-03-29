/*
  rec05 - Association and Delegation
  Jia Sen Wu / jw3675
  CS1124
  Polytechnic University
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

class Student {
public:
  Student( const string& stuName ) : name( stuName ), grades( 13, -1 ) {}
  string getName() const {
    return name;
  }
  void addGrade( const int& grade, const int& week ) {
    //cout << grades[week] << endl;
    grades[week] = grade;
    //cout << grades[week] << endl;
  }
  void display() const {
    cout << "Student: " << name << "; Grades: ";
    for( int grade : grades ) {
      cout << grade << ' ';
    }
    cout << endl;
  }
private:
  string name;
  vector<int> grades;
};

class TimeSlot {
public:
  TimeSlot( const string& date, const int& atime ) : day( date ), time( atime ) {}
  string getDay() const {
    return day;
  }
  unsigned int getTime() const {
    return time;
  }
private:
  string day;
  unsigned int time;
};

class Section {
public:
  Section( const string& secName, const string& date, const int& time ) : section( secName ), slot( date, time ) {}
  void addStudent( const string& name ) {
    Student* stuName = new Student( name );
    students.push_back( stuName );
  }
  // Finds the student and uses his/her addGrade function
  void addGrade( const string& name, const int& grade, const int& week ) {
    for( Student* stu: students ) {
      if( name == stu->getName() ) {
	stu->addGrade( grade, week );
	break;
      } //else {
	//cout << name << stu.getName() << endl;
        //}
    }
  }
  // Displays section, day, time, then uses student's display function
  void display() const {
    cout << "Section: " << section << "; " << slot.getDay() << ' ';
    if( slot.getTime() > 12 ) {
      cout << (slot.getTime()-12) << "PM" << endl;
    } else {
      cout << slot.getTime() << "AM" << endl;
    }
    for( Student* stu : students ) {
      stu->display();
    }
  }
  // Clears heapspace by deleting student and setting to null before clearing
  void reset() {
    for( size_t i = 0; i < students.size(); i++ ) {
      delete students[i];
      students[i] = NULL;
    }
    students.clear();
  }
private:
  string section;
  TimeSlot slot;
  vector<Student*> students;
};

class LabWorker {
public:
  LabWorker( const string& workName ) : name( workName ) {}
  void addSection( Section& section ) {
    this->section = &section;
  }
  // Uses section's addGrade function
  void addGrade( const string& name, const int& grade, const int& week ) {
    section->addGrade( name, grade, week );
  }
  // Displays name, then section's display function
  void displayGrades() {
    cout << name << " has ";
    section->display();
    cout << endl;
  }
private:
  string name;
  Section* section;
};

int main() {
  
  // lab workers
   LabWorker moe( "Moe" );
   LabWorker jane( "Jane" );
   
   // sections and setup and testing
   Section secA2( "A2", "Tuesday", 16 );
   //secA2.loadStudentsFromFile( "A2.txt" );
   secA2.addStudent("John");
   secA2.addStudent("George");
   secA2.addStudent("Paul");
   secA2.addStudent("Ringo");

   cout << "\ntest A2\n";    // here the modeler-programmer checks that load worked
   secA2.display();          // YOU'll DO THIS LATER AS: cout << secA2 << endl;
   moe.addSection( secA2 );
   cout << endl;
   moe.displayGrades();       // here the modeler-programmer checks that adding the Section worked
  
   Section secB3( "B3", "Thursday", 11 );
   //secB3.loadStudentsFromFile( "B3.txt" );
   secB3.addStudent("Thorin");
   secB3.addStudent("Dwalin");
   secB3.addStudent("Balin");
   secB3.addStudent("Kili");
   secB3.addStudent("Fili");
   secB3.addStudent("Dori");
   secB3.addStudent("Nori");
   secB3.addStudent("Ori");
   secB3.addStudent("Oin");
   secB3.addStudent("Gloin");
   secB3.addStudent("Bifur");
   secB3.addStudent("Bofur");
   secB3.addStudent("Bombur");

   cout << "\ntest B3\n";    // here the modeler-programmer checks that load worked
   secB3.display();          // YOU'll DO THIS LATER AS: cout << secB3 << endl;
   jane.addSection( secB3 );
   cout << endl;
   jane.displayGrades();      // here the modeler-programmer checks that adding Instructor worked

   
   // setup is complete, now a real world scenario can be written in the code
   // [NOTE: the modeler-programmer is only modeling joe's actions for the rest of the program]

   // week one activities  
   cout << "\nModeling week: 1\n";
   moe.addGrade( "John", 7, 1 );  
   moe.addGrade( "Paul", 9, 1 );  
   moe.addGrade( "George", 7, 1 );  
   moe.addGrade( "Ringo", 7, 1 );  
   cout << "End of week one\n";
   moe.displayGrades();

   // week two activities
   cout << "\nModeling week: 2\n";
   moe.addGrade( "John", 5, 2 );  
   moe.addGrade( "Paul", 10, 2 );  
   moe.addGrade( "Ringo", 0, 2 );  
   cout << "End of week two\n";
   moe.displayGrades();

   //test that reset works  // NOTE: can we check that the heap data was dealt with?
   cout << "\ntesting reset()\n";
   secA2.reset();
   secA2.display();
   moe.displayGrades();
   
} // main
