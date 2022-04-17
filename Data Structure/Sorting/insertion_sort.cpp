//插入排序
vector<int> insertSort(vector<int> arr)
{
  //从第一个元素作为基准元素，从第二个元素开始把其插到正确的位置
  for(int i=1;i<arr.size();i++)
  {  
     //如果第i个元素比前面的元素大，则不需要做改变
	 //如果第i个元素比前面的元素小，需要在前面已经排好序的序列中找到第i个元素的位置
     if(arr[i]<arr[i-1])
	 {
	   int j=i-1;
	   //因为后面元素后移会覆盖掉第i个元素，所以先将其保存到一个变量中
	   int waitInsertElem=arr[i]; 
	   //比第i个元素大的元素依次后移，直到找到第一个比第i个元素小的元素，在该元素后插入第i个元素
	   while(j>=0 && arr[j]>waitInsertElem)
	   {
	     arr[j+1]=arr[j];
		 j--;
	   }
	   arr[j+1]=waitInsertElem;
	 }
  }
  return arr;
}


// 平均时间复杂度是O(n^2)
// 最坏时间复杂度是O(n^2)
// 当输入序列本就是顺序序列，一共经过n-1轮排序，每轮排序都不需要移动元素，因此，最好时间复杂度是O(n)