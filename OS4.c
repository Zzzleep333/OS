#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct str_from_list {
        char* str;
        struct str_from_list* next_str;
};

typedef struct str_from_list String;

void str_copy(char* str1, char* str2) {
        if (strlen(str1) < strlen(str2)) {
                perror("Error");
                exit(-1);
        }
        for (int i = 0; i < strlen(str2) + 1; i++) {
                str1[i] = str2[i];
        }
}


void push(String** head, char* str) {
        String* tmp = (String*)malloc(sizeof(String));
        if (!tmp) {
                perror("Memory error\n");
                exit(-1);
        }
        tmp->str = str;
        tmp->next_str = (*head);
        (*head) = tmp;
}


String* getLast(String* head) {
        if (head == NULL) {
                return NULL;
        }
        while (head->next_str) {
                head = head->next_str;
        }
        return head;
}

String* getLastButOne(String* head) {
        if (head == NULL) {
                exit(-2);
        }
        if (head->next_str == NULL) {
                return NULL;
        }
        while (head->next_str->next_str) {
                head = head->next_str;
        }
        return head;
}

void popBack(String** head) {
        String* lastbn = NULL;
        if (!head) {
                exit(-1);
        }
        if (!(*head)) {
                exit(-1);
        }
        lastbn = getLastButOne(*head);
        if (lastbn == NULL) {
                free(*head);
                *head = NULL;
        }
        else {
                free((lastbn->next_str)->str);
                free(lastbn->next_str);
                lastbn->next_str = NULL;
        }
}

int main() {
        int max_len = 25;
        String* head = NULL;
        char* tmp;
        do {
                tmp = (char*)malloc(max_len);
                if (!tmp) {
                        perror("Memory error\n");
                        exit(-1);
                }
                fgets(tmp, 25, stdin);
                int len = strlen(tmp);
                while (*(tmp + len - 1) != '\n') {
                        char* str = (char*)malloc(max_len);
                        if (!str) {
                                perror("Memory error\n");
                                exit(-1);
                        }
                        str_copy(str, tmp);
                        max_len += max_len;
                        free(tmp);
                        tmp = (char*)malloc(max_len);
                        if (!tmp) {
                                perror("Memory error\n");
                                exit(-1);
                        }
                        str_copy(tmp, str);
                        fgets(tmp + len, max_len / 2, stdin);
                        len = strlen(tmp);
                        free(str);
                }
                if (strcmp(tmp, ".\n") == 0) {
                        break;
                }
                push(&head, tmp);
        } while (1);
        while (getLast(head)) {
                printf("%s", getLast(head)->str);
                popBack(&head);
        }
        return 0;
}

