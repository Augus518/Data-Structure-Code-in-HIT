#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>/*����CHAR_BIT�곣�������а�λ�洢ʱʹ��*/

#define CODE_SIZE 255            /*����255���ַ�*/
#define ZIP_HEAD_FLAG 0xaaaaaaaa /* �ļ�ͷ,дѹ���ļ�ʱ�� */

/*�Զ���޷��������б�������,��������*/
typedef unsigned int UINT;
typedef unsigned char UCHAR;
typedef unsigned short USHORT;

/*����곣�������������ڴ�*/
#define UINT_SIZE sizeof(UINT)
#define UCHAR_SIZE sizeof(UCHAR)
#define USHORT_SIZE sizeof(USHORT)

/*���������ڵ�*/
typedef struct treenode
{
    UINT  freq; /* Ƶ�� */
    UCHAR data;
    struct treenode *leftChild;
    struct treenode *rightChild;
} HuffmanTreeNode;

/*���ڱ���*/
typedef struct datacode
{
    USHORT len;
    UCHAR  *pCode;
} DataCode;

/*������ת��Ϊ����*/
typedef struct zhuanhua
{
    USHORT len;
    UCHAR *pCode;
    UCHAR data;
} Code2Data;


/*�������������뱨��Ƕ��ʹ����������*/
UCHAR ConvertToCodeData(const UCHAR codeStr[CHAR_BIT]);
void ConvertToCodeStr(UCHAR codeData, UCHAR codeStr[CHAR_BIT]);


/*�Ӻ���*/
void GetDataFreq(FILE *fp, UINT freqArr[CODE_SIZE])
{
    UCHAR buffer;

    fseek(fp, 0L, SEEK_SET); /* ���ļ�ָ�����¶�λ����ʼλ�� */
    memset(freqArr, 0, UINT_SIZE * CODE_SIZE);
    while(!feof(fp))
    {
        fread(&buffer, UCHAR_SIZE, 1, fp);
        freqArr[buffer]++;
    }
}

/*������������ָ����ָ����ڴ棬����voidΪ�˿ɽ��κ�ָ����룬��Linux���С�*/
void Swapper(void **vpnt1, void **vpnt2)/*����ָ�룬�����������ĵ�ַ���롣��ô�þ�Ȼ��windows�¿��ԣ�Linux�±���*/
{
    void *tempPnt = *vpnt1;
    *vpnt1 = *vpnt2;
    *vpnt2 = tempPnt;
}
void BuildHuffmanTree(HuffmanTreeNode **pTreeHead, const UINT freqArr[CODE_SIZE])
{
    HuffmanTreeNode **dataFreqArr;
    HuffmanTreeNode *tempInsertTreeNode;
    UINT freqLen = CODE_SIZE;
    int i;

    dataFreqArr = (HuffmanTreeNode **)malloc(sizeof(HuffmanTreeNode*) * freqLen);
    for(i = 0; i < CODE_SIZE; i++)
    {
        dataFreqArr[i] = (HuffmanTreeNode *)malloc(sizeof(HuffmanTreeNode));
        dataFreqArr[i]->data = (UCHAR)i;
        dataFreqArr[i]->freq = freqArr[i];
        dataFreqArr[i]->leftChild = NULL;
        dataFreqArr[i]->rightChild = NULL;
    }

    while(freqLen != 1)
    {
        /*ʵ�ַ�����ÿ�α����ҵ���С�������ṹ�壬��������ĩβ�������ӡ�*/
        /* ����С�����ڶ��� */
        if(dataFreqArr[freqLen-1]->freq > dataFreqArr[freqLen-2]->freq)
            Swapper(dataFreqArr + freqLen-1, dataFreqArr + freqLen-2);
        for(i = freqLen-2-1; i >= 0; i--)
        {
            if(dataFreqArr[freqLen-1]->freq > dataFreqArr[i]->freq)
            {
                Swapper(dataFreqArr + freqLen-2, dataFreqArr + i);
                Swapper(dataFreqArr + freqLen-1, dataFreqArr + freqLen-2);
            }
            else if(dataFreqArr[freqLen-2]->freq > dataFreqArr[i]->freq)
            {
                Swapper(dataFreqArr + freqLen-2, dataFreqArr + i);
            }
        }
        /* �ϲ�������� */
        tempInsertTreeNode = (HuffmanTreeNode *)malloc(sizeof(HuffmanTreeNode));
        tempInsertTreeNode->freq = dataFreqArr[freqLen-1]->freq + dataFreqArr[freqLen-2]->freq;
        tempInsertTreeNode->leftChild = dataFreqArr[freqLen-1];
        tempInsertTreeNode->rightChild = dataFreqArr[freqLen-2];
        dataFreqArr[freqLen-2] = tempInsertTreeNode;
        freqLen--;
    }

    *pTreeHead = dataFreqArr[0];
    free(dataFreqArr); /* ֻ�Ǵ�Žڵ��õ� �뿪֮ǰӦ�ͷ� */
}

int ZipCode2Data(const void *op1, const void *op2)
{
    UINT minLen = ((DataCode*)op1)->len < ((DataCode*)op2)->len ? ((DataCode*)op1)->len : ((DataCode*)op2)->len;
    UINT i;

    for(i = 0; i < minLen; ++i)
    {
        if(((DataCode*)op1)->pCode[i] != ((DataCode*)op2)->pCode[i])
            return ((DataCode*)op1)->pCode[i] - ((DataCode*)op2)->pCode[i];
    }
    if(((DataCode*)op1)->len == ((DataCode*)op2)->len)
        return 0;
    if(((DataCode*)op1)->len < ((DataCode*)op2)->len)
        return -((DataCode*)op2)->pCode[i];
    return ((DataCode*)op1)->pCode[i];
}

void RebuildHuffmanTreeOrder(HuffmanTreeNode **pTreeHead, UINT start, UINT end,UINT depth, const Code2Data code2DataArr[CODE_SIZE])
{
    UINT mid, i;
    HuffmanTreeNode *insertChild = NULL;
    /*�жϵ�ǰ��ʼ���������ȵ���ȷ�ԣ�����ȷ���˳�*/
    assert(start < end);
    assert(depth < CODE_SIZE);

    /* ���ݵ�ǰ����0����1 ������ֳ������� */
    mid = end;
    for(i = start; i < end; ++i)
    {
        assert(code2DataArr[i].len > depth);
        if(code2DataArr[i].pCode[depth] != 0)
        {
            mid = i;
            break;
        }
    }

    if(*pTreeHead == NULL)
    {
        *pTreeHead = (HuffmanTreeNode *)malloc(sizeof(HuffmanTreeNode));
        //assert(*pTreeHead);
        (*pTreeHead)->leftChild = NULL;
        (*pTreeHead)->rightChild = NULL;
    }

    /* ��ǰ����0�Ĳ��� */
    if(mid-1 == start)
    {
        insertChild = (HuffmanTreeNode *)malloc(sizeof(HuffmanTreeNode));
        insertChild->leftChild = NULL;
        insertChild->rightChild = NULL;
        insertChild->data = code2DataArr[mid - 1].data;
        (*pTreeHead)->leftChild = insertChild;
    }
    else
        RebuildHuffmanTreeOrder(&(*pTreeHead)->leftChild, start, mid, depth+1, code2DataArr);

    /* ��ǰ����1�Ĳ��� */
    if(mid == end-1)
    {
        insertChild = (HuffmanTreeNode *)malloc(sizeof(HuffmanTreeNode));
        insertChild->leftChild = NULL;
        insertChild->rightChild = NULL;
        insertChild->data = code2DataArr[mid].data;
        (*pTreeHead)->rightChild = insertChild;
    }
    else
        RebuildHuffmanTreeOrder(&(*pTreeHead)->rightChild, mid, end, depth+1, code2DataArr);
}

void RebuildHuffmanTree(HuffmanTreeNode **pTreeHead, const DataCode dataCodeArr[CODE_SIZE])
{
    Code2Data code2DataArr[CODE_SIZE];
    UINT i;

    for(i = 0; i < CODE_SIZE; ++i)
    {
        code2DataArr[i].data = i;
        code2DataArr[i].len = dataCodeArr[i].len;
        code2DataArr[i].pCode = dataCodeArr[i].pCode;
    }
    qsort(code2DataArr, CODE_SIZE, sizeof(Code2Data), ZipCode2Data);
    RebuildHuffmanTreeOrder(pTreeHead, 0, CODE_SIZE, 0, code2DataArr);
    /* ����code2DataArr�е�ָ������ͷ� code2DataArr��Ҫ���� */
}

void FreeTree(HuffmanTreeNode **pTreeHead)
{
    if(*pTreeHead != NULL)
    {
        if((*pTreeHead)->leftChild != NULL)
            FreeTree(&((*pTreeHead)->leftChild));
        if((*pTreeHead)->rightChild != NULL)
            FreeTree(&((*pTreeHead)->rightChild));
        free(*pTreeHead);
        *pTreeHead = NULL;
    }
}

void GetHuffmanCode(const HuffmanTreeNode *pTreeHead, UCHAR code[CODE_SIZE],USHORT codeLen, DataCode dataCodeArr[CODE_SIZE])
{
    if(pTreeHead != NULL)
    {
        if(pTreeHead->leftChild != NULL)/*��Ҷ�ӽڵ�*/
        {
            code[codeLen] = 0;
            GetHuffmanCode(pTreeHead->leftChild, code, codeLen+1, dataCodeArr);
            assert(pTreeHead->rightChild != NULL); /* �����ܳ���һ���к��ӽڵ� һ����û�е���� */
            code[codeLen] = 1;
            GetHuffmanCode(pTreeHead->rightChild, code, codeLen+1, dataCodeArr);
        }
        else     /* Ҷ�ӽڵ� */
        {
            dataCodeArr[pTreeHead->data].pCode = (UCHAR *)malloc(UCHAR_SIZE * codeLen);
            memcpy(dataCodeArr[pTreeHead->data].pCode, code, UCHAR_SIZE * codeLen);
            dataCodeArr[pTreeHead->data].len  = codeLen;
        }
    }
}

void GetFileHuffmanCode(FILE *fp, DataCode dataCodeArr[CODE_SIZE])
{
    HuffmanTreeNode *pTreeHead = NULL;
    UINT freqArr[CODE_SIZE];
    UCHAR code[CODE_SIZE];

    GetDataFreq(fp, freqArr);
    BuildHuffmanTree(&pTreeHead, freqArr);
    memset(dataCodeArr, 0, sizeof(DataCode) * CODE_SIZE);
    memset(code, 0, UCHAR_SIZE * CODE_SIZE);
    GetHuffmanCode(pTreeHead, code, 0, dataCodeArr);
    FreeTree(&pTreeHead);
}


/* ��ѹ���ļ�ͷ�ж�ȡ���� */
int ReadHead(FILE *fp, DataCode dataCodeArr[CODE_SIZE])
{
    UINT zipHeadFlag;
    USHORT codeLen, i, j;
    UCHAR codeBuffer, data;
    UCHAR codeStr[CHAR_BIT];

    fseek(fp, 0L, SEEK_SET);
    fread(&zipHeadFlag, UINT_SIZE, 1, fp);
    if(zipHeadFlag != ZIP_HEAD_FLAG)
        return 1;

    memset(dataCodeArr, 0, sizeof(DataCode) * CODE_SIZE);
    for(i = 0; i < CODE_SIZE; ++i)
    {
        fread(&data, UCHAR_SIZE, 1, fp);
        assert(data == i);
        fread(&codeLen, USHORT_SIZE, 1, fp);
        dataCodeArr[data].len  = codeLen;
        /* �ѱ��뻹ԭ���ַ��� */
        assert(dataCodeArr[data].pCode == NULL);
        dataCodeArr[data].pCode = (UCHAR *)malloc(UCHAR_SIZE * codeLen);
        for(j = 0; j < codeLen - codeLen % CHAR_BIT; j += CHAR_BIT)
        {
            fread(&codeBuffer, UCHAR_SIZE, 1, fp);
            ConvertToCodeStr(codeBuffer, codeStr);
            memcpy(dataCodeArr[data].pCode + j, codeStr, UCHAR_SIZE * CHAR_BIT);
        }
        if(codeLen % CHAR_BIT != 0)
        {
            fread(&codeBuffer, UCHAR_SIZE, 1, fp);
            ConvertToCodeStr(codeBuffer, codeStr);
            memcpy(dataCodeArr[data].pCode + j, codeStr, UCHAR_SIZE * (codeLen % CHAR_BIT));
        }
    }
    return 0;
}
/*���а�λѹ�����ѹ�Ĵ������������ҵ�*/
void WriteHead(FILE *fp, const DataCode dataCodeArr[CODE_SIZE])
{
    USHORT i, j;
    UCHAR codeBuffer, codeStr[CHAR_BIT];
    UINT zipHeadFlag = ZIP_HEAD_FLAG;

    fseek(fp, 0L, SEEK_SET);
    fwrite(&zipHeadFlag, UINT_SIZE, 1, fp);
    for(i = 0; i < CODE_SIZE; i++)
    {
        fwrite(&i, UCHAR_SIZE, 1, fp);
        fwrite(&dataCodeArr[i].len, USHORT_SIZE, 1, fp);
        /* ����λ���㣬���ַ����ĳɶ�����������ļ�ͷ�����ڽ������*/
        for(j = 0; j < dataCodeArr[i].len - dataCodeArr[i].len % CHAR_BIT; j += CHAR_BIT)
        {
            memcpy(codeStr, dataCodeArr[i].pCode + j, UCHAR_SIZE * CHAR_BIT);
            codeBuffer = ConvertToCodeData(codeStr);
            fwrite(&codeBuffer, UCHAR_SIZE, 1, fp);
        }
        if(dataCodeArr[i].len % CHAR_BIT != 0)
        {
            memcpy(codeStr, dataCodeArr[i].pCode + j, UCHAR_SIZE * (dataCodeArr[i].len % CHAR_BIT));
            codeBuffer = ConvertToCodeData(codeStr);
            fwrite(&codeBuffer, UCHAR_SIZE, 1, fp);
        }
    }
}

UCHAR ConvertToCodeData(const UCHAR codeStr[CHAR_BIT])
{
    UCHAR retCode = 0;
    int i;

    for(i = CHAR_BIT-1; i >= 0; --i)
    {
        retCode <<= 1;
        if(codeStr[i] != 0)
            retCode |= 1;
    }
    return retCode;
}

void ConvertToCodeStr(UCHAR codeData, UCHAR codeStr[CHAR_BIT])
{
    UINT i;

    for(i = 0; i < CHAR_BIT; ++i)
    {
        codeStr[i] = ((codeData & 1) != 0);
        codeData >>= 1;
    }
}

/*ѹ����������ʵ�ֽ��ַ��Ĺ������������ѹ������ļ�ͷ������ѹ�����������ĵ���*/
int ZipFile(const char *sourceFileName, const char *targetFileName)
{
    FILE *sourceFp = NULL, *targetFp = NULL;
    DataCode dataCodeArr[CODE_SIZE];
    USHORT writeCodeLen, i;
    UCHAR writeCode[CHAR_BIT], readData, writeData, lastBtyeLen;
    fpos_t lastBtyePos;

    if((sourceFp = fopen(sourceFileName, "rb")) == NULL)
    {
        printf("��%s�ļ����� ", sourceFileName);
        return 1;
    }
    if((targetFp = fopen(targetFileName, "w+b")) == NULL)
    {
        printf("��%s�ļ����� ", targetFileName);
        fclose(sourceFp);
        return 1;
    }
    GetFileHuffmanCode(sourceFp, dataCodeArr);
    WriteHead(targetFp, dataCodeArr);
    lastBtyeLen = 0;
    fgetpos(targetFp, &lastBtyePos); /* ��¼λ�� ����õ�������Ϣ�� ��������д */
    fwrite(&lastBtyeLen, UCHAR_SIZE, 1, targetFp);

    /* ��Դ���ݽ��б���ת�� ��д��Ŀ���ļ��� */
    memset(writeCode, 0, CHAR_BIT);
    writeCodeLen = 0;
    fseek(sourceFp, 0L, SEEK_SET);
    while(!feof(sourceFp))
    {
        /*�����ֽڣ������ҵ�����ת�档*/
        fread(&readData, UCHAR_SIZE, 1, sourceFp);
        for(i = 0; i < dataCodeArr[readData].len; i++)
        {
            writeCode[writeCodeLen++] = dataCodeArr[readData].pCode[i];
            /*ÿ�ܹ�һ���ֽڳ��ȵı��뼴ת��*/
            if(writeCodeLen >= CHAR_BIT)
            {
                writeData = ConvertToCodeData(writeCode);
                fwrite(&writeData, UCHAR_SIZE, 1, targetFp);
                memset(writeCode, 0, UCHAR_SIZE * CHAR_BIT);
                writeCodeLen = 0;
            }
        }
    }
    /* ��ʣ��Ĳ���һ�ֽ�д���ļ� */
    if(writeCodeLen != 0)
    {
        writeData = ConvertToCodeData(writeCode);
        fwrite(&writeData, UCHAR_SIZE, 1, targetFp);
    }
    lastBtyeLen = writeCodeLen;
    fsetpos(targetFp, &lastBtyePos);
    fwrite(&lastBtyeLen, UCHAR_SIZE, 1, targetFp);

    /* ���� */
    for(i = 0; i < CODE_SIZE; ++i)
    {
        if(dataCodeArr[i].pCode != NULL)
        {
            free(dataCodeArr[i].pCode);
            dataCodeArr[i].pCode = NULL;
        }
    }
    fclose(sourceFp);
    fclose(targetFp);
    return 0;
}

int UnzipFile(const char *sourceFileName, const char *targetFileName)
{
    FILE *sourceFp = NULL, *targetFp = NULL;
    DataCode dataCodeArr[CODE_SIZE];
    HuffmanTreeNode *pTreeHead = NULL, *pTreeNode = NULL;
    UCHAR codeStream[CODE_SIZE], codeStr[CHAR_BIT], readData, writeData, lastBtyeLen;
    int codeStreamLen, i;

    if((sourceFp = fopen(sourceFileName, "rb")) == NULL)
    {
        printf("Error�� ");
        return 1;
    }
    if((targetFp = fopen(targetFileName, "w+b")) == NULL)
    {
        printf("Error �� ");
        fclose(sourceFp);
        return 1;
    }

    ReadHead(sourceFp, dataCodeArr);
    fread(&lastBtyeLen,UCHAR_SIZE, 1, sourceFp);
    RebuildHuffmanTree(&pTreeHead, dataCodeArr);
    codeStreamLen = 0;
    while(!feof(sourceFp) || codeStreamLen > 0)
    {
        while(!feof(sourceFp) && codeStreamLen < CODE_SIZE - CHAR_BIT)
        {
            fread(&readData, UCHAR_SIZE, 1, sourceFp);
            ConvertToCodeStr(readData, codeStr);
            memcpy(codeStream+codeStreamLen, codeStr, CHAR_BIT);
            codeStreamLen += CHAR_BIT;
            if(feof(sourceFp))
                codeStreamLen -= lastBtyeLen + CHAR_BIT;
        }

        /* ͨ���������ԭ���� */
        pTreeNode = pTreeHead;
        for(i = 0; i < codeStreamLen; i++)
        {
            if(codeStream[i] == 0)
            {
                pTreeNode = pTreeNode->leftChild;
                if(pTreeNode->leftChild == NULL)
                    break;
            }
            else
            {
                pTreeNode = pTreeNode->rightChild;
                if(pTreeNode->leftChild == NULL)
                    break;
            }
        }

        if(pTreeNode->rightChild != NULL) return 1;/* �Ե�ǰ�ڵ�����жϣ��������Һ��Ӳ�Ϊ�գ���Ϊ�ǽڵ㣬�д� */
        writeData = pTreeNode->data;
        fwrite(&writeData, UCHAR_SIZE, 1, targetFp);

        /* ��ȡ֮��Ҫɾ�� */
        codeStreamLen -= i + 1;
        memcpy(codeStream, codeStream+i+1, codeStreamLen);
    }

    /* ���� */
    FreeTree(&pTreeHead);
    for(i = 0; i < CODE_SIZE; ++i)
    {
        if(dataCodeArr[i].pCode != NULL)
        {
            free(dataCodeArr[i].pCode);
            dataCodeArr[i].pCode = NULL;
        }
    }
    fclose(sourceFp);
    fclose(targetFp);
    return 0;
}

int main()
{
    char *fileName = "book.txt";
    char *zipFileName = "encoded.txt";
    char *unzipFileName = "decoded.txt";
    ZipFile(fileName, zipFileName);
    printf("Ziped file was saved.\n");
    UnzipFile(zipFileName, unzipFileName);
}


