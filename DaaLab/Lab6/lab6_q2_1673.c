#include <stdio.h>
#include <stdlib.h>

// Structure to represent a symbol (character) and its frequency
struct SYMBOL
{
    char alphabet;
    int frequency;
};

// Structure to represent a node in the Huffman tree
struct Node
{
    struct SYMBOL symbol;
    struct Node *left;
    struct Node *right;
};

// Min-Priority Queue Node
struct MinPriorityQueueNode
{
    struct Node *data;
    struct MinPriorityQueueNode *next;
};

// Min-Priority Queue structure
struct MinPriorityQueue
{
    struct MinPriorityQueueNode *front;
};

// Function to create a new Min-Priority Queue node
struct MinPriorityQueueNode *createMinPriorityQueueNode(struct Node *data)
{
    struct MinPriorityQueueNode *newNode = (struct MinPriorityQueueNode *)malloc(sizeof(struct MinPriorityQueueNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new Min-Priority Queue
struct MinPriorityQueue *createMinPriorityQueue()
{
    struct MinPriorityQueue *newQueue = (struct MinPriorityQueue *)malloc(sizeof(struct MinPriorityQueue));
    newQueue->front = NULL;
    return newQueue;
}

// Function to insert a node into the Min-Priority Queue
void enqueue(struct MinPriorityQueue *queue, struct Node *data)
{
    struct MinPriorityQueueNode *newNode = createMinPriorityQueueNode(data);
    if (queue->front == NULL || data->symbol.frequency < queue->front->data->symbol.frequency)
    {
        newNode->next = queue->front;
        queue->front = newNode;
    }
    else
    {
        struct MinPriorityQueueNode *current = queue->front;
        while (current->next != NULL && current->next->data->symbol.frequency < data->symbol.frequency)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to remove and return the front node from the Min-Priority Queue
struct Node *dequeue(struct MinPriorityQueue *queue)
{
    if (queue->front == NULL)
    {
        return NULL;
    }
    struct MinPriorityQueueNode *temp = queue->front;
    struct Node *data = temp->data;
    queue->front = queue->front->next;
    free(temp);
    return data;
}

// Function to create a new node for the Huffman tree
struct Node *createNode(struct SYMBOL symbol)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->symbol = symbol;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to construct the Huffman tree from an array of symbols with frequencies
struct Node *constructHuffmanTree(struct SYMBOL symbols[], int size)
{
    struct MinPriorityQueue *queue = createMinPriorityQueue();
    for (int i = 0; i < size; ++i)
    {
        enqueue(queue, createNode(symbols[i]));
    }
    while (queue->front->next != NULL)
    {
        struct Node *left = dequeue(queue);
        struct Node *right = dequeue(queue);
        struct SYMBOL mergedSymbol;
        mergedSymbol.alphabet = '\0';
        mergedSymbol.frequency = left->symbol.frequency + right->symbol.frequency;
        struct Node *mergedNode = createNode(mergedSymbol);
        mergedNode->left = left;
        mergedNode->right = right;
        enqueue(queue, mergedNode);
    }
    return dequeue(queue); // Return the root of the Huffman tree
}

// Function to print the Huffman codes for the characters
void printHuffmanCodes(struct Node *root, int arr[], int top)
{
    if (root->left)
    {
        arr[top] = 0;
        printHuffmanCodes(root->left, arr, top + 1);
    }
    if (root->right)
    {
        arr[top] = 1;
        printHuffmanCodes(root->right, arr, top + 1);
    }
    if (root->left == NULL && root->right == NULL)
    {
        printf("Character: %c, Huffman Code: ", root->symbol.alphabet);
        for (int i = 0; i < top; ++i)
        {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

int main()
{
    int n;
    printf("Enter the number of characters: ");
    scanf("%d", &n);
    struct SYMBOL symbols[n];
    for (int i = 0; i < n; ++i)
    {
        printf("Enter character %d and its frequency: ", i + 1);
        scanf(" %c%d", &symbols[i].alphabet, &symbols[i].frequency);
    }
    struct Node *root = constructHuffmanTree(symbols, n);
    int arr[100], top = 0;
    printf("Huffman Codes:\n");
    printHuffmanCodes(root, arr, top);
    return 0;
}
