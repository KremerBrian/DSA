/* 
ProjectTwo.cpp
Brian Kremer
June-23-2024
*/

#include <iostream> 
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;		//namespace declaration

//setting up the structure for course information
struct Course {
	string courseNumber;
	string courseTitle;
	vector<string> prerequisites;
};

vector<Course> courses;			//the vector storing course objects

//Function that loads the file data into the course vector.
void loadDataStructure(const string& fileName) {
	ifstream file(fileName);										//Opens file 
	if (!file.is_open()) {											//confirming the file is opened
		cout << "ERROR. Cannot open file " << fileName << endl;		//prints error message if file doesnt open
		return;
	}

	string line;										//string that stores each line of the file
	while (getline(file, line)) {						//reading each line of the file
		Course course;									//starting a course object for storing course data
		size_t pos = line.find(",");					//finds the postion of our first comma in the file
		course.courseNumber = line.substr(0, pos);		//extracting the course number
		line.erase(0, pos + 1);							//erasing the extracted portion from the line
		pos = line.find(",");							//finding the next comma
		course.courseTitle = line.substr(0, pos);		//extracting course title
		line.erase(0, pos + 1);							//erasing the extracted portion of the line

		//extracting and storing prerequisites
		while (!line.empty()) {
			pos = line.find(",");								//finding the next comma
			string prerequisite = line.substr(0, pos);			//extrating prerequisite
			course.prerequisites.push_back(prerequisite);		//stroing prerequisite
			if (pos == string::npos) break;						//if theres no more commas then we can exit the loop
			line.erase(0, pos + 1);								//erasing the extracted portion from the line
		}

		courses.push_back(course);			//add the course objects to the course vector

	}

	file.close();			//closing the file 
}

//function to print courses in an alphanumeric ordered list
void printCourseList() {
	//sorting courses vector based off their course numbers
	sort(courses.begin(), courses.end(), [](const Course& a, const Course& b) {
		return a.courseNumber < b.courseNumber;
		});

	cout << "Here's a list of courses: " << endl;			//printing the header of course list 
	//loop through each course and porint its number and title
	for (const auto& course : courses) {
		cout << course.courseNumber << ", " << course.courseTitle << endl;
	}
}

//function to print information on one course
void printCourse(const string& courseNumber) {
	//finding the course with the given course number
	auto it = find_if(courses.begin(), courses.end(), [&](const Course& c) {
		return c.courseNumber == courseNumber;
	});

	if (it != courses.end()) {											//checking if the course is found
		cout << it->courseNumber << ", " << it->courseTitle << endl;	//printing the course number and title
		cout << "Prerequisites: ";										//printing the header for prerequisites list
		if (it->prerequisites.empty()) {								//check if there are prerequsites
			cout << "None" << endl;										//printing None if theres no prerequisites
		}
		else {
			//loop through the prerequisites and print each one
			for (const auto& prerequisite : it->prerequisites) {
				cout << prerequisite << ", ";
			}
			cout << endl;
		}
	}
	else {										//if the course isnt found
		cout << "Course not found. " << endl;	//print the message for unfound course
	}
}

int main() {
	string fileName;		//string for file name
	int choice;				//integer to store the users choice
	string courseNumber;	//string to store course number

	cout << "Welcome to the course planner. " << endl;	//print the welcome message
	do {												//string the do-while loop
														//showing the menu options and prompting the user for a choice
		cout << "1. Load Data Structure." << endl;
		cout << "2. Print Course List." << endl;
		cout << "3. Print Course. " << endl;
		cout << "4. Exit" << endl; 
		cout << "What would you like to do?";
		cin >> choice;									//User's choice

		switch (choice) {						//switch statement based on users choice
			case 1:									//option 1 for user
				cout << "Enter the file name: ";	//prompt for the file name
				cin >> fileName;					//read the input file name
				loadDataStructure(fileName);		//call function to load the file data
				break;								//exit switch statement
			case 2:										//option 2 for user
				printCourseList();						//call function to print the course list
				break;									//exit switch statement
			case 3:														//option 3 for the user
				cout << "What course do you want to know about? ";		//prompt for course number
				cin >> courseNumber;									//read course number from the user
				printCourse(courseNumber);								//call function to print the course info
				break;													//exiting switch statement
			case 4:															//option 4 for user
				cout << "Thank you for using the course planner!" << endl;	//printing thank you to user
				break;														//exiting the switch statement
			default:														//outcome of the user choosing an invalid option
				cout << choice << " isn't a valid option." << endl;			//print invalid input message 
		}
	} while (choice != 4);	//the loop continues until the user selects exit

	return 0;				//return 0 for proof of successful execution
}