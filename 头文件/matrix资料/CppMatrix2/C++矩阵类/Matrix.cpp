/* * * * * * * * * * * * * * * * * * * * * 
* FileName:    Matrix.h
* Description: Matrix Class 
* 
* Version:     1.0
* Author:      wxs
* Finish Time: 2001��7��2��
* * * * * * * * * * * * * * * * * * * * * */

#include "stdafx.h"
#include "Matrix.h"
#include <math.h>

#ifndef _EPSINON_
    #define EPSINON 1e-18
#endif

#ifndef _MINDOUBLE_
#define MINDOUBLE -1.7e+308
#endif

#ifndef _MAXDOUBLE_
#define MAXDOUBLE 1.7e+308
#endif

CMatrix::CMatrix()//���캯��
{
	m_nRow = 0;
	m_nCol = 0;

	m_pData = NULL;
}

CMatrix::CMatrix(int nRow, int nCol)//���ι��캯��
{
    m_nRow = nRow; 
	m_nCol = nCol;

    m_pData = new double*[m_nRow];
    ASSERT(m_pData != NULL);

    for (int i = 0; i < m_nRow; i++)
    {
       m_pData[i] = new double[m_nCol];
       ASSERT(m_pData[i] != NULL);

	   for (int j = 0; j < m_nCol; j++)
       {
           (*this)[i][j] = 0;
       }
    }
}

CMatrix::CMatrix(int nRow, int nCol, double* pAry)//���ι��캯�� 
{
    ASSERT(pAry != NULL);

    m_nRow = nRow; 
	m_nCol = nCol;

    m_pData = new double*[m_nRow];
    ASSERT(m_pData != NULL);

	for (int i = 0; i < m_nRow; i++)
    {
       m_pData[i] = new double[nCol];
       ASSERT(m_pData[i] != NULL);

	   for (int j = 0; j < m_nCol; j++)
       {
           (*this)[i][j] = pAry[i*m_nCol+j];
       }
    }
}

CMatrix::CMatrix(CMatrix & src)
{
	m_nRow = src.Row();
	m_nCol = src.Col();

	m_pData = new double*[src.Row()];
    ASSERT(m_pData != NULL);

    for(int i = 0; i < src.Row(); i++)
	{
        m_pData[i] = new double[src.Col()];
        ASSERT(m_pData[i] != NULL);
		
        for(int j = 0; j < src.Col(); j++)
        {
            (*this)[i][j] = src[i][j];
        }
	}
}

CMatrix::~CMatrix(void)//��������
{
    this->Empty();
}

void CMatrix::Serialize(CArchive &ar)//�ļ�������
{
	CObject::Serialize(ar);
	
	if(ar.IsStoring())
	{
		ar << m_nRow<< m_nCol;

		for(int i = 0; i < m_nRow; i++)
		{
			for(int j = 0; j < m_nCol; j++)
			{
				ar << (*this)[i][j];
			}
		}
	}
	else
	{
		int nRow, nCol;
		
		ar >> nRow >> nCol;
		SetMatrix(nRow, nCol);

		for(int i = 0; i < nRow; i++)
		{
			for(int j = 0; j < nCol; j++)
			{
				ar >> (*this)[i][j];
			}
		}
	}
}

void CMatrix::Draw(CDC *pDC, CPoint pos)//������
{
}

void CMatrix::Empty(void)//��վ���
{
    if (m_pData != NULL)
    {
		for (int i = 0; i < Row(); i++)
		{
		   delete[] m_pData[i];
		}

		delete[] m_pData;

		m_pData = NULL;
    }

    m_nRow = 0; 
	m_nCol = 0;
}

BOOL CMatrix::IsEmpty(void)//�жϾ����Ƿ�Ϊ��
{
    if (m_pData != NULL)
    {
        return FALSE;
    }

	return TRUE;
}

void CMatrix::SetMatrix(int nRow, int nCol)//�����ʼ��Ϊ 0
{
    this->Empty();

    m_nRow = nRow; 
	m_nCol = nCol;

    m_pData = new double*[nRow];
	ASSERT(m_pData != NULL);

    for (int i = 0; i < nRow; i++)
    {
		m_pData[i] = new double[nCol];
		ASSERT(m_pData[i] != NULL);

		for (int j = 0; j < nCol; j++)
		{
		   (*this)[i][j] = 0;
		}
    }

}

void CMatrix::SetMatrix(int nRow, int nCol, double* pAry)//�����ʼ�� : ָ�븳ֵ
{
	ASSERT(pAry != NULL);

	this->Empty();

    m_nRow = nRow; 
	m_nCol = nCol;
	
	m_pData = new double*[nRow];
	ASSERT(m_pData != NULL);

    for (int i = 0; i < nRow; i++)
    {
       m_pData[i] = new double[nCol];
	   ASSERT(m_pData[i] != NULL);

       for (int j = 0; j < nCol; j++)
       {
           (*this)[i][j] = pAry[i*nCol+j];
       }
    }
}

void CMatrix::SetMatrix(double* pAry)//�����ʼ�� : ָ�븳ֵ
{
	ASSERT(!this->IsEmpty());

	for (int i = 0; i < m_nRow; i++)
	{
		for (int j = 0; j < m_nCol; j++)
		{
		   (*this)[i][j] = pAry[i*m_nCol+j];
		}
	}
}

double* & CMatrix::operator [] (int nRow)//���� []
{
	ASSERT(m_pData != NULL);

	ASSERT((nRow >= 0) && (nRow < m_nRow));

    return m_pData[nRow];
}

CMatrix & CMatrix::operator = (CMatrix & mx)//���� =
{
	if (this == &mx)
	{
		return (*this);
	}

	this->Empty();

	m_nRow = mx.Row();
	m_nCol = mx.Col();

	m_pData = new double* [m_nRow];
	ASSERT(m_pData != NULL);

    for (int i = 0; i < m_nRow; i++)
    {
		m_pData[i] = new double[m_nCol];
	    ASSERT(m_pData[i] != NULL);

		for (int j = 0; j < m_nCol; j++)
		{
		   (*this)[i][j] = mx[i][j];
		}
    }

	return (*this);
}

CMatrix & CMatrix::operator += (CMatrix & mx)//���� +=
{
    ASSERT((mx.Row() == m_nRow) && (mx.Col() == m_nCol));

	for (int i = 0; i < m_nRow; i++)
	{
		for (int j = 0; j < m_nCol; j++)
		{
		    (*this)[i][j] += mx[i][j];
		}
	}

    return (*this);
}

CMatrix & CMatrix::operator -= (CMatrix & mx)//���� -=
{
    ASSERT((mx.Row() == m_nRow) && (mx.Col() == m_nCol));

	for (int i = 0; i < m_nRow; i++)
	{
		for (int j = 0; j < m_nCol; j++)
		{
		   (*this)[i][j] -= mx[i][j];
		}
	}

    return (*this);
}

CMatrix & CMatrix::operator *= (CMatrix & mx)//���� *=
{
    ASSERT((mx.Row() == m_nRow) && (mx.Col() == m_nCol));

	for (int i = 0; i < m_nRow; i++)
	{
		for (int j = 0; j < m_nCol; j++)
		{
		   m_pData[i][j] *= mx[i][j];
		}
	}

    return (*this);
}

int CMatrix::Pivot(int nRow)//����Ԫ��Ԫ
{
	double fMax = (*this)[nRow][nRow];
	int nMaxRow = nRow;

    for (int i = nRow+1; i < m_nRow; i++)
    {
		double fTmp = fabs((*this)[i][nRow]);
        if (fTmp > fMax)
        {
            fMax = fTmp;
            nMaxRow = i;
        }
    }

    if (fabs((*this)[nMaxRow][nRow]) < EPSINON)
    {
        return -1;
    }

    if (nMaxRow != nRow)
    {
        SwapRow(nRow, nMaxRow);
        return nMaxRow;
    }

    return 0;
}

void CMatrix::SwapRow(int nRow1, int nRow2)//�н���                      
{
	ASSERT((nRow1 >= 0) && (nRow1 < m_nRow));
	ASSERT((nRow2 >= 0) && (nRow2 < m_nRow));

	if (nRow1 == nRow2)
	{
	    return;
	}

	double* p;
    p = m_pData[nRow1];
	m_pData[nRow1] = m_pData[nRow2];
    m_pData[nRow2] = p;
}

void CMatrix::SwapCol(int nCol1, int nCol2)//�н���
{
	ASSERT((nCol1 >= 0) && (nCol1 < m_nCol));
	ASSERT((nCol2 >= 0) && (nCol2 < m_nCol));

	if (nCol1 == nCol2)
	{
	    return;
	}

    double fTmp;
	for (int nRow = 0; nRow < m_nRow; nRow++)
	{
	    fTmp = (*this)[nRow][nCol1];
		(*this)[nRow][nCol1] = (*this)[nRow][nCol2];
		(*this)[nRow][nCol2] = fTmp;
	}
}

void CMatrix::ToUnit()//��λ����
{
    for(int i = 0; i < m_nRow; i++)
    {
        for(int j = 0; j < m_nCol; j++)
        {
            if( i == j )
			{
                (*this)[i][j] = 1;
			}
            else
			{
                (*this)[i][j] = 0;
			}
        }
    }
}

void CMatrix::ToNull()//�����
{
    for(int i = 0; i < m_nRow; i++)
    {
        for(int j = 0; j < m_nCol; j++)
        {
            (*this)[i][j] = 0;
        }
    }
}

double CMatrix::Max()//�����ֵ
{                        
    double fMax = MINDOUBLE;
    
	for (int i = 0; i < m_nRow; i++)
    {
        for (int j=0; j < m_nCol; j++)
        {
            fMax = max(fMax, (*this)[i][j]);
        }
    }

    return fMax;
}

double CMatrix::Min()//����Сֵ
{                        
    double fMin = MAXDOUBLE;
    
	for (int i = 0; i < m_nRow; i++)
    {
        for (int j=0; j < m_nCol; j++)
        {
            fMin = min(fMin, (*this)[i][j]);
        }
    }

    return fMin;
}
 
double CMatrix::Det()//����ʽ 
{                        
	ASSERT(m_nRow == m_nCol);

	double fDet = 1.0f; 

	int *pI, *pJ;

	pI = new int[this->Row()];
	ASSERT(pI != NULL);
	
	pJ = new int[this->Col()];
	ASSERT(pJ != NULL);

    CMatrix mxTmp(*this);
	int nSign = 1; 

	int k, i, j;

	for (k = 0; k < mxTmp.Row(); k++) 
	{
	    pI[k] = -1;
		pJ[k] = -1;
	}

	for (k = 0; k < mxTmp.Row(); k++) 
	{ 
	    //ȫѡ��Ԫ 
	    double fMax = MINDOUBLE; 
	    for (i = k; i < mxTmp.Row(); i++) 
		{ 
	        for (j = k; j < mxTmp.Col(); j++) 
			{ 
	            double fTmp = fabs(mxTmp[i][j]); 
	            if (fTmp > fMax) 
				{ 
	                fMax = fTmp; 
	                pI[k] = i; 
	                pJ[k] = j; 
				} 
			} 
		} 
	
		if (fabs(fMax) < EPSINON) 
		{
			return 0;
		}

	    if (pI[k] != k) 
		{ 
	        nSign = -nSign; 
			mxTmp.SwapRow(k, pI[k]);
		} 
	
		if (pJ[k] != k) 
		{ 
	        nSign = -nSign; 
			mxTmp.SwapCol(k, pJ[k]);
		} 

		//��������ʽ
		fDet *= mxTmp[k][k];

	    //��������� 
		mxTmp[k][k] = 1.0f / mxTmp[k][k]; 
		
		for (j = 0; j < mxTmp.Col(); j++) 
		{ 
		    if (j != k) 
			{
		        mxTmp[k][j] *= mxTmp[k][k];
			}
		} 

		for (i = 0; i < mxTmp.Row(); i++) 
		{ 
		    if (i != k) 
			{ 
		        for (j = 0; j < mxTmp.Col(); j++) 
				{ 
		            if (j != k) 
					{
		                mxTmp[i][j] = mxTmp[i][j] - mxTmp[i][k] * mxTmp[k][j]; 
					}
				} 
			} 
		} 

		for (i = 0; i < mxTmp.Row(); i++) 
		{ 
		    if (i != k) 
			{
		        mxTmp[i][k] *= -mxTmp[k][k]; 
			}
		} 
	}//for of end

	for (k = mxTmp.Row()-1; k >= 0; k--) 
	{ 
		if ((pJ[k] != -1) && (pJ[k] != k)) 
		{ 
			mxTmp.SwapCol(k, pJ[k]);
		} 

		if ((pI[k] != -1) && (pI[k] != k))
		{ 
			mxTmp.SwapRow(k, pI[k]);
		} 
	} 

	delete [] pI;
	delete [] pJ;

	return fDet*nSign; 
}

int CMatrix::SolveLinearQquations(double ary [])//����Ԫ��Ԫ�������Է�����
{
	ASSERT( (m_nRow+1) == m_nCol );

	int i, j, nIndex;
	double fTmp;
    CMatrix mxTmp(*this);

    for (int k = 0; k < mxTmp.Row()-1; k++)
    {
        nIndex = mxTmp.Pivot(k);
        if (nIndex == -1)// mxTmp[k][k] == 0 ==>> xk�ж��
        {
            //AfxMessageBox("Invalid Matrix!");
			continue;
        }

        for (i = k+1; i < mxTmp.Row(); i++)
        {
			fTmp = mxTmp[i][k] / mxTmp[k][k];

            for (j = k+1; j < mxTmp.Col(); j++)
            {
                mxTmp[i][j] -= fTmp * mxTmp[k][j];
            }
        }
    }

	for (i = mxTmp.Row()-1; i >= 0; i--)
	{
		ary[i] = 0;
		fTmp = 0 ;

		for (j = i+1; j < mxTmp.Row(); j++)
		{
		    fTmp += mxTmp[i][j] * ary[j];  
		}

		if (fabs(mxTmp[i][i]) < EPSINON)
			ary[i] = 0;
		else
		    ary[i] = (mxTmp[i][mxTmp.Col()-1] - fTmp) / mxTmp[i][i];
	}

    return ( nIndex );
}

BOOL CMatrix::SaveMatrix()
{ 
	TCHAR BASED_CODE szFilter[] = _T("ASCII Files(*.txt)|*.txt|Binary Files(*.mxb)|*.mxb|");

	CFileDialog dlg(false, _T("MatrixFile.mxa"), NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter);

	if(dlg.DoModal() != IDOK)
	{
        return FALSE;
	}

	CString strExt = dlg.GetFileExt();
	strExt.MakeUpper();
    BOOL bASCII = (strExt == _T("TXT"));
	

	BOOL bFlag = SaveMatrix(dlg.GetPathName(), bASCII);

	return bFlag;
}

BOOL CMatrix::SaveMatrix(CString strPath, BOOL bASCII)
{ 
	CFile file(strPath, CFile::modeCreate | CFile::modeReadWrite);
	CArchive ar(&file, CArchive::store);

	if(bASCII)
	{
		CString strTmp, strRow;
		
		ar.WriteString(_T("-------------------------------"));
		ar.WriteString(_T("\r\n"));//�س����з���
		strTmp.Format(_T("ROW : %d, COL : %d"), m_nRow, m_nCol);
		ar.WriteString(strTmp);
		ar.WriteString(_T("\r\n"));

		for(int i = 0; i < m_nRow; i++)
		{
		    strRow = _T("");
			for(int j = 0; j < m_nCol; j++)
			{
			    strTmp.Format(_T("%.8lf  "), (*this)[i][j]);
			    strRow += strTmp;
			}

			ar.WriteString(strRow);
			ar.WriteString(_T("\r\n"));
		} 
        
		ar.WriteString(_T("-------------------------------"));
		ar.WriteString(_T("\r\n"));

		return TRUE;
	}
	else
	{
	    Serialize(ar);
	    return TRUE;
	}

	return FALSE;
}

BOOL CMatrix::LoadMatrix(CString strPath)
{ 
	this->Empty();

	CFile file(strPath, CFile::modeRead);
	CArchive ar(&file, CArchive::load);

	Serialize(ar);

	return TRUE;
}

BOOL CMatrix::LoadMatrix()
{
	this->Empty();

	TCHAR BASED_CODE szFilter[] = _T("Binary Files(*.mxb)|*.mxb|");
	CFileDialog dlg(true, _T("Binary Files(*.mxb)"), NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter);

	if(dlg.DoModal() == IDOK)
	{
		CString strPath = dlg.GetPathName();
		CFile file(strPath, CFile::modeRead);
		CArchive ar(&file, CArchive::load);

		Serialize(ar);

		return TRUE;
	}

	return FALSE;
}


/*---------------------------------------
*��Ԫ
----------------------------------------*/
CMatrix operator + (CMatrix & mx, double k)//���� + : �������������
{
	CMatrix mxTmp(mx.Row(), mx.Col());

	for (int i = 0; i < mx.Row(); i++)
	{
		for (int j = 0; j < mx.Col(); j++)
		{
			mxTmp[i][j] = k + mx[i][j];
		}
	}

    return mxTmp;
}

CMatrix operator + (double k, CMatrix & mx)//���� + : �������������
{
	CMatrix mxTmp(mx.Row(), mx.Col());

	for (int i = 0; i < mx.Row(); i++)
	{
		for (int j = 0; j < mx.Col(); j++)
		{
			mxTmp[i][j] = k + mx[i][j];
		}
	}

    return mxTmp;
}

CMatrix operator + (CMatrix & mx1, CMatrix & mx2)//���� + : �������
{
    ASSERT((mx1.Row() == mx2.Row()) && (mx1.Col() == mx2.Col()));

	CMatrix mxTmp(mx1.Row(), mx1.Col());

	for (int i = 0; i < mxTmp.Row(); i++)
	{
		for (int j = 0; j < mxTmp.Col(); j++)
		{
		    mxTmp[i][j] = mx1[i][j] + mx2[i][j];
		}
	}

	return mxTmp;
}

CMatrix operator - (CMatrix & mx, double k)//���� - : �������������
{
	CMatrix mxTmp(mx.Row(), mx.Col());

	for (int i = 0; i < mx.Row(); i++)
	{
		for (int j = 0; j < mx.Col(); j++)
		{
			mxTmp[i][j] = mx[i][j] - k;
		}
	}

    return mxTmp;
}

CMatrix operator - (double k, CMatrix & mx)//���� - : �������������
{
	CMatrix mxTmp(mx.Row(), mx.Col());

	for (int i = 0; i < mx.Row(); i++)
	{
		for (int j = 0; j < mx.Col(); j++)
		{
			mxTmp[i][j] = k - mx[i][j];
		}
	}

    return mxTmp;
}

CMatrix operator - (CMatrix & mx1, CMatrix & mx2)//���� - : �������
{
    ASSERT((mx1.Row() == mx2.Row()) && (mx1.Col() == mx2.Col()));

	CMatrix mxTmp(mx1.Row(), mx1.Col());

	for (int i = 0; i < mx1.Row(); i++)
	{
		for (int j = 0; j < mx2.Col(); j++)
		{
		    mxTmp[i][j] = mx1[i][j] - mx2[i][j];
		}
	}

	return mxTmp;
}

CMatrix operator * (CMatrix & mx, double k)//���� * : �������������
{
	CMatrix mxTmp(mx.Row(), mx.Col());

	for (int i = 0; i < mx.Row(); i++)
	{
		for (int j = 0; j < mx.Col(); j++)
		{
			mxTmp[i][j] = mx[i][j] * k;
		}
	}

    return mxTmp;
}

CMatrix operator * (double k, CMatrix & mx)//���� * : �������������
{
	CMatrix mxTmp(mx.Row(), mx.Col());

	for (int i = 0; i < mx.Row(); i++)
	{
		for (int j = 0; j < mx.Col(); j++)
		{
			mxTmp[i][j] = k * mx[i][j];
		}
	}

    return mxTmp;
}

CMatrix operator * (CMatrix & mx1, CMatrix & mx2)//���� * : �������
{
    ASSERT((mx1.Row() == mx2.Row()) && (mx1.Col() == mx2.Col()));

	CMatrix mxTmp(mx1.Row(), mx1.Col());

	for (int i = 0; i < mx1.Row(); i++)
	{
		for (int j = 0; j < mx2.Col(); j++)
		{
		    mxTmp[i][j] = mx1[i][j] * mx2[i][j];
		}
	}

	return mxTmp;
}

BOOL operator == (CMatrix & mx1, CMatrix & mx2)//���� ==
{
    if ((mx1.Row() != mx2.Row()) || (mx1.Col() != mx2.Col()))
	{
        return FALSE;
	}

    for (int i = 0; i < mx1.Row(); i++)
	{
        for (int j = 0; j < mx1.Col(); j++)
		{
            if (mx1[i][j] != mx2[i][j])
			{
                return FALSE;
			}
		}
	}

    return TRUE;
}

BOOL operator != (CMatrix & mx1, CMatrix & mx2)//���� !=
{
    return((mx1 == mx2) ? FALSE : TRUE);
}

CMatrix operator ^ (CMatrix & mx, int pow)//�������
{    
	ASSERT(pow > 1);

	CMatrix mxTmp(mx);

	for (int i = 2; i <= pow; i++)
    {
        mxTmp *= mx;
    }

    return mxTmp;
}

CMatrix operator ~ (CMatrix & mx)//����ת��
{    
	CMatrix mxTmp(mx.Col(), mx.Row());

	for (int i = 0; i < mx.Row(); i++)
	{
		for (int j = 0; j < mx.Col(); j++)
		{
			mxTmp[j][i] = mx[i][j];
		}
	}

	return mxTmp;
}

CMatrix operator ! (CMatrix & mx)//�����
{
	ASSERT(mx.Row() == mx.Col());

	int *pI, *pJ;

	pI = new int[mx.Row()];
	ASSERT(pI != NULL);
	
	pJ = new int[mx.Col()];
	ASSERT(pJ != NULL);

    CMatrix mxTmp(mx);
	int k, i, j;

	for (k = 0; k < mxTmp.Row(); k++) 
	{
	    pI[k] = -1;
		pJ[k] = -1;
	}

	for (k = 0; k < mxTmp.Row(); k++) 
	{ 
	    //ȫѡ��Ԫ 
	    double fMax = MINDOUBLE; 
	    for (i = k; i < mxTmp.Row(); i++) 
		{ 
	        for (j = k; j < mxTmp.Col(); j++) 
			{ 
	            double fTmp = fabs(mxTmp[i][j]); 
	            if (fTmp > fMax) 
				{ 
	                fMax = fTmp; 
	                pI[k] = i; 
	                pJ[k] = j; 
				} 
			} 
		} 
	
		if (fabs(fMax) < EPSINON) 
		{
			//AfxMessageBox(_T("Matrix Not Inverse!"));
			return mxTmp;
		}

	    if (pI[k] != k) 
		{ 
			mxTmp.SwapRow(k, pI[k]);
		} 
	
		if (pJ[k] != k) 
		{ 
			mxTmp.SwapCol(k, pJ[k]);
		} 

	    //��������� 
		mxTmp[k][k] = 1.0f / mxTmp[k][k]; 
		
		for (j = 0; j < mxTmp.Col(); j++) 
		{ 
		    if (j != k) 
			{
		        mxTmp[k][j] *= mxTmp[k][k];
			}
		} 

		for (i = 0; i < mxTmp.Row(); i++) 
		{ 
		    if (i != k) 
			{ 
		        for (j = 0; j < mxTmp.Col(); j++) 
				{ 
		            if (j != k) 
					{
		                mxTmp[i][j] = mxTmp[i][j] - mxTmp[i][k] * mxTmp[k][j]; 
					}
				} 
			} 
		} 

		for (i = 0; i < mxTmp.Row(); i++) 
		{ 
		    if (i != k) 
			{
		        mxTmp[i][k] *= -mxTmp[k][k]; 
			}
		} 
	}//for of end

	for (k = mxTmp.Row()-1; k >= 0; k--) 
	{ 
		if ((pJ[k] != -1) && (pJ[k] != k)) 
		{ 
			mxTmp.SwapCol(k, pJ[k]);
		} 

		if ((pI[k] != -1) && (pI[k] != k))
		{ 
			mxTmp.SwapRow(k, pI[k]);
		} 
	} 

	delete [] pI;
	delete [] pJ;

	return mxTmp; 
}
