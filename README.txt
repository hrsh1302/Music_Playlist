# Playlist Maker Program

A C++ program that serves as a Playlist Maker, allowing users to manage a music playlist by performing operations such as adding, looking up, removing, and displaying songs based on genre.

## Introduction

This program provides a simple and interactive interface for managing a music playlist. Users can add new songs to the playlist, look up existing songs, remove songs, and display playlists based on different genres. The program utilizes file I/O to store and retrieve the playlist data.

## Features

- Add Song: Users can add a new song to the playlist by providing details such as title, artist, and genre.

- Look for Song: Users can search for a specific song in the playlist by entering the song's title.

- Remove Song: Users can remove a song from the playlist by specifying the title of the song they want to delete.

- Display Playlist: Users can view playlists based on different genres (Pop, Dance, Hip Hop, Country, R&B, Rock) or display the entire playlist.

## Getting started

Clone the repository:

```bash
git clone https://github.com/your-username/playlist-maker.git
cd playlist-maker
```

Compile the program:

```bash
g++ -o playlist_maker playlist_maker.cpp Song.cpp
```

Run the executable:

```bash
Copy code
./playlist_maker
```

## Usage

Upon running the program, a menu will be displayed with options to add, look up, remove, or display songs.

Follow the prompts to perform the desired operation.

To exit the program, select option -1.

## File Structure

playlist_maker.cpp: The main source code file containing the Playlist Maker program logic.
Song.cpp: Definition of the Song class used to represent individual songs.
Song.h: Header file for the Song class.

## Contributions

Contributions are welcome! Feel free to open issues or pull requests.

## Licence

[MIT](https://github.com/hrsh1302/Music_Playlist/blob/master/LICENSE)

