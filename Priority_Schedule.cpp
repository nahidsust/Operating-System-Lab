#include <bits/stdc++.h>
using namespace std;
struct process {
    int pid;
    int arrival;
    int burst;
    int priority;
    int completion;
    int turnaround;
    int waiting;
    bool done = false;
};

bool cmpArrival(const process &a, const process &b) {
    if (a.arrival == b.arrival)
        return a.priority < b.priority;
    return a.arrival < b.arrival;
}

int main() {
    int n;
    cout << "Enter Number of Processes: ";
    cin >> n;

    struct process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Enter Arrival time ,burst time and Priority" << p[i].pid << ": ";
        cin >> p[i].arrival >> p[i].burst >> p[i].priority;
    }

    int time = 0, completed = 0;
    while (completed < n) {
        int idx = -1;
        int min_priority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].arrival <= time && p[i].priority < min_priority) {
                min_priority = p[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            time = max(time, p[idx].arrival);
            p[idx].completion = time + p[idx].burst;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            time = p[idx].completion;
            p[idx].done = true;
            completed++;
        } else {
            time++; 
        }
    }
    int awt = 0;
    for (int i = 0; i < n; i++) {
        awt += p[i].waiting;
        cout << p[i].pid << "   " << p[i].arrival << "   " << p[i].burst << "  " << p[i].priority
             << "  " << p[i].completion << "   " << p[i].turnaround << "    " << p[i].waiting << endl;
    }
    return 0;
}
