#include <iostream> 
#include <cassert> 

double* geometric(double a, double ratio, std::size_t cap) {
    //array with capacity 0
    if (cap == 0){
        return new double[0];
    }

    double* sequence = new double[cap] {0};

    //set the first index to a
    sequence[0] = a;

    //multiply the previous the index by r
    for (std::size_t i{1}; i < cap; i++){
        sequence[i] = ratio * sequence[i-1];
    }

    return sequence;
}

double* cross_correlation(double array0[], std::size_t cap0, double array1[], std::size_t cap1){
    assert ((cap0 + cap1) >= 1);

    //set everything to 0
    double* correlation = new double[cap0 + cap1 -1] {0};
    
    //allocated values for i+jth entries
    for (std::size_t i{}; i < cap0; i++){
        for (std::size_t j{}; j < cap1; j++){
            correlation [i+j] += array0[i] * array1[j];
        }
    }

    return correlation;
}

std::size_t shift_duplicates(int array[], std::size_t capacity){
    //if array is empty or 1
    if (capacity <= 1) {
        return capacity;
    }
    
    std::size_t unique_position{};

    for (std::size_t i{}; i < capacity; i++){
        //reset check condition for each element
        bool is_duplicate{};

        //check if array [i] is duplicate 
        for (std::size_t j{}; j < unique_position; j++){
            
            if ((i != j) && (array[i] == array[j])){
                is_duplicate = true; 
                break;
            }
        }

        //if it is unique, swap
        if (!is_duplicate){
            std::swap(array[unique_position], array[i]);
            unique_position++;
        }
    }

    return unique_position;
}

void deallocate (double* &ptr, bool is_array, std::size_t capacity = 0) {
    if (ptr == nullptr){
        return;
    }

    //if input is array 
    if (is_array){
        //deallocate array
        for (std::size_t i{}; i < capacity; i ++){
            ptr[i] = 0;
        }
        delete[] ptr;
    } 
    //if input if double 
    else {
        //deallocate a single double
        *ptr = 0;
        delete ptr;
    }

    ptr = nullptr;
}

int main(){ 
    //function 1
    std::size_t cap{};
    std::cout << "Enter capacity: ";
    std::cin >> cap;
    
    while (cap <= 0){
        std::cout << "Cap must be greater than 0, enter again: ";
        std::cin >> cap;
    }

    //get inputs
    double a{};
    std::cout << "Enter a: ";
    std::cin >> a;

    double ratio{};
    std::cout << "Enter ratio: ";
    std::cin >> ratio;

    //run function 1 and print the array
    double* sequence = geometric(a, ratio, cap);
    for (std::size_t i{}; i < cap; i++){
        std::cout << sequence[i];
        if (i < cap - 1) {
             std::cout << ", ";
        }
    }
    std::cout << std::endl;

    //delete addresses
    delete[] sequence;
    sequence = nullptr;

    //function 2
    //get inputs
    std::size_t cap0{};
    std::cout << "Enter cap: ";
    std::cin >> cap0;

    double* array0 = new double[cap0] {0};
    std::cout << "Enter values: "; 
    for (std::size_t i{}; i < cap0; i++){
        std::cin >> array0[i];
    }

    std::size_t cap1{};
    std::cout << "Enter cap1: ";
    std::cin >> cap1;

    double* array1 = new double[cap1] {0};
    std::cout << "Enter values: "; 
    for (std::size_t i{}; i < cap1; i++){
        std::cin >> array1[i];
    }
    
    //run function 2 and print the array
    double* correlation = cross_correlation(array0, cap0, array1, cap1);
    for (std::size_t i{}; i < (cap0 + cap1 - 1); i++){
        std::cout << correlation[i];
        if (i < (cap0 + cap1 - 2)) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    //delete addresses
    delete[] correlation;
    correlation = nullptr;

    //third function 
    //get inputs
    std::size_t capacity{};
    std::cout << "Enter capacity: ";
    std::cin >> capacity;

    int* array = new int[capacity] {0};
    std::cout << "Enter values: "; 
    for (std::size_t i{}; i < capacity; i++){
        std::cin >> array[i];
    }

    //print the unique values
    std::cout << shift_duplicates(array, capacity) << std::endl;


    //function 4 
    std::size_t size{};
    std::cout << "Enter capacity of the array: ";
    std::cin >> size;

    if (size != 0){
        double* array_ptr = new double[size] {};
        
        std::cout << "Enter values: "; 
        for (std::size_t i{}; i < size; i++){
            std::cin >> array_ptr[i];
        }

        deallocate(array_ptr, true);
    } else {
        double* single_ptr = new double{};
        std::cout << "Enter value: "; 
        std::cin >> *single_ptr;

        deallocate(single_ptr, false);
    }

    return 0;
}
