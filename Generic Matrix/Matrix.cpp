//
//  Matrix.cpp
//  Generic Matrix
//
//  Created by Takáts Bálint on 2019. 04. 02..
//  Copyright © 2019. Takáts Bálint. All rights reserved.
//

#include "Matrix.hpp"
#include <exception>


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
type& Matrix<type>::operator()(size_t i, size_t j){
    if (i >= ROWS || j >= COLS)
        throw std::out_of_range("Out of range\n");
    return array[i*COLS+j];
}
template <typename type>
type Matrix<type>::operator()(size_t i, size_t j)const{
    if (i >= ROWS || j >= COLS)
        throw std::out_of_range("Out of range\n");
    return array[i*COLS+j];
}
template <typename type>
std::string Matrix<type>::info() const{
    using namespace std;
    std::string str = "<[Matrix], ";
    str += "size is: " + to_string(ROWS*COLS*sizeof(type)+8) + " bytes ";
    str += "(" + to_string(ROWS) + " x " +to_string(COLS) + ")> \n";
    return str;
}
template <typename type>
Matrix<type> Matrix<type>::T() const{
    Matrix m(COLS, ROWS);
    for (size_t i = 0; i < ROWS; i++)
        for (size_t j = 0; j < COLS; j++){
            m(j,i) = (*this)(i,j);
        }
    return m;
}
template <typename type>
Matrix<type> Matrix<type>::operator+(const Matrix& rhs) const{
    if (ROWS != rhs.ROWS || COLS != rhs.COLS)
        throw std::invalid_argument("The matricies doesn't match up!\n");
    Matrix m(*this);
    for (size_t i = 0; i < ROWS; i++)
        for (size_t j = 0; j < COLS; j++){
            m(i,j) += rhs(i,j);
        }
    return m;
}
template <typename type>
Matrix<type>& Matrix<type>::operator=(const Matrix& rhs){
    if(this == &rhs)
        throw std::invalid_argument("Don't do this pls...\n");
    delete[] array;
    COLS = rhs.COLS;
    ROWS = rhs.ROWS;
    array = new type[ROWS*COLS];
    size_t index = 0;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++){
            array[index] = rhs.array[index];
            index++;
        }
    return *this;
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













/* Hogy külön fordítási egységben lehessen a tamletelni kell az osztályt
   különben liker errort kapunk. Így elkészítve a fordítás jelentősen gyorsul
   mivel nem kell mindig külön fordítani ezt a sok kódot amikor változtatunk
   akármit egy fileban ahova includeolva van. Valamint az exe mérete is sokkal kissebb
   lesz mivel nem inline fügvény lesz belőlük.                                  */
template std::ostream& operator<<(std::ostream& os, const Matrix<int>& ref);
template std::ostream& operator<<(std::ostream& os, const Matrix<double>& ref);
template std::ostream& operator<<(std::ostream& os, const Matrix<float>& ref);
template std::ostream& operator<<(std::ostream& os, const Matrix<long>& ref);

template class Matrix<int>;
template class Matrix<double>;
template class Matrix<float>;
template class Matrix<long>;

