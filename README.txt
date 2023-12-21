This program plays with a playlist.txt file that stores all the music in the following format:
	songTitle, songArtist, songGenre

At first this program only sorts the .txt file and outputs all its songs into genre dedicated playlists. 
Program uses sets for each music genre. It reads the file, then stores line by line into which genre a song goes. Ideas to enhance program:

Create a real program, with user input that lets him have options
	- 1) Add data
		Enter song title:
		Enter song artist:
		Enter genre (Pop, Dance, Hip-Hop, Country, R&B, Rock):
		 Check if data entered is already here
		 Output: Entry was added! => songTitle, songArtist, songGenre

	- 2) Look up song
		Enter song title:
		 This will check inside the txt file in lowercase. Take the while-loop from populate() for the first ',' - compare the user input and txt file - return it
		 Output: If found => Entry already exists
			 If not found => Entry isn't in file.

	- 3) Remove data (At once, only enter the songTitle)
		Enter song name:
		 Check if it's in the .txt
		 Output: Entry removed!

	- 3) [DONE] Print out genre playlists
		(Pop [1], Dance [2], Hip-Hop [3], Country [4], R&B [5], Rock [6], or All [7])
