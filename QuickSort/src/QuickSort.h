/**
 * @file   QuickSort.h
 * @author Liu chenruo <1816655804@qq.com>
 * @date   Sun Dec 12 22:01:27
 * 
 * @brief  Implementation of quicksort using different partition methods.
 */
#include<random>
#include<ctime>
#include<vector>

using namespace std;

//Median-of-Three partitioning.
template <typename Comparable>
const Comparable & median3(vector<Comparable> & A, int left, int right)
{
  int center = (left + right) / 2;

  if(A[center] < A[left])
    std::swap(A[left], A[center]);
  if(A[right] < A[left])
    std::swap(A[left], A[right]);
  if(A[right] < A[center])
    std::swap(A[center], A[right]);

  std::swap(A[center], A[right - 1]);
  return A[right - 1];
}

//Chooses pivot randomly.
template <typename Comparable>
const Comparable & ran(vector<Comparable> & A, int left, int right)
{
  srand((int)time(0));
  int num = rand() % (right - left + 1) + left;
  
  std::swap(A[num], A[right - 1]);
  return A[right - 1];
}

template <typename Comparable>
void insertionSort(vector<Comparable> & A, int left, int right)
{
  for(int p = left + 1; p < right + 1; ++p)
  {
    Comparable tmp = std::move(A[p]);

    int j;
    for(j = p; j > left && tmp < A[j - 1]; --j)
      A[j] = std::move(A[j-1]);
    A[j] = std::move(tmp);
  }
}

template <typename Comparable>
void quicksort1(vector<Comparable> & A, int left, int right)
{
  if (left + 10 <= right)
  {
    const Comparable & pivot = median3(A, left, right);

    int i = left, j = right - 1;
    for(;;)
    {
      while (A[++i] < pivot) {}
      while (pivot < A[--j]) {}
      if (i < j)
	std::swap(A[i], A[j]);
      else
	break;
    }

    std::swap(A[i], A[right - 1]);

    quicksort1(A, left, i - 1);
    quicksort1(A, i + 1, right);
  }
  else
    insertionSort(A, left, right);
}

template <typename Comparable>
void sort1(vector<Comparable> & A)
{
  quicksort1(A, 0, A.size() - 1);
}


template <typename Comparable>
void quicksort2(vector<Comparable> & A, int left, int right)
{
  if (left + 10 <= right)
  {
    const Comparable & pivot = ran(A, left, right);

    int i = left, j = right - 1;
    for(;;)
    {
      while (A[++i] < pivot) {}
      while (pivot < A[--j]) {}
      if (i < j)
	std::swap(A[i], A[j]);
      else
	break;
    }

    std::swap(A[i], A[right - 1]);

    quicksort1(A, left, i - 1);
    quicksort1(A, i + 1, right);
  }
  else
    insertionSort(A, left, right);
}

template <typename Comparable>
void sort2(vector<Comparable> & A)
{
  quicksort2(A, 0, A.size() - 1);
}

