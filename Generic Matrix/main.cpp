//
//  main.cpp
//  Generic Matrix
//

#include <iostream>
#include <sstream>
#include "Matrix.hpp"
#include "memtrace.h"
#include "gtest_lite.h"


int main() {
   
    Matrix<int> hi(4,3,1);
    TEST(Matrix, info){
        EXPECT_STREQ("<[Matrix], size is: 56 bytes (4 x 3)>\n", hi.info().c_str())<< "Info nem ok";
    }END
    TEST(Matrix, transpose){
        Matrix<int> trans = hi.T();
        EXPECT_STREQ("<[Matrix], size is: 56 bytes (3 x 4)>\n", trans.info().c_str())<< "Transpose nem ok";
        Matrix<int> trans_cmp(3,4,1);
        EXPECT_EQ(true, trans_cmp == trans) << "Transpose nem ok";
    }END
    TEST(Matrix, equality){
        Matrix<int> a(3,4,2);
        Matrix<int> b(3,4,1);
        Matrix<int> c(3,4,2);
        Matrix<int> d(4,4,2);
        EXPECT_EQ(true, a == c) << "Egyenloseg nem ok";
        EXPECT_EQ(false, a == b) << "Egyenloseg nem ok";
        EXPECT_EQ(false, a == d) << "Egyenloseg nem ok";
    }END
    TEST(Matrix, mul){
        Matrix<int> mul = hi.T()*hi;
        Matrix<int> mulsol(3,3,4);
        EXPECT_STREQ("<[Matrix], size is: 44 bytes (3 x 3)>\n", mul.info().c_str())<< "Szorzas nem ok";
        EXPECT_EQ(true, mulsol == mul )<< "Szorzas nem ok";
        Matrix<int> mx(1, 3, 4);
        Matrix<int> sol(1, 3, 8);
        EXPECT_TRUE(mx*2 == sol);
        EXPECT_TRUE(2*mx == sol);
    }END
    TEST(Matrix, add){
        Matrix<int> mx1(1,3, 10);
        Matrix<int> mx2(1,3, 410);
        Matrix<int> added(1,3, 420);
        Matrix<int> fail(3,4, 69);
        EXPECT_TRUE(added == (mx1 + mx2));
        EXPECT_THROW(mx1 + fail , std::exception);
    }END
    TEST(Matrix, vector){
        Vector<int> veci(3, 2);
        EXPECT_STREQ("<[Vector], size is: 20 bytes (3 x 1)>\n", veci.info().c_str())<< "Info nem ok";
    }END
    TEST(Matrix, copyctor){
        Matrix<int> cpy1(hi);
        EXPECT_EQ(true, cpy1 == hi)<< "Copyctor rossz";
        Vector<int> veci(3,2);
        Vector<int> cpy2(veci);
        EXPECT_EQ(true, cpy2 == veci)<< "Copyctor rossz";
        Matrix<int> cpy3(cpy2);
        EXPECT_EQ(true, cpy3 == cpy2)<< "Copyctor rossz";
        EXPECT_EQ(true, cpy3 == veci)<< "Copyctor rossz";
    }END
    TEST(Matrix, indexoperator){
        Matrix<int> mx(1,3,4);
        EXPECT_THROW(mx(10,1), std::exception);
        EXPECT_EQ(mx(0,1), 4);
    }END
    TEST(Matrix, vec_mul){
        Matrix<int> mx(3,4,4);
        Vector<int> vec(4, 10);
        Matrix<int> mx_mul(3, 1, 160);
        Vector<int> vec_mul(3, 160);
        EXPECT_TRUE(mx*vec == vec_mul)<< "Vektor szorzás rossz";
        EXPECT_TRUE(mx*vec == mx_mul)<< "Vektor szorzás rossz";;
    }END
    TEST(Matrix, iterator){
        Matrix<int> mx(2, 21, 10);
        for (auto i: mx)
            EXPECT_EQ(i, 10);
        Matrix<int>::iterator it = mx.begin();
        for (int i = 0; i < 2 * 21; i++, it++);
        EXPECT_TRUE(it == mx.end());
        EXPECT_TRUE(mx.begin() != mx.end()); 
    }END
    TEST(Matrix, cpy){
        Matrix<int> mx1(2, 21, 10);
        Matrix<int> cpy1(mx1);
        Matrix<int> cpy2 = mx1;
        Matrix<int> mx2(2,10);
        mx2 = mx1;
        EXPECT_TRUE(mx2 == cpy1);
        EXPECT_FALSE(mx2 != cpy2);
    }END
    TEST(Matrix, save){
        Matrix<int> mx1(2, 3, 9);
        std::stringstream is("");
        mx1.save(is);
        Matrix<int> mx2;
        mx2.load(is);
        EXPECT_TRUE(mx2 == mx1);
    }END
    
    return 0;
}

