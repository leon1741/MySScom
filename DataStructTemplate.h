#ifndef __DATASTRUCTTEMPLATE_H_
#define __DATASTRUCTTEMPLATE_H_
///////////////////////////////////////////////////////////////////////////////////////
//�����װ��ģ���ඨ��
////////////////////////////////////////////////////////////////////////////////////////
// download by http://www.codefans.net
template < class LIST, class ITEM, int T>
class CDataStructTemplate
{
public:
	CDataStructTemplate()
	{
		TRACE0("CDataStructTemplate()\n");
		Init();
	}
	~CDataStructTemplate()
	{
		TRACE0("~CDataStructTemplate()\n");
		RemoveAll();
	}
protected:
	LIST	m_list;
	LIST	m_blank_list;
public:
	/*********************************************************************************
	���ܣ���ʼ��m_blank_list
	˵��������T��ITEM��㲢����m_blank_list
	��;����ʼ��
	������
	���أ�
	*********************************************************************************/
	void Init()
	{
//		TRACE0("begin alloc list memory\n");
		ASSERT(T>0);
		for(int i=0;i<T;i++)
		{
			ITEM *pitem=new ITEM;
			m_blank_list.AddTail(pitem);
		}
//		TRACE0("end alloc list memory\n");
	}
	/*********************************************************************************
	���ܣ���������ڴ�
	˵����
	��;��
	������
	���أ�
	*********************************************************************************/
	void RemoveAll()
	{
//		TRACE0("begin release list memory\n");
		POSITION pos;

		pos=m_list.GetHeadPosition();
		while(pos!=NULL)
		{
			ITEM *pitem=m_list.GetNext(pos);
			delete pitem;
		}

		m_list.RemoveAll();

		pos=m_blank_list.GetHeadPosition();
		while(pos!=NULL)
		{
			ITEM *pitem=m_blank_list.GetNext(pos);
			delete pitem;
		}
		m_blank_list.RemoveAll();
//		TRACE0("end release list memory\n");
	}
	/*********************************************************************************
	���ܣ�ȡ��m_list��ͷ����λ��
	˵����
	��;������m_list��
	������
	���أ��ɹ���ͷ���POSITION��ʧ�ܣ�NULL
	*********************************************************************************/
	POSITION GetHeadPosition()
	{
//		TRACE0("POSITION GetHeadPosition()\n");
		return m_list.GetHeadPosition();
	}
	/*********************************************************************************
	���ܣ���m_list��ȡ����һ�����
	˵�������������pos,������Ӧ��ITEM��ͬʱ��pos��ֵΪ��һ����λ��
	��;������m_list��
	������pos:���󷵻صĽ��λ��
	���أ��ɹ���ITEM��ʧ�ܣ�NULL
	*********************************************************************************/
	ITEM *GetNext(POSITION &pos)
	{
//		TRACE0("ITEM *GetNext(POSITION &pos)\n");
		ASSERT(pos!=NULL);
		return m_list.GetNext(pos);
	}
	/*********************************************************************************
	���ܣ���m_list��ȡ����һ����㣬����m_blank_list��
	˵�����������һ����㣬��m_list������ɾ���ýڵ㣬��ȡ�÷��ء����򷵻�NULL
	��;������Ϣ������ȡ��һ����Ϣ�����������Ϣ
	��������
	���أ��ɹ���ITEM��ʧ�ܣ�NULL
	*********************************************************************************/
	ITEM *GetNext()
	{
//		TRACE0("ITEM *GetNext()\n");
		ITEM *pitem=NULL;
		if(m_list.GetCount()>0)
		{
			pitem=m_list.RemoveHead();
			m_blank_list.AddTail(pitem);
		}
		return pitem;
	}
	/*********************************************************************************
	���ܣ�ȡ����һ���սڵ㣬���m_blank_list�ѿգ���ȡ��m_list��ͷ�ڵ㣬������m_listβ��
	˵����
	��;��������ʾ
	������
	���أ��ɹ���ITEM������ʧ��
	*********************************************************************************/
	ITEM *GetOwnCycleNext()
	{
//		TRACE0("ITEM *GetOwnCycleNext()\n");
		ASSERT(m_blank_list.GetCount()>0||m_list.GetCount()>0);
		ITEM *pitem=NULL;
		if(m_blank_list.GetCount()>0)
		{
			pitem=m_blank_list.RemoveHead();
			m_list.AddTail(pitem);
		}
		else
		{
			pitem=m_list.RemoveHead();
			m_list.AddTail(pitem);
		}
		return pitem;
	}
	/*********************************************************************************
	���ܣ���m_list��ɾ��һ����㣬���ŵ��ձ���
	˵��������λ���ƽ��
	��;����m_list�еĽ���Ƶ�m_blank_list��
	������pos:Ҫ�ƵĽ��λ��
	���أ��ɹ���ITEM��ʧ�ܣ�NULL
	*********************************************************************************/
	ITEM *RemoveAt(POSITION pos)
	{
//		TRACE0("ITEM *RemoveAt(POSITION pos)\n");
		ASSERT(pos!=NULL);
		ITEM *pitem=NULL;
		pitem=m_list.GetAt(pos);
		m_list.RemoveAt(pos);
		m_blank_list.AddTail(pitem);
		return pitem;
	}
	/*********************************************************************************
	���ܣ���m_list��ɾ��һ����㣬���ŵ��ձ���
	˵�������ݽ���ƽ��
	��;����m_list�еĽ���Ƶ�m_blank_list��
	������pitem
	���أ��ɹ���ITEM��ʧ�ܣ�NULL
	*********************************************************************************/
	ITEM *RemoveAt(ITEM *pitem)
	{
//		TRACE0("ITEM *RemoveAt(ITEM *pitem)\n");
		ASSERT(pitem!=NULL);
		POSITION pos=m_list.Find(pitem);
		ASSERT(pos!=NULL);
		m_blank_list.AddTail(pitem);
		m_list.RemoveAt(pos);
		return pitem;
	}
	/*********************************************************************************
	���ܣ��ӿձ��еõ�һ���սڵ㣬��ձ����Ѿ��޿��ý�㣬���������µĽڵ�
	˵����������������ܷ���һ���ս��
	��;�������½��
	������
	���أ��ɹ���ITEM������ʧ��
	*********************************************************************************/
	ITEM *GetBlank()
	{
//		TRACE0("ITEM *GetBlank()\n");
		ITEM *pitem=NULL;
		if(m_blank_list.GetCount()==0)
		{
			pitem=new ITEM;
		}
		else
		{
			pitem=m_blank_list.RemoveHead();
		}

		m_list.AddTail(pitem);
		ASSERT(pitem!=NULL);
		return pitem;
	}
	void PutToBlank()
	{
		POSITION pos=m_list.GetHeadPosition();
		while(pos!=NULL)
		{
			ITEM *pitem=m_list.GetNext(pos);
			m_blank_list.AddTail(pitem);
		}
		m_list.RemoveAll();
	}
};

#endif //__DATASTRUCTTEMPLATE_H_