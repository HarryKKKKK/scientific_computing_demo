#include <string>
#include <iostream>

class Researcher {
public:
    Researcher (std::string);
    void setName(std::string);
    virtual void accessBuilding();
    virtual void giveOneLecture() = 0;
protected:
    std::string m_name;
    std::string m_title;
};
Researcher::Researcher(std::string name) {
    m_name = name;
}
void Researcher::setName(std::string name) {
    m_name = name;
}
void Researcher::accessBuilding() {
    std::cout << "Access Denied - please specify the role!" << std::endl;
}


class Staff : public Researcher {
public:
    Staff (std::string, int, int, int);
    void giveOneLecture() override;
    void accessBuilding() override;
protected:
    int m_salary = 0;
    int m_num_student = 1;
    int m_hours_lect_given = 0;
};
Staff::Staff(std::string name, int salary, int num_student, int hours_lect_given) : Researcher(name) {
    m_salary = salary;
    m_num_student = num_student;
    m_hours_lect_given = hours_lect_given;
}
void Staff::giveOneLecture() {
    m_hours_lect_given += 1;
    m_salary += m_num_student * 5;
}
void Staff::accessBuilding() {
    std::cout << "Accessed!" << std::endl;
}


class Student : public Researcher {
public:
    Student (std::string, int, std::string, int);
    void giveOneLecture() override;
    void accessBuilding() override;
protected:
    int m_grant;
    std::string m_deadline;
    int m_hours_lect_taken;
};
Student::Student(std::string name, int grant, std::string deadline, int hours_lect_taken) : Researcher(name) {
    m_grant = grant;
    m_deadline = deadline;
    m_hours_lect_taken = hours_lect_taken;
}
void Student::giveOneLecture() {
    std::cout << "Error - no lectures should be given from student!" << std::endl;
}
void Staff::accessBuilding() {
    std::cout << "Accessed!" << std::endl;
}


class Visitor : public Researcher {
public:
    Visitor ();
    void giveOneLecture() override;
    void accessBuilding() override;
};
void Student::giveOneLecture() {
    std::cout << "Error - no lectures should be given from visitors!" << std::endl;
}
void Staff::accessBuilding() {
    std::cout << "Accessed Denied - no access for visitors!" << std::endl;
}
