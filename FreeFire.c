#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define TAM_NOME 30
#define TAM_TIPO 20

// Definição da struct Componente
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int prioridade;
} Componente;

// Variáveis globais para contagem de comparações
int comparacoes_bubble = 0;
int comparacoes_insertion = 0;
int comparacoes_selection = 0;
int comparacoes_busca = 0;

// Protótipos das funções
void cadastrarComponentes(Componente componentes[], int *quantidade);
void bubbleSortNome(Componente componentes[], int n);
void insertionSortTipo(Componente componentes[], int n);
void selectionSortPrioridade(Componente componentes[], int n);
int buscaBinariaPorNome(Componente componentes[], int n, char nome[]);
void mostrarComponentes(Componente componentes[], int n);
void medirTempo(void (*algoritmo)(Componente[], int), Componente componentes[], int n, char *nomeAlgoritmo);
void limparBuffer();

int main() {
    Componente componentes[MAX_COMPONENTES];
    int quantidade = 0;
    int opcao;
    char nomeBusca[TAM_NOME];
    int ordenadoPorNome = 0; // Flag para verificar se está ordenado por nome
    
    printf("=== SISTEMA DE MONTAGEM DA TORRE DE FUGA ===\n");
    printf("Bem-vindo ao desafio final! Monte sua estratégia...\n\n");
    
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Cadastrar componentes\n");
        printf("2. Ordenar por nome (Bubble Sort)\n");
        printf("3. Ordenar por tipo (Insertion Sort)\n");
        printf("4. Ordenar por prioridade (Selection Sort)\n");
        printf("5. Buscar componente por nome (Busca Binária)\n");
        printf("6. Mostrar componentes\n");
        printf("7. Montagem final da torre\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                cadastrarComponentes(componentes, &quantidade);
                ordenadoPorNome = 0; // Reset da flag ao cadastrar novos componentes
                break;
                
            case 2:
                if (quantidade > 0) {
                    comparacoes_bubble = 0;
                    medirTempo(bubbleSortNome, componentes, quantidade, "Bubble Sort (Nome)");
                    ordenadoPorNome = 1;
                    printf("Componentes ordenados por nome!\n");
                    printf("Comparações realizadas: %d\n", comparacoes_bubble);
                } else {
                    printf("Erro: Nenhum componente cadastrado!\n");
                }
                break;
                
            case 3:
                if (quantidade > 0) {
                    comparacoes_insertion = 0;
                    medirTempo(insertionSortTipo, componentes, quantidade, "Insertion Sort (Tipo)");
                    printf("Componentes ordenados por tipo!\n");
                    printf("Comparações realizadas: %d\n", comparacoes_insertion);
                } else {
                    printf("Erro: Nenhum componente cadastrado!\n");
                }
                break;
                
            case 4:
                if (quantidade > 0) {
                    comparacoes_selection = 0;
                    medirTempo(selectionSortPrioridade, componentes, quantidade, "Selection Sort (Prioridade)");
                    printf("Componentes ordenados por prioridade!\n");
                    printf("Comparações realizadas: %d\n", comparacoes_selection);
                } else {
                    printf("Erro: Nenhum componente cadastrado!\n");
                }
                break;
                
            case 5:
                if (quantidade > 0) {
                    if (!ordenadoPorNome) {
                        printf("Atenção: Para busca binária, os componentes devem estar ordenados por nome!\n");
                        printf("Deseja ordenar agora? (s/n): ");
                        char resposta;
                        scanf("%c", &resposta);
                        limparBuffer();
                        if (resposta == 's' || resposta == 'S') {
                            comparacoes_bubble = 0;
                            bubbleSortNome(componentes, quantidade);
                            ordenadoPorNome = 1;
                            printf("Componentes ordenados por nome!\n");
                        } else {
                            break;
                        }
                    }
                    
                    printf("Digite o nome do componente a buscar: ");
                    fgets(nomeBusca, TAM_NOME, stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = 0; // Remove quebra de linha
                    
                    comparacoes_busca = 0;
                    int posicao = buscaBinariaPorNome(componentes, quantidade, nomeBusca);
                    
                    if (posicao != -1) {
                        printf("\n✅ COMPONENTE ENCONTRADO!\n");
                        printf("Nome: %s\n", componentes[posicao].nome);
                        printf("Tipo: %s\n", componentes[posicao].tipo);
                        printf("Prioridade: %d\n", componentes[posicao].prioridade);
                        printf("Comparações realizadas: %d\n", comparacoes_busca);
                        
                        if (strcmp(componentes[posicao].nome, "chip central") == 0) {
                            printf("\n🎉 COMPONENTE-CHAVE ENCONTRADO! A torre pode ser ativada!\n");
                        }
                    } else {
                        printf("❌ Componente '%s' não encontrado!\n", nomeBusca);
                        printf("Comparações realizadas: %d\n", comparacoes_busca);
                    }
                } else {
                    printf("Erro: Nenhum componente cadastrado!\n");
                }
                break;
                
            case 6:
                if (quantidade > 0) {
                    mostrarComponentes(componentes, quantidade);
                } else {
                    printf("Nenhum componente cadastrado!\n");
                }
                break;
                
            case 7:
                if (quantidade > 0) {
                    printf("\n=== MONTAGEM FINAL DA TORRE ===\n");
                    printf("Componentes organizados para montagem:\n\n");
                    mostrarComponentes(componentes, quantidade);
                    
                    // Verificar se o componente-chave está presente
                    int encontrou_chave = 0;
                    for (int i = 0; i < quantidade; i++) {
                        if (strcmp(componentes[i].nome, "chip central") == 0) {
                            encontrou_chave = 1;
                            break;
                        }
                    }
                    
                    if (encontrou_chave) {
                        printf("\n🚀 TORRE MONTADA COM SUCESSO! Fuga autorizada!\n");
                    } else {
                        printf("\n⚠️  ALERTA: Componente-chave 'chip central' não encontrado!\n");
                        printf("A torre não pode ser ativada sem o componente-chave.\n");
                    }
                } else {
                    printf("Erro: Nenhum componente para montagem!\n");
                }
                break;
                
            case 0:
                printf("Saindo do sistema... Boa sorte na fuga!\n");
                break;
                
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
        
    } while (opcao != 0);
    
    return 0;
}

// Função para cadastrar componentes
void cadastrarComponentes(Componente componentes[], int *quantidade) {
    printf("\n=== CADASTRO DE COMPONENTES ===\n");
    printf("Quantos componentes deseja cadastrar? (máximo %d): ", MAX_COMPONENTES);
    int num;
    scanf("%d", &num);
    limparBuffer();
    
    if (num <= 0 || num > MAX_COMPONENTES) {
        printf("Quantidade inválida!\n");
        return;
    }
    
    for (int i = 0; i < num; i++) {
        printf("\nComponente %d:\n", i + 1);
        
        printf("Nome: ");
        fgets(componentes[*quantidade].nome, TAM_NOME, stdin);
        componentes[*quantidade].nome[strcspn(componentes[*quantidade].nome, "\n")] = 0;
        
        printf("Tipo (controle/suporte/propulsão): ");
        fgets(componentes[*quantidade].tipo, TAM_TIPO, stdin);
        componentes[*quantidade].tipo[strcspn(componentes[*quantidade].tipo, "\n")] = 0;
        
        printf("Prioridade (1-10): ");
        scanf("%d", &componentes[*quantidade].prioridade);
        limparBuffer();
        
        // Validação da prioridade
        if (componentes[*quantidade].prioridade < 1 || componentes[*quantidade].prioridade > 10) {
            printf("Prioridade inválida! Definindo como 1.\n");
            componentes[*quantidade].prioridade = 1;
        }
        
        (*quantidade)++;
        printf("✅ Componente cadastrado com sucesso!\n");
    }
    
    printf("\nTotal de componentes cadastrados: %d\n", *quantidade);
}

// Bubble Sort para ordenar por nome
void bubbleSortNome(Componente componentes[], int n) {
    int i, j;
    Componente temp;
    
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            comparacoes_bubble++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                // Troca os componentes
                temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort para ordenar por tipo
void insertionSortTipo(Componente componentes[], int n) {
    int i, j;
    Componente key;
    
    for (i = 1; i < n; i++) {
        key = componentes[i];
        j = i - 1;
        
        while (j >= 0) {
            comparacoes_insertion++;
            if (strcmp(componentes[j].tipo, key.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                j = j - 1;
            } else {
                break;
            }
        }
        componentes[j + 1] = key;
    }
}

// Selection Sort para ordenar por prioridade
void selectionSortPrioridade(Componente componentes[], int n) {
    int i, j, min_idx;
    Componente temp;
    
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            comparacoes_selection++;
            if (componentes[j].prioridade < componentes[min_idx].prioridade) {
                min_idx = j;
            }
        }
        // Troca o componente mínimo com o primeiro não ordenado
        temp = componentes[min_idx];
        componentes[min_idx] = componentes[i];
        componentes[i] = temp;
    }
}

// Busca binária por nome (requer vetor ordenado por nome)
int buscaBinariaPorNome(Componente componentes[], int n, char nome[]) {
    int esquerda = 0;
    int direita = n - 1;
    
    while (esquerda <= direita) {
        comparacoes_busca++;
        int meio = esquerda + (direita - esquerda) / 2;
        
        int comparacao = strcmp(componentes[meio].nome, nome);
        
        if (comparacao == 0) {
            return meio; // Componente encontrado
        } else if (comparacao < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    return -1; // Componente não encontrado
}

// Função para mostrar todos os componentes
void mostrarComponentes(Componente componentes[], int n) {
    printf("\n=== LISTA DE COMPONENTES (%d itens) ===\n", n);
    printf("%-3s %-25s %-15s %s\n", "No.", "Nome", "Tipo", "Prioridade");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("%-3d %-25s %-15s %d\n", 
               i + 1, 
               componentes[i].nome, 
               componentes[i].tipo, 
               componentes[i].prioridade);
    }
}

// Função para medir tempo de execução dos algoritmos
void medirTempo(void (*algoritmo)(Componente[], int), Componente componentes[], int n, char *nomeAlgoritmo) {
    clock_t inicio, fim;
    double tempo_gasto;
    
    printf("\nExecutando %s...\n", nomeAlgoritmo);
    
    inicio = clock();
    algoritmo(componentes, n);
    fim = clock();
    
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("Tempo de execução: %.6f segundos\n", tempo_gasto);
}

// Função auxiliar para limpar buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
