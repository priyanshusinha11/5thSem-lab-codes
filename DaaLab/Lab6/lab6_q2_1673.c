#include <stdio.h>
#include <stdlib.h>

// Structure to represent a sym (character) and its freq
struct SYM
{
    char alpha;
    int freq;
};

// Structure to represent a node in the Huffman tree
struct Node
{
    struct SYM sym;
    struct Node *left;
    struct Node *right;
};

// Min-Priority Queue Node
struct MinpqNode
{
    struct Node *data;
    struct MinpqNode *next;
};

// Min-Priority Queue structure
struct Minpq
{
    struct MinpqNode *front;
};

// Function to create a new Min-Priority Queue node
struct MinpqNode *createMinPriorityQueueNode(struct Node *data)
{
    struct MinpqNode *newNode = (struct MinpqNode *)malloc(sizeof(struct MinpqNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new Min-Priority Queue
struct Minpq *createMinPriorityQueue()
{
    struct Minpq *newQueue = (struct Minpq *)malloc(sizeof(struct Minpq));
    newQueue->front = NULL;
    return newQueue;
}

// Function to insert a node into the Min-Priority Queue
void enqueue(struct Minpq *queue, struct Node *data)
{
    struct MinpqNode *newNode = createMinPriorityQueueNode(data);
    if (queue->front == NULL || data->sym.freq < queue->front->data->sym.freq)
    {
        newNode->next = queue->front;
        queue->front = newNode;
    }
    else
    {
        struct MinpqNode *current = queue->front;
        while (current->next != NULL && current->next->data->sym.freq < data->sym.freq)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to remove and return the front node from the Min-Priority Queue
struct Node *dequeue(struct Minpq *queue)
{
    if (queue->front == NULL)
    {
        return NULL;
    }
    struct MinpqNode *temp = queue->front;
    struct Node *data = temp->data;
    queue->front = queue->front->next;
    free(temp);
    return data;
}

// Function to create a new node for the Huffman tree
struct Node *createNode(struct SYM sym)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->sym = sym;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to construct the Huffman tree from an array of symbols with frequencies
struct Node *constructHuffmanTree(struct SYM symbols[], int size)
{
    struct Minpq *queue = createMinPriorityQueue();
    for (int i = 0; i < size; ++i)
    {
        enqueue(queue, createNode(symbols[i]));
    }
    while (queue->front->next != NULL)
    {
        struct Node *left = dequeue(queue);
        struct Node *right = dequeue(queue);
        struct SYM mergedSymbol;
        mergedSymbol.alpha = '\0';
        mergedSymbol.freq = left->sym.freq + right->sym.freq;
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
        printf("%c : ", root->sym.alpha);
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
    struct SYM symbols[n];
    for (int i = 0; i < n; ++i)
    {
        printf("Enter character %d and its freq: ", i + 1);
        scanf(" %c%d", &symbols[i].alpha, &symbols[i].freq);
    }
    struct Node *root = constructHuffmanTree(symbols, n);
    int arr[100], top = 0;
    printf("Inorder traversal of the tree with codes:\n");
    printHuffmanCodes(root, arr, top);
    return 0;
}
