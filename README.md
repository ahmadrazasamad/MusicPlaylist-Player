# Music-Playlist Player & Manager
The Music Playlist Manager is a C++ console application that enables users to create and manage a music playlist using a doubly circular linked list. The program provides functionalities to add new songs, search for specific songs, play the playlist in both linear and circular fashions, display all songs, display songs by a specific release year, and delete songs.
## Features
- **Add New Song:** Add songs to the playlist with details such as song name, singer name, year of release, and duration.
- **Play Playlist (Linear):** Play all songs in the playlist sequentially.
- **Play Playlist (Circular):** Continuously play the playlist in a loop until stopped by the user.
- **Search Song:** Search for a specific song in the playlist by its name.
- **Display All Songs:** Display the complete list of songs in the playlist with details.
- **Display Songs by Year:** Display all songs released in a specific year.
- **Delete Song:** Remove the first song from the playlist.
- **Delete All Songs:** Remove all songs from the playlist.
## Installation
1. Clone the repository or download the source code.
2. Open the project in a C++ IDE or compile using a C++ compiler.
3. Ensure the playlist.txt file is in the same directory as the executable.
## Usage
1. Run the program.
2. Follow the on-screen prompts to perform various operations on your music playlist.
3. You can exit the program by choosing not to perform any further operations.
## Files
- **main.cpp:**  The main program file containing the source code.
- **playlist.txt:** A text file that stores the playlist data.
## How It Works
- The playlist is implemented as a doubly circular linked list.
- Songs are added to the end of the playlist and can be played in sequence or looped.
- The playlist data is saved in `playlist.txt` and loaded upon program startup.
## Contributing
Contributions are welcome! If you find a bug or have a suggestion for improvement, please open an issue or submit a pull request. 
