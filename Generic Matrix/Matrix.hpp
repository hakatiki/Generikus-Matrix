//
//  Matrix.hpp
//  Generic Matrix
//
//  Created by Takáts Bálint on 2019. 04. 02..
//  Copyright © 2019. Takáts Bálint. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include <iostream>


template <typename T> class Matrix;
template <typename T> std::ostream & operator<<(std::ostream& os, const Matrix<T> & ref);

template <typename type>
class Matrix{
private:
    type* array = nullptr;  // Gyorsabb memória műveletek
    size_t ROWS = 0;
    size_t COLS = 0;
public:
    Matrix(size_t R_ = 0, size_t C_ = 0);                           // Pipa
    Matrix(size_t R_, size_t C_, type t);                           // Pipa
    Matrix(const Matrix& ref);                                      // Pipa
    ~Matrix();                                                      // Pipa
    
    /*-----------------------------DEBUGHOZ-----------------------------*/
    friend std::ostream & operator<< <>(std::ostream& os, const Matrix & ref); // Pipa
    
 
    Matrix T() const;
    Matrix operator*(const Matrix& rhs)const;
    friend Matrix operator*(const int lhs, const Matrix& rhs);
    Matrix& operator=(const Matrix& rhs);
    Matrix operator+(const Matrix& rhs) const;
    type& operator()(const int x, const int y);
    type operator()(const int x, const int y) const;
    
};





#endif /* Matrix_hpp */
