#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

int main() {
    int n, time_quantum;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
	  //struct Process processes[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }

    cout << "Enter time quantum: ";
    cin >> time_quantum;

    int current_time = 0;
    int completed = 0;
    queue<int> q;
    vector<bool> in_queue(n, false);

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](Process &a, Process &b) {
        return a.arrival_time < b.arrival_time;
    });

    q.push(0);
    in_queue[0] = true;
    current_time = processes[0].arrival_time;

    while (completed < n) {
        if (q.empty()) {
            // No process in ready queue, move current time to next arriving process
            for (int i = 0; i < n; i++) {
                if (!in_queue[i] && processes[i].arrival_time > current_time) {
                    current_time = processes[i].arrival_time;
                    q.push(i);
                    in_queue[i] = true;
                    break;
                }
            }
            continue;
        }

        int idx = q.front();
        q.pop();

        if (processes[idx].remaining_time > time_quantum) {
            processes[idx].remaining_time -= time_quantum;
            current_time += time_quantum;
        } else {
            current_time += processes[idx].remaining_time;
            processes[idx].remaining_time = 0;
            completed++;
            processes[idx].completion_time = current_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
        }

        // Add processes that have arrived by current_time to the queue
        for (int i = 0; i < n; i++) {
            if (!in_queue[i] && processes[i].arrival_time <= current_time) {
                q.push(i);
                in_queue[i] = true;
            }
        }

        // If current process still has remaining time, add it back to queue
        if (processes[idx].remaining_time > 0) {
            q.push(idx);
        }
    }

    // Output results
    cout << "\nPID\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n";
    float total_wt = 0, total_tat = 0;
    for (auto &p : processes) {
        cout << p.pid << "\t" << p.arrival_time << "\t" << p.burst_time << "\t" 
             << p.completion_time << "\t\t" << p.waiting_time << "\t" << p.turnaround_time << "\n";
        total_wt += p.waiting_time;
        total_tat += p.turnaround_time;
    }

    cout << "\nAverage Waiting Time: " << total_wt / n << "\n";
    cout << "Average Turnaround Time: " << total_tat / n << "\n";

    return 0;
}
