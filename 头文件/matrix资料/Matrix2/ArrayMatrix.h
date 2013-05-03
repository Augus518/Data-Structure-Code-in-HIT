// ArrayMatrix.h: interface for the CArrayMatrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARRAYMATRIX_H__75314E61_4BBF_11D5_9DFE_5254AB1C303A__INCLUDED_)
#define AFX_ARRAYMATRIX_H__75314E61_4BBF_11D5_9DFE_5254AB1C303A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
#include <string.h>

class CArrayMatrix : public CObject  
{
public:
	BOOL SetName(CString m);
	CString GetName();
	CArrayMatrix GetAccompany()const;//�����İ������
	float GetRange()const;//����������ʽ
	BOOL CanContrary()const;//�Ƿ��������
	CArrayMatrix T()const;//������ת�þ���
	CArrayMatrix operator ~();//�����������
	CArrayMatrix operator /(CArrayMatrix & m);
	CArrayMatrix operator /(float m);
	CArrayMatrix operator *(const CArrayMatrix & m);
	CArrayMatrix operator *(float m);
	BOOL CanMutiply(const CArrayMatrix & m)const;
	BOOL CanAddSub(const CArrayMatrix & m)const;
	BOOL DisPlay(CString & out)const;
	static void DeleteHeadEnter(CString &);	//ɾ���ַ���������Ϣ�з��ڵȺ��ұߵ��������з��Ϳո�
	static void ProcString(CString &);
	static void ProcStringEnter(CString &);
	static void ProcStringComma(CString &);//���ַ����еĶ��ţ�������ɿո��ǽ������ֺţ�������ɻ��з�'\n'
	static void ProcStringBlank(CString &);//ʹ�ַ�����񻯣���ʹ���еĿո�Ϊһ��
	static BOOL SetStringName(CString & DataString,CString & sName);
	BOOL ProcessInput(CString DataString);
	CArrayMatrix(const CArrayMatrix &);
	void Serialize(CArchive& ar);
	DECLARE_SERIAL(CArrayMatrix)
	CArrayMatrix();
	virtual ~CArrayMatrix();
	CArrayMatrix operator +(const CArrayMatrix & m);
	CArrayMatrix operator -(const CArrayMatrix & m);
	CArrayMatrix & operator =(const CArrayMatrix &m);
	CArrayMatrix & operator =(float m);

protected:
	BOOL ConvertToNum(const CString &,const int &,float &);
	BOOL InputCon(const CString &,CString *&);
	BOOL InputRow(const CString &);
	CString m_Name;
	UINT m_wRow;
	UINT m_wCon;
	CArray<float,float &> m_Array;
};

#endif // !defined(AFX_ARRAYMATRIX_H__75314E61_4BBF_11D5_9DFE_5254AB1C303A__INCLUDED_)
