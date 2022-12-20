
#include "jobScheduler.hpp"
#include "policy1.hpp"
#include "policy2.hpp"

int main()
{
    // object
    JobScheduler scheduler;

    Policy1 *p1 = (Policy1 *)&scheduler;
    Policy2 *p2 = (Policy2 *)&scheduler;

    while (true)
    {
        cout << "1.Schedule a Job" << endl;
        cout << "2.Process a Job Policy 1 (FIFO)" << endl;
        cout << "3.Process a Job Policy 2 (LIFO)" << endl;
        cout << "4.Show Pending Tasks" << endl;
        cout << "5.Close scheduler" << endl;

        int option;
        cin >> option;

        if (option == 1)
        {
            size_t pid;
            string description;
            cout << "Enter PID: ";
            cin >> pid;
            cout << "Enter Description: ";
            cin >> description; // pendencia: leitura com espacos

            scheduler.SheduleJob(pid, description);
            continue;
        }
        if (option == 2)
        {
            p1->ProcessJob();
            continue;
        }
        if (option == 3)
        {
            p2->ProcessJob();
            continue;
        }
        if (option == 4)
        {
            scheduler.ListPendingJobs();
            continue;
        }
        if (option == 5)
        {
            break;
        }
    }
    return 0;
};
