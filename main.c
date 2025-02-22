#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LOG_LENGTH 1024  // Maksimum günlük satýr uzunluðu

// Günlük verilerini tutan baðlý liste düðüm yapýsý
typedef struct LogNode {
    char log[MAX_LOG_LENGTH]; // Günlük verisi
    struct LogNode* next; // Sonraki düðüm adresi
} LogNode;

// Yeni bir düðüm oluþturur ve geri döndürür
LogNode* createNode(const char* log) {
    LogNode* newNode = (LogNode*)malloc(sizeof(LogNode));
    if (newNode) {
        strncpy(newNode->log, log, MAX_LOG_LENGTH); // Günlük verisini kopyala
        newNode->next = NULL; // Sonraki düðümü baþlangýçta NULL yap
    }
    return newNode;
}

// Baðlý listeye yeni bir düðüm ekler (Baþa ekleme yöntemi)
void appendNode(LogNode** head, const char* log) {
    LogNode* newNode = createNode(log); // Yeni düðüm oluþtur
    if (!newNode) return; // Bellek tahsisi baþarýsýzsa çýk
    newNode->next = *head; // Yeni düðümün next'ini mevcut baþ düðüme baðla
    *head = newNode; // Baþý güncelle
}

// Baðlý listeyi ekrana yazdýrýr
void printList(const LogNode* head) {
    while (head) {
        printf("%s", head->log); // Günlük verisini ekrana yazdýr
        head = head->next; // Sonraki düðüme geç
    }
}

// Baðlý listeyi serbest býrakýr (Bellek sýzýntýsýný önlemek için)
void freeList(LogNode* head) {
    while (head) {
        LogNode* temp = head; // Geçici deðiþkene mevcut düðümü ata
        head = head->next; // Baþý güncelle
        free(temp); // Eski düðümü serbest býrak
    }
}

int main() {
    // Linux sistem günlüklerini içeren dosyayý aç
    FILE* file = fopen("/var/log/syslog", "r");
    if (!file) {
        perror("Dosya açýlamadý"); // Dosya açma hatasý durumunda hata mesajý yazdýr
        return 1;
    }
    
    LogNode* logList = NULL; // Baðlý listeyi baþlangýçta boþ oluþtur
    char buffer[MAX_LOG_LENGTH]; // Günlük satýrlarýný saklamak için tampon
    
    // Günlük dosyasýný satýr satýr oku ve baðlý listeye ekle
    while (fgets(buffer, MAX_LOG_LENGTH, file)) {
        appendNode(&logList, buffer);
    }
    
    fclose(file); // Dosyayý kapat
    
    printList(logList); // Günlükleri ekrana yazdýr
    freeList(logList); // Bellek temizliði yap
    return 0;
}
