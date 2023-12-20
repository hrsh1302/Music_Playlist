#include <iostream>
#include <fstream>
#include <set>
#include <string>

#include "Song.h"

using namespace std;

//Method that prints out according to genre passed and its set
auto printPlaylist = [](const string &genre, const set<Song> &songSet) {
    cout << genre << " song playlist\n";
    int count = 1;
    for (const auto &song : songSet) {
        cout << count << ": " << song.getTitle() << " - " << song.getArtist() << "\n";
        ++count;
    }
    std::cout << "\n";
};

//Prints out all the genre
void printAllPlaylist(const std::set<Song> &popSongs, const std::set<Song> &danceSongs,
                      const std::set<Song> &hipHopSongs, const std::set<Song> &countrySongs,
                      const std::set<Song> &rAndBSongs, const std::set<Song> &rockSongs) {
    printPlaylist("Pop", popSongs);
    cout << "=============================================" << endl;
    printPlaylist("Dance", danceSongs);
    cout << "=============================================" << endl;
    printPlaylist("Hip Hop", hipHopSongs);
    cout << "=============================================" << endl;
    printPlaylist("Country", countrySongs);
    cout << "=============================================" << endl;
    printPlaylist("R&B", rAndBSongs);
    cout << "=============================================" << endl;
    printPlaylist("Rock", rockSongs);
}

int main() {
    string filename = "resources\\musicList.txt";
    ifstream inputFile(filename);
    string songInformation;
    string title;
    string artist;
    string genre;

    //Creating sets for all genres
    set<Song> popSongs, danceSongs, hipHopSongs, countrySongs, rAndBSongs, rockSongs;


    while (getline(inputFile, songInformation)) {
        int commaPos1 = songInformation.find_first_of(",");
        title = songInformation.substr(0, commaPos1);
        int commaPos2 = songInformation.find(",", commaPos1 + 1);
        artist = songInformation.substr(commaPos1 + 1, commaPos2 - (commaPos1 + 1));
        commaPos1 = commaPos2;
        genre = songInformation.substr(commaPos1 + 1);

        Song newSong(title, artist, genre);

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

    printAllPlaylist(popSongs, danceSongs, hipHopSongs, countrySongs, rAndBSongs, rockSongs);

//    printPlaylist("Pop", popSongs);
//    printPlaylist("Dance", danceSongs);
//    printPlaylist("Hip Hop", hipHopSongs);
//    printPlaylist("Country", countrySongs);
//    printPlaylist("R&B", rAndBSongs);
//    printPlaylist("Rock", rockSongs);



    return 0;
}
