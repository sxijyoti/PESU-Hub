#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26  // Assuming only lowercase English letters

// Trie Node
struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    int isEndOfWord;  // True if the node represents the end of a word
};

// Trie structure
struct TrieNode* getNode() {
    struct TrieNode* node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    node->isEndOfWord = 0;
    
    // Initialize all children as NULL
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }

    return node;
}

// Insert a word into the Trie
void insert(struct TrieNode* root, const char* word) {
    struct TrieNode* current = root;

    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';  // Convert char to index (0 for 'a', 1 for 'b', etc.)
        
        // Create the child node if it doesn't exist
        if (current->children[index] == NULL) {
            current->children[index] = getNode();
        }
        
        current = current->children[index];
    }

    // Mark the end of the word
    current->isEndOfWord = 1;
}

// Function to print words of a specific length in a Trie
void printWordsOfLength(struct TrieNode* root, char* buffer, int length, int currentLength) {
    if (root == NULL) {
        return;
    }

    // If we've reached the end of a word and the length matches
    if (root->isEndOfWord && currentLength == length) {
        buffer[currentLength] = '\0';  // Null terminate the current word
        printf("%s\n", buffer);        // Print the word
        return;
    }

    // Recurse through all children (i.e., the alphabet letters)
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            buffer[currentLength] = i + 'a';  // Convert index back to character
            printWordsOfLength(root->children[i], buffer, length, currentLength + 1);
        }
    }
}

// Wrapper function to start the process of printing words of a specific length
void printWordsWithLength(struct TrieNode* root, int length) {
    char buffer[length + 1];  // Buffer to store the current word
    printWordsOfLength(root, buffer, length, 0);
}

int main() {
    // Create a new Trie
    struct TrieNode* root = getNode();
    
    // Insert some words into the Trie
    insert(root, "apple");
    insert(root, "app");
    insert(root, "bat");
    insert(root, "ball");
    insert(root, "batman");
    insert(root, "cat");
    
    printf("Words of length 3:\n");
    printWordsWithLength(root, 3);  // Print words of length 3
    
    printf("Words of length 4:\n");
    printWordsWithLength(root, 4);  // Print words of length 4
    
    return 0;
}
