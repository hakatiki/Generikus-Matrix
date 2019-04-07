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
#include <string>

template <typename T> class Matrix;
template <typename T> std::ostream & operator<<(std::ostream& os, const Matrix<T> & ref);
template <typename T> Matrix<T> operator*(T lhs, const Matrix<T>& rhs);

template <typename type>
class Matrix{
protected:
    type* array = nullptr;  // Gyorsabb memória műveletek és könnyebben vektorizálható
    size_t ROWS = 0;
    size_t COLS = 0;
public:
    Matrix(size_t R_ = 0, size_t C_ = 0);                           // Pipa
    Matrix(size_t R_, size_t C_, type t);                           // Pipa
    Matrix(const Matrix& ref);                                      // Pipa
    virtual ~Matrix();                                              // Pipa
    
    friend std::ostream & operator<< <>(std::ostream& os, const Matrix & ref); // Pipa
    friend Matrix operator* <>(type lhs, const Matrix& rhs);
 
    Matrix T() const;                                               //Pipa
    Matrix operator*(const Matrix& rhs)const;                       //Pipa
    Matrix operator*(type rhs)const;                                //Pipa
    
    Matrix& operator=(const Matrix& rhs);                           //Pipa
    Matrix operator+(const Matrix& rhs) const;                      //Pipa
    type& operator()(size_t x, size_t y);                           //Pipa
    type operator()(size_t x, size_t y) const;                      //Pipa
    virtual std::string info() const;                               //Pipa
    
};
template <typename type>
class Vector : public Matrix<type>{
public:
    Vector(size_t R_, type t);
    Vector(size_t R_);
    std::string info() const override;                      //Pipa
};




#endif /* Matrix_hpp */
