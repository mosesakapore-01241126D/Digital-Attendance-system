#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Student {
public:
    string name;
    string indexNumber;

    Student(string n, string i) {
        name = n;
        indexNumber = i;
    }
};

#include <map>

class AttendanceSession {
public:
    string courseCode;
    string date;
    string startTime;
    int duration;

    map<string, string> attendance;

    AttendanceSession(string code, string d, string time, int dur) {
        courseCode = code;
        date = d;
        startTime = time;
        duration = dur;
    }
};
vector<Student> students;
void saveStudentsToFile() {
    ofstream file("students.txt");

    for (int i = 0; i < students.size(); i++) {
        file << students[i].name << ","
             << students[i].indexNumber << endl;
    }

    file.close();
}
vector<AttendanceSession> sessions;

void addStudent() {
    string name;
    string index;

    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Index Number: ";
    getline(cin, index);

    students.push_back(Student(name, index));
saveStudentsToFile();

cout << "Student added successfully!\n";
}   

void loadStudentsFromFile() {
    ifstream file("students.txt");
    string name, index;

    while (getline(file, name, ',') && getline(file, index)) {
        students.push_back(Student(name, index));
    }

    file.close();
}

void viewStudents() {
    cout << "\nRegistered Students:\n";

    for (int i = 0; i < students.size(); i++) {
        cout << students[i].name << " - "
             << students[i].indexNumber << endl;
    }
}
void createSession() {
    string code, date, time;
    int duration;

    cout << "Enter Course Code: ";
    cin >> code;

    cout << "Enter Date (YYYY-MM-DD): ";
    cin >> date;

    cout << "Enter Start Time (HH:MM): ";
    cin >> time;

    cout << "Enter Duration (hours): ";
    cin >> duration;

    sessions.push_back(AttendanceSession(code, date, time, duration));

    cout << "Lecture session created successfully!\n";
}
void markAttendance() {
    if (sessions.empty()) {
        cout << "No sessions available.\n";
        return;
    }

    cout << "\nAvailable Sessions:\n";
    for (int i = 0; i < sessions.size(); i++) {
        cout << i << ". "
             << sessions[i].courseCode
             << " - "
             << sessions[i].date << endl;
    }

    int index;
    cout << "Select session number: ";
    cin >> index;

    if (index < 0 || index >= sessions.size()) {
        cout << "Invalid session number.\n";
        return;
    }

    for (int i = 0; i < students.size(); i++) {
        string status;
        cout << "Mark attendance for "
             << students[i].name
             << " (P/A/L): ";
        cin >> status;

        if (status == "P")
            sessions[index].attendance[students[i].indexNumber] = "Present";
        else if (status == "A")
            sessions[index].attendance[students[i].indexNumber] = "Absent";
        else if (status == "L")
            sessions[index].attendance[students[i].indexNumber] = "Late";
        else
            sessions[index].attendance[students[i].indexNumber] = "Absent";
    }

    cout << "Attendance marked successfully!\n";
}void showAttendanceSummary() {
    if (sessions.empty()) {
        cout << "No sessions available.\n";
        return;
    }

    cout << "\nAvailable Sessions:\n";
    for (int i = 0; i < sessions.size(); i++) {
        cout << i << ". "
             << sessions[i].courseCode
             << " - "
             << sessions[i].date << endl;
    }

    int index;
    cout << "Select session number: ";
    cin >> index;

    if (index < 0 || index >= sessions.size()) {
        cout << "Invalid session number.\n";
        return;
    }

    int present = 0, absent = 0, late = 0;

    for (auto record : sessions[index].attendance) {
        if (record.second == "Present")
            present++;
        else if (record.second == "Absent")
            absent++;
        else if (record.second == "Late")
            late++;
    }

    cout << "\nAttendance Summary:\n";
    cout << "Present: " << present << endl;
    cout << "Absent: " << absent << endl;
    cout << "Late: " << late << endl;
}
int main() {
    loadStudentsFromFile();

    int choice;


    do {
       cout << "1. Add Student\n";
       cout << "2. View Students\n";
       cout << "3. Create Lecture Session\n";
       cout << "4. Mark Attendance\n";
       cout << "5. Show Attendance Summaary\n";
       cout << "6. Exit\n";
       cout << "Choose an option: ";
       cin >> choice;

        switch(choice) {
    case 1:
        addStudent();
        break;
    case 2:
        viewStudents();
        break;
    case 3:
        createSession();
        break;
    case 4:
        markAttendance();
        break;    
    case 5: 
         showAttendanceSummary();
         break;
    case 6:
        cout << "Exiting program...\n";
        break;
    default:
        cout << "Invalid choice. Try again.\n";
}

    } while(choice != 6);

    return 0;
}

