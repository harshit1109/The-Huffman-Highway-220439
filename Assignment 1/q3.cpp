#include <iostream>
using namespace std;
int main(){
    float arr[10];
    float sum=0;
    float lowest=INT32_MAX;
    float highest=INT32_MIN;
    for(int i=0;i<10;i++){
        cin>>arr[i];
        sum+=arr[i];
        lowest=min(lowest,arr[i]);
        highest=max(highest,arr[i]);
    }
    float avg=sum/10;
    cout<<"The average exam score is "<<avg<<endl;
    cout<<"The highest exam score is "<<highest<<endl;
    cout<<"The lowest exam score is "<<lowest<<endl;
    cout<<"The exam scores above average are "<<endl;
    for(int i=0;i<10;i++){
        if(arr[i]>avg){
            cout<<arr[i]<<" ";
        }
    }
    cout<<endl;
    cout<<"The exam scores below average are "<<endl;
    for(int i=0;i<10;i++){
        if(arr[i]<avg){
            cout<<arr[i]<<" ";
        }
    }
}