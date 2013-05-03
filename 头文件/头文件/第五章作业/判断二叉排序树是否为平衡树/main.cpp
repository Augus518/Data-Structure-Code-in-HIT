//����ƽ��������Ķ��壬�������ڵ���������������������1�������������ƽ���������
//���ȱ�дһ�������������ȵĺ��������õݹ�ʵ�֡�
template<typename T>
static int Depth(BSTreeNode<T>* pbs)
{
	if (pbs==NULL)
		return 0;
	else
	{
		int ld = Depth(pbs->left);
		int rd = Depth(pbs->right);
		return 1 + (ld >rd ? ld : rd);
	}
}
//���������õݹ��ж���������������Ƿ����1���ж��Ƿ���ƽ��������ĺ�����
template<typename T>
static bool isBalance(BSTreeNode<T>* pbs)
{
	if (pbs==NULL)
		return true;
	int dis = Depth(pbs->left) - Depth(pbs->right);
	if (dis>1 || dis<-1 )
		return false;
	else
		return isBalance(pbs->left) && isBalance(pbs->right);
}
