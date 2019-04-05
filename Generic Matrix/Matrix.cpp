//
//  Matrix.cpp
//  Generic Matrix
//
//  Created by Takáts Bálint on 2019. 04. 02..
//  Copyright © 2019. Takáts Bálint. All rights reserved.
//

#include "Matrix.hpp"


template <typename type>
Matrix<type>::Matrix(size_t R_, size_t C_){
#ifdef DEBUG
    std::cout << "Created!\n";
#endif
    ROWS = R_;
    COLS = C_;
    array = new type[ROWS*COLS];
}

template <typename type>
Matrix<type>::Matrix(size_t R_, size_t C_, type t){
#ifdef DEBUG
    std::cout << "Created!\n";
#endif
    ROWS = R_;
    COLS = C_;
    array = new type[ROWS*COLS];
    for (size_t i = 0; i<ROWS*COLS; i++)
        array[i] = t;
}

template <typename type>
Matrix<type>::Matrix(const Matrix<type> & ref){
    ROWS = ref.ROWS;
    COLS = ref.COLS;
    array = new type[ROWS*COLS];
    size_t index = 0;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++){
            array[index] = ref.array[index];
            index++;
        }
}
template <typename type>
Matrix<type>::~Matrix(){
#ifdef DEBUG
    std::cout << "Deleted!\n";
#endif
    delete[] array;
}

template <typename type>
std::ostream& operator<<(std::ostream& os, const Matrix<type>& ref){
    size_t index = 0;
    os << "[";
    for (int i = 0; i < ref.ROWS; i++){
        os <<"[\t";
        for (int j = 0; j < ref.COLS-1; j++){
            os << ref.array[index] << ",\t";
            index++;
        }
        if (index != ref.COLS*ref.ROWS - 1 ){
            os << ref.array[index] << " ],\n";
            index++;
        }
        else
            os << ref.array[index] << " ]";
    }
    os << "]\n";
    return os;
}














template std::ostream& operator<<(std::ostream& os, const Matrix<int>& ref);
template std::ostream& operator<<(std::ostream& os, const Matrix<double>& ref);
template std::ostream& operator<<(std::ostream& os, const Matrix<float>& ref);
template std::ostream& operator<<(std::ostream& os, const Matrix<long>& ref);

template class Matrix<int>;
template class Matrix<double>;
template class Matrix<float>;
template class Matrix<long>;

