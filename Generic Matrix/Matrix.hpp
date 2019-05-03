//
//  Matrix.hpp
//  Generic Matrix
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <exception>
#include "memtrace.h"



template <typename type>
class Matrix{
protected:
    type* array = nullptr;  // Gyorsabb memória műveletek és könnyebben vektorizálható
    size_t ROWS = 0;
    size_t COLS = 0;
public:
    Matrix(size_t R_ = 0, size_t C_ = 0){
        ROWS = R_;
        COLS = C_;
        array = new type[ROWS*COLS];
    }
    Matrix(size_t R_, size_t C_, type t){
        ROWS = R_;
        COLS = C_;
        array = new type[ROWS*COLS];
        for (size_t i = 0; i<ROWS*COLS; i++)
            array[i] = t;
    }
    Matrix(const Matrix& ref){
        ROWS = ref.ROWS;
        COLS = ref.COLS;
        array = new type[ROWS*COLS];
        size_t index = 0;
        for (size_t i = 0; i < ROWS; i++)
            for (size_t j = 0; j < COLS; j++){
                array[index] = ref.array[index];    // Nem kell figyelni a cachre, így biztosan
                index++;                            // sorban megy végig a memórián
            }
    }
    virtual ~Matrix(){
        delete [] array;                            // Egyetlen new
    }
    // numpy szerű kiírás
    friend std::ostream & operator<<(std::ostream& os, const Matrix & ref){
        size_t index = 0;
        os << "[";
        for (size_t i = 0; i < ref.ROWS; i++){
            os <<"[\t";
            for (size_t j = 0; j < ref.COLS-1; j++){
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
    friend Matrix operator*(type lhs, const Matrix& rhs){
        return rhs * lhs;
    }
 
    Matrix T() const{
        Matrix m(COLS, ROWS);
        for (size_t i = 0; i < ROWS; i++)
            for (size_t j = 0; j < COLS; j++){
                m(j,i) = (*this)(i,j);
            }
        return m;
    }
    Matrix operator*(const Matrix& rhs)const{
        if (COLS != rhs.ROWS)   // Nem lehet minden mxet mindennel szorozni. Meg kell egyezni a dimenzióknak
            throw std::invalid_argument("The matricies doesn't match up!\n");
        Matrix m(ROWS, rhs.COLS,0);
        for (size_t i = 0; i < ROWS; i++){
            for (size_t j = 0; j < rhs.COLS; j++){
                for(size_t k = 0; k < COLS; k++){
                    m(i,j) += (*this)(i,k)*rhs(k,j);    // Nyugodtan használuk az indexelő operátort,
                }                                       // úgyis inline a függvény és olvashatóbb így
            }
        }
        return m;
    }
    Matrix operator*(type rhs)const{
        Matrix m(*this);
        size_t index = 0;
        for (size_t i = 0; i < ROWS; i++)
            for (size_t j = 0; j < COLS; j++){
                m.array[index] *= rhs;
                index++;
            }
        return m;
    }
    
    Matrix& operator=(const Matrix& rhs){
        if(this == &rhs)
            return (*this);
        delete[] array;
        COLS = rhs.COLS;
        ROWS = rhs.ROWS;
        array = new type[ROWS*COLS];
        size_t index = 0;
        for (size_t i = 0; i < ROWS; i++)
            for (size_t j = 0; j < COLS; j++){
                array[index] = rhs.array[index];
                index++;
            }
        return *this;
    }
    Matrix operator+(const Matrix& rhs) const{
        if (ROWS != rhs.ROWS || COLS != rhs.COLS)
            throw std::invalid_argument("The matricies doesn't match up!\n");
        Matrix m(*this);
        for (size_t i = 0; i < ROWS; i++)
            for (size_t j = 0; j < COLS; j++){
                m(i,j) += rhs(i,j);
            }
        return m;
    }
    inline type& operator()(size_t i, size_t j){
        if (i >= ROWS || j >= COLS)     // size_t unsigned nem kell alsó határt ellenőrizni
            throw std::out_of_range("Out of range\n");
        return array[i*COLS+j];
    }
    inline type operator()(size_t i, size_t j) const{
        if (i >= ROWS || j >= COLS)     // size_t unsigned nem kell alsó határt ellenőrizni
            throw std::out_of_range("Out of range\n");
        return array[i*COLS+j];
    }
    virtual std::string info() const{   // debugolásnál hasznos lehet
        using namespace std;
        std::string str = "<[Matrix], ";
        str += "size is: " + to_string(ROWS*COLS*sizeof(type)+8) + " bytes ";
        str += "(" + to_string(ROWS) + " x " +to_string(COLS) + ")>\n";
        return str;
    }
    bool operator==(const Matrix& rhs )const {
        if (this == &rhs)
            return true;
        if (ROWS != rhs.ROWS || COLS != rhs.COLS)
            return false;
        size_t index = 0;
        for (size_t i = 0; i < ROWS; i++)
            for (size_t j = 0; j < COLS; j++){
                if (array[index] != rhs.array[index])
                    return false;
            }
        return true;
    }
    bool operator!=(const Matrix& rhs )const{
        return !(*this == rhs);
    }
    size_t get_rows()const{
        return ROWS;
    }
    size_t get_cols()const{
        return COLS;
    }
    // egyszerű iterator class, kompatiblilis stl-el
    class iterator{
    private:
        type * it;
    public:
        iterator(type * p): it(p){};
        iterator& operator ++(int){it++; return (*this);};
        iterator operator ++(){iterator cpy = *this; it++; return cpy; };
        type& operator*()const {return *it;}
        type& operator*() {return *it;}
        bool operator == (const iterator& ref){ return it == ref.it;};
        bool operator != (const iterator& ref){ return !((*this) == ref);};
    };
    
    iterator begin(){return iterator(array);}
    iterator end(){return iterator(array+ROWS*COLS);}
    
};


template <typename type>
class Vector : public Matrix<type>{     // vektor az egy mx szóval öröklés kézenfekvő megoldás
public:
    Vector(size_t R_, type t):
    Matrix<type>(R_, 1, t )     // oszlopvektorokat hoz létre
    {                           // ha sorvektort akarunk .T()-t lehet használni
    }
    Vector(size_t R_):
    Matrix<type>(R_,1)
    {
    }
    std::string info() const override{
        using namespace std;
        std::string str = "<[Vector], ";
        str += "size is: " + to_string(Matrix<type>::ROWS*Matrix<type>::COLS*sizeof(type)+8) + " bytes ";
        str += "(" + to_string(Matrix<type>::ROWS) + " x " +to_string(Matrix<type>::COLS) + ")>\n";
        return str;
    }
    
};

#endif /* Matrix_hpp */
