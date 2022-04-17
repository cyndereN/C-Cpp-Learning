vector<int> selectionSort(vector<int>arr)
{
  for(int i=0;i<arr.size()-1;i++)
  {
    int current_min_index=i;
	int current_min=arr[i];
	bool needSwap=false;
    for(int j=i+1;j<arr.size();j++)
	{
	  if(arr[j]<current_min)
	  {
	     needSwap=true;
	     current_min_index=j;
		 current_min=arr[j];
	  }
	}
	if(needSwap)
	  {
	    int tmp=arr[i];
		arr[i]=arr[current_min_index];
		arr[current_min_index]=tmp;
	  }
  }
  return arr;
}
