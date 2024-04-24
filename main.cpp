#include <iostream>

using std::cout;
using std::endl;

///// LISTA DUPLAMENTE ENCADEADA /////

typedef struct Node
{
    int iPayload;
    Node* ptrNext;
    Node* ptrPrev;
} Node;


Node* createNode(int);
// A estrutura agora é apenas um ponteiro pra nó
// Ela é um ponteiro pro ponteiro pro primeiro elemento
void insertFront(Node**, int); 
void insertEnd(Node**, int); 
void displayList(Node*);
void insertAfter(Node*, int);
void deleteNode(Node**, Node*);
void insertBefore(Node**, Node*, int); // TODO
void deleteNodebyValue(Node**, int); // TODO
Node* searchNodebyValue(Node**, int); // TODO


int main()
{
    // A lista agora é um ponteiro pro primeiro elemento
    Node* head = nullptr; 

    cout << "===================================================================" << endl;
    
    displayList(head);

    cout << "===================================================================" << endl;
    
    // O endereço do ponteiro pro primeiro elemento é um ponteiro pro ponteiro pro primeiro elemento
    insertEnd(&head, 0);
    insertEnd(&head, 1);
    insertEnd(&head, 3);
    insertEnd(&head, 7);
    insertEnd(&head, 10);
    insertEnd(&head, 13);
    
    displayList(head);
    
    cout << "===================================================================" << endl;

    // Inserindo elementos na frente da lista
    insertFront(&head, 65);
    insertFront(&head, 78);
    
    displayList(head);
    
    cout << "===================================================================" << endl;

    // Inserindo elementos após um específico
    insertAfter(head, 10);
    insertAfter(head, 13);
    
    displayList(head);
    
    cout << "===================================================================" << endl;

    // Removendo um nó
    deleteNode(&head, head);
    
    displayList(head);
    
    cout << "===================================================================" << endl;

    // Inserindo nós antes de um específico
    insertBefore(&head, head->ptrNext, 27);
    
    displayList(head);

    cout << "==================================================================+" << endl;
    
    insertBefore(&head, head, 17);

    displayList(head);
    
    cout << "===================================================================" << endl;

    // Procurando um elemento
    Node* inexistentNode = searchNodebyValue(&head, 59);
    Node* node13 = searchNodebyValue(&head, 13);

    cout << node13 -> iPayload << endl;

    cout << "===================================================================" << endl;

    // Tentando remover um elemento inexistente
    deleteNodebyValue(&head, 58);

    cout << "===================================================================" << endl;

    // Removendo elementos
    deleteNodebyValue(&head, 0);

    displayList(head);

    deleteNodebyValue(&head, 65);
    deleteNodebyValue(&head, 13);
    deleteNodebyValue(&head, 13);

    displayList(head);
    
    return 0;
}


Node* createNode(int iPayload)
{
    // Sem a conversão dá um ponteiro pra void
    Node* temp = (Node*) malloc(sizeof(Node));
    temp -> iPayload = iPayload;
    temp -> ptrNext = nullptr;
    temp -> ptrPrev = nullptr;
    
    return temp;
}

void displayList(Node* node)
{
    // Se o nó é nulo, a lista é vazia
    if (node == nullptr)
    {
        cout << "Lista vazia: Não é possível realizar displayList" << endl;
        return;
    }
    
    // Se o nó tem algo antes dele, é um nó do meio da lista ou o último
    if (node -> ptrPrev != nullptr)
    {
        cout << "Meio ou fim da lista: Não é possível realizar displayList" << endl;
        return;
    }
    
    Node* temp = node;
    
    cout << "Payload: ";
    
    while (temp != nullptr)
    {
        cout << temp -> iPayload << " ";
        temp = temp -> ptrNext;
    }
    
    cout << endl;
}

void insertFront(Node** head, int iPayload)
{
    Node* newNode = createNode(iPayload);
    // newNode -> ptrPrev = nullptr;
    
    // Se a lista não está vazia...
    if (*head != nullptr)
    {
        // O anterior ao antigo primeiro passa a ser o novo
        (*head) -> ptrPrev = newNode;
        // O seguinte ao novo nó é o antigo primeiro
        newNode -> ptrNext = (*head);
        // O novo nó passa a ser o primeiro
        (*head) = newNode;
        
        return;
    }
    
    // Se ela está vazia, o novo nó passa a ser o primeiro
    (*head) = newNode;
}

void insertEnd(Node** head, int iPayload)
{
    // Criando o nó
    Node* newNode = createNode(iPayload);
    // newNode -> ptrNext = nullptr;
    
    // Se o ponteiro pro head for nulo
    if (*head == nullptr) 
    {
        // newNode -> ptrPrev = nullptr;
        
        // Parênteses: convenção de programação
        // O primeiro passa a ser o novo
        (*head) = newNode; 
        return;
    }
    
    Node* temp = (*head);
    
    // Encontra o final da lista
    while (temp -> ptrNext != nullptr)
    {
        temp = temp -> ptrNext;
    }
    
    // O anterior do novo é o antigo último
    newNode -> ptrPrev = temp;
    // O seguinte do antigo último é o novo
    temp -> ptrNext = newNode;
}

void insertAfter(Node* ptrLocation, int iPayload)
{
    if (ptrLocation == nullptr)
    {
        cout << "Location é NULL." << endl;
        return;
    }
    
    Node* newNode = createNode(iPayload);
    
    // Corrigir nó a ser inserido
    // O anterior ao novo nó é a localização
    newNode -> ptrNext = ptrLocation -> ptrNext;
    // O seguinte ao novo nó é o seguinte à localização
    newNode -> ptrPrev = ptrLocation;
    
    // Corrigir o ponto de inserção
    // O seguinte à localização passa a ser o novo nó
    ptrLocation -> ptrNext = newNode;
    
    // Se a localização não for o final da lista...
    if (newNode -> ptrNext != nullptr)
    {
        // O anterior do seguinte ao novo nó passa a ser o novo nó
        newNode -> ptrNext -> ptrPrev = newNode;
    }
}

void deleteNode(Node** head, Node* ptrDelete)
{
    if (*head == nullptr || ptrDelete == nullptr)
    {
        cout << "Não foi possível remover." << endl;
        return;
    }
    
    // Se for o primeiro elemento...
    if (*head == ptrDelete)
    {
        // O novo passa a ser o segundo
        (*head) = ptrDelete -> ptrNext;
    }
    
    // Se não for o último nó...
    if (ptrDelete -> ptrNext != nullptr)
    {
        ptrDelete -> ptrNext -> ptrPrev = ptrDelete -> ptrPrev;
    }
    
    // Se não for o primeiro nó...
    if (ptrDelete -> ptrPrev != nullptr)
    {
        ptrDelete -> ptrPrev -> ptrNext = ptrDelete -> ptrNext;
    }
    
    free(ptrDelete);
}

////////////////////////////////////////////////////////////////////////////////
// Exercício 1. Elaborar a função "void insertBefore(Node*, int)".
// Exercício 2. Elaborar a função "void deleteNodebyValue(Node**, int)".
// Exercício 3. Elaborar a função "Node* searchNodebyValue(Node**, int)".
////////////////////////////////////////////////////////////////////////////////

// Essa função não funciona para o caso especial de inserir antes do primeiro elemento sem receber o head
void insertBefore(Node** head, Node* ptrLocation, int iPayload){
    
    // Se o ponteiro for nulo, não podemos inserir
    if(ptrLocation == NULL){
        cout << "Location é NULL." << endl;
        return;
    }

    Node* newNode = createNode(iPayload);
    
    // O próximo do novo nó será o da localização
    newNode -> ptrNext= ptrLocation;
    // O anterior do novo nó será o anterior da localização
    newNode -> ptrPrev = ptrLocation -> ptrPrev;

    //O anterior da localização é o novo nó
    ptrLocation -> ptrPrev = newNode;

    //Se o novo nó for o primeiro, atualiza a head
    if(newNode -> ptrPrev == NULL){
        
        *head = newNode;
        return;
    }

    // Se o novo nó não for o primeiro, o próximo do anterior do novo é o próprio novo
    newNode -> ptrPrev -> ptrNext = newNode;
   return;
};
    

Node* searchNodebyValue(Node** head, int iValue)
{
    // Se a lista for vazia, não faz nada
    if (*head == nullptr)
    {
        cout << "Lista vazia: O elemento não existe" << endl;
        return nullptr;
    }
    else
    {
        // Ponteiro para percorrer a lista
        Node* current = (*head);
        
        // Até chegar ao final da lista...
        while (current != nullptr)
        {
            // Se o valor do nó for o que queremos, retorna ele e encerra a função
            if (current -> iPayload == iValue)
            {
                return current;
            }
            // Se não, avança
            current = current -> ptrNext;
        }
        
        // Se não fizer nada, o elemento não existe
        cout << "Elemento não encontrado" << endl;
        return current;
    }
}

void deleteNodebyValue(Node** head, int iValue)
{
    // Encontrando o nó a ser removido
    Node* removedNode = searchNodebyValue(head, iValue);
    
    // Se esse nó for nulo, o elemento não existe
    if (removedNode == nullptr)
    {
        cout << "Não é possível remover o elemento " << iValue << endl;
    }
    // Se não, remove ele
    else
    {
        cout << "Elemento " << removedNode -> iPayload << " removido" << endl;
        deleteNode(head, removedNode);
    }
}
    
