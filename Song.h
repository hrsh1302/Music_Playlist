#ifndef SETGROUP_SONG_H
#define SETGROUP_SONG_H

#include <string>

using namespace std;

class Song {
private:
    string title;
    string artist;
    string genre;
public:
    Song(const string &title, const string &artist, const string &genre);

    const string &getTitle() const;

    void setTitle(const string &title);

    const string &getArtist() const;

    void setArtist(const string &artist);

    const string &getGenre() const;

    void setGenre(const string &genre);

    bool operator<(const Song &rhs) const;

    void print() const;
};


#endif //SETGROUP_SONG_H
