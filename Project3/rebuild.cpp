#include <iomanip>
#include <iostream>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

using namespace std;
#define BUF_LEN 2048 * (sizeof(struct inotify_event) + 32)

int main(int argc, char *argv[])
{

    char buf[BUF_LEN];
    vector<char *> files;
    int inotify_fd = 0;
    int rc;
    struct inotify_event *event = NULL;
    map<int, string> eventFiles;

    inotify_fd = inotify_init();

    rc = fork();

    if (rc == 0)
    {
        vector<char *> args;
        args.push_back(strdup(argv[1]));
        args.push_back(NULL);
        for (int i = 2; i < argc; i++)
        {
            // wild card
            string file = strdup(argv[i]);
            if (file[0] == '*')
            {
                // ex: find all the files that have .cpp extension
                string extension = file.substr(1, file.length());
            }
            else
            {
                files.push_back(strdup(argv[i]));
            }
        }
        for (int i = 0; i < files.size(); i++)
        {
            int wd = inotify_add_watch(inotify_fd, files[i], IN_MODIFY);
            eventFiles[wd] = files[i];
        }

        cout << "Watching for changes to ";
        for (int i = 0; i < files.size(); i++)
        {
            cout << files[i] << " ";
        }
        cout << "..." << endl;

        // int i = 0;
        while (1)
        {
            int n = read(inotify_fd, buf, BUF_LEN);
            char *p = buf;

            while (p < buf + n)
            {
                event = (struct inotify_event *)p;
                uint32_t mask = event->mask;

                if (mask & IN_MODIFY)
                {

                    // string str(event->name);
                    cout << eventFiles[event->wd] << " has changed...\n";

                    execvp(args[0], args.data());
                }
            }
        }
    }
    else
    {
        int rc_wait = wait(NULL);
        for (int i = 2; i < argc; i++)
        {
            // wild card
            string file = strdup(argv[i]);
            if (file[0] == '*')
            {
                // ex: find all the files that have .cpp extension
                string extension = file.substr(1, file.length());
            }
            else
            {
                files.push_back(strdup(argv[i]));
            }
        }
        for (int i = 0; i < files.size(); i++)
        {
            int wd = inotify_add_watch(inotify_fd, files[i], IN_MODIFY);
            eventFiles[wd] = files[i];
        }

        cout << "Watching for changes to ";
        for (int i = 0; i < files.size(); i++)
        {
            cout << files[i] << " ";
        }
        cout << "..." << endl;

        while (1)
        {
            int n = read(inotify_fd, buf, BUF_LEN);
            char *p = buf;

            while (p < buf + n)
            {
                event = (struct inotify_event *)p;
                uint32_t mask = event->mask;

                if (mask & IN_MODIFY)
                {

                    cout << eventFiles[event->wd] << " has changed...\n";

                    cout << "Watching for changes to ";
                    for (int i = 0; i < files.size(); i++)
                    {
                        cout << files[i] << " ";
                    }
                    cout << "..." << endl;
                }

                p += sizeof(struct inotify_event) + event->len;
            }
        }
    }

    return 0;
}
