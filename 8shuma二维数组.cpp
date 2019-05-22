#include<iostream>
#include<queue>
#include<math.h>
#include<map>
using namespace std;

template<class T>
struct weizhi  //定义不同状态的结构体 
{
	T erwei[3][3];  //二维数组 
	int pot0;//0所在的位置 
	int step;//步数 
	weizhi() //初始化函数 
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
class shuma  //8数码类 
{
	public:
		shuma(T a[3][3]);
		void jiaohuan(int shu[3][3],int a,int b,int c,int d);//交换函数 
		int pot(int a[3][3],int &x,int &y);//0位置函数 
		int bfs();//广度搜索 
		bool cmp(int a[3][3],int b[3][3]); //比较函数 
		void fuzhi(int a[3][3],int b[3][3]);//赋值函数 
		int trans(int b[3][3]);
		int erfen(int l,int r,int num);
	private:
		int swap[9][4];  ///0在不同的位置上时可以做的变换：上、下、左、右   对0所在位置（i,j），对应到i*3+j 
		T shuru[3][3];//最初的状态 
		int jieguo[3][3];//结果状态 
		
};

template<class T>
shuma<T>::shuma(T a[3][3])//类的初始化 
{
//0在不同的位置上时可以做的变换：上、下、左、右   对0所在位置（i,j），对应到i*3+j 
	int swapp[9][4]={{0,1,0,1},{0,1,-1,1},{0,1,-1,0},{-1,1,0,1},{-1,1,-1,1},{-1,1,-1,0},{-1,0,0,1},{-1,0,-1,1},{-1,0,-1,0}};
	int jieguoo[3][3]={{1,2,3},{8,0,4},{7,6,5}};//结果状态 
	for(int i=0;i<9;i++)  //对类内成员进行赋值 
	{
		for(int j=0;j<4;j++)
			swap[i][j]=swapp[i][j];
	 } 
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			jieguo[i][j]=jieguoo[i][j];
	}
	for(int i=0;i<3;i++)  //输入初始状态 
	
	{
		for(int j=0;j<3;j++)
			shuru[i][j]=a[i][j];
	}
}

template<class T>
bool shuma<T>::cmp(int a[3][3],int b[3][3])  //比较两个二维数组是否一致 
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(a[i][j]!=b[i][j])
			{
				return false;//若不一致，返回false 
			}
		} 
	}
	return true;
}

template<class T>
void shuma<T>::jiaohuan(int shu[3][3],int a,int b,int c,int d)  //交换二维数组中两个元素的值 
{
	int aa=shu[a][b];
	shu[a][b]=shu[c][d];
	shu[c][d]=aa;
}

template<class T>
int shuma<T>::pot(int a[3][3],int &x,int &y)  //找到二维数组中0的位置以及横纵坐标 
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(a[i][j]==0)
			{
				x=i;//更新横纵坐标 
				y=j;
				return i*3+j;//返回0的位置 
			}
		}
	}
}

template<class T>
void shuma<T>::fuzhi(int a[3][3],int b[3][3])//将b数组赋值给a数组 
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
weizhi<int> w[4000000];//存放已经遍历的状态  
template<class T>
int shuma<T>::bfs()
{
	mm.clear();
	int l=0;
	weizhi<int> wei;//定义临时位置结构体变量 
	int x=0;  //0的横纵坐标 
	int y=0;
	//wei.erwei=shuru;
	fuzhi(wei.erwei,shuru);//将初状态赋值给结构体变量 
	//记下0当前位置 
	wei.pot0=pot(shuru,x,y); 
	 //将初状态如数组 
	w[l]=wei;
	l++;
	//比较与结果是否一致 
	if(cmp(wei.erwei,jieguo))
		return wei.step;
	
	int num=trans(wei.erwei);
	mm[num]=1;
	//定义结构体队列 
	queue<weizhi<int> > q;	
	q.push(wei);  //将第一个状态放入队列 

	//当队列不为空时 
	while(!q.empty())
	{
		wei=q.front();
	//	取出队首并删除 
		q.pop();
		int temp=pot(wei.erwei,x,y);//记录当前状态0所在的位置 以及步数 
	//cout<<"temp"<<temp<<endl;
		int b=wei.step;
		if(swap[temp][0]!=0) //找到0上移的情况 
		{
			//交换元素 
			jiaohuan(wei.erwei,x,y,x+swap[temp][0],y);
			wei.pot0=pot(wei.erwei,x,y);
			if(cmp(wei.erwei,jieguo))
				return b+1;//若与结果一致，返回b+1 
				bool kong=false;
			/*for(int i=0;i<l;i++) //在数组中寻找是否以及经过该状态 
			{
				if(cmp(wei.erwei,w[i].erwei))
				{
					kong=true;
					break;
				}
			}
			//若没有，则加入数组中并入队列 
			if(kong==false)	*/
			int nu=trans(wei.erwei); 
			if(mm.count(nu)==0)
			{
				wei.step=b+1;//更新步数和0的位置 
				wei.pot0=pot(wei.erwei,x,y);
				q.push(wei);
				mm[nu]=1;
				w[l]=wei;
				l++;
			}
			//返回到开始状态 
			jiaohuan(wei.erwei,x,y,x-swap[temp][0],y);
			//重新找到0的位置 
			wei.pot0=pot(wei.erwei,x,y);
		}
		if(swap[temp][1]!=0)//找到0小移的情况 
		{
			//交换元素 
			jiaohuan(wei.erwei,x,y,x+swap[temp][1],y);
			wei.pot0=pot(wei.erwei,x,y);
			if(cmp(wei.erwei,jieguo))
				return b+1;//若与结果一致，返回b+1 
				bool kong=false;
		/*	for(int i=0;i<l;i++) //在数组中寻找是否以及经过该状态 
			{
				if(cmp(wei.erwei,w[i].erwei))
				{
					kong=true;
				}
			}
			//若没有，则加入数组中并入队列 
			if(kong==false)*/
				int nu=trans(wei.erwei); 
			if(mm.count(nu)==0)
			{
				wei.step=b+1;//更新步数和0的位置 
				wei.pot0=pot(wei.erwei,x,y);
				q.push(wei);
				mm[nu]=1;
				w[l]=wei;
				l++;
			}
			//返回到开始状态 
			jiaohuan(wei.erwei,x,y,x-swap[temp][1],y);
				//重新找到0的位置 
			wei.pot0=pot(wei.erwei,x,y);
		}
		if(swap[temp][2]!=0)//找到0左移的情况 
		{
			//交换元素 
			jiaohuan(wei.erwei,x,y,x,y+swap[temp][2]);
			wei.pot0=pot(wei.erwei,x,y);
		//	cout<<wei<<endl;
			if(cmp(wei.erwei,jieguo))
				return b+1;//若与结果一致，返回b+1 
				bool kong=false;
		/*	for(int i=0;i<l;i++) //在数组中寻找是否以及经过该状态 
			{
				if(cmp(wei.erwei,w[i].erwei))
				{
					kong=true;
				}
			}
			if(kong==false)*/
			//若没有，则加入数组中并入队列 
			int nu=trans(wei.erwei); 
			if(mm.count(nu)==0)
			{
				wei.step=b+1;//更新步数和0的位置 
				wei.pot0=pot(wei.erwei,x,y);
				q.push(wei);
				mm[nu]=1;
				w[l]=wei;
				l++;
			}
			//返回到开始状态 
			jiaohuan(wei.erwei,x,y,x,y-swap[temp][2]);
				//重新找到0的位置 
			wei.pot0=pot(wei.erwei,x,y);
		}
		if(swap[temp][3]!=0)//找到0右移的情况 
		{
		//交换元素 
			jiaohuan(wei.erwei,x,y,x,y+swap[temp][3]);
			wei.pot0=pot(wei.erwei,x,y);
			if(cmp(wei.erwei,jieguo))
				return b+1;//若与结果一致，返回b+1 
				bool kong=false;
		/*	for(int i=0;i<l;i++)
			{
				if(cmp(wei.erwei,w[i].erwei)) //在数组中寻找是否以及经过该状态 
				{
					kong=true;
				}
			}
			//若没有，则加入数组中并入队列 
			if(kong==false)*/
				int nu=trans(wei.erwei); 
		if(mm.count(nu)==0)
			{
				wei.step=b+1;//更新步数和0的位置 
				wei.pot0=pot(wei.erwei,x,y);
				q.push(wei);
				mm[nu]=1;
				w[l]=wei;
				l++;
			}
			//返回到开始状态 
			jiaohuan(wei.erwei,x,y,x,y-swap[temp][3]);
				//重新找到0的位置 
			wei.pot0=pot(wei.erwei,x,y);
		} 
	}
	return -1;//0;
}

void shixian()
{
	int a[3][3];//输入状态数组
	int jishu[10];//对0-8计数
	int n;
	//cin>>n;
	cout<<"请按1开始："<<endl; 
	while(cin>>n)
	{
		system("cls");
		bool k=false;
		
		cout<<"请输入初始图："<<endl; 
		for(int i=0;i<=9;i++)
			jishu[i]=0;
		char x;
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)//输入初始状态并统计0-8的个数
			{
				cin>>x;
				a[i][j]=x-'0';
				jishu[a[i][j]]++;
			}
				
		}
		for(int i=0;i<=8;i++)
		{
			if(jishu[i]!=1)//如果0-8有一个计数不是1，k=true
			{
				k=true;
				break;
			}
		}
		if(k==true)
		{
			cout<<"输入错误！"<<endl<<"请按1继续..."<<endl;
			continue;
		}
		else
		{
			shuma<int> shu(a);//创建类对象
			int count=shu.bfs();//求解
			if(count==-1)
				cout<<"不能得到目标结果"<<endl;
			else
				cout<<"使用的步数是："<<count<<endl;
			cout<<"请按1继续..."<<endl;
		 //2 8 3 1 0 4 7 6 5
		}
		
	}
} 
int main()
{
	shixian();
	
	return 0;
} 
