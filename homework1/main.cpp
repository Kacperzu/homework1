#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Student{

    std::string name;
    std::string surname;
    std::vector<float> grades;
    std::string album;


public:

    Student(std::string n, std::string s, std::vector<float> g)
    {
        name = n;
        surname = s;
        grades = g;
    }

    void set_name(std::string n){ //setter
        name = n;
    }
    void set_surname(std::string n){ //setter
        surname = n;
    }
    bool set_album(std::string n)
    { //setter
        if (n.length() <5 || n.length()>6 )
        {
            cout << "invalid album number!!! "<< endl;
            return false;
        }


            album = n;
        return true;
    }

    std::string get_name(){ //getter
        return name;
    }






    float calculate_grade(){
        std::cout << "Calculating grade for " << name << std::endl;
        float sum = std::accumulate(grades.begin(), grades.end(), 0.0f);
        return sum/ grades.size();
    }

    bool add_grade(float grade){
        if(grade >= 2.0 && grade <= 5.0){
            grades.push_back(grade);
            return true;
        }
        return false;
    }

    void print_info() const {
           std::cout << "Name: " << name << std::endl;
           std::cout << "Surname: " << surname << std::endl;
           std::cout << "Grades: ";
           for (auto grade : grades) {
               std::cout << grade << " ";
           }
           std::cout << std::endl;
           std::cout << "Album: " << album << std::endl;
       }
    void fail_check()
    {
        int counter=0;
        for (auto grade :grades)
        {
            if (grade == 2.0)
            {
                counter++;
            }


        }

        if (counter >= 2)
        {
            cout << " student failed the semester" << endl;
        }

        else
            cout << "student passed the semester" << endl;




    }

};



int main()
{

    Student student("Jakub", "Grozba", { 3.5, 4.0, 3.0 ,2.0});

    student.set_album("1234567");
    student.add_grade(5);
    student.add_grade(3);

    student.print_info();

    std::cout << "Average grade is : " << student.calculate_grade() << std::endl;
    student.fail_check();


    return 0;
}
