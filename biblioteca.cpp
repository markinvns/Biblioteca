#include <iostream>
#include <cstdio>
#include <limits>
#include <cstring>
using namespace std;

    struct emprestimo {
        char data_emp[11], data_dev[11], usuario[50];
    };

    struct livro {
        int cod, n_pag;
        char area[50], titulo[255], autor[50], editora[50];
        struct emprestimo emp;
    };
    struct livro livro;
    
    int opc, cod_user, rmv_user, pos;
    char opc_sec;

    FILE *base_arquivo;
    FILE *bkp_base_arquivo;

int main(){

    // Fiz a criação do menu da minha biblioteca //
    do { 
        cout << "BEM-VINDO A BIBLIOTECA DEV" << endl;
        cout << "1- CADASTRO" << endl;
        cout << "2- ALTERAÇÃO" << endl;
        cout << "3- EXCLUSÃO" << endl;
        cout << "4- EMPRÉSTIMO" << endl;
        cout << "5- DEVOLUÇÃO" << endl;
        cout << "6- CONSULTA DE LIVROS" << endl;
        cout << "7- LIVROS DISPONÍVEIS" << endl;
        cout << "8- LISTAGEM GERAL DE LIVROS" << endl;
        cout << "9- SAIR" << endl; 
        cin >> opc;
        
        // Iniciei a estrutura de repetição e escolha//
        switch (opc){ 
        
            case 1:
                cout << "Você deseja cadastrar um livro? (S ou N)";
                cin >> opc_sec;
                while (opc_sec == 'S' || opc_sec == 's'){
                    cout << "Digite o código do livro:";
                    cin >> livro.cod;
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "Digite a área do livro:";
                    cin.get(livro.area, 50);
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "Digite o título do livro:";
                    cin.get(livro.titulo, 255);
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "Digite o autor(a) do livro:";
                    cin.get(livro.autor, 50);
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "Digite a editora do livro:";
                    cin.get(livro.editora, 50);
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "Digite o número de páginas:";
                    cin >> livro.n_pag;
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                
                    base_arquivo = fopen("cadast.txt","ab");
                    if (base_arquivo == NULL)
                    {
                        base_arquivo = fopen("cadast.txt","wb");
                    }
                    if (fwrite(&livro, sizeof(struct livro), 1, base_arquivo) == 1){
                        cout << "O livro " << livro.titulo << " foi gravado na base de dados com sucesso! :0";
                    }
                    else {
                        cout << "Erro ao gravar o livro" << livro.titulo << " na base de dados! :/";
                    }
                    fclose(base_arquivo);
                    cin.ignore();
                    cin.get();

                    cout << "Deseja fazer outro cadastro? S ou N:";
                    cin >> opc_sec;
                }
                
                break;
            case 2:
                cout << "Deseja fazer a alteração de algum código (S ou N):";
                cin >> opc_sec;
                while (opc_sec == 'S' || opc_sec == 's'){
                    base_arquivo = fopen("cadast.txt","rb+");
                    if (base_arquivo != NULL){
                        cout << "Digite o código do livro que sofrerá a alteração:";
                        cin >> cod_user;
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');

                        //REVISAR SOBRE ESSE POS//

                        pos = -1; 
                        while (!feof(base_arquivo)){
                            fread(&livro, sizeof(struct livro), 1, base_arquivo);
                            pos++;
                            if (cod_user == livro.cod){
                                cout << "Digite a área do livro:";
                                cin.get(livro.area, 50);
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                cout << "Digite o título do livro:";
                                cin.get(livro.titulo, 255);
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                cout << "Digite o autor(a) do livro:";
                                cin.get(livro.autor, 50);
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                cout << "Digite a editora do livro:";
                                cin.get(livro.editora, 50);
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                cout << "Digite o número de páginas:";
                                cin >> livro.n_pag;
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                cout << "============================================" << endl;

                                fseek(base_arquivo, sizeof(struct livro) * pos, SEEK_SET);
                                if (fwrite(&livro, sizeof(struct livro), 1, base_arquivo) == 1){
                                    cout << "O livro " << livro.titulo << " foi alterado com sucesso!! :)";  
                                } else {
                                    cout << "!!FALHA EM CONCLUIR A ALTERAÇÃO!!";
                                }
                                cin.ignore();
                                cin.get();
                                break;
                            }
                           
                        } 
                        fclose(base_arquivo);
                        cout << "Deseja excluir mais algum livro (S ou N):";
                        cin >> opc_sec;


                    } else {
                        cout << "!!Falha na execução do programa, tente novamente ou mais tarde!!";
                        cin.ignore();
                        cin.get();
                    }
                        
                }
                break;
            case 3:
                cout << "Deseja excluir um livro (S ou N):";
                cin >> opc_sec;
                
                while (opc_sec == 'S' || opc_sec == 's') {
                        cout << "Digite o código do livro que deseja fazer a exclusão:";
                        cin >> rmv_user;
                        base_arquivo = fopen("cadast.txt","rb");
                        bkp_base_arquivo = fopen("cadast.bkp","wb");
                        fread(&livro , sizeof(struct livro), 1, base_arquivo);
                        while (!feof(base_arquivo)){
                            if (rmv_user != livro.cod) {
                                fwrite(&livro, sizeof(struct livro), 1, bkp_base_arquivo); 
                        }
                        fread(&livro, sizeof(struct livro), 1, base_arquivo);
                    }  
                }
                fclose(base_arquivo);
                fclose(bkp_base_arquivo);
                remove("cadast.txt");
                rename("cadast.bkp", "cadast.txt");
                
                cout << "Deseja excluir mais algum livro (S ou N):";
                cin >> opc_sec;

                break;
            case 4:
                cout << "Você deseja fazer um empréstimo de um livro:";
                cin >> opc_sec;
                while (opc_sec == 'S' || opc_sec == 's'){
                    base_arquivo = fopen("cadast.txt", "rb+");
                    if (base_arquivo != NULL){
                        cout << "Digite o código do livro que deseja emprestar:";
                        cin >> cod_user;
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');

                        pos = -1;

                        while (!feof(base_arquivo)){
                            fread(&livro, sizeof(struct livro), 1, base_arquivo);
                            pos++;
                            if (cod_user == livro.cod){
                                fseek(base_arquivo, sizeof(struct livro) * pos, SEEK_SET);
                                cout << "Digite a data do empréstimo do livro:";
                                cin >> livro.emp.data_emp;
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                cout << "Digite a data da devolução do livro:";
                                cin.get(livro.emp.data_dev, 11);
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                cout << "Digite o seu nome de usuário:";
                                cin.get(livro.emp.usuario, 50);
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                fwrite(&livro, sizeof(struct livro), 1, base_arquivo);
                                break;
                            }

                        }
                         fclose(base_arquivo);
                    } else {
                        cout << "!!Falha no empréstimo do livro!!";
                        cin.ignore();
                        cin.get();
                    }
                        cout << "Deseja fazer mais algum empréstimo (S ou N):";
                        cin >> opc_sec;
                }cout << "\e[2J" << "\e[0;0H";
                
                break;
            case 5:
                cout << "Deseja fazer a devolução de um livro (S ou N):";
                cin >> opc_sec;
                    while (opc_sec == 'S' || opc_sec == 's'){
                        base_arquivo == fopen("cadast.txt","rb+");
                        if (base_arquivo != NULL){
                            cout << "Digite o código do livro que deseja devolver:";
                            cin >> cod_user;
                            
                            pos = -1;
                            while (!feof(base_arquivo)){
                                fread(&livro, sizeof(struct livro), 1, base_arquivo);
                                pos++;
                                if (cod_user == livro.cod){
                                    fseek(base_arquivo, sizeof(struct livro) * pos, SEEK_SET);
                                    //OS COMANDOS ABAIXO SÃO UTILIZADOS PARA SOBREESCREVER VARIÁVEIS//
                                    //(1-variavel, "oque vai ser sobreescrito")
                                    strcpy(livro.emp.data_emp, "");
                                    strcpy(livro.emp.data_dev, "");
                                    stcout << "\e[2J" << "\e[0;0H";rcpy(livro.emp.usuario, "");
                                    fwrite(&livro, sizeof(struct livro), 1, base_arquivo);
                                    break;
                                }

                            }
                            fclose(base_arquivo);
                            
                        } else {
                            cout << "!!FALHA AO DEVOLVER O LIVRO!!";
                            cin.ignore();
                            cin.get();
                        }
                        cout << "Deseja fazer mais alguma devolução (S ou N):";
                        cin >> opc_sec;
                    }
                    
                break;
            case 6:
                cout << "Você deseja fazer a consulta de livros? (S ou N)";
                cin >> opc_sec;
                while (opc_sec == 'S' || opc_sec == 's') {
                    base_arquivo = fopen("cadast.txt","rb");
                    if (base_arquivo != NULL) {
                    cout << "Digite o código do livro que deseja consultar:";
                    cin >> cod_user;
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');

                    while (!feof (base_arquivo)){
                    fread(&livro, sizeof(struct livro), 1, base_arquivo);
                    if (cod_user == livro.cod)
                    {   
                        cout << "Código do livro:" << livro.cod << endl;
                        cout << "Título do livro:" << livro.titulo << endl;
                        cout << "Área do livro:" << livro.area << endl;
                        cout << "Autor(a) do livro:" << livro.autor << endl;
                        cout << "Editora do livro:" << livro.editora << endl;
                        cout << "Número de páginas:" << livro.n_pag << endl;
                        cout << "==========================================" << endl;

                    }
                    
                }
                    
            }
                    
        }
                
                break;
            case 7:
                cout << "Você deseja consultar os livros disponíveis para empréstimo (S ou N)";
                cin >> opc_sec;
                    while (opc_sec == 'S' || opc_sec == 's'){
                        base_arquivo = fopen("cadast.txt", "rb");
                        if (base_arquivo != NULL){
                        fread(&livro, sizeof(struct livro), 1, base_arquivo);
                        while (!feof(base_arquivo)){
                            //O CÓDIGO ABAIXO FAZ A COMPARAÇÃO DE VALORES//
                            
                            if (strcmp(livro.emp.data_emp, " ") == 0){
                                cout << "Código do livro disponível:"<< livro.cod << endl;
                                cout << "Área do livro disponível:" << livro.cod << endl;
                                cout << "Título do livro disponível:" << livro.cod << endl;
                                cout << "Autor to livro disponível:" << livro.cod << endl;;
                                cout << "Editora do livro disponível:" << livro.cod << endl;
                                cout << "Número de páginas do livro disponível:" << livro.cod << endl;
                            }
                            fread(&livro, sizeof(struct livro), 1, base_arquivo);
                        }
                        fclose(base_arquivo);
                        cin.ignore();
                        cin.get();
                    } else {
                        cout << "Erro em devolver o livro";
                        cin.ignore();
                        cin.get();
                    }
                        
                }
                    
                break;
            case 8:
                cout << "Você deseja listar os livros disponíveis? (S ou N)";
                cin >> opc_sec;
                while (opc_sec == 'S' || opc_sec == 's') {
                    base_arquivo = fopen("cadast.txt","rb");
                    if (base_arquivo != NULL) {
                    cout << "Fique com a listagem de todos os livros disponíveis:" << endl;
                    while (fread(&livro, sizeof(struct livro), 1, base_arquivo)==1){
                    cout << "Código do livro:\n" << livro.cod << endl;
                    cout << "Área do livro:\n" << livro.area << endl;
                    cout << "Título do livro:\n" << livro.titulo << endl;
                    cout << "Autor(a) do livro:\n" << livro.autor << endl;
                    cout << "Editora do livro:\n" << livro.editora << endl;
                    cout << "Número de páginas do livro:\n" << livro.n_pag << endl;
                    cout << "==============================================" << endl;

                    }   
                    }else {
                        cout << "Erro ao ler os dados do arquivo! :[";
                    }
                    fclose (base_arquivo);
                    cin.ignore();
                    cin.get(); 
                    cout << "Deseja listar os livros novamente (S ou N):";
                    cin >> opc_sec;
                }

                break;
            case 9:
                cout << "Obrigado por utilizar este programa!!! :)";
                cin.ignore();
                cin.get();
                break;

            default:
                cout << "Erro ao informar a opção!";
                break;
                
        } 
        cout << "\e[2J" << "\e[0;0H";
    }while (opc != 9);
    
}