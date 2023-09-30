/**
 * @file    main.cpp
 * @author  Liu Chenruo <1816688804@qq.com>
 * @date    Sun Oct 3 22:50:40 2021
 *
 * @brief   A test program for class Matrix.
 *
 */

/**
 * Set the specific typename.
 *
 * NOTE THAT manual changes of random distribution 
 * template is required when TN is changed.
 */
#define TN int

#include "Matrix.h"

#include <iostream>
#include <cstdlib>
#include <random>
#include <chrono>


/// To stop the program abnormally.
void exitAbnormal(int error_code)
{
  switch (error_code)
  {
  case 1:
    std::cout << "Need arguements." << std::endl;
    break;
  default:
    break;
  }
  exit(-1);
}

int main(int argc, char* argv[])
{
  /// Set an internal clock to generate a random seed.
  typedef std::chrono::high_resolution_clock myclock;
  myclock::time_point beginning = myclock::now();

  /**
   * Initialize 2 matrices, 2 rowvectors and 2 colvectors.
   *
   * @param m1_r Rows of Matrix1;
   *        m1_c Columns of Matrix1;
   *        m2_r Rows of Matrix2;
   *        m2_c Columns of Matrix2;
   *        r1   Dimension of Rowvector1;
   *        r2   Dimension of Rowvector2;
   *        c1   Dimension of Colvector1;
   *        c2   Dimension of Colvector2;
   */
  if (argc < 9)
    exitAbnormal(1);
  int m1_r = std::atoi(argv[1]);
  int m1_c = std::atoi(argv[2]);
  int m2_r = std::atoi(argv[3]);
  int m2_c = std::atoi(argv[4]);
  int r1 = std::atoi(argv[5]);
  int r2 = std::atoi(argv[6]);
  int c1 = std::atoi(argv[7]);
  int c2 = std::atoi(argv[8]);

  
  Matrix<TN> M1(m1_r, m1_c);
  Matrix<TN> M2(m2_r, m2_c);
  RowVector<TN> R1(r1);
  RowVector<TN> R2(r2);
  ColVector<TN> C1(c1);
  ColVector<TN> C2(c2);

  /**
   * Setup the random generator.
   *
   * NOTE THAT when TN is changed, uniform_int_distribution is
   * needed to be changed accordingly.
   */
  myclock::duration d = myclock::now() - beginning;
  unsigned seed = d.count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<> distribution(0,10);


  /// Assign random values to matrixs and vectors.
  for (int i = 0; i < m1_r; i++)
    for (int j = 0; j < m1_c; j++)
      M1(i, j) = distribution(generator);
  std::cout << "Matrix1 = " << std::endl;
  for (int i = 0; i < m1_r; i++)
    {
      for (int j = 0; j < m1_c; j++)
	std::cout << M1(i, j) << "\t";
      std::cout << std::endl;
    }

  for (int i = 0; i < m2_r; i++)
    for (int j = 0; j < m2_c; j++)
      M2(i, j) = distribution(generator);
   std::cout << "Matrix2 = " << std::endl;
  for (int i = 0; i < m2_r; i++)
    {
      for (int j = 0; j < m2_c; j++)
	std::cout << M2(i, j) << "\t";
      std::cout << std::endl;
    }

  for (int i = 0; i < r1; i++)
    R1(0, i) = distribution(generator);
  std::cout << "Rowvector1 = " << std::endl;
  for (int i = 0; i < r1; i++)
    std::cout << R1(0, i) << "\t";
  std::cout << std::endl;

  for (int i = 0; i < r2; i++)
    R2(0, i) = distribution(generator);
  std::cout << "Rowvector2 = " << std::endl;
  for (int i = 0; i < r2; i++)
    std::cout << R2(0, i) << "\t";
  std::cout << std::endl;

  for (int i = 0; i < c1; i++)
    C1(i, 0) = distribution(generator);
  std::cout << "Colvector1 = " << std::endl;
  for (int i = 0; i < c1; i++)
    std::cout << C1(i, 0) << std::endl;

  for (int i = 0; i < c2; i++)
    C2(i, 0) = distribution(generator);
  std::cout << "Colvector2 = " << std::endl;
  for (int i = 0; i < c2; i++)
    std::cout << C2(i, 0) << std::endl;

  
  /// Determine whether Matrix1 is a square matrix.
  if (M1.is_square())
    std::cout << "Matrix1 is square matrix." << std::endl;
  else
    std::cout << "Matrix1 is not square matrix." << std::endl;
  
  /// Caculate Matrix1 * Matrix2.
  Matrix<TN> Re1(m1_r, m2_c);
  Re1 = M1 * M2;
  std::cout << "Matrix1 * Matrix2 = " << std::endl;
  for (int i = 0; i < m1_r; i++)
    {
      for (int j = 0; j < m2_c; j++)
	std::cout << Re1(i, j) << "\t";
      std::cout << std::endl;
    }

  /// Caculate Colvector1 * Rowvector1.
  Matrix<TN> Re2(c1, r1);
  Re2 = C1 * R1;
  std::cout << "Colvector1 * Rowvector1 = " << std::endl;
  for (int i = 0; i < c1; i++)
    {
      for (int j = 0; j < r1; j++)
	std::cout << Re2(i, j) << "\t";
      std::cout << std::endl;
    }

  /// Caculate Rowvector1 * Colvector1.
  TN Re3 = TN();
  Re3 = R1 * C1;
  std::cout << "Rowvector1 * Colvector1 = " << Re3 << std::endl;

  /// Caculate Rowvector1 * Rowvector2.
  TN Re4 = TN();
  Re4 = R1 * R2;
  std::cout << "Rowvector1 * Rowvector2 = " << Re4 << std::endl;

  /// Caculate Colvector1 * Colvector2.
  TN Re5 = TN();
  Re5 = C1 * C2;
  std::cout << "Colvector1 * Colvector2 = " << Re5 << std::endl;

  return 0;
}
