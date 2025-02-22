#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LOG_LENGTH 1024  // Maksimum g�nl�k sat�r uzunlu�u

// G�nl�k verilerini tutan ba�l� liste d���m yap�s�
typedef struct LogNode {
    char log[MAX_LOG_LENGTH]; // G�nl�k verisi
    struct LogNode* next; // Sonraki d���m adresi
} LogNode;

// Yeni bir d���m olu�turur ve geri d�nd�r�r
LogNode* createNode(const char* log) {
    LogNode* newNode = (LogNode*)malloc(sizeof(LogNode));
    if (newNode) {
        strncpy(newNode->log, log, MAX_LOG_LENGTH); // G�nl�k verisini kopyala
        newNode->next = NULL; // Sonraki d���m� ba�lang��ta NULL yap
    }
    return newNode;
}

// Ba�l� listeye yeni bir d���m ekler (Ba�a ekleme y�ntemi)
void appendNode(LogNode** head, const char* log) {
    LogNode* newNode = createNode(log); // Yeni d���m olu�tur
    if (!newNode) return; // Bellek tahsisi ba�ar�s�zsa ��k
    newNode->next = *head; // Yeni d���m�n next'ini mevcut ba� d���me ba�la
    *head = newNode; // Ba�� g�ncelle
}

// Ba�l� listeyi ekrana yazd�r�r
void printList(const LogNode* head) {
    while (head) {
        printf("%s", head->log); // G�nl�k verisini ekrana yazd�r
        head = head->next; // Sonraki d���me ge�
    }
}

// Ba�l� listeyi serbest b�rak�r (Bellek s�z�nt�s�n� �nlemek i�in)
void freeList(LogNode* head) {
    while (head) {
        LogNode* temp = head; // Ge�ici de�i�kene mevcut d���m� ata
        head = head->next; // Ba�� g�ncelle
        free(temp); // Eski d���m� serbest b�rak
    }
}

int main() {
    // Linux sistem g�nl�klerini i�eren dosyay� a�
    FILE* file = fopen("/var/log/syslog", "r");
    if (!file) {
        perror("Dosya a��lamad�"); // Dosya a�ma hatas� durumunda hata mesaj� yazd�r
        return 1;
    }
    
    LogNode* logList = NULL; // Ba�l� listeyi ba�lang��ta bo� olu�tur
    char buffer[MAX_LOG_LENGTH]; // G�nl�k sat�rlar�n� saklamak i�in tampon
    
    // G�nl�k dosyas�n� sat�r sat�r oku ve ba�l� listeye ekle
    while (fgets(buffer, MAX_LOG_LENGTH, file)) {
        appendNode(&logList, buffer);
    }
    
    fclose(file); // Dosyay� kapat
    
    printList(logList); // G�nl�kleri ekrana yazd�r
    freeList(logList); // Bellek temizli�i yap
    return 0;
}
