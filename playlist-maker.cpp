#include <iostream>
#include <fstream>
#include <set>
#include <string>

#include "Song.h"

using namespace std;

/**
 * @brief Void function that display the program's header
 */
void menuHeader() {
    cout << "\n======================================================" << endl;
    cout << "\t\tPlaylist Maker Program" << endl;
    cout << "======================================================" << endl;
    cout << "1.  Add song" << endl;
    cout << "2.  Look for song" << endl;
    cout << "3.  Remove song" << endl;
    cout << "4.  Display playlist" << endl;
    cout << "-1. End program" << endl;
    cout << "\nWhat do you want to do today? (Enter the numbered option):  ";
}

/**
 * @brief Adds a new song to the playlist.
 * @param fileName A reference to a string to where the playlist is stored.
 * @param title A reference to a string to store the title of the song.
 * @param artist A reference to a string to store the artist of the song.
 * @param genre A reference to a string to store the genre of the song.
 */
void addSong(const string &fileName, string &title, string &artist, string &genre) {
    ofstream out(fileName, ios::app);

    if (!out.is_open()) {
        std::cerr << "Unable to open file: " << fileName << endl;
        exit(1);
    }

    cin.ignore();
    cout << "You choose to add a song" << endl;
    cout << "  Enter the song's title: ";
    getline(cin, title);
    cout << " Enter the artist of the song: ";
    getline(cin, artist);
    cout << " Enter the genre of the song, " << endl;
    cout << "  Pop / Dance / Hip-Hop / Country / R&B / Rock : ";
    getline(cin, genre);

    Song newSong(title, artist, genre);

    out << "\n" << newSong.getTitle() << "," << newSong.getArtist() << "," << newSong.getGenre();
    cout << "New entry has been added to the playlist!: ";
    newSong.print();
    out.close();
}

/**
 * @brief Removes a song from the playlist.
 * @param fileName A reference to a string to the file name.
 * @param tempFile A reference to a string to the temporary file name.
*/
void removeSong(const string &fileName, const string &tempFile, string &songName) {
    string line;
    ifstream inputFile(fileName);
    ofstream temp(tempFile, ofstream::trunc);

    if (!inputFile.is_open()) {
        cerr << "Unable to open file: " << fileName << endl;
        exit(1);
    }

    if (!temp.is_open()) {
        std::cerr << "Unable to open file: " << "resources\\temp.txt" << endl;
        exit(1);
    }

    while (getline(inputFile, line)) {
        // Check if the line contains the user input, and skip it if found
        if (line.find(songName) == string::npos) {
            temp << line << endl;
        }
    }

    inputFile.close();
    temp.close();

    if (remove(fileName.c_str()) != 0) {
        cerr << "Error removing original file: " << fileName << endl;
        exit(1);
    }

    if (rename("resources\\temp.txt", fileName.c_str()) != 0) {
        cerr << "Error replacing file." << endl;
        exit(1);
    }

    cout << "\nSong has been removed!" << endl;
}

/**
 * @brief Reads the txt file and looks for the song the user entered.
 * @param fileName A reference to a string to the file name.
 * @param songInfo A reference to a string to store song information.
 * @param title A reference to a string to store the title of the song.
 * @param artist A reference to a string to store the artist of the song.
 * @param genre A reference to a string to store the genre of the song.
 * @param songName A reference to a string to store the song's name.
 */
void lookForSong(const string &fileName, string &songInfo,
                 string &title, string &artist, string &genre,
                 string &songName) {
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file: " << fileName << endl;
        exit(1);
    }

    bool songFound = false;

    while (getline(inputFile, songInfo)) {
        int commaPos1 = songInfo.find_first_of(",");
        title = songInfo.substr(0, commaPos1);
        int commaPos2 = songInfo.find(",", commaPos1 + 1);
        artist = songInfo.substr(commaPos1 + 1, commaPos2 - (commaPos1 + 1));
        commaPos1 = commaPos2;
        genre = songInfo.substr(commaPos1 + 1);

        Song newSong(title, artist, genre);

        if (songName == newSong.getTitle()) {
            songFound = true;
            break;
        }
    }

    if (songFound) {
        cout << "It exists" << endl;
    } else {
        cout << "It doesn't exist. You should add it!" << endl;
    }
    inputFile.close();
}

/**
 * @brief Gets the user's genre selection with error handling.
 * @return The selected genre as an int.
 */
int getGenreSelection() {
    int genreSelect;
    while (true) {
        if (!(cin >> genreSelect) || genreSelect < 1 || genreSelect > 7) {
            //Clear the cin data and the buffer for user to re-enter
            cin.clear();
            while (cin.get() != '\n') {}
            cerr << "Invalid genre. Try again.";
        } else {
            break;
        }
    }
    return genreSelect;
}

/**
 * @brief Clears the temporary file used for removal process.
 */
void clearTemp() {
    ofstream temp("resources\\temp.txt", ofstream::trunc);
    if (!temp.is_open()) {
        cerr << "Unable to open file: " << "resources\\temp.txt" << endl;
        exit(1);
    }
    temp.close();
}

/**
 * @brief Populates playlists based on the information from the input file.
 * @param fileName A reference to a string to the file name.
 * @param songInfo A reference to a string to store song information.
 * @param title A reference to a string to store the title of the song.
 * @param artist A reference to a string to store the artist of the song.
 * @param genre A reference to a string to store the genre of the song.
 * @param popSongs Set of Pop songs.
 * @param danceSongs Set of Dance songs.
 * @param hipHopSongs Set of Hip Hop songs.
 * @param countrySongs Set of Country songs.
 * @param rAndBSongs Set of R&B songs.
 * @param rockSongs Set of Rock songs.
 */
void populatePlaylist(const string &fileName, string &songInfo,
                      string &title, string &artist, string &genre,
                      set<Song> &popSongs, set<Song> &danceSongs,
                      set<Song> &hipHopSongs, set<Song> &countrySongs,
                      set<Song> &rAndBSongs, set<Song> &rockSongs) {
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file: " << fileName << endl;
        exit(1);
    }

    while (getline(inputFile, songInfo)) {
        int commaPos1 = songInfo.find_first_of(",");
        title = songInfo.substr(0, commaPos1);
        int commaPos2 = songInfo.find(",", commaPos1 + 1);
        artist = songInfo.substr(commaPos1 + 1, commaPos2 - (commaPos1 + 1));
        commaPos1 = commaPos2;
        genre = songInfo.substr(commaPos1 + 1);

        //Create objects of all songs read from .txt file
        Song newSong(title, artist, genre);

        //Sort songs according to genre
        if (genre == "Pop") {
            popSongs.insert(newSong);
        } else if (genre == "Dance") {
            danceSongs.insert(newSong);
        } else if (genre == "Hip Hop") {
            hipHopSongs.insert(newSong);
        } else if (genre == "Country") {
            countrySongs.insert(newSong);
        } else if (genre == "R&B") {
            rAndBSongs.insert(newSong);
        } else if (genre == "Rock") {
            rockSongs.insert(newSong);
        }
    }

    inputFile.close();
}

/**
 * @brief Void function to print the playlist for a specific genre.
 * @param genre A reference to a string to store the genre of the songs.
 * @param songSet A set of all songs belonging to the specified genre.
 */
auto printPlaylist = [](const string &genre, const set<Song> &songSet) {
    cout << "============================================" << endl;
    cout << "\t\t" << genre << " Playlist\n\n";
    int count = 1;
    for (const auto &song: songSet) {
        cout << count << ": " << song.getTitle() << " - " << song.getArtist() << "\n";
        ++count;
    }
    std::cout << "\n";
};

/**
 * Void function that calls printPlaylist to print out all playlists.
 * @param popSongs Set of all pop songs.
 * @param danceSongs Set of all pop songs.
 * @param hipHopSongs Set of all pop songs.
 * @param countrySongs Set of all pop songs.
 * @param rAndBSongs Set of all pop songs.
 * @param rockSongs Set of all pop songs.
 */
void printAllPlaylist(const set<Song> &popSongs, const set<Song> &danceSongs,
                      const set<Song> &hipHopSongs, const set<Song> &countrySongs,
                      const set<Song> &rAndBSongs, const set<Song> &rockSongs) {
    printPlaylist("Pop", popSongs);
    printPlaylist("Dance", danceSongs);
    printPlaylist("Hip Hop", hipHopSongs);
    printPlaylist("Country", countrySongs);
    printPlaylist("R&B", rAndBSongs);
    printPlaylist("Rock", rockSongs);
}


/**
 * A Playlist Maker Program that manages a music playlist by allowing users to add, look for, remove, and display songs based on genre.
 */
int main() {
    const string MUSIC_PATH = "resources\\musicList.txt";
    const string TEMP_PATH = "resources\\temp.txt";
    string songInformation;
    string title;
    string artist;
    string genre;
    string userSongName;
    int menuSelect;
    int genreSelect;

    set<Song> popSongs, danceSongs, hipHopSongs, countrySongs, rAndBSongs, rockSongs;


    while (true) {
        menuHeader();
        try {
            if (!(cin >> menuSelect)) {
                throw runtime_error("Invalid menu option. Enter an integer: ");
            }

            if (menuSelect == -1) {
                cout << "Thank you! Exiting Program..." << endl;
                break;
            } else if (menuSelect < 1 || menuSelect > 4) {
                throw runtime_error("Invalid menu option. Enter an integer between 1 and 4: ");
            }

            switch (menuSelect) {
                case 1: {
                    addSong(MUSIC_PATH, title, artist, genre);
                    break;
                }
                case 2: {
                    cout << "You choose to look up for a song" << endl;
                    cout << "  Enter the song's title you want to look for (case-sensitive):  ";
                    cin.ignore();
                    getline(cin, userSongName);
                    lookForSong(MUSIC_PATH, songInformation, title, artist, genre, userSongName);
                    break;
                }
                case 3: {
                    cout << "You choose to remove a song" << endl;
                    cout << "  Enter the song's title you want to remove (case-sensitive):  ";
                    cin.ignore();
                    getline(cin, userSongName);
                    removeSong(MUSIC_PATH, TEMP_PATH, userSongName);
                    clearTemp();
                    break;
                }
                case 4: {
                    cout << "  You choose to display playlist. But which one?" << endl;
                    cout << "  Pop[1] / Dance[2] / Hip-Hop[3] / Country[4] / R&B[5] / Rock[6] / All[7]:  ";
                    genreSelect = getGenreSelection();
                    populatePlaylist(MUSIC_PATH, songInformation,
                                     title, artist, genre,
                                     popSongs, danceSongs, hipHopSongs,
                                     countrySongs, rAndBSongs, rockSongs);
                    switch (genreSelect) {
                        case 1:
                            printPlaylist("Pop", popSongs);
                            break;
                        case 2:
                            printPlaylist("Dance", danceSongs);
                            break;
                        case 3:
                            printPlaylist("Hip Hop", hipHopSongs);
                            break;
                        case 4:
                            printPlaylist("Country", countrySongs);
                            break;
                        case 5:
                            printPlaylist("R&B", rAndBSongs);
                            break;
                        case 6:
                            printPlaylist("Rock", rockSongs);
                            break;
                        case 7:
                            printAllPlaylist(popSongs, danceSongs, hipHopSongs,
                                             countrySongs, rAndBSongs, rockSongs);
                            break;
                        default:
                            cout << "Invalid genre";
                    }
                    break;
                }
                default: {
                    break;
                }
            }
        } catch (const runtime_error &e) {
            //Clear the cin data and the buffer for user to re-enter
            cin.clear();
            while (cin.get() != '\n') {}
            cerr << e.what();
        }
    }
    return 0;
}