/**
 * @file   main.cpp
 * @author Liu chenruo <1816655804@qq.com>
 * @date   Sun Oct 17 11:10:20
 *
 * @brief  A test program for optimal SPARE_CAPACITY.
 *
 */

/// Sets the specific typename.
#define TN int

#include <iostream>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <limits>
#include "Vector.h"


/// Stops the program abnormally.
void exitAbnormal(int error_code)
{
  switch(error_code)
  {
  case1:
    std::cout << "Need arguments." << std::endl;
    break;
  default:
    break;
  }
  exit(-1);
}

int main(int argc, char* argv[])
{

  if (argc < 3)
    exitAbnormal(1);
  int N = std::atoi(argv[1]);
  double k = std::atof(argv[2]);


  /**
   * maxspare: the maximum SPARE_CAPACITY we test;
   * Repeatnum: the repeat number of each SPARE_CAPACITY;
   * Times: stores running times of program of each SPER_CAPACITY;
   */
  int maxspare = ceil(N * k);
  const int RepeatNum = 100;
  int Times[ maxspare ];
  typedef std::chrono::high_resolution_clock myclock;

  /// Tests runnning times of each SPARE_CAPACITY;
  for (int i = 1; i <= maxspare ; i++)
    {
      myclock::time_point begin = myclock::now();
      for (int m = 1; m <= RepeatNum ; m++)
	for (int j = 1; j <= N; j++)
	  {
	    Vector<TN> Test(j);
	    Test.SPARE_CAPACITY = i;
	    for (int n = 1; n <= ceil(j * k) ; n++)
	      Test.push_back(TN());
	  }
      myclock::time_point end = myclock::now();
      Times[i - 1] = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    }

  /// Sorts the SPARE_CAPACITY by time and memory space it used.
  int rank[ maxspare ];
  for (int i = 1; i <= maxspare; i++)
    rank[i - 1]= maxspare + 1 - i;
  int weight = maxspare;
  for (int i = 1; i <= maxspare; i++)
  {
    int min = std::numeric_limits<int>::max();
    int p = 0;
    for (int j = 1; j <= maxspare; j++)
      if (Times[j - 1] < min)
      {
	min = Times[j - 1];
	p = j - 1;
      }
    rank[p] = rank[p] * weight;
    weight = weight - 1;
    Times[p] = std::numeric_limits<int>::max();
  }

  /**
   * Caculates the optimal SPARE_CAPACITY.
   * Takes average value of the smallest part to reduce accidental error.
   */ 
  int sum =  0;
  for (int j = 1; j <= ceil(maxspare * 0.2); j++)
  {
    int max = 0;
    int pp = 0;
    for (int i = 1; i <= maxspare; i++)
      if (rank[i - 1] > max)
      {
	max = rank[i - 1];
	pp = i;
      }
    sum = sum + pp;
    rank[pp - 1] = 0;
  }
  int op = round(sum / ceil(maxspare * 0.2));

  
  std::cout << "The optimal size of SPARE_CAPACITY is:";
  std::cout << op << "," << std::endl;
  std::cout << "Approximately " << round(op * 100 / (k * N));
  std::cout << "% of k * N" << std::endl;

  return 0;
}
