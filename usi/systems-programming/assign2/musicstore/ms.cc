#include <iostream>
#include <ostream>
#include <cassert>
#include <string>
#include <vector>

#include "musicstore.h"

#pragma region CALLBACKS

void song_print(const char *artist, const char *album, unsigned sequence, const char *title) {
    std::cout << "Artist: " << artist << ", Album: " << album << "Track (" << sequence << "): " << title << std::endl;
}

void album_print(const char *artist, const char *album, unsigned songs_count) {
    std::cout << "Artist: " << artist << ", Album: " << album << ", Songs: " << songs_count << std::endl;
}

void artist_print(const char *artist, unsigned albums_count, unsigned songs_count) {
    std::cout << "Artist: " << artist << ", Albums: " << albums_count << ", Songs: " << songs_count << std::endl;
}

#pragma endregion

// ms -i;
// ...;
// ms;
int main(int argc, char *argv[]) {
    // check if "-i" passed as string, hence interactive shell
    //
    bool prompt;
    if (argc > 1 && std::string(argv[1]) == "-i") prompt = true;
    else prompt = false;
    std::vector<struct musicstore *> M;
    unsigned i = 0;
    M.push_back(ms_create());
    assert(M[0]);

    std::string artist, album, title, command;

    // executed only once if not interactive shell "-i" set
    for (std::cout << (prompt ? "> " : "") << std::flush;
         std::getline(std::cin, command);
         std::cout << (prompt ? "> " : "") << std::flush) {

        if (command.substr(0, 1) == "?") {
            // print info of current data and music store
            std::cout << "M: " << i << std::endl
                      << "artist: " << artist << std::endl
                      << "album: " << album << std::endl
                      << "title: " << title << std::endl;
        } else if (command.substr(0, 1) == "+") {
            // add new music store instance
            i = M.size();
            M.push_back(ms_create());
            assert(M[i]);
            std::cout << i << std::endl;
        } else if (command.substr(0, 1) == "-") {
            // remove music store instance (free memory): -0 to remove first instance
            unsigned j = stoul(command.substr(1, std::string::npos));
            ms_destroy(M[j]);
            M[j] = nullptr;
        } else if (command.substr(0, 1) == "=") {
            // set music store instance to interact with: =0 to set first instance
            i = stoul(command.substr(1, std::string::npos));
        } else if (command.substr(0, 1) == ">") {
            // print a comment to the console
            std::cout << command.substr(1, std::string::npos) << std::endl;
        } else if (command.substr(0, 8) == "artist: ") {
            // get from console artist title (space excluded): artist: The Beatles
            artist = command.substr(8, std::string::npos);
        } else if (command.substr(0, 7) == "album: ") {
            // get from console album title (space excluded): album: Beatles album
            album = command.substr(7, std::string::npos);
        } else if (command.substr(0, 7) == "title: ") {
            // get from console the song title (space excluded): title: Lemon Tree
            title = command.substr(7, std::string::npos);
        } else if (command.substr(0, 5) == "read ") {
            // get from console directory title to read (space excluded): read tests
            std::string dir = command.substr(5, std::string::npos);

            if (!ms_read_from_directory(M[i], dir.c_str()))
                std::cout << "errors in reading directory '" << dir << "'" << std::endl;
        } else if (command == "get_songs") {
            // retrieve all songs from the music store matching the artist, album, title and
            // then call the callback function in every song the function found
            ms_get_songs(M[i],
                         (artist.length() > 0 ? artist.c_str() : nullptr),
                         (album.length() > 0 ? album.c_str() : nullptr),
                         (title.length() > 0 ? title.c_str() : nullptr),
                         song_print);
        } else if (command == "get_artist") {
            // retrieve all artists from the music store matching the artist and
            // then call the callback function in every artist the function found
            ms_get_artist(M[i], (artist.length() > 0 ? artist.c_str() : nullptr), artist_print);
        } else if (command == "get_albums") {
            // retrieve all albums from the music store matching the artist and
            // then call the callback function on every album the function found
            ms_get_albums(M[i],
                          (artist.length() > 0 ? artist.c_str() : nullptr),
                          (album.length() > 0 ? album.c_str() : nullptr),
                          album_print);
        } else {
            // print that given command was unknown
            std::cout << "unknown command: '" << command << "'" << std::endl;
        }
    }

    for (struct musicstore *m: M) {
        std::cout << "destroying music store" << std::endl;
        if (m) {
            std::cout << "deleted!" << std::endl;
            ms_destroy(m);
        }
    }
}
