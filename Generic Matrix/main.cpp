//
//  main.cpp
//  Generic Matrix
//
//  Created by Takáts Bálint on 2019. 04. 02..
//  Copyright © 2019. Takáts Bálint. All rights reserved.
//

#include <iostream>
#include "Matrix.hpp"



int main(int argc, const char * argv[]) {
    // insert code here...
    {
       
    }
    Matrix<float> hi(4,2,1.3);
    std::cout << hi << hi.info();
    Matrix<float> hihi = hi.T();
    std::cout << hihi << hihi.info();
    std::cout << "Hello, World!\n";
    return 0;
}
