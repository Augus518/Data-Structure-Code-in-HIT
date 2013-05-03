/* * * * * * * * * * * * * * * * * * * * * 
* FileName:    Matrix.h
* Description: Matrix Class 
* 
* Version:     1.0
* Author:      wxs
* Finish Time: 2001��7��2��
* * * * * * * * * * * * * * * * * * * * * */

#ifndef _MATRIX_H_
#define _MATRIX_H_

class CMatrix : public CObject
{
public:

	//���캯��
	CMatrix();
	CMatrix(int nRow, int nCol);
	CMatrix(int nRow, int nCol, double* pAry);
	CMatrix(CMatrix & src);//�������캯��

	//��������
	virtual ~CMatrix();

	void Serialize(CArchive& ar);//�ļ�������

	void Draw(CDC *pDC, CPoint pos);//������

	//���������
	double* & operator [] (int nRow);
	CMatrix & operator =  (CMatrix & mx);
	CMatrix & operator += (CMatrix & mx);
	CMatrix & operator -= (CMatrix & mx);
	CMatrix & operator *= (CMatrix & mx);
	
	//��������
	void Empty(void);
	BOOL IsEmpty(void);
	void SetMatrix(int nRow, int nCol);
	void SetMatrix(int nRow, int nCol, double* pAry);
	void SetMatrix(double* pAry);
	int Pivot(int nRow);//private partial pivoting method

    void SwapRow(int nRow1, int nRow2);//�н���   
    void SwapCol(int nCol1, int nCol2);//�н���
	void ToUnit(void);//��λ����
	void ToNull(void);//�����
	double Max(void);//�����ֵ
	double Min(void);//����Сֵ
	double Det(void);//����ʽ
	int SolveLinearQquations(double ary []);//����Ԫ��Ԫ�������Է����� Solution system of linear eqations

	int Row() const { return m_nRow; }
	int Col() const { return m_nCol; }
  
	BOOL LoadMatrix();
	BOOL LoadMatrix(CString strPath);
	BOOL SaveMatrix(CString strPath, BOOL bASCII = TRUE); 
	BOOL SaveMatrix();

	//��Ԫ
	friend CMatrix operator + (CMatrix & mx, double k);
	friend CMatrix operator + (double k, CMatrix & mx);
    friend CMatrix operator + (CMatrix & mx1, CMatrix & mx2);
	//friend CMatrix operator - (CMatrix & mx, double k);
	//friend CMatrix operator - (double k, CMatrix & mx);
	//friend CMatrix operator - (CMatrix & mx1, CMatrix & mx2);
	friend CMatrix operator * (CMatrix & mx, double k);
	friend CMatrix operator * (double k, CMatrix & mx);
	friend CMatrix operator * (CMatrix & mx1, CMatrix & mx2);
	friend CMatrix operator ^ (CMatrix & mx, int pow);//�������
	friend BOOL operator != (CMatrix & mx1, CMatrix & mx2);
	friend BOOL operator == (CMatrix & mx1, CMatrix & mx2);
	friend CMatrix operator ~ (CMatrix & mx);//����ת��
	friend CMatrix operator ! (CMatrix & mx);//�����

#ifdef _DEBUG
    void Output() const;
#endif

private:

    int m_nRow;//����
	int m_nCol;//����

	double* *m_pData;
};

#endif //#ifndef _MATRIX_H_
