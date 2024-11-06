// SISTEMA DE ATENDIMENTO AO CLIENTE 
// DEFININDO BIBLIOTECAS 
#include <iostream>
#include <string>

// DEFININDO ESTRUTURA DO NÓ 
struct No {
    int data; // armazena o ID do cliente 
    std::string nome; // armazena o nome do cliente
    No* next; // ponteiro que aponta para o próximo nó da fila
};

// ESTRUTURA DA FILA
struct Fila {
    No* first = nullptr;
    No* last = nullptr;
};

// FUNÇÃO PARA INSERIR UM NOVO CLIENTE NO FINAL DA FILA 
void insertClient(Fila* f, int valor, const std::string& nome) {
    No* novo = new No;
    novo->data = valor; 
    novo->nome = nome; // armazena o nome do cliente 
    novo->next = nullptr;
    if (f->last == nullptr) 
        f->first = novo;
    else 
        f->last->next = novo;
    f->last = novo;
}

// FUNÇÃO PARA ATENDER O CLIENTE NA FRENTE DA FILA
int attendClient(Fila* f) {
    if (f->first == nullptr) {
        std::cout << "Fila vazia.\n";
        return -1;
    }
    No* temp = f->first;
    int valor = temp->data;
    f->first = f->first->next;
    if (f->first == nullptr) 
        f->last = nullptr;
    delete temp;
    return valor;
}

// FUNÇÃO PARA REMOVER UM CLIENTE DA FILA 
void removeValor(Fila* f, int valor) {
    No* atual = f->first;
    No* anterior = nullptr;

    while (atual != nullptr) {
        if (atual->data == valor) {
            if (anterior == nullptr) { // Valor está no início da fila
                f->first = atual->next;
                if (f->first == nullptr) 
                    f->last = nullptr; // A fila ficou vazia
            } else {
                anterior->next = atual->next;
                if (atual->next == nullptr) 
                    f->last = anterior; // Atualiza o último nó se o removido for o último
            }
            delete atual;
            std::cout << "Valor " << valor << " removido da fila.\n";
            return;
        }
        anterior = atual;
        atual = atual->next;
    }
    std::cout << "Valor " << valor << " não encontrado na fila.\n";
} 

// FUNÇÃO PARA IMPRIMIR A FILA
void printLista(Fila* f) {
    No* atual = f->first;
    if (atual == nullptr) {
        std::cout << "Fila vazia.\n";
        return;
    }
    while (atual != nullptr) {
        std::cout << "ID: " << atual->data << ", Nome: " << atual->nome << " -> ";
        atual = atual->next;
    }
    std::cout << "NULL\n";
}

// FUNÇÃO PARA LIBERAR A MEMÓRIA DA FILA 
void freeLista(Fila* f) {
    No* atual = f->first;
    while (atual != nullptr) {
        No* temp = atual;
        atual = atual->next;
        delete temp;
    }
    f->first = nullptr;
    f->last = nullptr;
}

// FUNÇÃO PARA INVERTER A FILA E IMPRIMI-LA
void inverterFila(Fila* f) {
    Fila* filaAuxiliar = new Fila;
    while (f->first != nullptr) {
        // ARMAZENA O CLIENTE DA FRENTE DA FILA 
        No* atual = f->first;
        int valor = atual->data;
        std::string nome = atual->nome; // armazena o nome do cliente
        
        // REMOVE O CLIENTE DA FILA ORIGINAL
        attendClient(f);
        
        // ADICIONA O CLIENTE Á FILA AUXILIAR 
        No* novo = new No;
        novo->data = valor;
        novo->nome = nome; // armazena o nome do cliente
        novo->next = filaAuxiliar->first;
        filaAuxiliar->first = novo;   
        if (filaAuxiliar->last == nullptr) 
            filaAuxiliar->last = novo;
    }
    
    // REINSERE OS CLIENTES NA FILA ORIGINAL 
    while (filaAuxiliar->first != nullptr) {
        No* temp = filaAuxiliar->first;
        filaAuxiliar->first = filaAuxiliar->first->next;
        insertClient(f, temp->data, temp->nome);
        delete temp;
    }
    
    delete filaAuxiliar;

    // IMPRIMINDO A FILA 
    std::cout << "Fila invertida: \n";
    printLista(f); 
}


int main () {
    // CRIANDO UMA NOVA FILA 
    Fila* f = new Fila;

    // DEFININDO VARIÁVEIS 
    int opcao, valor; 
    std::string nome; 

    // DEFININDO CONDIÇÕES
    do {
        // MENU INTERATIVO 
        std::cout << "\n--- Bem-vindo ao Sistema de Atendimento! ---\n";
        std::cout << "1. Adicionar Cliente\n";
        std::cout << "2. Atender Cliente\n";
        std::cout << "3. Exibir Fila\n";
        std::cout << "4. Remover Cliente Especifico\n";
        std::cout << "5. Inverter Fila\n";
        std::cout << "6. Sair\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        // CHAMANDO FUNÇÕES E IMPRIMINDO 
        switch (opcao) {
            // ADICIONAR CLIENTE 
            case 1:
                std::cout << "Digite o ID do cliente: " << std::endl;
                std::cin >> valor;
                std::cin.ignore(); // para ignorar o newline após o inteiro
                std::cout << "Digite o nome do cliente: " << std::endl;
                std::getline(std::cin, nome); // para permitir que o nome tenha espaços
                insertClient(f, valor, nome); 
                std::cout << "Cliente adicionado a fila!" << std::endl;
                break;
            // ATENDER CLIENTE
            case 2: 
                valor = attendClient(f); 
                if (valor != -1) {
                    std::cout << "Atendendo cliente: ID: " << valor << std::endl;
                }
                break;
            // EXIBIR FILA
            case 3: 
                std::cout << "Clientes na fila: " << std::endl; 
                printLista(f); 
                break; 
            // REMOLVER CLIENTE ESPECÍFICO 
            case 4:
                std::cout << "Digite o ID do cliente que deseja remover: " << std::endl; 
                std::cin >> valor; 
                removeValor(f, valor);
                break; 
            // INVERTER FILA
            case 5: 
                inverterFila(f);
                std::cout << "Fila invertida!\n";
                break; 
            // SAIR DO PROGRAMA 
            case 6:
                std::cout << "Saindo do sistema...\n";
                break; 
            default: 
                std::cout << "Opcao invalida. Tente novamente!\n";
                break; 
        }
    } while (opcao != 6);

    // LIBERANDO A MEMÓRIA DA FILA 
    freeLista(f); 
    delete f;

    return 0;
}
