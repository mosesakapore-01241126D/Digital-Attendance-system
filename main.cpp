#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>
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
#include <sstream>
void saveSessionsToFile() {
    ofstream file("sessions.txt");

    for (int i = 0; i < sessions.size(); i++) {
        file << sessions[i].courseCode << ","
             << sessions[i].date << ","
             << sessions[i].startTime << ","
             << sessions[i].duration << endl;

        for (auto record : sessions[i].attendance) {
            file << record.first << ","
                 << record.second << endl;
        }

        file << "END" << endl;
    }

    file.close();
}void loadSessionsFromFile() {
    ifstream file("sessions.txt");
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        string code, date, time;
        int duration;

        stringstream ss(line);
        getline(ss, code, ',');
        getline(ss, date, ',');
        getline(ss, time, ',');
        ss >> duration;

        AttendanceSession session(code, date, time, duration);

        while (getline(file, line) && line != "END") {
            string index, status;
            stringstream ss2(line);
            getline(ss2, index, ',');
            getline(ss2, status);

            session.attendance[index] = status;
        }

        sessions.push_back(session);
    }

    file.close();
}
#include <iomanip> // for setw if needed

void exportToExcel() {
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
    cout << "Select session number to export: ";
    cin >> index;

    if (index < 0 || index >= sessions.size()) {
        cout << "Invalid session number.\n";
        return;
    }

    // Create CSV file
    string filename = sessions[index].courseCode + "_" + sessions[index].date + ".csv";
    ofstream file(filename);

    // Write headers
    file << "Index Number,Student Name,Attendance Status\n";

    for (int i = 0; i < students.size(); i++) {
        string status = "Absent"; // default
        if (sessions[index].attendance.count(students[i].indexNumber)) {
            status = sessions[index].attendance[students[i].indexNumber];
        }

        file << students[i].indexNumber << ","
             << students[i].name << ","
             << status << "\n";
    }

    file.close();
    cout << "Exported to Excel-compatible CSV: " << filename << endl;
}
int main() {
    loadStudentsFromFile();
    loadSessionsFromFile();

    int choice;


    do {
       cout << "1. Add Student\n";
       cout << "2. View Students\n";
       cout << "3. Create Lecture Session\n";
       cout << "4. Mark Attendance\n";
       cout << "5. Show Attendance Summaary\n";
       cout << "6. Export Session to Excel\n";
       cout << "7. Exit\n";
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
        saveSessionsToFile();
        break;
    case 4:
        markAttendance();
        saveSessionsToFile();
        break;    
    case 5: 
         showAttendanceSummary();
         break;
    case 6:
         exportToExcel();
         break;
    case 7:
        cout << "Exiting program...\n";
        break;
    default:
        cout << "Invalid choice. Try again.\n";
}

    } while(choice != 7);

    return 0;
}

