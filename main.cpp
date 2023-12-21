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
    cout << "======================================================" << endl;
    cout << "\t\tPlaylist Maker Program" << endl;
    cout << "======================================================" << endl;
    cout << "1.  Add song" << endl;
    cout << "2.  Look for song" << endl;
    cout << "3.  Remove song" << endl;
    cout << "4.  Display playlist" << endl;
    cout << "\nWhat do you want to do today? (Enter the numbered option):  ";
}

/**
 * @brief Populates playlists based on the information from the input file.
 * @param inputFile The input file stream.
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

void populatePlaylist(ifstream &inputFile, string &songInfo,
                      string &title, string &artist, string &genre,
                      set<Song> &popSongs, set<Song> &danceSongs,
                      set<Song> &hipHopSongs, set<Song> &countrySongs,
                      set<Song> &rAndBSongs, set<Song> &rockSongs) {

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

}

/**
 * @brief Void function to print the playlist for a specific genre.
 * @param genre The genre of the songs to be printed.
 * @param songSet The set of songs belonging to the specified genre.
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
void printAllPlaylist(const std::set<Song> &popSongs, const std::set<Song> &danceSongs,
                      const std::set<Song> &hipHopSongs, const std::set<Song> &countrySongs,
                      const std::set<Song> &rAndBSongs, const std::set<Song> &rockSongs) {
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
    string filename = "resources\\musicList.txt";
    ifstream inputFile(filename);
    string songInformation;
    string title;
    string artist;
    string genre;
    int menuSelect;
    int genreSelect;

    //Creating sets for all genres
    set<Song> popSongs, danceSongs, hipHopSongs, countrySongs, rAndBSongs, rockSongs;

    //File error handling
    if (!inputFile.is_open()) {
        cerr << "Error opening the file: " << filename << endl;
        exit(1);
    }

    menuHeader();

    while (true) {
        try {
            if (!(cin >> menuSelect)) {
                throw runtime_error("Invalid menu option. Enter an integer: ");
            }

            switch (menuSelect) {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    cout << "  What genre do you want to display?" << endl;
                    cout << "  Pop[1] / Dance[2] / Hip-Hop[3] / Country[4] / R&B[5] / Rock[6] / All[7]:  ";
                    genreSelect = getGenreSelection();

                    populatePlaylist(inputFile, songInformation,
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
                default:
                    throw runtime_error("Invalid menu option. Enter an integer: ");
            }
            break;
        } catch (const runtime_error &e) {
            //Clear the cin data and the buffer for user to re-enter
            cin.clear();
            while (cin.get() != '\n') {}
            cerr << e.what();
        }
    }
    return 0;
}