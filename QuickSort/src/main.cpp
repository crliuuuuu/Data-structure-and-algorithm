/**
 * @file   main.cpp 
 * @author Liu chenruo <1816655804@qq.com>
 * @date   Sun Dec 12 22:04:23
 * 
 * @brief  A test program for quicksort.
 */
#include<iostream>
#include<vector>
#include<random>
#include<chrono>
#include<cstdlib>
#include<ctime>
#include "QuickSort.h"

// Sets the specific typename.
#define TN int

using namespace std;

const int rt = 200; //rt: repeat number of quicksort.

// Sets an internal clock to generate a random seed.
typedef chrono::high_resolution_clock myclock;
myclock::time_point beginning;

// Stops the program abnormally.
void exitAbnormal(int _e)
{
  switch (_e)
  {
  case 1:
    cout << "Need 1 argument." << endl;
    break;
  default:
    break;
  }
  exit(-1);
}

int main(int argc, char* argv[])
{
  beginning = myclock::now();

  if (argc < 2)
    exitAbnormal(1);

  int N = atoi(argv[1]);
  vector<TN> DATA1(N);
  vector<TN> DATA2(N);

  // Setups the random seed.
  myclock::duration d = myclock::now() - beginning;
  unsigned seed = d.count();
  default_random_engine generator(seed);
  uniform_int_distribution<> distribution(0,N);

  int TIME1 = 0;
  int TIME2 = 0;
  for (int i = 0; i < rt; i++)
  {
    for (int j = 0; j < N; j++)
    {
      DATA1[j] = distribution(generator);
      DATA2[j] = DATA1[j];
    }
    if (i == 0)
    {
       cout << "Data before sorting is:" << endl;
       for (int j = 0; j < N; j++)
       {
	 cout << DATA1[j] << "\t";
	 if ((j + 1) % 10 == 0)
	   cout << endl;
       }
       cout << endl;
    }

    //Caculates the sorting time of two methods.
    myclock::time_point begin1 = myclock::now();
    sort1(DATA1);
    myclock::time_point end1 = myclock::now();
    TIME1 = TIME1 + chrono::duration_cast<chrono::microseconds>(end1 - begin1).count();

    myclock::time_point begin2 = myclock::now();
    sort2(DATA2);
    myclock::time_point end2 = myclock::now();
    TIME2 = TIME2 + chrono::duration_cast<chrono::microseconds>(end2 - begin2).count();

    if(i == 0)
    {
      cout << "Data after sorting using Median-of-Three Partitioning is:" << endl;;
      for (int j = 0; j < N; j++)
      {
	cout << DATA1[j] << "\t ";
	if ((j + 1) % 10 == 0)
	  cout << endl;
      }
      cout << endl;

      cout << "Data after sorting using random partitioning is:" << endl;;
      for (int j = 0; j < N; j++)
      {
	cout << DATA2[j] << "\t ";
	if ((j + 1) % 10 == 0)
	  cout << endl;
      }
      cout << endl;
    }
  }
  cout << "The average sorting time using Median-of-Three Partitioning is: ";
  cout << TIME1 / rt << " microseconds."<< endl;
  cout << "The average sorting time using random partitioning is: ";
  cout << TIME2 / rt << " microseconds."<< endl; 

  
  return 0;
}
