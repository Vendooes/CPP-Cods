#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Student {
    string first;
    string last;

    bool operator<(const Student& other) const {
        if (last !=other.last) {
            return last <other.last;
        }
        return first <other.first;}
};

int main() {
    vector<Student> students;

    Student s1;
    s1.first = "Иван";
    s1.last = "Иванов";
    students.push_back(s1);

    Student s2;
    s2.first = "Мария";
    s2.last = "Петрова";
    students.push_back(s2);

    Student s3;
    s3.first = "Анна";
    s3.last = "Сидорова";
    students.push_back(s3);

    Student s4;
    s4.first = "Пётр";
    s4.last = "Иванов";
    students.push_back(s4);


    sort(students.begin(), students.end());

    for (int i = 0; i < students.size(); i++) {
        cout << students[i].last << " "<< students[i].first << endl;
    }
    return 0;
}