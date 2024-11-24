#include <iostream>
#include <cassert>
#include "p_4_header.hpp"

std::size_t length(char const * a){
    std::size_t length{};

    while (a[length] != '\0'){
        length++;
    }

    return length;
}

int compare( char const * str1, char const * str2){
    std::size_t k{};

    //check the characters of the strings 
    while (str1[k] != '\0' && str2[k] != '\0'){     
            if (str1[k] < str2[k]){
                //str1 is smaller 
                return -1;
            } else if (str1[k] > str2[k]){
                //str1 is greater
                return 1;
            }
            k++;
    }
    
    //check endings of the strings
    if (str1[k] == '\0' && str2[k] == '\0') {
        //they are the same
        return 0;
    } else if (str1[k] == '\0') {
        //str1 is shorter
        return -1;
    } else {
        //str2 is longer
        return 1;
    }
}

void assign(char * str1, char const * str2){
    std::size_t cap {length(str2) + 1};

    for (std::size_t k{}; k < cap; k++){
        str1[k] = str2[k];
    }

}

unsigned int distance(char const * str1, char const *str2){
    unsigned int d{};
    
    //check if they are the same string
    if (compare(str1, str2) == 0){
        return d;
    }

    //check to see which one of the str is empty
    if (*str1 == '\0'){
        d = length(str2);
        return d;
    } else if (*str2 == '\0'){
        d = length(str1);
        return d;
    } 

    //keep checking until one of the str is empty
    if (str1[0] == str2[0]){
        d = distance(str1 + 1, str2 + 1);
        return d;
    } else {
        unsigned int d_1{distance(str1 + 1, str2 + 1)};
        unsigned int d_2{distance(str1, str2 + 1)};
        unsigned int d_3{distance(str1 + 1, str2)};
        d = 1 + std::min(std::min(d_1, d_2), d_3);
        return d;
    }
}

std::size_t is_sorted(char * array[], std::size_t capacity){ 
    //array with capacity 0 is sorted
    if (capacity == 0){
        return capacity;
    }

    for (std::size_t k{}; k < capacity - 1; k++){
        if (compare(array[k], array[k+1]) == 1){
            return k + 1;
        }
    }

    return capacity;
}

void insert(char *array[], std::size_t capacity){
    //std::cout << "is_sorted(array, " << capacity - 1 << ") = " << is_sorted(array, capacity - 1) << std::endl;
    assert(is_sorted(array, capacity - 1) == capacity - 1);

    //check if the last entry is out of place
    if (compare(array[capacity - 2], array[capacity - 1]) == 1){
        
        //create temp that stores the value we need to shift
        std::size_t size{length(array[capacity - 1]) + 1};
        char * temp = new char[size]{};
        assign(temp, array[capacity - 1]);

        //find location for temp
        std::size_t k{capacity - 1}; 
        while (k > 0 && compare(array[k-1], temp) == 1){
            //shift the other entries that are greater than temp
            assign(array[k], array[k-1]);
            k--;
        }

        //insert temp at the correct location
        assign(array[k], temp);

        delete[] temp;
        temp = nullptr;
    }
}

void insertion_sort(char * array[], std::size_t capacity){
    if (capacity <= 1){
        return;
    }

    insertion_sort(array, capacity-1);
    insert(array, capacity);
}

// i did this in project 3
std::size_t remove_duplicates(char *array[], std::size_t capacity){
    if (capacity <= 1) {
        return capacity;
    }
    
    std::size_t unique_cap{};

    for (std::size_t k{}; k < capacity; k++){
        //reset check condition for each element
        bool is_duplicate{};

        //check if array[k] is duplicate 
        for (std::size_t j{}; j < unique_cap; j++){
            
            if ((k != j) && (array[k] == array[j])){
                is_duplicate = true; 
                break;
            }
        }

        //if it is unique, swap
        if (!is_duplicate){
            array[unique_cap] = array[k];
            unique_cap++;
        }
    }

    return unique_cap;
}

std::size_t find(char *array[], std::size_t capacity, char const *str){    
    std::size_t shortest_distance_index{};
    std::size_t shortest_distance{};

    //go through each entry of the array 
    for (std::size_t k{}; k < capacity; k++){
        
        //check if there is a match 
        std::size_t compare_result{compare(array[k], str)};
        if (compare_result == 0){
            return k;
        }

        //find distance between the index and str
        std::size_t current_distance{distance(array[k], str)};
        if (current_distance < shortest_distance){
            shortest_distance = current_distance;
            shortest_distance_index = k;
        }       
    }
    return shortest_distance_index;
}

void free_word_array(char** word_array){
    delete[] word_array[0];
    delete[] word_array;
    word_array = nullptr;
}
