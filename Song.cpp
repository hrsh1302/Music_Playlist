
#include "Song.h"

using namespace std;

Song::Song(const string &title, const string &artist, const string &genre) : title(title),
                                                                             artist(artist),
                                                                             genre(genre) {}

const string &Song::getTitle() const { return title; }

void Song::setTitle(const string &title) { Song::title = title; }

const string &Song::getArtist() const { return artist; }

void Song::setArtist(const string &artist) { Song::artist = artist; }

const string &Song::getGenre() const { return genre; }

void Song::setGenre(const string &genre) { Song::genre = genre; }

bool Song::operator<(const Song &rhs) const {
    if (title != rhs.title) {
        return title < rhs.title;
    }
    if (artist != rhs.artist) {
        return artist < rhs.artist;
    }
    return genre < rhs.genre;
}