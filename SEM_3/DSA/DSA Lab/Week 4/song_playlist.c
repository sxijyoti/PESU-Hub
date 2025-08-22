/* You are tasked with managing a playlist of songs using a doubly linked list. 
Each song has a unique song_id, a title, and a duration (in seconds). 
Your task is to implement a function to split the playlist into two parts based on a given duration. 
The first part of the playlist should contain all songs with a duration less than or equal to the given duration, 
and the second part should contain all songs with a duration greater than the given duration. 
The function should modify the original playlist and return the head of the second part. */

// Input Format

// Number of Songs in the Playlist: N (Integer)
// Songs: N lines, each containing the song_id (integer), title (string), and duration (integer).
// Split Duration: D (Integer) - The duration used to split the playlist.

// Output Format

// First Playlist: Print the songs in the first part of the playlist, sorted by their original order.
// Second Playlist: Print the songs in the second part of the playlist, sorted by their original order.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
   int song_id;
   char title[256];
   int duration;
   struct Song* prev;
   struct Song* next;
} Song;

typedef struct {
   Song* head;
   Song* tail;
} Playlist;

// Function prototypes
Playlist* createPlaylist();
void addSong(Playlist* playlist, int song_id, const char* title, int duration);
Song* splitPlaylist(Playlist* playlist, int duration);
void printPlaylist(Playlist* playlist);
void freePlaylist(Playlist* playlist);

int main() {
   int N;
   scanf("%d", &N);
    Playlist* playlist = createPlaylist();
    for (int i = 0; i < N; i++) {
       int song_id, duration;
       char title[256];
       scanf("%d", &song_id);
       getchar(); // Consume the newline character
       fgets(title, 256, stdin);
       title[strcspn(title, "\n")] = '\0'; // Remove newline character
       scanf("%d", &duration);
       addSong(playlist, song_id, title, duration);
   }
    int D;
   scanf("%d", &D);
   Song* secondPartHead = splitPlaylist(playlist, D);
    // Print the first playlist
   printf("The first part of the playlist\n");
   printPlaylist(playlist);
    // Print the second part
   Playlist secondPart = { secondPartHead, NULL };
   printf("The second part of the playlist\n");
   printPlaylist(&secondPart);
    // Free memory
   freePlaylist(playlist);
   freePlaylist(&secondPart);
    return 0;
}

// Create a new playlist
Playlist* createPlaylist() {
   Playlist* playlist = (Playlist*)malloc(sizeof(Playlist));
   playlist->head = NULL;
   playlist->tail = NULL;
   return playlist;
}

// Add a song to the playlist
void addSong(Playlist* playlist, int song_id, const char* title, int duration) {
   Song* newSong = (Song*)malloc(sizeof(Song));
   newSong->song_id = song_id;
   strncpy(newSong->title, title, sizeof(newSong->title));
   newSong->duration = duration;
   newSong->prev = NULL;
   newSong->next = NULL;

   if (playlist->head == NULL) {
       playlist->head = playlist->tail = newSong;
   } else {
       playlist->tail->next = newSong;
       newSong->prev = playlist->tail;
       playlist->tail = newSong;
   }
}

// Split the playlist based on the given duration
Song* splitPlaylist(Playlist* playlist, int duration) {
   //Write the code here
    Playlist secondPart = { NULL, NULL };
    Song* cur = playlist->head;
    while (cur != NULL) {
        Song* next = cur->next;
        if (cur->duration > duration) {
            if (cur->prev != NULL) {
                cur->prev->next = cur->next;
            } else {
                playlist->head = cur->next;
            }
            if (cur->next != NULL) {
                cur->next->prev = cur->prev;
            } else {
                playlist->tail = cur->prev;
            }
            if (secondPart.head == NULL) {
                secondPart.head = secondPart.tail = cur;
                cur->prev = NULL;
                cur->next = NULL;
            } else {
                secondPart.tail->next = cur;
                cur->prev = secondPart.tail;
                secondPart.tail = cur;
                cur->next = NULL;
            }
        }
 
        cur = next;
    }
 
    return secondPart.head; 
}

// Print all songs in the playlist
void printPlaylist(Playlist* playlist) {
   //Write the code here
    Song* cur = playlist->head;
    while (cur != NULL) {
        printf("%d %s %d\n", cur->song_id, cur->title,cur->duration);
        cur = cur->next;
    }
 }

// Free all nodes in the list
void freePlaylist(Playlist* playlist) {
   Song* current = playlist->head;
   Song* next;
   while (current != NULL) {
       next = current->next;
       free(current);
       current = next;
   }
}