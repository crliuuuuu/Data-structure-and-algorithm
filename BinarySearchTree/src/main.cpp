/**
 * @file   main.cpp 
 * @author Liu chenruo <1816655804@qq.com>
 * @date   Fri Oct 29 14:01:07
 * 
 * @brief  A test program for BinarySearchTree sorting.
 */
#include<iostream>
#include<vector>
#include<random>
#include<chrono>
#include<cstdlib>
#include "BinarySearchTree.h"

// Sets the specific typename.
#define TN int

using namespace std;

const int rt = 200; //rt: repeat number of BST sorting.

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

// Sorts data using Binary Search Tree and outputs the result.
void Randomized_BST_sort(vector<TN> &_data)
{
  int SIZE = _data.size();
  vector<TN> order(SIZE);
  int TIME = 0;

  for (int t = 0; t < rt; t++)
  {
    for (int i = 0; i < SIZE; i++)
      {
	order[i] = -1;
      }

    // Setups the random seed.
    myclock::duration d = myclock::now() - beginning;
    unsigned seed = d.count();
    default_random_engine generator(seed);
    uniform_int_distribution<> distribution(0, SIZE);

    // Scrambles data randomly
    for (int i = 0; i < SIZE; i++)
    {
      int p = distribution(generator);
      while (order[p] != -1)
	p = (p + 1) % SIZE;
      order[p] = i;
    }

    // Constructs BinarySearchTree, sorts data and records time.
    BinarySearchTree<TN> BST;
    myclock::time_point begin = myclock::now();
    for (int i = 0; i < SIZE; i++)
      BST.insert(_data[order[i]]);
    _data.clear();
    BST.printTree(_data);
    myclock::time_point end = myclock::now();
    TIME = TIME + chrono::duration_cast<chrono::microseconds>(end - begin).count();
  }

  cout << "Data after sorting is:" << endl;;
  for (int i = 0; i < SIZE; i++)
  {
    cout << _data[i] << "\t ";
    if ((i + 1) % 10 == 0)
      cout << endl;
  }
  cout << endl;
  cout << "The average T(N) is: ";
  cout << TIME / rt << " microseconds."<< endl; 
    
    
}


int main(int argc, char* argv[])
{
  beginning = myclock::now();

  if (argc < 2)
    exitAbnormal(1);

  int N = atoi(argv[1]);
  vector<TN> DATA(N);

  // Setups the random seed.
  myclock::duration d = myclock::now() - beginning;
  unsigned seed = d.count();
  default_random_engine generator(seed);
  uniform_int_distribution<> distribution(0,N);

  // Randomly generates a vector of integers in the range 0-N.
  for (int i = 0; i < N; i++)
  {
    DATA[i] = -1;
  }
  for (int i = 0; i < N; i++)
  {
    int p = distribution(generator);
    while (DATA[p] != -1)
      p = (p + 1) % N;
    DATA[p] = i;
  }
  cout << "Data before sorting is:" << endl;
  for (int i = 0; i < N; i++)
  {
    cout << DATA[i] << "\t";
    if ((i + 1) % 10 == 0)
      cout << endl;
  }
  cout << endl;
  
  Randomized_BST_sort(DATA);

  
  return 0;
}
