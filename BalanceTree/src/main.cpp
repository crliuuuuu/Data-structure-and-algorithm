/**
 * @file   main.cpp 
 * @author Liu chenruo <1816655804@qq.com>
 * @date   Sat Nov 13 23:37:01
 * 
 * @brief  A test program for AVLTree and SplayTree sorting.
 */
#include<iostream>
#include<vector>
#include<random>
#include<chrono>
#include<cstdlib>
#include "BalanceTree.h"

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
void Randomized_BT_sort(vector<TN> &_data)
{
  int SIZE = _data.size();
  vector<TN> order(SIZE);
  int TIME1 = 0;
  int TIME2 = 0;

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
    
    // Constructs AVLTree, sorts data and records time.
    myclock::time_point begin1 = myclock::now();
    AVLTree<TN> BST1;
    for (int i = 0; i < SIZE; i++)
      BST1.insert(_data[order[i]]);
    _data.clear();
    BST1.printTree(_data);
    myclock::time_point end1 = myclock::now();
    TIME1 = TIME1 + chrono::duration_cast<chrono::microseconds>(end1 - begin1).count();
    
    // Outputs to validate sorting results.
    if (t == 0)
    {     
      cout << "Data after AVLTree sorting is:" << endl;;
      for (int i = 0; i < SIZE; i++)
      {
	cout << _data[i] << "\t ";
	if ((i + 1) % 10 == 0)
	  cout << endl;
      }
    }

    // Constructs SplayTree, sorts data and records time.
    myclock::time_point begin2 = myclock::now();
    SplayTree<TN> BST2;
    for (int i = 0; i < SIZE; i++)
      BST2.insert(_data[order[i]]);
    _data.clear();
    BST2.printTree(_data);
    myclock::time_point end2 = myclock::now();
    TIME2 = TIME2 + chrono::duration_cast<chrono::microseconds>(end2 - begin2).count();

    // Outputs to validate sorting results.
    if (t == 0)
    {     
      cout << "Data after SplayTree sorting is:" << endl;;
      for (int i = 0; i < SIZE; i++)
	{
	  cout << _data[i] << "\t ";
	  if ((i + 1) % 10 == 0)
	    cout << endl;
	}
    }
  }
  
    cout << endl;
    cout << "The total time of AVLTree sort is: " << TIME1 << " microseconds."<< endl;
    cout << "The total time of SplayTree sort is:" << TIME2 << " microseconds."<< endl;
    
}


int main(int argc, char* argv[])
{
  beginning = myclock::now();

  if (argc < 2)
    exitAbnormal(1);

  int N = atoi(argv[1]);
  vector<TN> DATA(N);

  for (int i = 0; i < N; i++)
  {
    DATA[i] = i;
  }
 
  Randomized_BT_sort(DATA);

  return 0;
}
