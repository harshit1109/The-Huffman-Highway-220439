#include <iostream>
#include<cmath>
#include <string>
using namespace std;
double op(double a,double b,string s){
 if(s=="+") return a+b;
 if(s=="-") return a-b;
 if(s=="*") return a*b;
 if(s=="/") return a/b;
 if(s=="%") return (int)a%(int)b;
 return 0;
}
double ln(double x){
    return log(x);
}
double Trigno(double x,string s){
    if(s=="sin") return sin(x);
    if(s=="cos") return cos(x);
    if(s=="tan") return tan(x);
    if(s=="cot") return 1/tan(x);
    if(s=="cosec") return 1/sin(x);
    if(s=="sec") return 1/cos(x);
    return 0;
}
double exponential(double x){
    return exp(x);
}
int main(){
    string s1,s2,s3;
    cin>>s1>>s2>>s3;
    int x;
    cin>>x;
    double a,b;
    if(s1=="sin"||s1=="cos"||s1=="tan"||s1=="cot"||s1=="cosec"||s1=="sec"){
       a=Trigno(x,s1);
    }
    if(s1=="ln"){
       a=ln(x);
    }
    if(s1=="e"){
        a=exponential(x);
    }
    if(s3=="sin"||s3=="cos"||s3=="tan"||s3=="cot"||s3=="cosec"||s3=="sec"){
       b=Trigno(x,s3);
    }
    if(s3=="ln"){
       b=ln(x);
    }
    if(s3=="e"){
        b=exponential(x);
    }
    double c=op(a,b,s2);
    cout<<c;
}