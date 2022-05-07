/*
Purpose and design: This program use four sorting algorithms to prove that thier time is Big(O) . The program sorts four similar arrays and sorts each one with a sorting algorithm. Each sorting algorithms has a characteristic operation counter. After the sorting, the program will print the sorting algorithms counters. Then, those counters over multiple runs of the program will be used in a graph against the choose problem size to prove the Big(O) times of those sorting algorithms. Also, the program will print the sorted and unsorted array contents of based on the user input.
*/

// File: project8.cpp
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<fstream>
using namespace std;
int length;
// A function that sorts an integer array by inserstion
// Precondition: An integer array, the length of the array, and the counter of characteristic operations 
// Postcondition: The integer array is sorted
void insertionSort(int arr[],int len,int &InserCount)
{
    int x,y;
    for(x=1;x<len;x++)                            // loop along the length of array
        {
            y=x;                                  // assign the nested loop variable
            while(y>0 && arr[y]<arr[y-1])         // loop as long y>0 and the pervoisu element in the array is greater than the one infront
            {
                InserCount++;                     // characteristic operation
                int temp=arr[y];                  // swap
                arr[y]=arr[y-1];
                arr[y-1]=temp;
                --y;                              // decrement 
            }
            
        }
}
// A function that merges two segments of an array in order
// Precondition: An integer array, the first index , the middle index, the length of the array, and the counter of characteristic operations 
// Postcondition: The two segements of the array are mereged and sorted
void merge(int a[],int low,int mid,int high,int &MergeCount)
{
    int b[length];                                  //local array
    int i1,i2,index;                                // indexes
    for(int i=low;i<=high;++i)                      
    {
         MergeCount++;                              // characteristic operation
         b[i]=a[i];                                 // copy segement elements into local array
    } 
    i1=low;
    i2=mid+1;
    index=low;
    while(i1<=mid && i2<=high)                      // merges in the correct order until one segement reached the middle point
    {
        if(b[i1]<b[i2])
        {
            a[index]=b[i1];                         // move element from local array into segement inputted
            ++i1;                                   // increment local array right segment index
            MergeCount++;                           // characteristic operation
        }
        else
        {
            a[index]=b[i2];                         // move element from local array into segement inputted
            ++i2;                                   // increment local array left segment index
            MergeCount++;                           // characteristic operation
        }
        ++index;                                    // increment segement index
        
    }
    while(i1<=mid)                                  // if right segment index has not reach the midpoint
    {
        a[index]=b[i1];
        ++i1;
        ++index;
        MergeCount++;
    }
    while(i2<=high)                                  // if left segment index has not reach the midpoint
    {
        a[index]=b[i2];
        ++i2;
        ++index;
        MergeCount++;
    }
}
// A function that arranges array segements calls to the merge function
// Precondition: An integer array, the first index , the middle index, the length of the array, and the counter of characteristic operations 
// Postcondition: The integer array as a whole is sorted
void merge_sort(int a[],int low,int high,int &MergeCount)
{
    int mid;
    if(low<high)                                          // if there is an element still in array
    {
        mid=(low+high)/2;                                 // find mid
        merge_sort(a,low,mid,MergeCount);                 // call recusivly on right segement 
        merge_sort(a,mid+1,high,MergeCount);              // call recusivly on left segement
        merge(a,low,mid,high,MergeCount);                 // merge segments

    }
}
// A function that partitions an array about a chosen pivot
// Precondition: An integer array, the first index , the length of the array, the pivot, and the counter of characteristic operations 
// Postcondition: The integer array as a whole is sorted
void partition(int a[],int low,int high,int pivot,int &i,int &j,int &QuickCount)
{
    int lastS1=low-1;                                    // the segement with elements < pivot
    int firstU=low;                                      // the segement with unexamined elements
    int firstS3=high+1;                                  // the segement with elements > pivot
    while(firstU<firstS3)                                // while there is still  unexamined elements
    {
        QuickCount++;                                    // characteristic operation      
        if(a[firstU]<pivot)                              // elements < pivot
        {
            ++lastS1;
            swap(a[firstU],a[lastS1]);
            ++firstU;
        }
        else if(a[firstU]==pivot)                       // elements == pivot
            ++firstU;
        else                                            // elements > pivot
        {
            --firstS3;
            swap(a[firstU],a[firstS3]);
        }  
    }
    i=lastS1;                                           // "return" segement index
    j=firstS3;                                          // "return" segement index
}
// A function that arranges calls to the partition function
// Precondition: An integer array, the first index , the length of the array, and the counter of characteristic operations 
// Postcondition: The integer array as a whole is sorted
void quick_sort(int a[],int low,int high,int &QuickCount)
{
    int pivot;
    int lastS1,firstS3;
    if(low<high)                                          // if there is an element still in array
    {
        pivot=a[low];                                     // choose pivot
        partition(a,low,high,pivot,lastS1,firstS3,QuickCount);  //parition the array
        quick_sort(a,low,lastS1,QuickCount);                    //patitioned array call
        quick_sort(a,firstS3,high,QuickCount);                  //patitioned array call     
    }
}
// A function that makes the array as a heap 
// Precondition: An integer array, the parent index , the length of the array, and the counter of characteristic operations 
// Postcondition: The integer array is a heap
void reheap_down(int a[], int parnet, int last,int &HeapCount)
{
    int max_child;
    bool done=false;
    while(2*parnet+1<=last && !done)                            // until there is a child and not done
    {
        HeapCount++;    
        max_child=2*parnet+1;                                   // left child             
        if(max_child<last && a[max_child+1] > a[max_child])     // if parent has child and right child is bigger than left
        {
            ++max_child;                    // make the max child be the right child
        }
        if(a[max_child]>a[parnet])          // if the bigger child is greater than parent then swap
        {
            int temp=a[parnet];             // swap
            a[parnet]=a[max_child];
            a[max_child]=temp;
            parnet=max_child;
        }
        else                                // else leave loop
        {
            done=true;
        }
    }
}
// A function that calls reheap down to make the array as a heap and to sort the array
// Precondition: An integer array, the length of the array, and the counter of characteristic operations 
// Postcondition: The integer array is a sorted heap
void heap_sort(int arr[],int len,int &HeapCount)
{
    for(int i = (len-2)/2; i>=0;--i)            // make array to look like heap
    {
        reheap_down(arr,i,len-1,HeapCount);
    }
    for(int i = len-1; i>0;--i)                 // make the heap to be sorted
    {
        swap(arr[0],arr[i]);                    // swap root with right most leaf
        reheap_down(arr,0,i-1,HeapCount);       // reheap down the root
    }
    
}
int main()
{
    int seed,randomNum;
    char flag;
    // characteristic operations counters
    int InserCount=0;
    int MergeCount=0;
    int QuickCount=0;
    int HeapCount=0;
    cout<<"Enter the number of values to generate and sort, between 1 and 5000: ";   // values the user wants to be sorted
    cin>>length;
    cout<<"Enter an integer seed value: ";      //seed value
    cin>>seed;
    srand(seed);
    // delcare 4 arrays each for one sorting alogrthim
    int array_insertion[length];            
    int array_Merge[length];
    int array_Quick[length];
    int array_Heap[length];
    for(int x=0;x<length;x++)                   // fill the arrays
    {
        randomNum=(rand()%5000)+1;              // find random numbers between 1->5000
        array_insertion[x]=randomNum;           
        array_Merge[x]=randomNum;
        array_Quick[x]=randomNum;
        array_Heap[x]=randomNum;
    }
    cout<<"Print the values?(y/n)";
    cin>>flag;
    cout<<endl;
    if(flag=='y')                                   // if user want to see the values then print them 
    {
        cout<<"Unsorted Values:"<<endl;             // print all unsorted values
        cout<<"Insertion  Sort Values: "<<endl;
        for(int x=0;x<length;x++)
            cout<<array_insertion[x]<<" ";  
        cout<<endl;
        cout<<"Merge Sort Values: "<<endl;
        for(int x=0;x<length;x++)
            cout<<array_Merge[x]<<" ";
        cout<<endl;
        cout<<"Quick Sort Values: "<<endl;
        for(int x=0;x<length;x++)
            cout<<array_Quick[x]<<" ";
        cout<<endl;
        cout<<"Heap Sort Values: "<<endl;
        for(int x=0;x<length;x++)
            cout<< array_Heap[x]<<" ";
        cout<<endl;

        cout<<endl;
        cout<<"Sorted Values:"<<endl;          
        cout<<"Insertion  Sort Values: "<<endl;
        //sort the arrays
        insertionSort(array_insertion,length,InserCount);   
        merge_sort(array_Merge,0,length-1,MergeCount);
        quick_sort(array_Quick,0,length-1,QuickCount);
        heap_sort( array_Heap,length,HeapCount);

        //print sorted arrays
        for(int x=0;x<length;x++)
            cout<<array_insertion[x]<<" ";  
        cout<<endl;
        cout<<"Merge Sort Values: "<<endl;
        for(int x=0;x<length;x++)
            cout<<array_Merge[x]<<" ";
        cout<<endl;
        cout<<"Quick Sort Values: "<<endl;
        for(int x=0;x<length;x++)
            cout<<array_Quick[x]<<" ";
        cout<<endl;
        cout<<"Heap Sort Values: "<<endl;
        for(int x=0;x<length;x++)
            cout<< array_Heap[x]<<" ";
        cout<<endl;
    }
    else                                                           // if user doesn't want to see arrays then just sort them
    {
        insertionSort(array_insertion,length,InserCount);
        merge_sort(array_Merge,0,length-1,MergeCount);
        quick_sort(array_Quick,0,length-1,QuickCount);
        heap_sort( array_Heap,length,HeapCount);
        cout<<endl;
    }
    // print counts of charactetics operations
    cout<<"Insertion Sort count  = "<<InserCount<<endl; 
    cout<<"Merge Sort count      = "<<MergeCount<<endl; 
    cout<<"Quick Sort count      = "<<QuickCount<<endl; 
    cout<<"Heap Sort count       = "<<HeapCount<<endl;
    
    
    
    // to copy to excel...
    ofstream file;
    file.open("pro8.txt",ofstream::app);
    file<<length<<"  "<<InserCount<<"  "<<MergeCount<<"  "<<QuickCount<<"  "<<HeapCount<<endl;
    

    
}