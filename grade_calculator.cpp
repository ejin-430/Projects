#include <iostream>
#include <cmath>

int main() {
    //Entering the grades
    //Final 
    double final_max = 0;
    double final = 0;
    
    while (true) {
        std::cout << "Enter maximum grade of final exam: ";
        std::cin >> final_max;

        if ((final_max > 0) && (std::round (final_max) == final_max)) {
            break;
        } else {
            std::cin.clear();  // Clear error flags
            std::cin.ignore(1000, '\n');  // Discard 
        }
    } 

    while (true) {
        std::cout << "Enter your grade for final exam: ";
        std::cin >> final;
        if ((final >= 0) && (final <= final_max)) {
            break;
        } 
    }

//     std::cout << final_max << " " << final << std::endl;

//     return 0;
// }

    //Midterm
    double midterm_max = 0;
    double midterm = 0;

    while (true) {
        std::cout << "Enter maximum grade of midterm exam: ";
        std::cin >> midterm_max;

        if ((midterm_max > 0) && (std::round (midterm_max) == midterm_max)) {
            break;
        } else {
            std::cin.clear();  // Clear error flags
            std::cin.ignore(1000, '\n');  // Discard 
        }
    }

    while (true) {
        std::cout << "Enter your grade for midterm exam: ";
        std::cin >> midterm;
        if ((midterm >= 0) && (midterm <= midterm_max)) {
            break;
        } 
    }

    //Project 1
    double project1_max = 0;
    double project1 = 0;
    
    while (true) {
        std::cout << "Enter maximum grade of Project 1: ";
        std::cin >> project1_max;

        if ((project1_max > 0) && (std::round (project1_max) == project1_max)) {
            break;
        } else {
            std::cin.clear();  // Clear error flags
            std::cin.ignore(1000, '\n');  // Discard 
        }
    }

    while (true) {
        std::cout << "Enter your grade for Project 1: ";
        std::cin >> project1;
        if ((project1 >= 0) && (project1 <= project1_max)) {
            break;
        }
    }

    //Project 2
    double project2_max = 0;
    double project2 = 0;
    
    while (true) {
        std::cout << "Enter maximum grade of Project 2: ";
        std::cin >> project2_max;

        if ((project2_max > 0) && (std::round (project2_max) == project2_max)) {
            break;
        } else {
            std::cin.clear();  // Clear error flags
            std::cin.ignore(1000, '\n');  // Discard 
        }
    }

    while (true) {
        std::cout << "Enter your grade for Project 2: ";
        std::cin >> project2;
        if ((project2 >= 0) && (project2 <= project2_max)) {
            break;
        } 
    }

    //Project 3
    double project3_max = 0;
    double project3 = 0;
    
    while (true) {
        std::cout << "Enter maximum grade of Project 3: ";
        std::cin >> project3_max;

        if ((project3_max > 0) && (std::round (project3_max) == project3_max)) {
            break;
        } else {
            std::cin.clear();  // Clear error flags
            std::cin.ignore(1000, '\n');  // Discard 
        }
    }

    while (true) {
        std::cout << "Enter your grade for Project 3: ";
        std::cin >> project3;
        if ((project3 >= 0) && (project3 <= project3_max)) {
            break;
        } 
    }

    //Project 4
    double project4_max = 0;
    double project4 = 0;
    
    while (true) {
        std::cout << "Enter maximum grade of Project 4: ";
        std::cin >> project4_max;

        if ((project4_max > 0) && (std::round (project4_max) == project4_max)) {
            break;
        } else {
            std::cin.clear();  // Clear error flags
            std::cin.ignore(1000, '\n');  // Discard 
        }
    }

    while (true) {
        std::cout << "Enter your grade for Project 4: ";
        std::cin >> project4;
        if ((project4 >= 0) && (project4 <= project4_max)) {
            break;
        } 
    }

    //Project 5
    double project5_max = 0;
    double project5 = 0;
    
    while (true) {
        std::cout << "Enter maximum grade of Project 5: ";
        std::cin >> project5_max;

        if ((project5_max > 0) && (std::round (project5_max) == project5_max)) {
            break;
        } else {
            std::cin.clear();  // Clear error flags
            std::cin.ignore(1000, '\n');  // Discard 
        }
    }

    while (true) {
        std::cout << "Enter your grade for Project 5: ";
        std::cin >> project5;
        if ((project5 >= 0) && (project5 <= project5_max)) {
            break;
        } 
    }

    //supremacy of final exam
    double f_100 = ((final/final_max) * 100);

    double m_100 = ((midterm/midterm_max) * 100);
    if (m_100 < f_100){
        m_100 = f_100;
    }

    double p1_100 = ((project1/project1_max) * 100);
    if (p1_100 < f_100){
        p1_100 = f_100;
    }

    double p2_100 = ((project2/project2_max) * 100);
    if (p2_100 < f_100){
        p2_100 = f_100;
    }

    double p3_100 = ((project3/project3_max) * 100);
    if (p3_100 < f_100){
        p3_100 = f_100;
    }
    
    double p4_100 = ((project4/project4_max) * 100);
    if (p4_100 < f_100){
        p4_100 = f_100;
    }

    double p5_100 = 100*(project5/project5_max);
    if (p5_100 < f_100){
        p5_100 = f_100;
    }
  
    //examination weighted average
    double e = ((3 * f_100) + (m_100))/4;

    //project weighted average 
    double p = (p1_100 + p2_100 + p3_100 + p4_100 + p5_100)/5;

    //final grade calculation
    double final_grade = 0;
    if (e <= 40) {
        final_grade = e;
    } else if (e >= 60) {
        final_grade = ((2 * e) + (p))/3;
    } else {
        final_grade =  ((p * ((e - 40)/(60))) + (e * (1 - ((e - 40)/(60)))));
    }

    std::cout << "Final grade: " << std::round(final_grade) << std::endl;

    return 0;
}