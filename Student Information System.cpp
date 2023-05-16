#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>
#include <chrono>
#include <sstream>
#include "md5.h"
#include "md5.cpp"
#include <algorithm>
using namespace std;





//Structures
struct date {
	string day;
	string startTime;
	string endTime;
};

struct course {
	string courseID;
	int classNumber = 0;
	string courseName;
	string courseCredits;
	string prerequiste;
	int capacity = 0;
	date d;
};

struct student {
	string studentID;
	string firstName;
	string lastName;
	string password;
	string phone;
	string email;
	int nbCourses = 0;
	course* c = 0;
};







//Related to the home page
void ClearScreen() {
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void WelcomePage() {

	cout << "----------------------------------------------------------------------------------------" << endl;
	cout << "------------------------------ STUDENT INFORMATION SYSTEM ------------------------------" << endl;
	cout << "----------------------------------------------------------------------------------------" << endl << endl;
	cout << "   1 - PRESS 1 TO SIGN IN" << endl << endl << "----------------------------------------------------------------------------------------" << endl;
	cout << "----------------------------------------------------------------------------------------" << endl << endl;
	cout << "   2 - PRESS 2 TO REGISTER" << endl << endl << "----------------------------------------------------------------------------------------" << endl;
	cout << "----------------------------------------------------------------------------------------" << endl << endl;
}




//Related to Password Checker
bool Length(string password) {
	bool check = false;
	int length = password.length();

	if (length >= 8)
		check = true;

	return check;
}

bool SpecialCharacters(string Password) {
	bool check = false;
	int counter = 0;
	for (unsigned int i = 0; i < Password.length(); i++) {
		if (Password[i] == '@' || Password[i] == '!' || Password[i] == '#' || Password[i] == '$' || Password[i] == '%' ||
			Password[i] == '&' || Password[i] == '*') {
			counter++;
		}
	}
	if (counter >= 1)
		check = true;

	return check;
}

bool UpperCases(string password) {
	bool check = false;
	int counter = 0;

	for (unsigned int i = 0; i < password.length(); i++) {
		if (password[i] >= 65 && password[i] <= 90)
			counter++;
	}
	if (counter >= 1)
		check = true;

	return check;
}

bool LowerCases(string password) {
	bool check = false;
	int counter = 0;

	for (unsigned int i = 0; i < password.length(); i++) {
		if (password[i] >= 97 && password[i] <= 122)
			counter++;
	}
	if (counter >= 1)
		check = true;

	return check;
}

bool Numbers(string password) {
	bool check = false;
	int counter = 0;

	for (unsigned int i = 0; i < password.length(); i++) {
		if (password[i] == '0' || password[i] == '1' || password[i] == '2' || password[i] == '3' || password[i] == '4' ||
			password[i] == '5' || password[i] == '6' || password[i] == '7' || password[i] == '8' || password[i] == '9')
			counter++;
	}
	if (counter >= 1)
		check = true;

	return check;
}

void verifyPassword(string password) {

	if (Length(password) == false)
		cout << "     Your password is too short" << endl << endl;
	else if (SpecialCharacters(password) == false)
		cout << "     Add special characters" << endl << endl;
	else if (Numbers(password) == false)
		cout << "     Add numbers" << endl << endl;
	else if (UpperCases(password) == false)
		cout << "     Add upper cases" << endl << endl;
	else if (LowerCases(password) == false)
		cout << "     Add lower cases" << endl << endl;

}




//Related to Phone Number Verification
bool phonenumb_Validation(string phoneNumb) {
	string Valid_PhoneNums[] = { "70","76","71","78","79","81","03" };

	for (int i = 0; i < 7; i++) {
		if (phoneNumb.substr(0, 2) == Valid_PhoneNums[i]) {
			return true;
		}

	}
	return false;
}




//Related to the Id Generator
string getCurrentMonth() {
	time_t now = time(nullptr);
	tm* timePtr = localtime(&now);

	string month = to_string(timePtr->tm_mon + 1);


	return month;
}

string getCurrentYear() {
	time_t now = time(nullptr);
	tm* timePtr = localtime(&now);

	string year = to_string(timePtr->tm_year + 1900);

	return year;
}

string idGenerator() {


	int nbOfstPerMonth = 0;
	ifstream file("nbOfstPerMonth.csv");
	string line;


	if (file.is_open()) {
		getline(file, line);
		nbOfstPerMonth = stoi(line);
		file.close();
	}


	time_t now = time(0);
	tm* date = localtime(&now);
	int year = date->tm_year + 1900;
	int month = date->tm_mon + 1;

	string yearStr = to_string(year);
	string monthStr = (month < 10 ? "0" : "") + to_string(month);

	string nbOfstd = to_string(nbOfstPerMonth);
	while (nbOfstd.length() < 3) {
		nbOfstd = "0" + nbOfstd;
	}

	string ID = yearStr + monthStr + nbOfstd;

	ofstream outfile("nbOfstPerMonth.csv");
	outfile << nbOfstPerMonth + 1;
	outfile.close();

	return ID;
}




//Search User Info
bool searchStudentID(const string& id) {

	ifstream StudentData("students.csv");

	if (!StudentData) {
		cout << "Failed to open file\n";
		return false;

	}

	string line;

	while (getline(StudentData, line)) {
		// to search for the ID in each line in the file
		if (line.find(id + ",") == 0) {
			// ID found
			StudentData.close();
			return true;
		}
	}
	return false;
	StudentData.close();
}

bool searchStudentPW(const string& ID, const string& PW) {
	ifstream StudentData("students.csv");
	if (!StudentData) {
		cout << "Failed to open file\n";
		return false;
	}

	string line;
	while (getline(StudentData, line)) {
		// to search for the ID and password in each line in the file
		if (line.find(ID + ',' + md5(PW) + ',') == 0) {
			// ID and password match
			StudentData.close();
			return true;
		}
	}
	StudentData.close();
	return false;
}





//Related to Email Verification
bool EmailVerification(string email, string Id) {

	string suffix = "@ua.edu.lb";

	if (email.find(Id) >= 0 && email.find(Id) < email.length() && email.find(suffix) >= 0
		&& email.find(suffix) < email.length())
		return true;

	return false;
}




//Related to Student
void Register(student* s, int& NbofStudents) {

	student newStudent;

	fstream StudentData("students.csv", ios::out | ios::app | ios::in);

	//Form
	cout << "----------------------------------------------------------------------------------------" << endl;
	cout << "----------------------------------------" << "REGISTER" << "----------------------------------------" << endl;
	cout << "----------------------------------------------------------------------------------------" << endl << endl;




	//Input First name and Last name
	cin.ignore();
	cout << "  Enter your first name : ";
	getline(cin, newStudent.firstName);
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "  Enter your lastname : ";
	getline(cin, newStudent.lastName);
	cout << "-------------------------------------------------------------------------------" << endl;




	//Input password and verification
	do {
		cout << "  Enter your password :";
		getline(cin, newStudent.password);
		verifyPassword(newStudent.password);

	} while (Length(newStudent.password) == false || SpecialCharacters(newStudent.password) == false ||
		UpperCases(newStudent.password) == false || LowerCases(newStudent.password) == false || Numbers(newStudent.password) == false);
	cout << endl << "-------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------" << endl << endl;




	//Generate a unique ID
	newStudent.studentID = idGenerator();
	cout << "  Your student ID will be : " << newStudent.studentID << endl;
	cout << endl << "-------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------" << endl << endl;




	//Input Email Address and verify
	cout << "  Enter you email address: ";
	getline(cin, newStudent.email);

	while (EmailVerification(newStudent.email, newStudent.studentID) == false) {
		cout << "  ERROR! Your email address should contain your student ID and ends with @ua.edu.lb" << endl << endl;
		cout << "  Enter your email address: ";
		getline(cin, newStudent.email);
	}
	cout << "-------------------------------------------------------------------------------" << endl;



	//Input Phone number and verify Format
	cout << "  Enter your phone number: +961 ";
	getline(cin, newStudent.phone);
	phonenumb_Validation(newStudent.phone);

	while (newStudent.phone.length() != 8 || phonenumb_Validation(newStudent.phone) == false) {
		cout << "    Wrong Format! Please Try Again: ";
		getline(cin, newStudent.phone);
	}



	cout << endl << "----------------------------------------------------------------------------------------" << endl;
	cout << "----------------------------------------------------------------------------------------" << endl;
	cout << "----------------------------------------------------------------------------------------" << endl << endl;
	cout << "YOU HAVE BEEN SUCCESSFULLY REGISTERED!" << endl;
	cout << "-------------------------------------------------------------------------------" << endl << endl;


	StudentData << newStudent.studentID << ',' << md5(newStudent.password) << ',' << newStudent.firstName << ',' << newStudent.lastName << ',' << newStudent.email << ',' << newStudent.phone << endl;


	NbofStudents++;


	fstream nbOfStudents("nbOfStudents.csv", ios::in | ios::out);
	nbOfStudents << NbofStudents;

	nbOfStudents.close();

}


void SignIn(student* s, int& NbofStd, string& SID) {

	fstream file("students.csv", ios::in | ios::app | ios::out);

	cout << "----------------------------------------------------------------------------------------" << endl;
	cout << "----------------------------------------" << " LogIn " << "-----------------------------------------" << endl;
	cout << "----------------------------------------------------------------------------------------" << endl << endl;

	cin.ignore();


	string input_id;
	bool found = false;

	while (!found) {
		cout << "Enter your ID: ";
		getline(cin, input_id);

		found = searchStudentID(input_id);
		if (!found) {
			if (input_id == "0")
			{
				break;
				break;
			}

			cout << "Invalid ID, Try Again or Press 0 to Exit" << endl;
			cout << "--------------------------------------------------------------------------------" << endl;


		}
	}

	if (found) {
		cout << "Proceeding..." << endl;
		SID = input_id;
		cout << "--------------------------------------------------------------------------------" << endl;
		string input_pw;
		bool found_pw = false;
		while (!found_pw) {


			cout << "Enter your password: ";
			getline(cin, input_pw);


			found_pw = searchStudentPW(input_id, input_pw);
			if (!found_pw) {
				cout << "Incorrect password. Try again:(Press 0 to Exit) " << endl;
				if (input_pw == "0") {
					break;
				}

			}
		}

	}
}

int GetNbofStudents() {

	int nbOfStudents = 0;

	fstream file("nbOfStudents.csv", ios::out | ios::in);
	string line;



	if (file.is_open()) {
		getline(file, line);
		nbOfStudents = stoi(line);
	}

	return nbOfStudents;

	file << nbOfStudents + 1;
	file.close();



}

void LoadCourses(course*& c, int& NbOfCourses) {
	ifstream nbOfCourses("nbOfCourses.csv");
	ifstream coursesFile("Courses.csv");

	if (nbOfCourses.is_open()) {
		nbOfCourses >> NbOfCourses;
	}
	else {
		// Handle file opening error
		cerr << "Error opening nbOfCourses.csv" << endl;
		return;
	}

	if (coursesFile.is_open()) {
		c = new course[NbOfCourses];
		string line;
		int lineCount = 0; // Track the current line number

		while (getline(coursesFile, line)) {
			stringstream ss(line);

			// Check if line is empty or consists only of whitespace
			if (line.find_first_not_of(' ') == string::npos)
				continue;
			

			getline(ss, c[lineCount].courseID, ',');
			ss >> c[lineCount].classNumber;
			ss.ignore(1000, ',');
			getline(ss, c[lineCount].courseName, ',');
			getline(ss, c[lineCount].courseCredits, ',');
			getline(ss, c[lineCount].prerequiste, ',');
			ss >> c[lineCount].capacity;
			ss.ignore(1000, ',');
			getline(ss, c[lineCount].d.day, ',');
			getline(ss, c[lineCount].d.startTime, ',');
			getline(ss, c[lineCount].d.endTime, ',');

			++lineCount;
		}

		coursesFile.close();

		// Reduce NbOfCourses based on the number of valid lines
		NbOfCourses = lineCount;
	}
	else {
		// Handle file opening error
		cerr << "Error opening Courses.csv" << endl;
	}

	nbOfCourses.close();
}

//void LoadRegCourse(course*& regCourses, int& numOfRegCourses) {
//	ifstream regCourseFile("RegisteredCourses.csv");
//
//	if (!regCourseFile) {
//		cerr << "Error opening RegisteredCourses.csv" << endl;
//		return;
//	}
//
//	string line;
//	numOfRegCourses = 0;
//
//	// Count the number of valid lines in the file
//	while (getline(regCourseFile, line)) {
//		// Check if line is empty or consists only of whitespace
//		if (line.find_first_not_of(' ') != string::npos) {
//			++numOfRegCourses;
//		}
//	}
//
//	// Allocate memory for the regCourses array
//	regCourses = new course[numOfRegCourses];
//
//	// Reset file stream to the beginning
//	regCourseFile.clear();
//	regCourseFile.seekg(0, ios::beg);
//
//	int lineCount = 0;
//
//	// Read the first 6 characters from each line and store them in the classNumber field
//	while (getline(regCourseFile, line)) {
//		if (line.find_first_not_of(' ') != string::npos) {
//			string classNumString = line.substr(0, 6);
//			regCourses[lineCount].classNumber = stoi(classNumString);
//			++lineCount;
//		}
//	}
//
//	regCourseFile.close();
//}

void AddCourse(course* c, int& NbofCourses) {

	course newCourse;
	string courseID;
	int classNumber = 0; // modified recently

	fstream file("Courses.csv", ios::in | ios::app | ios::out);


	ClearScreen();


	cout << "----------------------------------------------------------------------------------------" << endl;
	cout << "------------------------------ STUDENT INFORMATION SYSTEM ------------------------------" << endl;
	cout << "----------------------------------------------------------------------------------------" << endl << endl;




	cin.ignore();
	cout << "Enter the ID course  : ";
	getline(cin, newCourse.courseID);

	cout << "----------------------------------------------------------------------------------------" << endl;

	cout << "Enter the class number : ";
	cin >> newCourse.classNumber;
	while (newCourse.classNumber < 0) {
		cout << "ERROR! Enter a valid number: ";
		cin >> newCourse.classNumber;
	}
	cout << "----------------------------------------------------------------------------------------" << endl;


	cout << "Enter the name of the course : ";
	cin.ignore();
	getline(cin, newCourse.courseName);
	cout << "----------------------------------------------------------------------------------------" << endl;


	cout << "Enter the credits of the course : ";
	getline(cin, newCourse.courseCredits);
	while (newCourse.courseCredits != "1" && newCourse.courseCredits != "3" && newCourse.courseCredits != "1 Credit"
		&& newCourse.courseCredits != "3 Credits" && newCourse.courseCredits != "1 credit"
		&& newCourse.courseCredits != "3 credits") {
		cout << "ERROR! 1 Credit or 3 Credits : ";
		getline(cin, newCourse.courseCredits);
	}
	cout << "----------------------------------------------------------------------------------------" << endl;


	cout << "Enter the prerequiste of the course : ";
	getline(cin, newCourse.prerequiste);
	cout << "----------------------------------------------------------------------------------------" << endl;


	cout << "Enter the maximum capacity of the course : ";
	cin >> newCourse.capacity;
	while (newCourse.capacity < 0 && newCourse.capacity > 100) {
		cout << "ERROR! Capacity should be between 1 and 100";
		cin >> newCourse.capacity;
	}
	cout << "----------------------------------------------------------------------------------------" << endl;


	cout << "Enter the day of the course : ";
	cin.ignore();
	getline(cin, newCourse.d.day);
	cout << "----------------------------------------------------------------------------------------" << endl;


	cout << "Enter the start time of the course : ";
	getline(cin, newCourse.d.startTime);
	cout << "----------------------------------------------------------------------------------------" << endl;


	cout << "Enter the end time of the course : ";
	getline(cin, newCourse.d.endTime);
	cout << "----------------------------------------------------------------------------------------" << endl;

	file << newCourse.courseID << ',' << newCourse.classNumber << ',' << newCourse.courseName << ',' << newCourse.courseCredits << ','
		<< newCourse.prerequiste << ',' << newCourse.capacity << ',' << newCourse.d.day << ',' << newCourse.d.startTime << ',' << newCourse.d.endTime << endl;



	file.close();

	NbofCourses++;


	fstream nbOfCourses("nbOfCourses.csv", ios::in | ios::out);
	nbOfCourses << NbofCourses;

	nbOfCourses.close();

}

void RemoveCourse(course* c, int& NbofCourses) {

	fstream file("Courses.csv", ios::in | ios::out | ios::app);
	string courseID, courseName, courseCredits, prerequiste, day, startTime, endTime;
	int classNumber = 0, capacity = 0, removeClassNumber = 0;
	course* allCourses = new course[NbofCourses];
	//course* allcourses;

	string line;
	ClearScreen();

	cout << "----------------------------------------------------------------------------------------" << endl;
	cout << "------------------------------ STUDENT INFORMATION SYSTEM ------------------------------" << endl;
	cout << "----------------------------------------------------------------------------------------" << endl << endl;
	cout << "  LIST OF COURSES: " << endl << endl;
	cout << "----------------------------------------------------------------------------------------" << endl;


	while (file) {
		getline(file, line, '\n');
		cout << line << endl << endl;
	}
	LoadCourses(allCourses, NbofCourses);
	cout << "----------------------------------------------------------------------------------------" << endl;
	cout << "Enter the number of the class you want to remove: ";
	cin >> removeClassNumber;

	for (int j = 0; j <= NbofCourses; j++) {
		if (removeClassNumber == allCourses[j].classNumber) {
			for (int i = j; i <= NbofCourses; i++) {
				allCourses[i].courseID = allCourses[i + 1].courseID;
				allCourses[i].classNumber = allCourses[i + 1].classNumber;
				allCourses[i].courseName = allCourses[i + 1].courseName;
				allCourses[i].courseCredits = allCourses[i + 1].courseCredits;
				allCourses[i].prerequiste = allCourses[i + 1].prerequiste;
				allCourses[i].capacity = allCourses[i + 1].capacity;
				allCourses[i].d.day = allCourses[i + 1].d.day;
				allCourses[i].d.startTime = allCourses[i + 1].d.startTime;
				allCourses[i].d.endTime = allCourses[i + 1].d.endTime;
			}

		}
	}

	NbofCourses--;

	file.clear();

	for (int i = 0; i <= NbofCourses; i++) {
		file << allCourses[i].courseID << ',' << allCourses[i].classNumber << ',' << allCourses[i].courseName << ','
			<< allCourses[i].courseCredits << ',' << allCourses[i].prerequiste << ',' << allCourses[i].capacity << ','
			<< allCourses[i].d.day << ',' << allCourses[i].d.startTime << ',' << allCourses[i].d.endTime << endl;
	}


	fstream nbOfCourses("nbOfCourses.csv", ios::in | ios::out);
	nbOfCourses << NbofCourses;

	nbOfCourses.close();


	file.close();

}

void ModifyCourse(course* c, int& NbofCourses) {

	ClearScreen();


	cout << "----------------------------------------------------------------------------------------" << endl;
	cout << "------------------------------ STUDENT INFORMATION SYSTEM ------------------------------" << endl;
	cout << "----------------------------------------------------------------------------------------" << endl << endl;




}

void CoursesToFile(course* c, int& NbofCourses, string filename) {

	fstream file(filename, ios::in | ios::out | ios::app);
	ofstream NbOfCoursesFile("nbOfCourses.csv");
	string line;

	NbOfCoursesFile << NbofCourses;

	if (!file.is_open()) {
		cout << "Error opening file!" << endl;
		return;
	}

	for (int i = 0; i < NbofCourses; i++) {
		file << c[i].courseID << ',' << c[i].classNumber << ',' << c[i].courseName << ',' << c[i].courseCredits
			<< ',' << c[i].d.day << ',' << c[i].d.startTime << ',' << c[i].d.endTime << ','
			<< c[i].prerequiste << ',' << c[i].capacity << endl;
	}

	file.close();
	NbOfCoursesFile.close();

	cout << "----------------------------------------------------------------------------------------" << endl;
	cout << "Course Added To The File Successfully!";
}

int GetNbofCourses() {
	fstream file("nbOfCourses.csv", ios::out | ios::in);
	string line;
	int nbOfCourses = 0;

	if (file.is_open()) {
		getline(file, line);
		nbOfCourses = stoi(line);
	}

	return nbOfCourses;
	file << nbOfCourses + 1;
	file.close();


}

void RegCoursesToFile(int classnumber, string filename, string SID) {
	
	fstream file(filename, ios::in | ios::out | ios::app);


	if (!file.is_open()) {
		cout << "Error opening file!" << endl;
		return;
	}
	string line;
	streampos lineStartPos = 0;
	streampos valuePos;

	// haw byestaamalo la temshe bel file as stream w tekhod l  position tabaa l cursor bel file 
	while (getline(file, line)) {
		stringstream SS(line);
		string value;
		bool valueFound = false;

		while (getline(SS, value, ',')) {
			int variable = stoi(value);
			// i will cout Class number Found here just to check if it's working
			// w hon aamelneha string rje3na hawalna la integer la2an mostly l values bel files bi kouno string w ahyan eza badna naaml 
			// handle lal error aw barke ma ken fi valid integer bel file
			if (variable == classnumber) {
				valueFound = true;
				//break;
				cout << "Class Number Found!:" << classnumber << endl;
				system("pause");

			}
			valuePos = file.tellg();

		}
		if (valueFound) {
			file.seekg(valuePos);
			// puts the file pointer to the position t hat value is found in 
			file << SID << ",";
			// bade et2akad hon eza rah taamel shifting aw overrite
			// 
			// stores the id in front of the class number
			break;
			//file.seekp(0, ios::end);
				// retakes the file pointer to the end of the line to continue the loop until file is read totaly
			// not necessary because when SID is appended then my purpose is done from this function
		}

		if (!valueFound) {
			// Append the new line at the end of the file
			file.seekp(0, ios::end);
			file << classnumber << "," << SID << endl;
		}

		//	lineStartPos = file.tellg();
	}
	file.close();
}

void GetCoursesFromRegFile(string filename, string SID) { // this function will display all courses the student is enrolled in
	fstream file(filename, ios::out | ios::in | ios::app);
	string line;
	if (file.is_open())
	{

		while (getline(file, line))
		{
			if (!line.empty()) {
				size_t found = line.find(SID);
				if (found != string::npos) {
					// Extract the class number from the beginning of the line
					string classNumber = line.substr(0, 4);
					cout << "Class number: " << classNumber << endl;
				}

			}
		}



		file.close();
	}
	else {
		cout << "Unable to open the file." << endl;
	}
}


bool SearchforClassNumInRCourse(int classnum, string filename, string& foundline) {
	fstream file(filename, ios::in | ios::out | ios::app);
	string line;
	if (file.is_open()) {
		while (getline(file, line)) {
			size_t found = line.find(classnum);
			if (found != string::npos) {
				// Class number found in the line
				return true;
				foundline = line;
			}

		}
		return false;

		file.close();
	}
	else {
		return false;
	}
}

void removeStudentID(const string& filePath, const int& classNumber, const string& studentID) {
	ifstream inputFile(filePath);
	ofstream outputFile("temp.csv");
	string line;

	if (inputFile.is_open() && outputFile.is_open()) {
		while (getline(inputFile, line)) {
			istringstream iss(line);
			int currentClassNumber;  // Updated data type
			char colon;
			if (iss >> currentClassNumber >> colon && currentClassNumber == classNumber) {  // Comparison modified
				// Class number found in the line, remove student ID
				ostringstream updatedLine;
				string token;
				bool firstID = true;

				while (iss >> token) {
					if (token != studentID) {
						if (!firstID) {
							updatedLine << ' ';
						}
						updatedLine << token;
						firstID = false;
					}
				}

				// Rewrite the line to the output file
				outputFile << currentClassNumber << colon << ' ' << updatedLine.str() << '\n';
			}
			else {
				outputFile << line << '\n';  // No changes, copy the line as is
			}
		}

		inputFile.close();
		outputFile.close();

		// Replace the original file with the updated contents
		remove(filePath.c_str());
		rename("temp.csv", filePath.c_str());
	}
	else {
		cout << "Unable to open the file." << endl;
	}
}
void searchStudentByID(const std::string& studentID) {
	std::ifstream file("RegisteredCourse.csv");

	if (!file) {
		std::cerr << "Error opening RegisteredCourse.csv" << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		// Split the line by comma
		size_t pos = line.find(',');
		if (pos != std::string::npos) {
			std::string currentID = line.substr(0, pos);
			if (currentID == studentID) {
				std::cout << line << std::endl;
				file.close();
				return;
			}
		}
	}

	std::cout << "Student ID not found." << std::endl;

	file.close();
}
void ArrToFile(course*& c, int& NbofCourses) {
	ofstream file("Courses.csv", ios::out);

	if (!file.is_open()) {
		cout << "Error opening file!" << endl;
		return;
	}

	for (int i = 0; i < NbofCourses; i++) {
		file << c[i].courseID << ',' << c[i].classNumber << ',' << c[i].courseName << ',' << c[i].courseCredits << ',' <<
			c[i].prerequiste << ',' << c[i].capacity << ',' << c[i].d.day << ',' << c[i].d.startTime << ',' << c[i].d.endTime << endl;
	}
}

void EnrollCourse(course*& c,course& SelectedCourse, int& nbOfCourses,int course_index,string addchoice1,string SID){
ClearScreen();
fstream file("Courses.csv", ios::in | ios::out | ios::app);
string line;
cout << "Choose One Of The Following Courses To Enroll By Entering It's Class Number: " << endl;

system("pause");
while (file) {
	getline(file, line, '\n');
	cout << line << endl << endl;
}
do {
	cin >> SelectedCourse.classNumber;
	for (int i = 0; i < nbOfCourses; i++) {
		if (c[i].classNumber == SelectedCourse.classNumber && c[i].capacity > 0) {
			course_index = i;
		}


	}

	if (course_index != -1) {
		cout << "Are You Sure You Want To Enroll " << endl << c[course_index].courseID
			<< " Course In The Following Date: " << c[course_index].d.day << '\t' << c[course_index].d.startTime << '\t' << c[course_index].d.endTime;
		cout << endl << "(Yes / No)";
		cin >> addchoice1;
		if (addchoice1 == "Yes" || addchoice1 == "yes")
			cout << "Course Added Successfully !" << endl;
		system("pause");
		c[course_index].capacity--;
		ArrToFile(c, nbOfCourses);
		// hon lezem baad hon validation lal prerequiste w lal day wel time
		int classnumber = c[course_index].classNumber;
		RegCoursesToFile(classnumber, "RegisteredCourse.csv", SID);
		if (addchoice1 == "No" || addchoice1 == "no")
			cout << "Enrollement Failed.";
		break;
	}
	else {
		cout << "Course not Available Please Select Another One: ";
	}

} while (course_index == -1);
}

void DropCourse(course SelectedCourse,string SID, string foundline,int& nbOfCourses,course*& c, int course_index,string addchoice1) {
	ClearScreen();

	cout << "Choose One Of The Following Courses To Drop By Entering It's Class Number: " << endl;

	GetCoursesFromRegFile("RegisteredCourse.csv", SID);

	bool ClassNumFound = false;

	do
	{
		cin >> SelectedCourse.classNumber;
		ClassNumFound = SearchforClassNumInRCourse(SelectedCourse.classNumber, "RegisteredCourse.csv", foundline);
		ClassNumFound = true;
		if (ClassNumFound)
		{

			for (int i = 0; i < nbOfCourses; i++)
			{
				if (SelectedCourse.classNumber == c[i].classNumber)
				{
					SelectedCourse = c[i];
					course_index = i;
				}
			}
			cout << "Are You Sure You Want To Drop This Course: " << SelectedCourse.courseName;
			cout << endl << "(Yes / No)";
			cin >> addchoice1;
			if (addchoice1 == "Yes" || addchoice1 == "yes")
			{
				cout << "Course Dropped Successfully !";
				c[course_index].capacity++;
				ArrToFile(c, nbOfCourses);
				const int Classnum = SelectedCourse.classNumber;
				removeStudentID("RegisteredCourse.csv", Classnum, SID);

			}
			else if (addchoice1 == "No" || addchoice1 == "no")
			{
				cout << "Enrollement Failed.";

				ClassNumFound = false;
			}
			else {
				cout << "Course not found";
				system("pause");
			}

		}
		else {
			cout << "You Aren't Registered In That Course. Please Select Another One: ";
		}

	} while (!ClassNumFound);
}
//Admin Or Student
void Student(course*& c, int& nbOfCourses, string SID) {

	fstream file("Courses.csv", ios::in | ios::out | ios::app);
	string line;
	int choice = -1;
	string addchoice1 = "";
	course SelectedCourse;
	int course_index = -1;
	string foundline = "";
	int swapchoice2;
	int course_index_2 = -1;
	course* SelectedSwapCourse = new course[nbOfCourses];
	int course_index_3 = -1;

	do {
		ClearScreen();
		cout << "----------------------------------------------------------------------------------------" << endl;
		cout << "------------------------------ STUDENT INFORMATION SYSTEM ------------------------------" << endl;
		cout << "----------------------------------------------------------------------------------------" << endl;
		cout << "----------------------------------- STUDENT PAGE ---------------------------------------" << endl;
		cout << "----------------------------------------------------------------------------------------" << endl << endl;
		cout << "   1 - PRESS 1 TO ADD A COURSE" << endl << "----------------------------------------------------------------------------------------" << endl;
		cout << "----------------------------------------------------------------------------------------" << endl << endl;
		cout << "   2 - PRESS 2 TO DROP A COURSE" << endl << "----------------------------------------------------------------------------------------" << endl;
		cout << "----------------------------------------------------------------------------------------" << endl << endl;
		cout << "   3 - PRESS 3 TO SWAP TWO COURSES" << endl << "----------------------------------------------------------------------------------------" << endl;
		cout << "----------------------------------------------------------------------------------------" << endl << endl;
		cout << "   4 - PRESS 4 TO CHECK YOUR SCHEDULE" << endl << "----------------------------------------------------------------------------------------" << endl;
		cout << "----------------------------------------------------------------------------------------" << endl << endl;
		cout << "   0 - PRESS 0 TO EXIT" << endl << "----------------------------------------------------------------------------------------" << endl;
		cout << "----------------------------------------------------------------------------------------" << endl << endl;
		cin >> choice;
		if (choice == 1) {
			EnrollCourse(c, SelectedCourse, nbOfCourses, course_index, addchoice1, SID);
		}
		else if (choice == 2)
		{

			DropCourse(SelectedCourse,SID, foundline,nbOfCourses, c,course_index,addchoice1);


		}
		else if (choice == 3)
		{
			ClearScreen();

			cout << "-------------------------------------------------------------------------------------------------" << endl;
			cout << "-------------------------------------------------------------------------------------------------" << endl;


			cout << endl << "Here's Your Enrolled Courses: " << endl;
			GetCoursesFromRegFile("RegisteredCourse.csv", SID); // this function will display courses that the user is already enrolled in
			cout << "-------------------------------------------------------------------------------------------------" << endl;




			bool ClassNumFound = SearchforClassNumInRCourse(SelectedCourse.classNumber, "RegisteredCourse.csv", foundline);
			ClassNumFound = true;
			do
			{

				cout << "Choose The Course That You Want To Swap By Entering It's Class Number: " << endl;
				cin >> SelectedCourse.classNumber;
				cout << "-------------------------------------------------------------------------------------------------" << endl;

				if (ClassNumFound)
				{

					for (int i = 0; i < nbOfCourses; i++)
					{
						if (SelectedCourse.classNumber == c[i].classNumber)
						{

							course_index = i;
						}
					}
					SelectedCourse = c[course_index];
					cout << "Here's The Available Courses To Swap: " << endl;
					for (int i = 0; i < nbOfCourses; i++) {
						if (SelectedCourse.courseName == c[i].courseName && c[i].classNumber != SelectedCourse.classNumber) {
							cout << c[i].courseID << ',' << c[i].classNumber << endl;
							SelectedSwapCourse[i] = c[i];
						
						}
					}
					do {
						cout << "Enter The Class Number Of The Course You Wish To Swap To: ";
						cin >> swapchoice2;

					

						for (int i = 0; i < nbOfCourses; i++) {
							if (swapchoice2 = SelectedSwapCourse[i].classNumber) {
								course_index_3 = i;
							}
							
							
						}
					course SelectedSwap = 	SelectedSwapCourse[course_index_3];
						if (course_index_3 != -1) {
							cout << "Are You Sure You Want To Swap These Following Courses: " << endl;
							cout << c[course_index].classNumber << " <--> " << SelectedSwapCourse[course_index_3].classNumber;
							cin >> addchoice1;
							if (addchoice1 == "Yes" || addchoice1 == "yes") {
								DropCourse(SelectedCourse, SID, foundline, nbOfCourses, c, course_index, addchoice1);
								//EnrollCourse(SelectedSwap, nbOfCourses);
							}
						}
					} while (course_index_3 == -1);

					system("pause");
				}

				else
				{
					cout << "Not Found";
				}


			} while (!ClassNumFound);


		}
		
				else if (choice == 4) {
			searchStudentByID(SID);
		
			system("pause");
				}

			

		

	} while (choice != 0);
}

void Admin(course*& c, int& NbofCourses) {

	string password;
	int choice;

	ClearScreen();

	cout << "----------------------------------------------------------------------------------------" << endl;
	cout << "------------------------------ STUDENT INFORMATION SYSTEM ------------------------------" << endl;
	cout << "----------------------------------------------------------------------------------------" << endl << endl;

	cin.ignore();
	cout << "Enter the password to continue : ";
	getline(cin, password);
	while (password != "admin") {
		cout << "Enter the password to continue : ";
		getline(cin, password);
	}
	do {
		ClearScreen();

		cout << "----------------------------------------------------------------------------------------" << endl;
		cout << "------------------------------ STUDENT INFORMATION SYSTEM ------------------------------" << endl;
		cout << "----------------------------------------------------------------------------------------" << endl;
		cout << "------------------------------------ ADMIN PAGE ----------------------------------------" << endl;
		cout << "----------------------------------------------------------------------------------------" << endl << endl;
		cout << "   1 - PRESS 1 TO ADD A COURSE" << endl << "----------------------------------------------------------------------------------------" << endl;
		cout << "----------------------------------------------------------------------------------------" << endl << endl;
		cout << "   2 - PRESS 2 TO REMOVE A COURSE" << endl << "----------------------------------------------------------------------------------------" << endl;
		cout << "----------------------------------------------------------------------------------------" << endl << endl;
		cout << "   3 - PRESS 2 TO MODIFY A COURSE" << endl << "----------------------------------------------------------------------------------------" << endl;
		cout << "----------------------------------------------------------------------------------------" << endl << endl << endl;

		cin >> choice;
		while (choice != 1 && choice != 2 && choice != 3) {
			cout << "ERROR! Enter a valid number: ";
			cin >> choice;
		}

		if (choice == 1) {

			AddCourse(c, NbofCourses);
			cout << "Course Successfully Added" << endl;
			system("pause");
		}

		else if (choice == 2)
			RemoveCourse(c, NbofCourses);
		else if (choice == 3)
			ModifyCourse(c, NbofCourses);

	} while (choice != 1 || choice != 2 || choice != 3);
}







int AdminOrStudent() {

	int choice;

	ClearScreen();

	cout << "----------------------------------------------------------------------------------------" << endl;
	cout << "------------------------------ STUDENT INFORMATION SYSTEM ------------------------------" << endl;
	cout << "----------------------------------------------------------------------------------------" << endl << endl;
	cout << "   1 - PRESS 1 TO LOGIN AS AN ADMINISTRATOR" << endl << endl << "----------------------------------------------------------------------------------------" << endl;
	cout << "----------------------------------------------------------------------------------------" << endl << endl;
	cout << "   2 - PRESS 2 TO LOGIN AS A STUDENT" << endl << endl << "----------------------------------------------------------------------------------------" << endl;
	cout << "----------------------------------------------------------------------------------------" << endl << endl;

	cin >> choice;
	while (choice != 1 && choice != 2) {
		cout << "ERROR! Enter a valid number : ";
		cin >> choice;
	}

	return choice;


}









int main() {

	int WelcomeChoice;
	int NbofCourses = 0, NbofStudents = 0;

	fstream nbOfCourses("nbOfCourses.csv", ios::in | ios::out);
	fstream nbOfStudents("nbOfStudents.csv", ios::in | ios::out);

	if (nbOfCourses) {
		nbOfCourses >> NbofCourses;
	}

	if (nbOfStudents) {
		nbOfStudents >> NbofStudents;
	}


	course* Courses = new course[NbofCourses];
	student* Students = new student[NbofStudents];
	string StudentID = "";
	LoadCourses(Courses, NbofCourses);

	WelcomePage();


	cin >> WelcomeChoice;
	while (WelcomeChoice != 1 && WelcomeChoice != 2) {
		cout << "ERROR! Enter a valid number: ";
		cin >> WelcomeChoice;
	}


	if (WelcomeChoice == 1) {

		ClearScreen();

		SignIn(Students, NbofStudents, StudentID);

		if (AdminOrStudent() == 1) {
			Admin(Courses, NbofCourses);
		}
		else if (AdminOrStudent() == 2) {
			LoadCourses(Courses, NbofCourses);
			Student(Courses, NbofCourses, StudentID);
		}
	}


	else if (WelcomeChoice == 2) {

		ClearScreen();

		Register(Students, NbofStudents);

		int signIn_choice;
		cout << "   1 - Press 1 to LogIn \n   2 - Press 0 to exit " << endl;
		cout << endl << "-------------------------------------------------------------------------------" << endl;
		cin >> signIn_choice;

		while (signIn_choice != 0 && signIn_choice != 1) {
			cout << "ERROR: Enter a valid number : ";
			cin >> signIn_choice;
		}

		if (signIn_choice == 0) {
			exit(0);
		}

		else if (signIn_choice == 1) {
			ClearScreen();
			SignIn(Students, NbofStudents, StudentID);

			if (AdminOrStudent() == 1) {
				Admin(Courses, NbofCourses);
			}
			else if (AdminOrStudent() == 2) {
				LoadCourses(Courses, NbofCourses);
				Student(Courses, NbofCourses, StudentID);
			}
			
		}
	}




	return 0;
}

