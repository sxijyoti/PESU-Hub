#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct Message {
    char content[300];
    char sender[30];
    struct Message *next;
    struct Message *prev;
} Message;

typedef struct Chat {
    Message *head;
    Message *tail;
} Chat;

typedef struct User {
    char username[30];
    Chat chatHistory;
    struct User *next; 
} User;

User *userDirectory[MAX_USERS];

int hashFunction(const char* username) {
    int hash = 0;
    for (int i = 0; username[i] != '\0'; i++) {
        hash = (hash + username[i]) % MAX_USERS;
    }
    return hash;
}

void createUser(const char* username) {
    int index = hashFunction(username);
    User* newUser = (User*)malloc(sizeof(User));
    strcpy(newUser->username, username);
    newUser->chatHistory.head = NULL;
    newUser->chatHistory.tail = NULL;
    newUser->next = userDirectory[index];
    userDirectory[index] = newUser;
}

User* findUser(const char* username) {
    int index = hashFunction(username);
    User* temp = userDirectory[index];
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

Message* createMessage(const char* content, const char* senderId) {
    Message* newMessage = (Message*)malloc(sizeof(Message));
    strcpy(newMessage->content, content);
    strcpy(newMessage->sender, senderId);
    newMessage->next = newMessage->prev = NULL;
    return newMessage;
}

void sendMessage(User* user, const char* content, const char* senderId) {
    Message* newMessage = createMessage(content, senderId);
    if (user->chatHistory.tail == NULL) {
        user->chatHistory.head = user->chatHistory.tail = newMessage;
    } else {
        user->chatHistory.tail->next = newMessage;
        newMessage->prev = user->chatHistory.tail;
        user->chatHistory.tail = newMessage;
    }
}

void listMessages(User* user) {
    Message* cur_msg = user->chatHistory.head;
    if (cur_msg == NULL) {
        printf("No messages for user %s.\n", user->username);
        return;
    }
    printf("\nChat history for user %s:\n", user->username);
    printf("------------------------\n");
    while (cur_msg != NULL) {
        printf("%s: %s\n", cur_msg->sender, cur_msg->content);
        cur_msg = cur_msg->next;
    }
    printf("------------------------\n");
}

void listAllMessages() {
    int found = 0;
    for (int i = 0; i < MAX_USERS; i++) {
        User* user = userDirectory[i];
        while (user != NULL) {
            if (user->chatHistory.head != NULL) {
                listMessages(user);
                found = 1;
            }
            user = user->next;
        }
    }
    if (!found) {
        printf("No messages found for any users.\n");
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    // Initialize user directory
    for (int i = 0; i < MAX_USERS; i++) {
        userDirectory[i] = NULL;
    }

    int num_user;
    char user_name[30];

    printf("Enter number of users: ");
    scanf("%d", &num_user);
    clearInputBuffer();

    for (int i = 0; i < num_user; i++) {
        printf("Enter username %d: ", i+1);
        fgets(user_name, sizeof(user_name), stdin);
        user_name[strcspn(user_name, "\n")] = 0;
        createUser(user_name);
    }

    char senderId[20], chat_mes[300];

    while (1) {
        printf("Enter sender ID (or type 'exit' to finish): ");
        fgets(senderId, sizeof(senderId), stdin);
        senderId[strcspn(senderId, "\n")] = 0;
        
        if (strcmp(senderId, "exit") == 0) {
            break;
        }

        User* sender = findUser(senderId);
        if (sender == NULL) {
            printf("User not found.\n");
            continue;
        }

        while (1) {
            printf("Enter message (or press Enter to finish): ");
            fgets(chat_mes, sizeof(chat_mes), stdin);
            chat_mes[strcspn(chat_mes, "\n")] = 0;

            if (strlen(chat_mes) == 0) {
                break;
            }

            sendMessage(sender, chat_mes, senderId);
        }
    }

    printf("\nDo you want to view chat history? (yes/no): ");
    char choice[5];
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = 0;

    if (strcmp(choice, "yes") == 0) {
        printf("View chat history for (all/specific): ");
        char historyChoice[10];
        fgets(historyChoice, sizeof(historyChoice), stdin);
        historyChoice[strcspn(historyChoice, "\n")] = 0;

        if (strcmp(historyChoice, "all") == 0) {
            listAllMessages();
        } else if (strcmp(historyChoice, "specific") == 0) {
            printf("Enter user ID to view chat history: ");
            char userId[20];
            fgets(userId, sizeof(userId), stdin);
            userId[strcspn(userId, "\n")] = 0;
            
            User* user = findUser(userId);
            if (user != NULL) {
                listMessages(user);
            } else {
                printf("User not found.\n");
            }
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}