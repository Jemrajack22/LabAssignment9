#include <stdio.h>
#include <stdlib.h> // Added for malloc and exit

#define HASH_SIZE 10 // Added hash size constant

// RecordType
struct RecordType
{
    int id;
    char name;
    int order; 
};

// Define a structure for each node in the linked list
struct Node
{
    struct RecordType data;
    struct Node *next;
};

// Define the hash table structure
struct HashType
{
    struct Node *head; // Head of the linked list
};

// Compute the hash function
int hash(int x)
{
    return x % HASH_SIZE; // Simple modulo operation for hashing
}

// Parses input file to an array of RecordType
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

// Prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// Display records in the hash structure
// Skip the indices which are free
// The output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    int i;
    struct Node *temp;

    for (i=0;i<hashSz;++i)
    {
        printf("Index %d -> ", i);
        temp = pHashArray[i].head;
        while (temp != NULL)
        {
            printf("%d %c %d", temp->data.id, temp->data.name, temp->data.order);
            temp = temp->next;
            if (temp != NULL)
            {
                printf(" -> ");
            }
        }
        printf("\n");
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;
    int i;
    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);
    // Your hash implementation

    // Create hash table
    struct HashType hashTable[HASH_SIZE];
    // Initialize hash table
    for (i = 0; i < HASH_SIZE; ++i)
    {
        hashTable[i].head = NULL;
    }
    // Insert records into hash table
    for (i = 0; i < recordSz; ++i)
    {
        int index = hash(pRecords[i].id);
        struct Node *newNode = (struct Node*) malloc(sizeof(struct Node));
        newNode->data = pRecords[i];
        newNode->next = NULL;
        if (hashTable[index].head == NULL)
        {
            hashTable[index].head = newNode;
        }
        else
        {
            struct Node *temp = hashTable[index].head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    // Display records in hash table
    displayRecordsInHash(hashTable, HASH_SIZE);
    return 0;
}
