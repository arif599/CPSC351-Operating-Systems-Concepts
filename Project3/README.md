# Project 3
---
## Group Members
Arifulla Shaik (arifullashaik@csu.fullerton.edu)

Angarag Gansukh (angaraggansukh@csu.fullerton.edu)

Lea Albano (leaalbano@csu.fullerton.edu)

---

# box.cpp
**Summary:** When the create command is called, we extract all the file names and store them in a struct. This Metadata struct contains all the information about the files such as the name, mode, start offset, end offset, and the fd. Once this information is calculated, the metadata gets stored in the box file. After the Metadata limit offset, the contents of the files get stored. When the list command is called, the Metadata within the box file is read and the names of the files are extracted and printed out. When the unpack command is called, the contents of the files given as arguments are extracted from the box file and a new file is created with the original mode and name. 




---

# rebuild.cpp
**Summary:** We watch file activity by using inotify. We store all the given files in a vector and then add all the files to our inotify watch that is watching for any modifications. At the same time, we keep track of all the files in a hash map where the watch descriptor is the key and the file name is the value. We watch for any file modifications and if there is one, we will print out which file has been modified using our hash map. Since we are given a command to execute once there is a modification the first time, we created a child process that is also watching for mofications and once there is a modification it will execute the given command. The parent process will wait for the child to finish then continue to watch for more file modifications. 
