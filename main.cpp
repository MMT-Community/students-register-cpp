/*
  ! Language: C++
  ! Project: Student Register
  ? Core Concepts:
    * OOP
    * Encapsulation
    * Vectors
    * Console Interface
    * File I/O
    * Exception Handling

  ? Features:
    * Add student
    * View all students
    * Save to file
    * Load from file

  ? Collected Data:
    * Name
    * Age
    * ID

  ? How it Works:
    * Use CLI to get user input
    * Use vectors to store data
    * Use file I/O to save and load data
*/

#include <iostream> // Input/Output to the terminal => cin, cout
#include <vector> // Vector => vector
#include <fstream> // File I/O => fstream
using namespace std;

class Student {

  private:
    // Properties
    string name;
    int age;
    string id;

  public:
    // Constructor
    Student(string n, int a, string i){
      name = n;
      age = a;
      id = i;
    }

    Student() {}

    // Getters
    string getName() const { return name; }
    int getAge() const { return age;}
    string getId() const { return id;}

    // Setters
    void setName(string n) {name = n;}
    void setAge(int a) {age = a;}
    void setId(string i) {id = i;}

    void saveToFile(ofstream &out) const {
      out << name << endl;
      out << age << endl;
      out << id << endl;
    }

    void loadFromFile(ifstream &in) {
      getline(in, name);
      in >> age; 
      in.ignore();
      getline(in, id);
    }

    void display() const {
      cout << "ID: " << id << " | Name: " << name << " | Age: " << age << endl;
    }
};



void addStudent(vector<Student> &students);
void viewStudents(const vector<Student> &students);
void saveToFile(const vector<Student> &Student, const string &filename);
void loadFromFile(vector<Student> &students, const string &filename);

int main() {
  vector<Student> students; // array
  string filename = "students.txt";

  int choice;
  do {
    cout << "\n========< Students Register Menu >========\n";
    cout << "1. Add Student\n";
    cout << "2. View Students\n";
    cout << "3. Save to File\n";
    cout << "4. Load from File\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch(choice){
      case 1:
        addStudent(students);
      break;
      case 2:
        viewStudents(students);
      break;
      case 3:
        saveToFile(students,filename);
      break;
      case 4:
        loadFromFile(students, filename);
      break;
      case 0:
        cout << "Exiting the program..." << endl;
      break;
      default:
        cout << "Invalid choice. Please try again." << endl;
    }



  } while(choice != 0); // choice = 0 => exit

  return 0;
}

void addStudent(vector<Student> &students){
  string name, id;
  int age;
 
  cout << "Enter student name: ";
  getline(cin, name);
  cout << "Enter student age: ";
  cin >> age;
  cin.ignore();
  cout << "Enter student ID: ";
  getline(cin, id);

  Student s(name, age, id);
  students.push_back(s);
  cout << "Student added successfully!" << endl;
}

void viewStudents(const vector<Student> &students){
  if(students.empty()){
    cout << "No students found." << endl;
    return;
  }

  cout << "\n=====< Students List >=====\n";
  for(const Student &s : students){
    s.display(); // id: 20421 | name: mohammed | age: 21
  }
}

void saveToFile(const vector<Student> &students, const string &filename){
  ofstream out(filename);
  if(!out){
    cout << "Error Opening File!\n";
    return;
  }

  out << students.size() << endl;
  for (const Student &s : students){
    s.saveToFile(out);
  }

  out.close();
  cout << "Data Been Saved To: " << filename << " Successfully!" << endl;
}


void loadFromFile(vector<Student> &students, const string &filename){
  ifstream in(filename);
  if(!in){
    cout << "Error Opening File!\n";
    return;
  }
  size_t count;
  in >> count;
  in.ignore();

  students.clear();
  for(size_t i =0; i< count; ++i){
    Student s;
    s.loadFromFile(in);
    students.push_back(s);
  }

  in.close();
  cout << "Data Been Loaded From: " << filename << " Successfully!" << endl;
}
