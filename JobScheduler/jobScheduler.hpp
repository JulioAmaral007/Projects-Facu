#ifndef JOB_SCHEDULER_HPP
#define JOB_SCHEDULER_HPP

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class JobScheduler
{
protected:
    vector<pair<size_t, string>> m_listOfJobs;

public:
    JobScheduler(){};
    ~JobScheduler(){};

    void SheduleJob(size_t pid, string description);
    // ProcessJob()

    void ListPendingJobs();
    void ProcessJob() { cout << "Nothing to do at this level" << endl; };
};

#endif
