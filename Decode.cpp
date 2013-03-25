#include "Decode.h"

// Reconstroi a arvore Shannon-Fano
void remake_tree(string *encoded, Node** root)
{
    // Extrai o primeiro caracter da string, removendo-o da mesma
    char bit = (*encoded)[0]; 
    
    (*encoded).erase((*encoded).begin());
    
    if (bit == '0')
    {
        // Cria o novo no, e seta seus atributos
        Node * n = new Node();
        n->parent = *root;
        n->setBit('0');
        (*root)->child0 = n;
        remake_tree(encoded,&n);
                
        // Verifica se a raiz pode ser expandida para outro lado a depender da string
        remake_tree(encoded,root);
    }    
    else if (((*root)->child0 != NULL) && ((*root)->child1 == NULL) && (bit == '1'))
//  Se a raiz possuir o filho esquerdo e nao possuir o direito, e o bit for um, entao a mesma pode ter um filho no nó direito
    {
        // Cria o novo no, e seta seus atributos
        Node *n = new Node();
        n->parent = *root;
        n->setBit('1');
        (*root)->child1 = n;
        remake_tree(encoded,&n);
        
        // Verifica se a raiz pode ser expandida para outro lado a depender da string
        remake_tree(encoded,root);
    }
    else
//  Caso nenhuma possibilidade seja possivel, recoloca-se o bit no inicio da string      
        (*encoded).insert((*encoded).begin(),1,bit);
}

// Associa as raizes da arvore seus simbolos
void finishTree(string *codes, Node* root)
{
    // Varrendo os nós da esquerda e da direita de cada nó
    if (root->child0 != NULL)
        finishTree(codes,root->child0);
    if (root->child1 != NULL)
        finishTree(codes,root->child1);
    
    if ((root->child0 == NULL) && (root->child1 == NULL))
//  Caso o nó seja folha
    {
        // Associa-se o primeiro simbolo possivel, e remove-o da lista de simbolos
        root->setSymbol((*codes)[0]);
        (*codes).erase((*codes).begin());
    }   
}

// Transforma uma sequencia binaria num simbolo da arvore de Shannon-Fano
char extractCharacter(Node *root, string *msg)
{
    if ((root->child0 == NULL) && (root->child1 == NULL))
//  Se o no for folha, entao encontrei o simbolo que procuro      
        return root->getSymbol();
    else
    {
        if ((*msg)[0] == '0')
//      Neste caso, vou para o filho a esquerda de root, e removo um bit da string      
        {
            (*msg).erase((*msg).begin());
            return extractCharacter(root->child0,msg);
        }
        else
//      Neste caso, vou para o filho a direita de root, e removo um bit da string
        {
            (*msg).erase((*msg).begin());
            return extractCharacter(root->child1,msg);
        }
    }
}

// Transforma uma sequencia binaria de Shannon-Fano na mensagem original
string shToIn(Node *root, string msg)
{
    string decoded = "";
    while (!msg.empty())
        decoded+= extractCharacter(root,&msg);
    return decoded;
}

// Decodifica um arquivo binario que contem uma codificação Shannon-Fano
string decode(string *raw) 
{
    string out = "", chars = "", encoded = "";
    unsigned short qnt = 0;
    Node *root = NULL;
    
    encoded = readOutput(raw);
    
    encoded.erase(encoded.end()-8,encoded.end()); // Removendo os ultimos 8 bits correspondentes ao caracter de EOF
    
    out.assign(encoded,0,8); // Associa a out o primeiro byte da string codificada
    
    qnt = binToInt(out); // Transforma out em binario para saber a quantidade de simbolos existe na mensagem
    
    encoded.erase(encoded.begin(),encoded.begin() + 8); // Remove bits ja verificados da string
    
    root = new Node();
    
    remake_tree(&encoded, &root); // Reconstroi a arvore de Shannon-Fano baseado na string codificada
    
    encoded.erase(encoded.begin());  // Apaga o bit que delimita o final da arvore
    
    for (unsigned short i = 0; i < qnt; i++)
//  Transforma a quantidade qnt de bytes subsequentes em simbolos      
    {
        out.assign(encoded,0,8);
        encoded.erase(encoded.begin(),encoded.begin() + 8);  // Remove bits ja verificados da string
        chars += binToInt(out); // Converte a sequencia de bits out em um simbolo (byte)
    }
    
    finishTree(&chars,root); // Associa os simbolos encontrados as folhas da arvore de Shannon-Fano
    
    out.assign(encoded,encoded.size()-8,8);  // Associa a out os ultimos 8 bits da string codificada
    
    encoded.erase(encoded.size()-8,8); // Remove bits ja verificados da string
    
    encoded += intToBin(binToInt(out)); // Transforma out em um numero inteiro,
//  para em seguida transforma-lo numa sequencia binaria, e entao associa-lo a string codificada novamente
    
    out = shToIn(root,encoded); // Decodifica a string codificada com o algoritmo de Shannon-Fano
    
    return out;
}