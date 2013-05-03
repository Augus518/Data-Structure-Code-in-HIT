#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 255
#define MAX_LEN     100

struct tnode
{


    struct tnode* left;
    struct tnode* right;
    struct tnode* parent;
    struct tnode* next;
    float freq;
    int isleaf;
    char symbol;
};


/*global variables*/
//�洢0-255ÿ��ASCII���huffman����
char code[MAX_SYMBOLS][MAX_LEN];
struct tnode* root = NULL; /*tree of symbols*/
// queue head pointer, code head pointer
struct tnode* qhead = NULL; /*list of current symbols*/
struct tnode* chead = NULL; /*list of code*/

//�½��Լ���ʼ���ڵ� talloc: tree node allocation
struct tnode* talloc(int symbol, float freq)
{
    struct tnode* p = (struct tnode*) malloc(sizeof (struct tnode));
    if (p != NULL)
    {
        p->left = p->right = p->parent = p->next = NULL;
        p->symbol = symbol;
        p->freq = freq;
        p->isleaf = 1;		//default is leaf node
    }
    return p;
}

//priority queue display
void pq_display(struct tnode* head)
{
    struct tnode* p = NULL;
    printf("list:");
    for (p = head; p != NULL; p = p->next)
    {
        printf("(%c,%f) ", p->symbol, p->freq);
    }
    printf("\n");
}

//priority queue intert: *p node to be inserted, *curr: working pointer
void pq_insert(struct tnode* p)
{
    struct tnode* curr = NULL;
    struct tnode* prev = NULL;
    printf("inserting:%c,%f\n", p->symbol, p->freq);

    /*TODO: write code to find correct position to insert*/
    curr = qhead;	//	pq head pointer traverse from head of pq, current pointer ��ʼ��ָ������ͷ

    //������¼����ǰ��ڵ��λ��
    while(curr)  	//	traverse the pq, not end of pq ��������β��
    {
        if(p -> freq <= curr -> freq)
        {
            break;
        }
        prev = curr;					//��¼�����ǰ�����λ��
        curr = curr -> next;			//����λ��
    }

    //�������������Ϊ��
    //insert when pq is empty
    if (qhead == NULL) /*qhead is null*/
    {
        /*TODO: write code to insert when queue is empty*/
        // curr = (struct tnode*) malloc(sizeof (struct tnode));	// memory leak ! assert(curr != NULL);
        curr = p;				//currָ��ָ���������p
        curr -> next = NULL;		//��ǰ���βָ��ֵΪ��NULL
        qhead = curr;			//ȫ��ͷָ��ָ���һ���ڵ�
    }

    //insert at headͷ������
    else if((curr == qhead) && qhead != NULL)
    {
        /*TODO: write code to insert before the current start*/
        p -> next = qhead;
        qhead = p;

    }

    else 	/*insert between prev and next �м���� */
    {
        /*TODO: write code to insert in between*/
        prev -> next = p;
        p -> next = curr;
    }
}

//���ض�����Ƶ����С�Ľڵ�Ϳ���
struct tnode* pq_pop()
{
    //��Ҫ����Ƶ����С�Ľڵ�
    //working pointer p
    struct tnode* p = NULL;
    /*TODO: write code to remove front of the queue*/
    p = qhead;
    qhead = qhead -> next;	//modify global pq head pointer
    printf("popped:%c,%f\n", p->symbol, p->freq);
    //free(p);		//ע�⣺��������ͷ�pִ�е�pqͷ��㣬ͷ�����Ϊ��������ֵʹ��
    return p;
}

//	ǰ������������������ÿ��Ҷ�ڵ��0,1���룬ע�⣺1�����������ĸ߶�==���볤�ȣ�
//2���ݹ麯��ʵ��
void generate_code(struct tnode* root, int depth)
{
    int symbol;
    int len; /*length of code*/

    if (root->isleaf)  		//ֻΪҶ�ڵ㹹������,��Ҷ�ӽڵ�����һֱ���������ڵ�
    {

        //root��Ҷ�ӽڵ㣬len ��Ҷ�ڵ�Ĺ��������볤��, symbolΪ�����ĸ

        symbol = root->symbol;
        len = depth;

        /* start backwards! */
        //���洢����ĸ��������������code�����һλ��Ϊ'\0'
        code[symbol][len] = '\0';

        /*
                TODO: follow parent pointer to the top
                to generate the code string
         */

        //ͨ��parentָ���Ҷ�ӽڵ�һֱ���������ڵ㣬�����Լ���
        //������ӻ����Ҷ�����ȷ����ĸ��0,1���У���"����"���浽code��

        while(root->parent)  	   //ֻ�и��ڵ���->parentָ���ΪNULL���Ƿ񵽸��ڵ�
        {
            if(root == root->parent->left)  	//��ǰ���Ϊ����ӣ�����Ϊ0
            {
                code[symbol][len-1] = '0';
                len --;
            }
            else
            {
                code[symbol][len-1] = '1';		//�Ҷ��ӣ�����Ϊ1
                len --;
            }
            root = root -> parent;				//��Ҷ�ӽڵ����ϱ������丸�ڵ�
        }
        printf("built code:%c,%s\n", symbol, code[symbol]);
    }
    else  	//non leaf node
    {
        generate_code(root->left, depth + 1);	//recursive function �ݹ麯����depth=0��ʼ����ж��Ƿ�ΪҶ�ڵ� depth + 1
        generate_code(root->right, depth + 1);	//�Ҷ���
    }

}

//������Ҷ�ӽڵ�(�������Ϊ��ЧҶ�ӽڵ�)�Ĺ��������뱣�浽code.txt�У������������, FILE* can be used as stdout as well
void dump_code(FILE* fp)
{
    int i = 0;
    for (i = 0; i < MAX_SYMBOLS; i++)
    {
        if (code[i][0])								/* non empty */
            fprintf(fp, "%c %s\n", i, code[i]);		//Print formatted data to a stream.
    }
}

//ѹ���ļ�,ֱ�Ӱ�ÿ����ĸ�ù����������0,1�ַ������б�ʾ������ѹ����϶���󡣽���ʹ��ʵ��˵���еķ����ﵽ����ѹ����Ŀ��(��ѡ)
void encode(char* str, FILE* fout)  		//*str: ascii code �ַ�ָ�룬������Ӧ�ַ���ASCII��
{

    while (*str)
    {
        fprintf(fout, "%s", code[*str]);	// ��ASCII��������������haffman��������code[*str] (����������ʿ��ٵ��ص�)��code���鱣����0-255���ַ���huffman����
        str++;
    }
}

/*
    @function main
 */

int main()
{
    /*test pq*/
    struct tnode* p = NULL;
    struct tnode* lc, *rc;		//pointer of left chile, right child
    //����Ƶ�ȣ���Ҫ�Լ�ͨ���ļ���ͳ�ƴ�ѹ���ļ���������ĸ��Ƶ�ȣ�Ƶ����Ϣֻ������ʹ��
    float freq[] = {0.01, 0.04, 0.05, 0.11, 0.19, 0.20, 0.4};
    int NCHAR = 7; /*number of characters*/
    int i = 0;
    const char *CODE_FILE = "code.txt";		// haffman code output file	����	huffman����
    const char *OUT_FILE = "encoded.txt";	//output encoded code

    FILE* fout = NULL;
    /*zero out code*/
    memset(code, 0, sizeof (code));		//MSDN	<memory.h>/<string.h>
    qhead = NULL;
    for (i = 0; i < NCHAR; i++)
    {
        pq_insert(talloc('a' + i, freq[i]));
    }
    /*build tree*/
    for (i = 0; i < NCHAR - 1; i++)
    {
        lc = pq_pop();		//left child is always less than right child
        rc = pq_pop();		//right child	�������ԶС���Ҷ��ӣ���˵�һ��������Ϊlc, �ڶ���Ϊrc
        /*create parent*/
        p = talloc(0, lc->freq + rc->freq);		//parent tnode
        /*set parent link*/
        lc->parent = rc->parent = p;			//���ڵ�
        /*set child link*/
        p->right = rc;
        p->left = lc;
        /*make it non-leaf*/
        p->isleaf = 0;							//һ���Ƿ�Ҷ�ڵ� 0
        /*add the new node to the queue*/
        pq_insert(p);		// insert at the proper position ��Ȩfrequency ��С�����������ȷλ��
    }

    /*get root */
    root = pq_pop();			//������pq��ֻ��һ���ڵ��root
    /* build code for root node, ���ڵ�root���Ϊ 0 depth */
    generate_code(root, 0);		/* ����Ƶ������huffman����� */
    /*output code*/
    puts("code:");
    fout = fopen(CODE_FILE, "w");		//char* CODE_FILE, "w" write only
    dump_code(stdout);
    dump_code(fout);
    fclose(fout);


    //ѹ������
    puts("orginal:dgdfsgsdfgdsgfgdfgdgdesgdbgdfgdfsgxgxgdfgdfbg");
    fout = fopen(OUT_FILE, "w");
    encode("dgdfsgsdfgdsgfgdfgdgdesgdbgdfgdfsgxgxgdfgdfbg", stdout);
    encode("dgdfsgsdfgdsgfgdfgdgdesgdbgdfgdfsgxgxgdfgdfbg", fout);
    fclose(fout);
    getchar();
    /*TODO: clear resources*/
    return 0;
}

