#include <iostream> 
#include <cassert>

void pattern(unsigned int n){
    //rows when number of * decreasing
    for (unsigned int row_d{}; row_d < n; row_d++){
        //print spaces
        for (unsigned int space_d{}; space_d < row_d; ++space_d){
            std::cout << " ";
        }
        //print *
        for (unsigned int star_d{}; star_d <= (2*(n - row_d)); ++star_d){
            std::cout << "*";
        }
        std::cout << std::endl;
    }

    // middle row + rows when number of * increases 
    for (unsigned int row_i{}; row_i <= n; row_i++){
        //print spaces
        for (unsigned int space_i{}; space_i < (n - row_i); ++space_i){
            std::cout << " ";
        }
        //print *
        for (unsigned int star_i{}; star_i < (2*(row_i) + 1); ++star_i){
            std::cout << "*";
        }
        std::cout << std::endl;
    }
}

unsigned int log10(unsigned int n) {
    assert(n != 0);

    unsigned int exponent = 0;

        //Count the exponent of 10
        while (n >= 10){
            exponent++;
            n = n / 10;
        }

        //Print m
        std::cout << "m = " << exponent << std::endl;

    return exponent;
}

unsigned int count (unsigned int n, unsigned int bit){
    assert(bit == 0 || bit == 1);

    unsigned int count = 0; 
    
    //create mask
    unsigned int mask = 0;
    mask = 1 << 31;
    
    //when mask is still in bounds of the bit
    while (mask > 0) {
        //count if the current bit is the same as what you want
        if (((n & mask) != 0 && bit == 1) || ((n & mask) == 0 && bit == 0)){
            count++;
        }
        
        //shift mask
        mask = mask >> 1;
    }

    //print count
    std::cout << "Number of " << bit << " in " << n << ": " << count << std::endl;
    
    return count;
}

unsigned int swap_bytes (unsigned int n, unsigned int b0, unsigned int b1){
    assert (b0 <= 3 && b0 >= 0);
    assert (b1 <= 3 && b1 >= 0);

    if (b0 == b1) {
        return n; 
    } else {
        unsigned int mask = 0xFF;

        //extract bytes
        unsigned int byte0 = (n >> (8 * b0)) & mask;
        unsigned int byte1 = (n >> (8 * b1)) & mask;

        //clear bytes
        unsigned int clear_byte0 = ~(mask << (8 * b0));
        unsigned int clear_byte1 = ~(mask << (8 * b1));
        n = n & clear_byte0;
        n = n & clear_byte1;

        //swap byte
        n = n | (byte1 << (8 * b0));  
        n = n | (byte0 << (8 * b1)); 

        return n;
    }
}

//print binary 
void print_int (unsigned int n) {
    unsigned int mask = 1 << 31;

    while (mask > 0) {    
        //print out first bit 
        if ((n & mask) == 0) {
            std::cout << "0";
        } else {
            std::cout << "1";
        }       
        //shift mask 
        mask = mask >> 1;
    }

}

int main(){
    
    unsigned int n = 0; 
    std::cout << "Enter n: ";
    std::cin >> n; 
    if (n <= 5){
        pattern (n);
    }
    if (n > 0) {
    log10(n);
    }

    unsigned int b = 0; 
    std::cout << "Enter b: ";
    std::cin >> b;
    count (n, b);

    unsigned int b0 = 0;
    unsigned int b1 = 0;
    std::cout << "Enter b0: ";
    std::cin >> b0;
    std::cout << "Enter b1: ";
    std::cin >> b1;
    n = swap_bytes (n, b0, b1);
    print_int(n);

    return 0;
}
