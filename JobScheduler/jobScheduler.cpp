#include "jobScheduler.hpp"

void JobScheduler::SheduleJob(size_t pid, string description)
{
    pair<size_t, string> newPair;
    newPair.first = pid;
    newPair.second = description;

    m_listOfJobs.push_back(newPair);
};

void JobScheduler::ListPendingJobs()
{
    for(size_t i=0; i<m_listOfJobs.size(); i++)
    {
        cout << "Position: " << i << " - PID: " << m_listOfJobs.at(i).first << " - Description: " << m_listOfJobs.at(i).second << endl;
    }
}

