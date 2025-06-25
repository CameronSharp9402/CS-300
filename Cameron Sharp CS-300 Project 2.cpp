#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Course 
{
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

class CoursePlanner {
private:
    unordered_map<string, Course> courseTable;

public:
    void loadData(const string& filename) 
    {
        courseTable.clear();
        ifstream file(filename);
        if (!file.is_open()) 
        {
            cout << "Error: Unable to open file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) 
        {
            stringstream ss(line);
            string token;
            Course course;

            getline(ss, course.courseNumber, ',');
            getline(ss, course.courseTitle, ',');

            while (getline(ss, token, ',')) 
            {
                course.prerequisites.push_back(token);
            }

            courseTable[course.courseNumber] = course;
        }

        cout << "Courses loaded successfully from " << filename << "." << endl;
    }

    void printCourseList() 
    {
        if (courseTable.empty()) 
        {
            cout << "No course data loaded. Please load data first." << endl;
            return;
        }

        vector<string> keys;
        for (const auto& pair : courseTable) 
        {
            keys.push_back(pair.first);
        }

        sort(keys.begin(), keys.end());

        cout << "\nHere is a sample schedule:\n" << endl;
        for (const auto& key : keys) 
        {
            cout << key << ", " << courseTable[key].courseTitle << endl;
        }
    }

    void printCourseInfo(const string& courseNum) 
    {
        string upperCourse = courseNum;
        transform(upperCourse.begin(), upperCourse.end(), upperCourse.begin(), ::toupper);

        if (courseTable.find(upperCourse) == courseTable.end()) 
        {
            cout << "Course not found." << endl;
            return;
        }

        const Course& course = courseTable[upperCourse];
        cout << "\n" << course.courseNumber << ", " << course.courseTitle << endl;

        if (!course.prerequisites.empty()) 
        {
            cout << "Prerequisites: ";
            for (size_t i = 0; i < course.prerequisites.size(); ++i) 
            {
                cout << course.prerequisites[i];
                if (i < course.prerequisites.size() - 1) cout << ", ";
            }
            cout << endl;
        }
        else 
        {
            cout << "Prerequisites: None" << endl;
        }
    }
};

void displayMenu() 
{
    cout << "\n1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit\n" << endl;
}

int main() 
{
    CoursePlanner planner;
    int choice = 0;
    const string defaultFilename = "CS 300 ABCU_Advising_Program_Input.csv";

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) 
    {
        displayMenu();
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
            planner.loadData(defaultFilename);
            break;
        case 2:
            planner.printCourseList();
            break;
        case 3: 
        {
            cout << "What course do you want to know about? ";
            string courseNum;
            cin >> courseNum;
            planner.printCourseInfo(courseNum);
            break;
        }
        case 9:
            cout << "\nThank you for using the course planner!" << endl;
            break;
        default:
            cout << "\n" << choice << " is not a valid option." << endl;
            break;
        }
    }

    return 0;
}