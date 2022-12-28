#include <bits/stdc++.h>
using namespace std;

unordered_map<string, vector<string>> student;
unordered_map<string, vector<string>> professor;
unordered_map<string, vector<string>> course;
unordered_map<string, vector<string>> admin;

class Student
{
    string ROLLNO;
    string NAME;
    string DEPARTMENT;

public:
    Student(string roll_no, string name, string dept)
    {
        ROLLNO = roll_no;
        NAME = name;
        DEPARTMENT = dept;
        if (student[ROLLNO].size() == 0)
        {
            student[ROLLNO].push_back(NAME);
            student[ROLLNO].push_back(DEPARTMENT);
        }
        else
        {
            cout << "Data is already in the Database about this Student!" << endl;
        }
    }

    void StudentDetails()
    {
        cout << "Student Name : " << student[ROLLNO][0] << endl;
        cout << "Student Department : " << student[ROLLNO][1] << endl;
        cout << "Enrolled Courses: " << endl;
        for (int i = 2; i < student[ROLLNO].size(); i++)
        {
            cout << "-Course ID : " << student[ROLLNO][i] << endl;
            cout << " Course Name : " << course[student[ROLLNO][i]][0] << endl;
            cout << " Course Credits : " << course[student[ROLLNO][i]][1] << endl;
        }
    }

    void RequestCourse(string CourseID)
    {
        if ((course[CourseID].size() != 0) && (course[CourseID][2] != "no-prof"))
        {
            if (course[CourseID][3] == DEPARTMENT)
            {
                bool flag = false;
                for (int i = 0; i < student[ROLLNO].size() && (flag == false); i++)
                {
                    if (student[ROLLNO][i] == CourseID)
                    {
                        flag = true;
                    }
                }
                if (flag)
                {
                    cout << "Sorry, This course is already in your template!" << endl;
                }
                else
                {
                    student[ROLLNO].push_back(CourseID);
                    course[CourseID].push_back(ROLLNO);
                    cout << "Course Added in you Template" << endl;
                }
            }
        }
        else if ((course[CourseID].size() != 0) && (course[CourseID][2] == "no-prof"))
        {
            cout << "This Course will be available to you once it's finalized. Rest Easy, it will not take much time!" << endl;
        }
        else
        {
            cout << "This course is not being offered!" << endl;
        }
    }

    void DropCourse(string CourseID)
    {
        bool flag = false;
        int i;
        for (i = 0; i < student[ROLLNO].size() && (flag == false); i++)
        {
            if (student[ROLLNO][i] == CourseID)
            {
                flag = true;
            }
        }
        if (flag)
        {
            vector<string>::iterator it;
            it = find(course[CourseID].begin(), course[CourseID].end(), ROLLNO);
            course[CourseID].erase(it);
            student[ROLLNO].erase(student[ROLLNO].begin() + i);
            cout << "Course Dropped" << endl;
        }
        else
        {
            cout << "This course is not in your template!" << endl;
        }
    }
};

class Course
{
    string CourseID;
    string CourseTitle;
    string CourseCredit;
    string CourseDepartment;

public:
    Course(string course_id, string title, string credits, string course_dept)
    {
        CourseID = course_id;
        CourseTitle = title;
        CourseCredit = credits;
        CourseDepartment = course_dept;
        if (course[CourseID].size() == 0)
        {
            course[CourseID].push_back(CourseTitle);
            course[CourseID].push_back(CourseCredit);
            course[CourseID].push_back("no-prof");
            course[CourseID].push_back(CourseDepartment);
        }
        else
        {
            cout << "Course is already in Database!" << endl;
        }
    }

    void CourseDetails()
    {
        if (course[CourseID][2] != "no-prof")
        {
            cout << "Course ID: " << CourseID << endl;
            cout << "Course Title: " << course[CourseID][0] << endl;
            cout << "Course Credit: " << course[CourseID][1] << endl;
            cout << "Professor Name: " << course[CourseID][2] << endl;
            cout << "Course Department: " << course[CourseID][3] << endl;
            cout << "Total Students registered are " << (course[CourseID].size() - 4) << endl;
            cout << "Details of those that are enrolled in this course:" << endl;
            for (int i = 4; i < course[CourseID].size(); i++)
            {
                cout << "-Roll no: " << course[CourseID][i] << endl;
                cout << " Name: " << student[course[CourseID][i]][0] << endl;
                cout << " Student Department: " << student[course[CourseID][i]][1] << endl;
            }
        }
        else
        {
            cout << "No professor is alloted for this course yet! \n Try Again later Sometime!" << endl;
        }
    }
};

class Professor
{
    string PROFNAME;
    string PROFDEPARTMENT;

public:
    Professor(string prof_name, string prof_dept)
    {
        PROFNAME = prof_name;
        PROFDEPARTMENT = prof_dept;
        if (professor[PROFNAME].size() == 0)
        {
            professor[PROFNAME].push_back(PROFDEPARTMENT);
            professor[PROFNAME].push_back("no-course");
        }
        else
        {
            cout << "Professor already in Database!" << endl;
        }
    }

    void ProfDetails()
    {
        cout << "Professor Name: " << PROFNAME << endl;
        cout << "Professor Department: " << professor[PROFNAME][0] << endl;
    }
};

class Admin
{
    string USERNAME;
    string ID;
    string PASSWORD;

public:
    Admin(string username, string id, string pswd)
    {
        USERNAME = username;
        ID = id;
        PASSWORD = pswd;
        if (admin[USERNAME].size() == 0)
        {
            admin[USERNAME].push_back(ID);
            admin[USERNAME].push_back(PASSWORD);
        }
    }

    void linkCoursetoProf(string CourseID, string ProfName)
    {
        course[CourseID][2] = ProfName;
        professor[ProfName][1] = CourseID;
    }

    void dropLinkProfCourse(string CourseID, string PROFNAME)
    {
        course[CourseID][2] = "no-prof";
        professor[PROFNAME][1] = "no-course";
    }

    void CourseDetails(string CourseID)
    {
        if (course[CourseID].size() != 0)
        {
            Course _ = Course(CourseID, course[CourseID][0], course[CourseID][1], course[CourseID][3]);
            _.CourseDetails();
        }
        else
        {
            cout << "This Course is not in our Database! Check the values and Try Again!" << endl;
        }
    }

    void StudentDetails(string ROLLNO)
    {
        if (student[ROLLNO].size() != 0)
        {
            Student _ = Student(ROLLNO, student[ROLLNO][0], student[ROLLNO][1]);
            _.StudentDetails();
        }
        else
        {
            cout << "This Student is not in our Database! Check the values and Try Again!" << endl;
        }
    }

    void ProfessorDetails(string PROFNAME)
    {
        if (professor[PROFNAME].size() != 0)
        {
            Professor _ = Professor(PROFNAME, professor[PROFNAME][0]);
            _.ProfDetails();
        }
        else
        {
            cout << "This Professor is not in our Database! Check the values and Try Again!" << endl;
        }
    }

    // Dynamic Data: On the Fly Generate
    void createNewStudent(string rollno, string name, string dept)
    {
        if (student[rollno].size() == 0)
        {
            Student _ = Student(rollno, name, dept);
            cout << "Student " << name << " with Roll No. of " << rollno << " created successfully!" << endl;
        }
        else
        {
            cout << "This Student is already present! Please Try Again with different values!" << endl;
        }
    }

    void createNewCourse(string courseid, string title, string credit, string dept)
    {
        if (course[courseid].size() != 0)
        {
            cout << "This Course is already present! Please Try Again with different values!" << endl;
        }
        else
        {
            Course _ = Course(courseid, title, credit, dept);
            cout << "Course [" << courseid << "] - " << title << " (" << credit << ") created successfully!" << endl;
        }
    }

    void createnewProf(string profname, string dept)
    {
        if (professor[profname].size() != 0)
        {
            cout << "This Professor is already present! Please Try Again with different values!" << endl;
        }
        else
        {
            Professor _ = Professor(profname, dept);
            cout << "Professor " << profname << " created successfully!" << endl;
        }
    }

    // Student Functions
    void putCoursetoStudent(string rollno, string courseid)
    {
        if ((student[rollno].size() == 0) || (course[courseid].size() == 0))
        {
            cout << "Student/Course Does not Exist!" << endl;
        }
        else
        {
            Student _ = Student(rollno, student[rollno][0], student[rollno][1]);
            _.RequestCourse(courseid);
        }
    }

    void dropStudentCourseFrom(string rollno, string courseid)
    {
        if ((student[rollno].size() == 0) || (course[courseid].size() == 0))
        {
            cout << "Student/Course Does not Exist!" << endl;
        }
        else
        {
            Student _ = Student(rollno, student[rollno][0], student[rollno][1]);
            _.DropCourse(courseid);
        }
    }
};

bool checkAdmin(string username, string pswd)
{
    return ((admin[username].size() != 0) && (pswd == admin[username][1]));
}

void forStudent();
void forProfessor();
void forAdmin();

int main()
{
    // Admins
    Admin kartikey = Admin("kartikey", "23359", "not-easy");
    Admin manish = Admin("manish", "23356", "very-easy");
    Admin divya = Admin("divya", "23459", "no-password");

    // Static Data
    // Data: Student
    Student stdn1 = Student("200493", "Kartikey", "CE");
    Student stdn2 = Student("190316", "Pankaj", "EE");
    Student stdn3 = Student("200345", "Sakshi", "CE");
    Student stdn4 = Student("188001", "Dinesh", "CE");
    Student stdn5 = Student("210036", "Mansi Sharma", "MTH");

    // Data: Courses
    Course crs1 = Course("MTH312", "Easy Mathematics", "9", "MTH");
    Course crs2 = Course("CE311", "Early Pollution Solutions", "11", "CE");
    Course crs3 = Course("EE302", "Electronics: Hard - VERY COURSE", "6", "EE");
    Course crs4 = Course("CE412", "Soil and Its Properties", "2", "CE");

    // Data: Professors
    Professor prof1 = Professor("Rahul Yadav", "CE");
    Professor prof2 = Professor("Manmeta Singh", "EE");
    Professor prof3 = Professor("Priya Saral", "CE");
    Professor prof4 = Professor("Kanhaiya Thakur", "MTH");

    // Linking Professors so that Courses will be available
    kartikey.linkCoursetoProf("MTH312", "Kanhaiya Thakur");
    kartikey.linkCoursetoProf("CE311", "Priya Saral");
    kartikey.linkCoursetoProf("EE302", "Manmeta Singh");
    kartikey.linkCoursetoProf("CE412", "Rahul Yadav");

    // Code::

    char currentUserCategory;

    cout << "Welcome to Student-Database-Management System!" << endl;

    while (1)
    {
        cout << "Specify your category : ( [S - Student] | [P - Professor] | [A - Admin] ) ";
        cin >> currentUserCategory;
        if ((currentUserCategory == 'S') || (currentUserCategory == 'P') || (currentUserCategory == 'A'))
        {
            break;
        }
        else
        {
            cout << "Choose from only 3 options given above!" << endl;
        }
    }

    switch (currentUserCategory)
    {
    case 'S':
        forStudent();
        break;

    case 'P':
        forProfessor();
        break;

    case 'A':
        forAdmin();
        break;

    default:
        break;
    }

    cout << "Thank You For Using This Application!" << endl;
}

void forStudent()
{
    string rollno;
    string courseid;
    char command;
    while (true)
    {
        cout << "Type your Roll No. : ";
        cin >> rollno;
        if (student[rollno].size() == 0)
        {
            cout << "There is no student with Roll no " << rollno << endl;
            cout << "Try Again!" << endl;
        }
        else
        {
            cout << "You Logged In Successfully!" << endl;
            break;
        }
    }

    Student _ = Student(rollno, student[rollno][0], student[rollno][1]);

    while (true)
    {
        cout << "What do you want to do?" << endl;
        cout << "[S - Show Details] | [R - Request Course] | [D - Drop Course] | [E - Exit]" << endl;
        cin >> command;
        switch (command)
        {
        case 'S':
            _.StudentDetails();
            break;

        case 'R':
            cout << "Enter Course ID : ";
            cin >> courseid;
            _.RequestCourse(courseid);
            break;

        case 'D':
            cout << "Enter Course ID : ";
            cin >> courseid;
            _.DropCourse(courseid);
            break;

        case 'E':
            cout << "Log Out Successful!" << endl;
            return;

        default:
            cout << "Choose only from the [S], [R], [D] and [E]! Try Again!" << endl;
            break;
        }
    }
}

void forProfessor()
{
    string profname;
    char command;
    while (true)
    {
        cout << "Type your Name : ";
        cin >> profname;
        if (professor[profname].size() == 0)
        {
            cout << "There is no Professor with name " << profname << endl;
            cout << "Try Again!" << endl;
        }
        else
        {
            cout << "You Logged In Successfully!" << endl;
            break;
        }
    }

    Professor _ = Professor(profname, professor[profname][0]);

    while (true)
    {
        cout << "What do you want to do?" << endl;
        cout << "[S - Show Details] | [E - Exit]" << endl;
        cin >> command;
        switch (command)
        {
        case 'S':
            _.ProfDetails();
            break;

        case 'E':
            cout << "Log Out Successful!" << endl;
            return;

        default:
            cout << "Choose only from the [S] and [E]! Try Again!" << endl;
            break;
        }
    }
}

void forAdmin()
{
    string username;
    string pass;
    char command;

    string courseid;
    string professor;
    string rollno;
    string dept;
    string credit;
    string name;

    while (true)
    {
        cout << "Type your Username : ";
        cin >> username;
        cout << "Password :";
        cin >> pass;
        if (checkAdmin(username, pass))
        {
            cout << "Log In Successful!" << endl;
            break;
        }
        else
        {
            cout << "Username or Password Wrong!!" << endl;
        }
    }

    Admin _ = Admin(username, admin[username][0], admin[username][1]);

    while (true)
    {
        cout << "What do you want to do?" << endl;
        cout << "[L - Link Course to Professor] | [U - Unlink Course to Professor] | [H - Show all Commands] | [E - Exit]" << endl;
        cin >> command;
        switch (command)
        {
        case 'L':
            cout << "Course ID :";
            cin >> courseid;
            cout << "Professor Name :";
            cin >> professor;
            _.linkCoursetoProf(courseid, professor);
            break;

        case 'U':
            cout << "Course ID :";
            cin >> courseid;
            cout << "Professor Name :";
            cin >> professor;
            _.dropLinkProfCourse(courseid, professor);
            break;

        case 'H':
            cout << "L - Link Professor to Course" << endl;
            cout << "U - Unlink Professor to Course" << endl;
            cout << "S - Student Details" << endl;
            cout << "C - Course Details" << endl;
            cout << "P - Professor Details" << endl;
            cout << "R - Put Course for Student" << endl;
            cout << "D - Drop Course for Student" << endl;
            cout << "1 - Create New Student" << endl;
            cout << "2 - Create New Course" << endl;
            cout << "3 - Create New Professor" << endl;
            break;

        case 'R':
            cout << "Enter Student's Roll No. : ";
            cin >> rollno;
            cout << "Enter Course ID : ";
            cin >> courseid;
            _.putCoursetoStudent(rollno, courseid);
            break;

        case 'D':
            cout << "Enter Student's Roll No. : ";
            cin >> rollno;
            cout << "Enter Course ID : ";
            cin >> courseid;
            _.dropStudentCourseFrom(rollno, courseid);
            break;

        case '1':
            cout << "Enter Student's Roll No. : ";
            cin >> rollno;
            cout << "Enter Student's Name : ";
            cin >> name;
            cout << "Enter Student's Department : ";
            cin >> dept;
            _.createNewStudent(rollno, name, dept);
            break;

        case '2':
            cout << "Enter Course's Course ID : ";
            cin >> courseid;
            cout << "Enter Course's Name : ";
            cin >> name;
            cout << "Enter Course's Department : ";
            cin >> dept;
            cout << "Enter Course's Credits : ";
            cin >> credit;
            _.createNewCourse(courseid, name, credit, dept);
            break;

        case '3':
            cout << "Enter Professor's Name. : ";
            cin >> name;
            cout << "Enter Professor's Department : ";
            cin >> dept;
            _.createnewProf(name, dept);
            break;

        case 'S':
            cout << "Enter Student's Roll No. : ";
            cin >> rollno;
            _.StudentDetails(rollno);
            break;

        case 'C':
            cout << "Enter Course ID : ";
            cin >> courseid;
            _.CourseDetails(courseid);
            break;

        case 'P':
            cout << "Enter Professor Name : ";
            cin >> professor;
            _.ProfessorDetails(professor);
            break;

        case 'E':
            cout << "Log Out Successful!" << endl;
            break;

        default:
            cout << "Choose only from given Commands!!" << endl;
            break;
        }
    }
}
