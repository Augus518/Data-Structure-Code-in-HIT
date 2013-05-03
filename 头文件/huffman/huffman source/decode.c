#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 255
#define MAX_LEN     10

/**
*1.��ԭ��ʱ��ע���Ѿ��ж��ӵĽڵ㲻��Ҫ���½����ӽڵ�
*2.��encodeʱ�����һ���ַ�����뽫currָ������ָ����ڵ�
*/

struct tnode {
    struct tnode* left; /*used when in tree*/
    struct tnode* right; /*used when in tree*/
    int isleaf;
    char symbol;
};

struct code {
    int symbol;
    char strcode[MAX_LEN];
};

/*global variables*/
struct tnode* root = NULL; /*tree of symbols*/

/*
    @function   talloc
    @desc       allocates new node
 */

struct tnode* talloc() {
    struct tnode* p = (struct tnode*) malloc(sizeof (struct tnode));
    if (p != NULL) {
        p->left = p->right = NULL;
        p->symbol = 0;
        p->isleaf = 0;
    }
    return p;
}

/*
    @function build_tree
    @desc     builds the symbol tree given the list of symbols and code.h
        NOTE: alters the global variable root that has already been allocated in main
 */

//����code.txt�����ݻ�ԭhuffman��

void build_tree(FILE* fp) {
    char symbol;
    char strcode[MAX_LEN];
    int items_read;
    int i, len;
    struct tnode* curr = NULL;

    while (!feof(fp)) {			//����ÿ1�У���Ϊÿ��symbol����
        items_read = fscanf(fp, "%c %s\n", &symbol, strcode);	//��ʽ: symbol strcode
        if (items_read != 2) break;								//�жϳɹ�
        curr = root;				//from root	��ʼ��Ϊ���ڵ�(�Ӹ��ڵ㿪ʼ�ؽ�)
        len = strlen(strcode);		//hufman code length = depth ���볤�ȵ����������
        for (i = 0; i < len; i++) {	//rebuild the tree according to strcode[len]����strcode�б����huffman�����ÿһ���ַ��ؽ���depth
            /*TODO: create the tree as you go*/
			
            if(strcode[i] == '0') {				//strcode[i] == 0 : left �����
                if(curr -> left == NULL)
                    curr -> left = talloc();
                curr = curr -> left;
            }
            else {
                if(curr -> right == NULL)		//strcode[i] != 0 :  right �Ҷ���
                    curr -> right = talloc();
                curr = curr -> right;
            }
        }

        /*assign code for the leaf node */
        curr->isleaf = 1;						
        curr->symbol = symbol;
        printf("inserted symbol:%c\n", symbol);
    }
}

/*
        function decode
 */
//��ѹ��
void decode(FILE* fin, FILE* fout) {
    char c;
    struct tnode* curr = root;			//start from root
    while ((c = getc(fin)) != EOF) {
        /*TODO:
                traverse the tree
                print the symbols only if you encounter a leaf node
		*/
        // ��������Ҷ�ڵ㣬˵��һ��huffman�������������ָ�currentָ��ָ��root��������һ��huffman�����
		if(c == '0') {
            curr = curr -> left;
            if(curr->isleaf) {			//when leaf traverse go on from the root
                fprintf(fout, "%c", curr -> symbol);
                curr = root;			//�ָ�ʹ��currentָ��ָ����ڵ�root
            }
        }else {
            curr = curr -> right;
            if(curr->isleaf) {			//when leaf travrse goon from the root
                fprintf(fout, "%c", curr -> symbol);
                curr = root;			//current points to the root again
            }
        }
    }
}

/*
        @function freetree
        @desc	  cleans up resources for tree
 */

//ɾ������� recursive function�ݹ麯��
void freetree(struct tnode* root) {
    if (root == NULL)
        return;					
								//�ݹ鵽base case���ͷ����ҡ����ڵ�
    freetree(root->right);		//�ͷ��Ҷ��ӽڵ�
    freetree(root->left);		//�ͷ�����ӽڵ�
    free(root);					//�ͷŸ��ڵ�
}

int main() {
    const char* IN_FILE = "encoded.txt";
    const char* CODE_FILE = "code.txt";
    const char* OUT_FILE = "decoded.txt";
    FILE* fout;
    FILE* fin;
    /*allocate root*/
    root = talloc();
    fin = fopen(CODE_FILE, "r");
    /*build tree*/
    build_tree(fin);
    fclose(fin);

    /*decode*/
    fin = fopen(IN_FILE, "r");
    fout = fopen(OUT_FILE, "w");
    decode(fin, fout);
    fclose(fin);
    fclose(fout);
    /*cleanup*/
    freetree(root);
    return 0;
}

