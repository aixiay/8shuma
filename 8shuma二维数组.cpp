#include<iostream>
#include<queue>
#include<math.h>
#include<map>
using namespace std;

template<class T>
struct weizhi  //���岻ͬ״̬�Ľṹ�� 
{
	T erwei[3][3];  //��ά���� 
	int pot0;//0���ڵ�λ�� 
	int step;//���� 
	weizhi() //��ʼ������ 
	{
		pot0=0;
		step=0;
	}
	
};
/* 
ostream& operator<<(ostream &out, weizhi<int> &obj)
{
     // << obj.a << " " << obj.b;
     for(int i=0;i<3;i++)
     {
     	for(int j=0;j<3;j++)
     	cout<<obj.erwei[i][j]<<" ";
	 }
	 out<<endl<<obj.pot0<<" "<<obj.step<<endl;
     return out;
}
*/
template<class T>
class shuma  //8������ 
{
	public:
		shuma(T a[3][3]);
		void jiaohuan(int shu[3][3],int a,int b,int c,int d);//�������� 
		int pot(int a[3][3],int &x,int &y);//0λ�ú��� 
		int bfs();//������� 
		bool cmp(int a[3][3],int b[3][3]); //�ȽϺ��� 
		void fuzhi(int a[3][3],int b[3][3]);//��ֵ���� 
		int trans(int b[3][3]);
		int erfen(int l,int r,int num);
	private:
		int swap[9][4];  ///0�ڲ�ͬ��λ����ʱ�������ı任���ϡ��¡�����   ��0����λ�ã�i,j������Ӧ��i*3+j 
		T shuru[3][3];//�����״̬ 
		int jieguo[3][3];//���״̬ 
		
};

template<class T>
shuma<T>::shuma(T a[3][3])//��ĳ�ʼ�� 
{
//0�ڲ�ͬ��λ����ʱ�������ı任���ϡ��¡�����   ��0����λ�ã�i,j������Ӧ��i*3+j 
	int swapp[9][4]={{0,1,0,1},{0,1,-1,1},{0,1,-1,0},{-1,1,0,1},{-1,1,-1,1},{-1,1,-1,0},{-1,0,0,1},{-1,0,-1,1},{-1,0,-1,0}};
	int jieguoo[3][3]={{1,2,3},{8,0,4},{7,6,5}};//���״̬ 
	for(int i=0;i<9;i++)  //�����ڳ�Ա���и�ֵ 
	{
		for(int j=0;j<4;j++)
			swap[i][j]=swapp[i][j];
	 } 
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			jieguo[i][j]=jieguoo[i][j];
	}
	for(int i=0;i<3;i++)  //�����ʼ״̬ 
	
	{
		for(int j=0;j<3;j++)
			shuru[i][j]=a[i][j];
	}
}

template<class T>
bool shuma<T>::cmp(int a[3][3],int b[3][3])  //�Ƚ�������ά�����Ƿ�һ�� 
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(a[i][j]!=b[i][j])
			{
				return false;//����һ�£�����false 
			}
		} 
	}
	return true;
}

template<class T>
void shuma<T>::jiaohuan(int shu[3][3],int a,int b,int c,int d)  //������ά����������Ԫ�ص�ֵ 
{
	int aa=shu[a][b];
	shu[a][b]=shu[c][d];
	shu[c][d]=aa;
}

template<class T>
int shuma<T>::pot(int a[3][3],int &x,int &y)  //�ҵ���ά������0��λ���Լ��������� 
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(a[i][j]==0)
			{
				x=i;//���º������� 
				y=j;
				return i*3+j;//����0��λ�� 
			}
		}
	}
}

template<class T>
void shuma<T>::fuzhi(int a[3][3],int b[3][3])//��b���鸳ֵ��a���� 
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			a[i][j]=b[i][j];
	}
}

template<class T>
int shuma<T>::trans(int b[3][3])
{
	int num=0;
	int x=8;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			num=num+b[i][j]*pow(10,x);
			x--;
		}
			
	}
	return num;
}
/*
template<class T>
int shuma<T>::erfen(int l,int r,int n)
{
	int mid=l+(r-1)/2;
	if(biaoji[mid]==n)
		return mid;
	else if(l<r&&biaoji[mid]>n)
		return erfen(l,mid-1,n);
	else if(l<r&&biaoji[mid]<n) 
		return erfen(mid+1,r,n);
	return -1;
}
*/

 map<int,int> mm;
weizhi<int> w[4000000];//����Ѿ�������״̬  
template<class T>
int shuma<T>::bfs()
{
	mm.clear();
	int l=0;
	weizhi<int> wei;//������ʱλ�ýṹ����� 
	int x=0;  //0�ĺ������� 
	int y=0;
	//wei.erwei=shuru;
	fuzhi(wei.erwei,shuru);//����״̬��ֵ���ṹ����� 
	//����0��ǰλ�� 
	wei.pot0=pot(shuru,x,y); 
	 //����״̬������ 
	w[l]=wei;
	l++;
	//�Ƚ������Ƿ�һ�� 
	if(cmp(wei.erwei,jieguo))
		return wei.step;
	
	int num=trans(wei.erwei);
	mm[num]=1;
	//����ṹ����� 
	queue<weizhi<int> > q;	
	q.push(wei);  //����һ��״̬������� 

	//�����в�Ϊ��ʱ 
	while(!q.empty())
	{
		wei=q.front();
	//	ȡ�����ײ�ɾ�� 
		q.pop();
		int temp=pot(wei.erwei,x,y);//��¼��ǰ״̬0���ڵ�λ�� �Լ����� 
	//cout<<"temp"<<temp<<endl;
		int b=wei.step;
		if(swap[temp][0]!=0) //�ҵ�0���Ƶ���� 
		{
			//����Ԫ�� 
			jiaohuan(wei.erwei,x,y,x+swap[temp][0],y);
			wei.pot0=pot(wei.erwei,x,y);
			if(cmp(wei.erwei,jieguo))
				return b+1;//������һ�£�����b+1 
				bool kong=false;
			/*for(int i=0;i<l;i++) //��������Ѱ���Ƿ��Լ�������״̬ 
			{
				if(cmp(wei.erwei,w[i].erwei))
				{
					kong=true;
					break;
				}
			}
			//��û�У�����������в������ 
			if(kong==false)	*/
			int nu=trans(wei.erwei); 
			if(mm.count(nu)==0)
			{
				wei.step=b+1;//���²�����0��λ�� 
				wei.pot0=pot(wei.erwei,x,y);
				q.push(wei);
				mm[nu]=1;
				w[l]=wei;
				l++;
			}
			//���ص���ʼ״̬ 
			jiaohuan(wei.erwei,x,y,x-swap[temp][0],y);
			//�����ҵ�0��λ�� 
			wei.pot0=pot(wei.erwei,x,y);
		}
		if(swap[temp][1]!=0)//�ҵ�0С�Ƶ���� 
		{
			//����Ԫ�� 
			jiaohuan(wei.erwei,x,y,x+swap[temp][1],y);
			wei.pot0=pot(wei.erwei,x,y);
			if(cmp(wei.erwei,jieguo))
				return b+1;//������һ�£�����b+1 
				bool kong=false;
		/*	for(int i=0;i<l;i++) //��������Ѱ���Ƿ��Լ�������״̬ 
			{
				if(cmp(wei.erwei,w[i].erwei))
				{
					kong=true;
				}
			}
			//��û�У�����������в������ 
			if(kong==false)*/
				int nu=trans(wei.erwei); 
			if(mm.count(nu)==0)
			{
				wei.step=b+1;//���²�����0��λ�� 
				wei.pot0=pot(wei.erwei,x,y);
				q.push(wei);
				mm[nu]=1;
				w[l]=wei;
				l++;
			}
			//���ص���ʼ״̬ 
			jiaohuan(wei.erwei,x,y,x-swap[temp][1],y);
				//�����ҵ�0��λ�� 
			wei.pot0=pot(wei.erwei,x,y);
		}
		if(swap[temp][2]!=0)//�ҵ�0���Ƶ���� 
		{
			//����Ԫ�� 
			jiaohuan(wei.erwei,x,y,x,y+swap[temp][2]);
			wei.pot0=pot(wei.erwei,x,y);
		//	cout<<wei<<endl;
			if(cmp(wei.erwei,jieguo))
				return b+1;//������һ�£�����b+1 
				bool kong=false;
		/*	for(int i=0;i<l;i++) //��������Ѱ���Ƿ��Լ�������״̬ 
			{
				if(cmp(wei.erwei,w[i].erwei))
				{
					kong=true;
				}
			}
			if(kong==false)*/
			//��û�У�����������в������ 
			int nu=trans(wei.erwei); 
			if(mm.count(nu)==0)
			{
				wei.step=b+1;//���²�����0��λ�� 
				wei.pot0=pot(wei.erwei,x,y);
				q.push(wei);
				mm[nu]=1;
				w[l]=wei;
				l++;
			}
			//���ص���ʼ״̬ 
			jiaohuan(wei.erwei,x,y,x,y-swap[temp][2]);
				//�����ҵ�0��λ�� 
			wei.pot0=pot(wei.erwei,x,y);
		}
		if(swap[temp][3]!=0)//�ҵ�0���Ƶ���� 
		{
		//����Ԫ�� 
			jiaohuan(wei.erwei,x,y,x,y+swap[temp][3]);
			wei.pot0=pot(wei.erwei,x,y);
			if(cmp(wei.erwei,jieguo))
				return b+1;//������һ�£�����b+1 
				bool kong=false;
		/*	for(int i=0;i<l;i++)
			{
				if(cmp(wei.erwei,w[i].erwei)) //��������Ѱ���Ƿ��Լ�������״̬ 
				{
					kong=true;
				}
			}
			//��û�У�����������в������ 
			if(kong==false)*/
				int nu=trans(wei.erwei); 
		if(mm.count(nu)==0)
			{
				wei.step=b+1;//���²�����0��λ�� 
				wei.pot0=pot(wei.erwei,x,y);
				q.push(wei);
				mm[nu]=1;
				w[l]=wei;
				l++;
			}
			//���ص���ʼ״̬ 
			jiaohuan(wei.erwei,x,y,x,y-swap[temp][3]);
				//�����ҵ�0��λ�� 
			wei.pot0=pot(wei.erwei,x,y);
		} 
	}
	return -1;//0;
}

void shixian()
{
	int a[3][3];//����״̬����
	int jishu[10];//��0-8����
	int n;
	//cin>>n;
	cout<<"�밴1��ʼ��"<<endl; 
	while(cin>>n)
	{
		system("cls");
		bool k=false;
		
		cout<<"�������ʼͼ��"<<endl; 
		for(int i=0;i<=9;i++)
			jishu[i]=0;
		char x;
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)//�����ʼ״̬��ͳ��0-8�ĸ���
			{
				cin>>x;
				a[i][j]=x-'0';
				jishu[a[i][j]]++;
			}
				
		}
		for(int i=0;i<=8;i++)
		{
			if(jishu[i]!=1)//���0-8��һ����������1��k=true
			{
				k=true;
				break;
			}
		}
		if(k==true)
		{
			cout<<"�������"<<endl<<"�밴1����..."<<endl;
			continue;
		}
		else
		{
			shuma<int> shu(a);//���������
			int count=shu.bfs();//���
			if(count==-1)
				cout<<"���ܵõ�Ŀ����"<<endl;
			else
				cout<<"ʹ�õĲ����ǣ�"<<count<<endl;
			cout<<"�밴1����..."<<endl;
		 //2 8 3 1 0 4 7 6 5
		}
		
	}
} 
int main()
{
	shixian();
	
	return 0;
} 
