#include <iostream>
#include <string>
#include <fstream>
#include <cctype>    // for tolower
#include <ctime>     // for time functions
#include <limits>    // for numeric_limits
#include <windows.h> // for Sleep
using namespace std;

struct song
{
    int yrReleased, duration;
    string songName, singerName;
    song *next;
    song *prev;
};
song *head = nullptr; // initially the playlist is empty
song *tail = nullptr;

// helping functions (starts here)
string trim(const string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    if (first == string::npos || last == string::npos)
        return ""; // If the string contains only whitespace characters
    return str.substr(first, last - first + 1);
}

void addInLinkedList(string songName, string singerName, int yearReleased, int durationOfSong)
{
    song *temp = new song();
    temp->songName = songName;
    temp->singerName = singerName;
    temp->yrReleased = yearReleased;
    temp->duration = durationOfSong;
    if (head == nullptr)
    {
        head = temp;
        tail = temp;
        head->next = tail; // in the case when there is only one song
        tail->prev = head;
    }
    else
    {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
    // for circular fashion
    head->prev = tail;
    tail->next = head;
}
// helping functions (ends here)

void addNewSong()
{
    string songName = "";
    cout << "Enter name of song: ";
    getline(cin, songName);

    songName = trim(songName);
    while (songName.empty())
    {
        cout << "Name of the song cannot be empty or contain whitespaces only! Kindly re-enter the name of the song again: ";
        getline(cin, songName);
        songName = trim(songName);
    }

    string singerName = "";
    cout << "Enter name of singer of the song '" << songName << "': ";
    getline(cin, singerName);

    singerName = trim(singerName);
    while (singerName.empty())
    {
        cout << "Name of the singer cannot be empty or contain whitespaces only! Kindly re-enter the name of the singer again: ";
        getline(cin, singerName);
        singerName = trim(singerName);
    }

    int yr = 0;
    cout << "Enter release year of song: ";
    while (true)
    {
        cin >> yr;

        time_t now = time(0);
        tm *ltm = localtime(&now);
        int currentYear = 1900 + ltm->tm_year;

        if (cin.fail() || yr <= 0 || yr > currentYear) // Check if input is numeric and valid (i.e. neither negative nor greater than the current yr)
        {
            cout << "Invalid year! Please enter a valid release year between 1900 and " << currentYear << ": ";
            cin.clear();                                         // Clear the error flag set by invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        }
        else
            break;
    }
    cin.ignore(); // to ignore the remaining newline character

    int minutes = 0, seconds = 0;
    cout << "Enter the duration of the song in both combined: 1) Minutes and 2) Seconds\n";
    cout << "o) Minutes: ";

    while (true)
    {
        cin >> minutes;
        if (cin.fail() || minutes < 0)
        {
            cout << "Invalid minutes input! Please enter a positive number that represents duration in minute(s): ";
            cin.clear();                                         // Clear the error flag set by invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        }
        else
            break;
    }
    cin.ignore();

    cout << "o) Seconds: ";
    while (true)
    {
        cin >> seconds;
        if (cin.fail() || seconds < 0 || (minutes == 0 && seconds == 0))
        {
            cout << "Invalid seconds input! Please enter a positive number that represents duration in second(s): ";
            cin.clear();                                         // Clear the error flag set by invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        }
        else
            break;
    }
    cin.ignore();

    int totalDuration = (minutes * 60) + seconds;

    addInLinkedList(songName, singerName, yr, totalDuration);

    ofstream outFile("playlist.txt", ios::out | ios::app);
    outFile << "o) Song Name: " << songName << endl;
    outFile << "   Singer Name: " << singerName << endl;
    outFile << "   Released in year: " << yr << endl;
    outFile << "   Duration: " << totalDuration << " second(s).\n";
    outFile.close(); // closing file (append mode)

    cout << tail->songName << " added successfully.\n";
}

void playingPlaylistLinear()
{
    if (head == nullptr)
    {
        cout << "The playlist is empty please insert/add some songs in the playlist first.\n";
        return;
    }

    song *temp = head;
    do
    {
        cout << "Now playing: " << temp->songName << " by- " << temp->singerName << endl;
        Sleep(temp->duration * 1000); // Sleep for the duration in milliseconds
        temp = temp->next;
    } while (temp != head);
}

void playingPlaylistCircular()
{
    if (head == nullptr)
    {
        cout << "The playlist is empty! Please insert/add some songs in the playlist first.\n";
        return;
    }

    song *temp = head;
    while (true)
    {
        cout << "Now playing: " << temp->songName << " by- " << temp->singerName << endl;
        Sleep(temp->duration * 1000); // Sleep for the duration in milliseconds
        temp = temp->next;

        if (temp == head)
        {
            char choice = '\0';
            cout << "The playlist is completely played. Do you want to play the playlist again. Press 'y' to continue and any other key to go back to the menu: ";
            cin >> choice;
            cin.ignore();
            choice = tolower(choice);
            if (choice != 'y')
                break;
        }
    }
}

void searchSong()
{
    if (head == nullptr)
    {
        cout << "The playlist is empty! Please insert/add some songs in the playlist first.\n";
        return;
    }

    string songName = "";
    cout << "Enter name of the song: ";
    getline(cin, songName);

    songName = trim(songName);
    while (songName.empty())
    {
        cout << "Name of the song cannot be empty or contain whitespaces only! Kindly re-enter the name of the song again: ";
        getline(cin, songName);
        songName = trim(songName);
    }

    bool found = false;
    song *temp = head;
    do
    {
        if (temp->songName == songName)
        {
            found = true;
            cout << "o) Song Name: " << temp->songName << endl;
            cout << "   Singer Name: " << temp->singerName << endl;
            cout << "   Released in year: " << temp->yrReleased << endl;
            cout << "   Duration: " << temp->duration << " second(s).\n\n";
        }
        temp = temp->next;
    } while (temp != head);

    if (!found)
        cout << "No song with this name: '" << songName << "', found in the playlist.";
}

void displayAllSongs()
{
    if (head == nullptr)
    {
        cout << "The playlist is empty! Please insert/add some songs in the playlist first.\n";
        return;
    }

    song *temp = head;
    do
    {
        cout << "o) Song Name: " << temp->songName << endl;
        cout << "   Singer Name: " << temp->singerName << endl;
        cout << "   Released in year: " << temp->yrReleased << endl;
        cout << "   Duration: " << temp->duration << " second(s).\n\n";

        temp = temp->next;
    } while (temp != head);
}

void displaySongsSpecificByYear()
{
    if (head == nullptr)
    {
        cout << "The playlist is empty! Please insert/add some songs in the playlist first.\n";
        return;
    }

    int yrOfRelease = 0;
    cout << "Enter release year of song: ";
    while (true)
    {
        cin >> yrOfRelease;

        if (cin.fail() || yrOfRelease <= 0) // Check if input is numeric and valid
        {
            cout << "Invalid year! Please enter a valid release year: ";
            cin.clear();                                         // Clear the error flag set by invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        }
        else
            break;
    }
    cin.ignore(); // to ignore the remaining newline character

    bool found = false;
    song *temp = head;
    do
    {
        if (temp->yrReleased == yrOfRelease)
        {
            found = true;
            cout << "o) Song Name: " << temp->songName << endl;
            cout << "   Singer Name: " << temp->singerName << endl;
            cout << "   Released in year: " << temp->yrReleased << endl;
            cout << "   Duration: " << temp->duration << " second(s).\n\n";
        }
        temp = temp->next;
    } while (temp != head);

    if (!found)
        cout << "No song with release year " << yrOfRelease << " found in the playlist.\n";
}

void deleteSong()
{
    if (head == nullptr)
    {
        cout << "The playlist is empty. No song to delete.\n";
        return;
    }

    song *temp = head;
    if (head == tail) // Only one song in the playlist
        head = tail = nullptr;
    else
    {
        head = head->next;
        tail->next = head;
        head->prev = tail;
    }

    ifstream inFile("playlist.txt");
    string line = "";
    string contentAfterDeletion = "";

    for (int i = 1; i <= 4; i++)
    { // getting the first four lines
        getline(inFile, line);
        contentAfterDeletion += line + (i == 4 ? "": "\n");
    }
    contentAfterDeletion += "\n";

    for (int i = 1; i <= 4; i++) // getting the next four lines as it will be the first song that is to be deleted
        getline(inFile, line);

    while (getline(inFile, line))
        contentAfterDeletion += line + "\n";
    inFile.close(); // closing the file (reading mode)

    ofstream outFile("playlist.txt");
    outFile << contentAfterDeletion;
    outFile.close(); // closing the file (writing mode)

    cout << temp->songName << " deleted sucessfully!\n";
    delete temp;
}

void deleteAllSong()
{
    while (head != nullptr)
        deleteSong();
}

void initializePlaylist()
{
    ifstream inFile("playlist.txt");
    string line = "";

    for (int i = 1; i <= 4; i++) // getting the starting 4 lines
        getline(inFile, line);
    while (getline(inFile, line))
    {
        string songName = line.substr(14);
        getline(inFile, line);
        string singerName = line.substr(16);
        getline(inFile, line);
        string year = line.substr(21);
        int yearReleased = stoi(year);
        getline(inFile, line);
        string duration = line.substr(13);
        int i = 0;
        string dOfSong = "";
        while (!isspace(duration[i])) {
            dOfSong += duration[i];
            i++;
        }
        int durationOfSong = stoi(dOfSong);

        addInLinkedList(songName, singerName, yearReleased, durationOfSong);
    }
    inFile.close(); // closing the file (reading mode)
}

int main()
{
    ifstream inFile("playlist.txt");
    if (!inFile)
    {
        cout << "Error opening file for reading." << endl;
        return 1;
    }
    string line = "";
    getline(inFile, line);
    inFile.close(); // closing the file (reading mode)

    string userName = "";
    string playlistName = "";
    if (line.empty())
    {
        ofstream outFile("playlist.txt", ios::out | ios::trunc); // emptying the file becuase since the first line is empty and hence there is a possibility that there has been some unknown modification in the file
        outFile.close();                                         // closing the file (truncation mode)

        cout << "\t\t\tWelcome to Music-Playlist Player\n";

        cout << "Enter your name please: ";
        getline(cin, userName);

        userName = trim(userName);
        while (userName.empty())
        {
            cout << "Username cannot be empty or contain whitespaces! Kindly re-enter your name: ";
            getline(cin, userName);
            userName = trim(userName);
        }

        cout << "Enter the name of playlist please: ";
        getline(cin, playlistName);

        playlistName = trim(playlistName);
        while (playlistName.empty())
        {
            cout << "Playlist name cannot be empty or contain whitespaces! Kindly re-enter the playlist name: ";
            getline(cin, playlistName);
            playlistName = trim(playlistName);
        }

        ofstream outFile1("playlist.txt");
        if (!outFile1)
        {
            cout << "Error opening file for writing." << endl;
            return 1;
        }
        // Writing username and playlist name to the file
        outFile1 << "Username: " << userName << endl;
        outFile1 << "Playlist name: " << playlistName << endl;
        outFile1 << endl;
        outFile1 << "Songs:\n";
        outFile1.close(); // closing the file (writing mode)
    }
    else
    {
        userName = line.substr(10);

        cout << "\t\t\t" << userName << ", Welcome to Music-Playlist Player\n";
        ifstream inFile1("playlist.txt");
        getline(inFile1, line);
        getline(inFile1, line);
        playlistName = line.substr(15);
        inFile1.close();

        initializePlaylist();
    }

    char choice = '\0';
    do
    {
        int opt = 0;
        cout << "\nHere is the list of operations " << userName << " you can do with the playlist " << playlistName << ":\n1) Add new song\n2) Play Playlist(linear fashion)\n3) Play Playlist(circular fashion)\n4) Search a song\n5) Display all songs in the playlist\n6) Display song specific by year of release\n7) Delete first song of the playlist\n8) Delete all songs of the playlist\nEnter your choice: ";
        cin >> opt;
        cout << endl;

        if (cin.fail() || opt <= 0 || opt > 8)
        { // cin.fail() for checking if the input is not interger i.e string or char
            cout << "Invalid character entered.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            cin.ignore();
            switch (opt)
            {
            case 1:
                addNewSong();
                break;
            case 2:
                playingPlaylistLinear();
                break;
            case 3:
                playingPlaylistCircular();
                break;
            case 4:
                searchSong();
                break;
            case 5:
                displayAllSongs();
                break;
            case 6:
                displaySongsSpecificByYear();
                break;
            case 7:
                deleteSong();
                break;
            case 8:
                deleteAllSong();
                break;
            }
        }

        cout << "\nDo you want to do more operations. Press 'Y' to continue and any other key to exit: ";
        cin >> choice;
        cin.ignore();

        choice = tolower(choice);
    } while (choice == 'y');

    cout << "Thanks for using the program.\n";

    return 0;
}