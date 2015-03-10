/* 
 * File:   Max Sum Subvector
 * Author: Paul Senatillaka
 *
 */
#include <stdio.h>

#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

int list[10] = {13, -12, 50,-1,50};

int maxSum(int left, int right)
{
  int mid, sum, maxToLeft, maxToRight, maxCrossing, maxInA, maxInB;
  int i;

  // Zero element Vector
  if (left>right) {
      return 0;
  }

  // One element Vector
  if (left==right) {
      return max(0,list[left]);
  }

  // A is List[Left...Mid], B is List[Mid+1...Right]
  mid = (left + right)/2;

  // Find max crossing to left
  sum=0;
  maxToLeft=0;
  for(i=mid; i>=left; i--)
  {
     sum = sum + list[i];
     maxToLeft = max(maxToLeft,sum);
  }

  // Find max crossing to right
  sum=0;
  maxToRight=0;
  for(i=mid+1; i<=right; i++)
  {
      sum = sum + list[i];
      maxToRight = max(maxToRight,sum);
  }

  maxCrossing = maxToLeft + maxToRight;
  maxInA = maxSum(left,mid);
  maxInB = maxSum(mid+1,right);

 return max(max(maxCrossing,maxInA),maxInB);
}

int main(int argc, char** argv) {

    printf ("%d \n", maxSum(0,4));

    return 0;
}

