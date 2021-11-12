#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <sys/stat.h>
#include <cstring>
#include <vector>
#include <sstream>
using namespace std;

// Used to store data about a file
struct Metadata
{
  string filename;
  int mode;
  int startOffset;
  int endOffset;
  int fd;
};

int main(int argc, char *argv[])
{
  vector<char *> filenames;
  vector<Metadata> FileObj;
  int fileCount = argc - 3;
  int metadataOffset = 1000; // limit on the metadata stored
  int fileContentStart = metadataOffset;
  bool fileCountinFile = false;
  int spaceUsed; // used to track of much of the metadata limit is being used

  if (argc == 1)
  {
    cerr << "Usage: ./box COMMAND BOXFILE [FILE]..." << endl;
    exit(EXIT_FAILURE);
  }

  if (strcmp(argv[1], "create") == 0)
  {
    int fdBox = open(argv[2], O_CREAT | O_RDWR | O_APPEND, 0777);

    // extracting all the filenames and storing them in a vector
    for (int i = 3; i < argc; i++)
    {
      filenames.push_back(strdup(argv[i]));
    }

    for (int i = 0; i < fileCount; i++)
    {
      // storing the data of the file in an vector of Metadata
      FileObj.push_back(Metadata());
      FileObj[i].filename = filenames[i];
      FileObj[i].fd = open(filenames[i], O_RDONLY, 0777);

      // if the file was opened successfully
      if (FileObj[i].fd != -1)
      {
        // gets the mode of the opened file
        struct stat stats;
        stat(filenames[i], &stats);
        FileObj[i].mode = stats.st_mode;

        // getting the offset of where the file contents end
        char buffer[100];
        int fileEndLoc;
        while (int readPtr = read(FileObj[i].fd, buffer, 100))
        {
          fileEndLoc += readPtr;
        }

        // storing the start offset of a file
        if (i == 0)
        {
          FileObj[i].startOffset = metadataOffset;
        }
        else
        {
          FileObj[i].startOffset = FileObj[i - 1].endOffset;
        }

        // storing the end offset of a file
        FileObj[i].endOffset = metadataOffset + fileEndLoc;

        // storing filecount in box file
        if (!fileCountinFile)
        {
          string filecount_str = std::to_string(fileCount);
          char const *filecount_char = filecount_str.c_str();
          spaceUsed += write(fdBox, filecount_char, strlen(filecount_char));
          spaceUsed += write(fdBox, "\n", 1);

          fileCountinFile = true;
        }

        // storing filename in box file
        const char *filename_char = FileObj[i].filename.c_str();
        spaceUsed += write(fdBox, filename_char, strlen(filename_char));
        spaceUsed += write(fdBox, " ", 1);

        // storing mode in box file
        string mode_str = std::to_string(FileObj[i].mode);
        char const *mode_char = mode_str.c_str();
        spaceUsed += write(fdBox, mode_char, strlen(mode_char));
        spaceUsed += write(fdBox, " ", 1);

        // storing startOffser in box file
        string startOffset_str = std::to_string(FileObj[i].startOffset);
        char const *startOffser_char = startOffset_str.c_str();
        spaceUsed += write(fdBox, startOffser_char, strlen(startOffser_char));
        spaceUsed += write(fdBox, " ", 1);

        // storing endOffset in box file
        string endOffset_str = std::to_string(FileObj[i].endOffset);
        char const *endOffset_char = endOffset_str.c_str();
        spaceUsed += write(fdBox, endOffset_char, strlen(endOffset_char));
        spaceUsed += write(fdBox, " ", 1);

        // storing fd in box file
        string fd_str = std::to_string(FileObj[i].fd);
        char const *fd_char = fd_str.c_str();
        spaceUsed += write(fdBox, fd_char, strlen(fd_char));
        spaceUsed += write(fdBox, "\n", 1);
      }
      else
      {
        cerr << "ERROR: file cannot be opened" << endl;
        exit(EXIT_FAILURE);
      }
    }

    close(fdBox);

    // sotring the contents of the files in the box file
    int fdBoxContents = open(argv[2], O_RDWR, 0777);
    fileContentStart -= spaceUsed;
    lseek(fdBoxContents, fileContentStart, SEEK_END);

    for (int i = 0; i < fileCount; i++)
    {
      FileObj[i].fd = open(filenames[i], O_RDONLY, 0777);
      char buffer[100];
      while (int readPtr = read(FileObj[i].fd, buffer, 100))
      {
        write(fdBoxContents, buffer, readPtr);
      }

      // deleting the files from the main directory
      unlink(filenames[i]);
    }
  }

  if (strcmp(argv[1], "list") == 0)
  {
    // checking to see if the box file exits
    struct stat boxfile;
    if (stat(argv[2], &boxfile) == 0)
    {
      // reading the contents of the metadata
      int fdBox = open(argv[2], O_RDWR, 0777);
      char buffer[1];
      string temp;
      int i = 0;

      while (int filePtr = read(fdBox, buffer, 1))
      {
        temp += buffer[0];
        if (strncmp(buffer, "\n", 1) == 0)
        {
          stringstream ss(temp);
          ss >> fileCount;
          temp = "";
          break;
        }
      }

      while (read(fdBox, buffer, 1) && i < fileCount)
      {
        temp += buffer[0];
        if (strncmp(buffer, "\n", 1) == 0)
        {
          // getting the filename
          string filename = temp.substr(0, temp.find(" "));
          cout << filename << endl;
          temp = "";
          i++;
        }
      }
    }
    else
    {
      cerr << "ERROR: box file not found" << endl;
      exit(EXIT_FAILURE);
    }
  }

  if (strcmp(argv[1], "unpack") == 0)
  {
    // checking to see if the box file exits
    struct stat boxfile;
    if (stat(argv[2], &boxfile) == 0)
    {
      // reading the contents of the metadata
      int fdBox = open(argv[2], O_RDWR, 0777);
      char buffer[1];
      string temp;
      int i = 0;

      while (int filePtr = read(fdBox, buffer, 1))
      {
        temp += buffer[0];
        if (strncmp(buffer, "\n", 1) == 0)
        {
          stringstream ss(temp);
          ss >> fileCount;
          temp = "";
          break;
        }
      }

      while (read(fdBox, buffer, 1) && i < fileCount)
      {
        temp += buffer[0];
        if (strncmp(buffer, "\n", 1) == 0)
        {
          // storing the metadata in an object
          FileObj.push_back(Metadata());
          stringstream ss(temp);
          string word;
          int j = 0;
          while (ss >> word)
          {
            if (j == 0)
            {
              FileObj[i].filename = word;
              j++;
              continue;
            }
            if (j == 1)
            {
              FileObj[i].mode = stoi(word);
              j++;
              continue;
            }
            if (j == 2)
            {
              FileObj[i].startOffset = stoi(word);
              j++;
              continue;
            }
            if (j == 3)
            {
              FileObj[i].endOffset = stoi(word);
              j++;
              continue;
            }
            if (j == 4)
            {
              FileObj[i].fd = stoi(word);
              j++;
              continue;
            }
          }
          temp = "";
          i++;
        }
      }

      for (int i = 3; i < argc; i++)
      {
        for (int j = 0; j < fileCount; j++)
        {
          if (strdup(argv[i]) == FileObj[j].filename)
          {
            // extracts the contents of the given file from the box file and creates a new file
            int insertedPtr = FileObj[j].startOffset;
            char buffer[1];
            lseek(fdBox, FileObj[j].startOffset, SEEK_SET);
            const char *unpackFile = FileObj[j].filename.c_str();
            int fdUnpack = creat(unpackFile, FileObj[j].mode);

            while (int readPtr = read(fdBox, buffer, 1))
            {
              if (insertedPtr == FileObj[j].endOffset)
              {
                break;
              }
              write(fdUnpack, buffer, readPtr);
              insertedPtr += readPtr;
            }
          }
        }
      }
    }
    else
    {
      cout << "ERROR: box file not found" << endl;
    }
  }
}
