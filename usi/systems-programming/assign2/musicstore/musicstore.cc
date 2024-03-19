/*
 * Author: Jeferson Morales Mariciano.
 * Artist title are unique. 2 identical artistcareer means the same artistcareer.
 * Album names are unique only for a given artistcareer. 2 identical albumrecords names doesn't mean always the same albumrecords.
 * For query functions, they have as parameters query filters that will match data in the musicstore and then
 * the last callback parameter function will be used for that instance.
 *
 * multimap used to sublinear complexity.
 *
 * To DEBUG put in makefile the flag -DDEBUG
 * To look for memory leaks put in makefile the flag -ggdb3, then
 * run in the cmd line: valgrind --leak-check=full --show-leak-kinds=all ./ms
 */
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <dirent.h>

#include "musicstore.h"

using namespace std;
const set<string> supported_formats = {".flac", ".mp3", ".mpc", ".ogg", ".wma"};
const string DELIMITER = " - ";

#pragma region STRUCTS
/*
 * songs contains a reference to its artist instance and its album instance.
 * also the sequence of the song on the album and its own title.
 */
struct song {
    const struct albumrecords* album = nullptr;
    unsigned sequence = 0;
    string title;
};

struct song_compare {
    bool operator()(const song* lhs, const song* rhs) const { return lhs->sequence < rhs->sequence; }
};

/*
 * the title of the albumrecords is the 'key' to the struct,
 * giving a set of songs on the albumrecords: O(1) lookup
 */
struct albumrecords {
    const struct artistcareer* artist = nullptr;
    string title;
    map<string, song*> songs;
    set<song*, song_compare> songs_ordered;
};

/*
 * the title of the artistcareer is the 'key' to the struct,
 * giving the albums indexed by title as 'key' to the struct
*/
struct artistcareer {
    string name;
    map<string, albumrecords*> albums;  // albumrecords title -> albumrecords records
    unsigned total_songs = 0;    // maybe useless
};

/*
 * each musicstore object represents a collection of music files, each containing a song
 * from an albumrecords by a certain artistcareer.
 * info: artistcareer, albums, songs retrieved by title so either bfs and dfs are fine for input reading
*/
struct musicstore {
    map<string, artistcareer*> artists;  // title -> artist_career, artist are sure to be unique
    multimap<string, albumrecords*> albums;  // more than one artist can have the same album named e.g. the greatest hits
    multimap<string, song*> songs;   // more than one artist can have the same song named e.g. I love you
};
#pragma endregion

#pragma region CONSTRUCTOR DESTRUCTOR
/**
 * Constructor of the music store.
 * @return pointer to dynamically allocated music store in heap
 */
musicstore* ms_create() { return new musicstore(); }

/**
 * Destructor of the music store.
 * @param ms destroys the dynamically allocated music store object in heap
 */
void ms_destroy(musicstore* ms) {
    for (auto& song : ms->songs) delete song.second;
    for (auto& album : ms->albums) delete album.second;
    for (auto& artist : ms->artists) delete artist.second;
    delete ms;
}
#pragma endregion

#pragma region INPUT
/**
 * read from directory and add all music files to the music store, with their related info.
 * @param s music store struct pointer
 * @param dirname string of directory title
 * @return 1 if successful, 0 otherwise
 */
int ms_read_from_directory(struct musicstore* s, const char* dirname) {
    // get pointer to directory and check if its valid
    DIR *dir_ptr = opendir(dirname);
    if (dir_ptr == nullptr) {
        // cerr << "Error: cannot open directory " << dirname << endl;
        return 0;
    }

    // get all directory entries through stream buffer
    struct dirent *dirent_ptr;
    while ((dirent_ptr = readdir(dir_ptr)) != nullptr) {
        // read directory entries until null pointer (end buffer) is reached

        if (dirent_ptr->d_type == DT_DIR) {
#ifdef DEBUG
            // cout << "DIRECTORY: " << dirent_ptr->d_name << endl; // debug
#endif

            // if the directory is not . or .., then recursively call this function
            // hidden folders are ignored
            if (dirent_ptr->d_name[0] == '.') continue;

            // if the directory is valid, recursively visit the subdirectories
            string new_dir = dirname + string("/") + dirent_ptr->d_name;
            if (!ms_read_from_directory(s, new_dir.c_str())) {
                // cerr << "Error: cannot read from directory " << new_dir << endl;
                continue;
            }

        } else if (dirent_ptr->d_type == DT_REG) {
#ifdef DEBUG
            cout << "FILE: " << dirent_ptr->d_name << endl; // debug
#endif

            // inspecting a file, check if it is a supported format
            // if so, add it to the music store
            string filename = dirent_ptr->d_name;
            string extension = filename.substr(filename.find_last_of('.'));

            // if the file extension is not a supported format, ignore it
            if (supported_formats.find(extension) == supported_formats.end()) {
                // cout << "Ignoring - not supported extension: " << dirent_ptr->d_name << endl;
                continue;
            }

            // read files in format:
            // artist-name - album-title - song-number - song-title.extension
            // e.g. The Beatles - Abbey Road - 01 - Come Together.mp3
            string::size_type pos = filename.find(DELIMITER);
            if (pos == string::npos) {
                // cout << "Ignoring - invalid file format artist: " << filename << endl;
                continue;
            }
            string artist_str = filename.substr(0, pos);
            filename.erase(0, pos + DELIMITER.length());
            pos = filename.find(DELIMITER);
            if (pos == string::npos) {
                // cout << "Ignoring - invalid file format album: " << filename << endl;
                continue;
            }
            string album_str = filename.substr(0, pos);
            filename.erase(0, pos + DELIMITER.length());
            pos = filename.find(DELIMITER);
            if (pos == string::npos) {
                // cout << "Ignoring - invalid file format sequence: " << filename << endl;
                continue;
            }
            unsigned sequence;
            try {
                sequence = stoi(filename.substr(0, pos));
            } catch (invalid_argument& e) {
                // cout << "Ignoring - invalid file format sequence: " << filename.substr(0, pos) << endl;
                continue;
            }
            filename.erase(0, pos + DELIMITER.length());
            pos = filename.find_last_of('.');
            if (pos == string::npos) {
                // cerr << "Error - song must not happen because extension and set used: " << filename << endl;
                continue;
            }
            string song_str = filename.substr(0, pos);  // ignored file format
            // check if the artist doesn't exist yet - view artistcareer
            artistcareer* artist;
            if (s->artists.find(artist_str) == s->artists.end()) {
                // if not, create a new artistcareer and add it to the music store
                artist = new artistcareer();
                artist->name = artist_str;
                artist->total_songs = 0;
                s->artists[artist_str] = artist;   // put and also copy instance on map
            }
            artist = s->artists[artist_str];   // get pointer to the artistcareer in the music store

            // check if the albumrecords already exists - view albumrecords
            albumrecords* album;
            if (artist->albums.find(album_str) == artist->albums.end()) {
                // if not, create a new albumrecords and add it to the artistcareer and the music store
                album = new albumrecords();
                album->title = album_str;
                album->artist = artist;
                artist->albums[album_str] = album; // put and also copy instance on map
                s->albums.insert({album_str, album});      // put and also copy instance on map
            }
            album = s->artists[artist_str]->albums[album_str];    // retrieve safe memory alloc

            // create always instance - songs are not unique
            // link the artist and album instances
            song* new_song = new song();
            new_song->album = album;
            new_song->sequence = sequence;
            new_song->title = song_str;
            // add the song to the musicstore and albumrecords of artistcareer
            s->songs.insert({song_str, new_song});
            album->songs[song_str] = new_song;
            album->songs_ordered.insert(new_song);
            artist->total_songs++;
        } else {
            // cout << "Ignoring - not a file or directory: " << dirent_ptr->d_name << endl;
            continue;
        }
    }
    closedir(dir_ptr);
#ifdef DEBUG
    cout << "FINISHED READING FROM DIRECTORY: " << dirname << endl;
#endif
    return 1;
}
#pragma endregion

#pragma region METHODS
/**
 * Return the artists in alphabetical order.
 * @param s music store
 * @param artist name of the artist c_str
 * @param cb callback function pointer: artist name, albums count, songs count
 */
void ms_get_artist(const struct musicstore* s, const char* artist, artist_callback cb) {
    if (artist == nullptr) {
        // interact all artists
        for (const pair<string, artistcareer*> a : s->artists) {
            cb(a.first.c_str(), a.second->albums.size(), a.second->total_songs);
        }
    } else {
        // interact a specific artistcareer
        auto it = s->artists.find(artist);
        if (it == s->artists.end()) return;     // if not found, ignore it
        cb(artist, it->second->albums.size(), it->second->total_songs);
    }
}

/**
 * Return the artist and albums in alphabetical order in the callback.
 * @param s musicstore pointer
 * @param artist artist name c_str
 * @param album album title c_str
 * @param cb callback function pointer: artist name, album title, songs count
 */
void ms_get_albums(const struct musicstore* s, const char* artist, const char* album, album_callback cb) {
    if (artist == nullptr && album == nullptr) {
        // get all albums
        for (const pair<string, albumrecords*> a : s->albums) {
            cb(a.second->artist->name.c_str(), a.first.c_str(), a.second->songs.size());
        }
    } else if (artist != nullptr && album != nullptr) {
        auto artist_queried = s->artists.find(artist);
        if (artist_queried == s->artists.end()) return;     // if not found, ignore it
        auto album_queried = artist_queried->second->albums.find(album);
        if (album_queried == artist_queried->second->albums.end()) return;     // if not found, ignore it
        cb(artist, album, album_queried->second->songs.size());
    } else if (artist == nullptr) {
        // interact with albumrecords from specific artist
        auto range = s->albums.equal_range(album);
        for (auto al = range.first; al != range.second; al++) {
            cb(al->second->artist->name.c_str(), al->first.c_str(), al->second->songs.size());
        }
    } else { //if (artist != nullptr) {
        // interact with specific artist albums
        auto artists_queried = s->artists.find(artist);
        if (artists_queried == s->artists.end()) return;     // if not found, ignore artists_queried
        for (const pair<string, albumrecords*> ar : artists_queried->second->albums) {
            cb(artist, ar.first.c_str(), ar.second->songs.size());
        }
    }
}

/**
 * Return the artist and albums in alphabetical order in the callback.
 * @param s musicstore pointer
 * @param artist artist name c_str
 * @param album album title c_str
 * @param title song title c_str
 * @param cb callback function: artist name, album title, song sequence number, song title
 */
void ms_get_songs(const struct musicstore* s, const char* artist, const char* album, const char* title,
        song_callback cb) {

    if (artist == nullptr && album == nullptr && title == nullptr) {
        // print ordered songs, sorted by artist name, album title and sequence number
        for (const pair<string, artistcareer*> ar : s->artists)
            for (const pair<string, albumrecords*> al : ar.second->albums)
                for (const song* so : al.second->songs_ordered)
                    cb(ar.first.c_str(), al.first.c_str(), so->sequence, so->title.c_str());
    } else if (artist != nullptr && album != nullptr && title != nullptr) {
        // print specific song
        auto artist_queried = s->artists.find(artist);
        if (artist_queried == s->artists.end()) return;     // if not found, ignore it
        auto album_queried = artist_queried->second->albums.find(album);
        if (album_queried == artist_queried->second->albums.end()) return;     // if not found, ignore it
        auto song_queried = album_queried->second->songs.find(title);
        if (song_queried == album_queried->second->songs.end()) return;     // if not found, ignore it
        cb(artist, album, song_queried->second->sequence, title);
    } else if (artist == nullptr && album == nullptr && title != nullptr) {
        // print all songs with specific title, no order because all songs have the same title
        auto matching_songs = s->songs.equal_range(title);
        for (auto so = matching_songs.first; so != matching_songs.second; so++) {
            cb(so->second->album->artist->name.c_str(), so->second->album->title.c_str(), so->second->sequence, title);
        }
    } else if (artist == nullptr && album != nullptr && title == nullptr) {
        // print all songs from specific album, ordered by album title and sequence song number
        auto matching_albums = s->albums.equal_range(album);
        for (auto al = matching_albums.first; al != matching_albums.second; al++) {
            for (const song* so : al->second->songs_ordered) {
                cb(al->second->artist->name.c_str(), album, so->sequence, so->title.c_str());
            }
        }
    } else if (artist == nullptr && album != nullptr && title != nullptr) {
        // print all songs with specific title from specific album, ordered artist name and album title
        auto matching_albums = s->albums.equal_range(album);
        for (auto al = matching_albums.first; al != matching_albums.second; al++) {
            auto matching_songs = al->second->songs.equal_range(title);
            for (auto so = matching_songs.first; so != matching_songs.second; so++) {
                cb(al->second->artist->name.c_str(), album, so->second->sequence, title);
            }
        }
    } else if (artist != nullptr && album == nullptr && title == nullptr) {
        // print all songs from specific artist, ordered by artist name, album title and song sequence number
        auto artist_queried = s->artists.find(artist);
        if (artist_queried == s->artists.end()) return;     // if not found, ignore it
        for (const pair<string, albumrecords*> al : artist_queried->second->albums) {
            for (const song* so : al.second->songs_ordered) {
                cb(artist, al.first.c_str(), so->sequence, so->title.c_str());
            }
        }
    } else if (artist != nullptr && album == nullptr && title != nullptr) {
        // print all songs with specific artist and title, ordered by album title
        auto artist_queried = s->artists.find(artist);
        if (artist_queried == s->artists.end()) return;     // if not found, ignore it
        for (const pair<string, albumrecords*> al : artist_queried->second->albums) {
            auto matching_songs = al.second->songs.equal_range(title);
            for (auto so = matching_songs.first; so != matching_songs.second; so++) {
                cb(artist, al.first.c_str(), so->second->sequence, title);
            }
        }
    } else if (artist != nullptr && album != nullptr && title == nullptr) {
        // print all songs from specific artist and album, ordered by artist name, album title and song sequence number
        auto artist_queried = s->artists.find(artist);
        if (artist_queried == s->artists.end()) return;     // if not found, ignore it
        auto album_queried = artist_queried->second->albums.find(album);
        if (album_queried == artist_queried->second->albums.end()) return;     // if not found, ignore it
        for (const song* so : album_queried->second->songs_ordered) {
            cb(artist, album, so->sequence, so->title.c_str());
        }
    }
}
#pragma endregion
