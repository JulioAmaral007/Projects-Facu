#include "jobScheduler.hpp"

class Policy2 : public JobScheduler
{
protected:
public:
    Policy2(){};
    ~Policy2(){};

    void ProcessJob()
    {
        cout << "Processing using Policy 2..." << endl;
        pair<size_t, string> job = m_listOfJobs.at(m_listOfJobs.size() - 1);

        cout << "-> Processing job PID: " << job.first << " - Description: " << job.second << endl;
        m_listOfJobs.erase(m_listOfJobs.begin() + m_listOfJobs.size() - 1);
    };
};
