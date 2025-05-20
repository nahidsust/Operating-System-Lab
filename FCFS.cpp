#include<bits/stdc++.h>
using namespace std;
struct process{
int pid;
int arrival;
int burst;
int completion;
int turnaround;
int waiting;
};
bool srt(const process&a,const process&b){
        if (a.arrival == b.arrival)
        return a.pid < b.pid;
         return a.arrival<b.arrival;
}
int main(){
    int n;
    cout<<"Inter Number of Processes:";
    cin>>n;
    struct process p[n];
    for(int i=0;i<n;i++){
	p[i].pid=i+1;
	cout<<"Enter Arrival time and Burst time for  process: "<<p[i].pid<<endl;
	cin>>p[i].arrival>>p[i].burst;
    }
    sort(p,p+n,srt);       
    int time=0;
    for (int i=0;i<n;i++) {
        if (time<p[i].arrival)
            time=p[i].arrival;
        p[i].completion=time+p[i].burst;
        p[i].turnaround=p[i].completion-p[i].arrival;
        p[i].waiting=p[i].turnaround-p[i].burst;
        time=p[i].completion;
    }
    int awt=0;
    cout<<"PID"<<" "<<"AT"<<" "<<"BT"<<" "<<"CT"<<" "<<"TAT"<<" "<<"WT"<<endl;
    for (int i=0;i<n;i++) {
	      awt+=p[i].waiting;
cout<<p[i].pid<<" "<<p[i].arrival<<" "<<p[i].burst<<" "<<p[i].completion<<" "<<p[i].turnaround<<" "<<p[i].waiting<<endl;
    }
    cout<<awt;
}