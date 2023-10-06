#include "jobScheduler.hpp"

class Policy1 : public JobScheduler
{
protected:
public:
    Policy1(){};
    ~Policy1(){};

    void ProcessJob()
    {
        cout << "Processing using Policy 2..." << endl;
        pair<size_t, string> job = m_listOfJobs.at(0);

        cout << "-> Processing job PID: " << job.first << " - Description: " << job.second << endl;
        m_listOfJobs.erase(m_listOfJobs.begin() + 0);
    };
};
