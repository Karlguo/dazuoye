/*
 * ʵ��һ��list������ΪMyList���书����python�������ơ�����������ʵ�֣�Ҳ����������ʵ�֡�
 * ����ʹ��template <class T>��������ʹ��<iostream>����Ŀ⡣
 * ��Ҫʵ�ֵĹ�������Դ�����¡�����ظ����ÿһ������壬����ʲôʱ����Ҫ����Ԫ����ʲôʱ����Ҫconstʲôʱ����Ҫ&��
 * ��ĳЩ���û������������ܲ�����run time error����popһ�������飬�����һ�������±��Ԫ�أ���
 * ��ʹ��try-catch-throw�������
 * �����ඨ�岻��֤��ȫ��ȷ�������ʵ�������޸ģ���ʵ����������Ϊ����
 */

/* 
 * ����ϰ���漰���������̳У�������ĩ�����ҾͲ�֪���ˡ������ʱ����������ϵ�shape������ϰ��
 */

#include<iostream>
using namespace std;
template<class T>
class MyList;

template<class T>
MyList<T> operator +(const MyList<T> &l1, const MyList<T> &l2)
{	MyList<T> tmp(l1);
	for (int i=0;i<l2.last;++i)	tmp.push(l2.a[i]);
	return tmp;
	
}

template<class T>
MyList<T> operator +(const MyList<T> &l1, const T &item)
{	MyList<T> tmp(l1);
	tmp.push(item);
	return tmp;
}

template<class T>
ostream & operator<<(ostream &os, const MyList<T> &obj)
{	os << endl;
	for (int i=0;i<obj.last;++i) os << obj.a[i] << '\t';
	return os;
}


template<class T>
class MyList{
	friend MyList<T> operator + <>(const MyList<T> &, const MyList<T> &);//�ϲ�����MyList
    friend MyList<T> operator + <>(const MyList<T> &, const T &); //ͬpush(T item)�������޸�l1������һ��������
    friend ostream &operator<< <>(ostream &, const MyList<T> &);//���T�ǿ���ֱ��cout����Ļ�������int������Python����ĸ�ʽ���MyList�е�ÿһ��Ԫ�أ����磺
    // [1, 2, 5, 4, 1]
    
private:
	int last;
	T *a;
	int size;

	void double_space()//�����С������ʱ�������С�����Ĳ�����
	{	size = size * 2;
		T *b;
		b = new T [size];
		for (int i=0;i<size/2;++i) b[i] = a[i];
		for (int i=size/2;i<size;++i) b[i] = 0;
		delete [] a;
		a = b;
	}

	int divide (int a[],int low,int high)
	{	T k = a[low];
		do{	while (low < high && a[high] >= k) --high;
			if (low<high){a[low] = a[high];++low;}
			while (high > low && a[low]  <= k) ++low;
			if (low<high) {a[high] = a[low];--high;}
		}while (low < high);
		a[low] = k;
		return low;
	}
	void quicksort (int a[],int low,int high)
	{	int mid;
		if (low >= high) return;
		mid = divide (a,low,high);
		quicksort (a,low,mid-1);
		quicksort (a,mid+1,high);
		
	}	
	
	
	
public:
	MyList(){
		size = 100;
		a = new T [size];
		last=0;
	}
	MyList(int num, const T &item)//��item�ظ�num�����������С�
	{	a = new T [num+1];
		size = num;
		last = num;
		for (int i=0;i<num;++i)a[i] = item;
	}
	MyList(const MyList &l)//�������һ��MyList��
	{	a = new T [l.last+1];
		size = l.last;
		last = l.last;
		for (int i=0;i<l.last;++i)	a[i] = l.a[i];
	}
    MyList(T *arr, int len)//��arr��ǰlen��Ԫ�ع�������
    {	a = new T [len+1];
    	size = len;
    	last = len;
		for (int i=0;i<len;++i)	a[i] = arr[i];
	}

	void push(const T &item)//��item�����MyList���
	{	if (last>=size) double_space();
		a[last] = item;
		++last;
	}
	T pop()//��MyList�����һ��Ԫ��ɾ�������������ɾ����Ԫ�ء�
	{	int k=a[last];
		a[last] = NULL;
		--last;
		return k; 
	}
	
	void insert(int index, const T &item)//��item���뵽place����
	{	try	{	if(index >= (-1)*last && index < last+1)
				{	if (last>=size) double_space();
					for (int i=last;i>index;--i)	a[i] = a[i-1];
					a[index] = item;
					++last;
				}
				else throw 1;
			}
		catch(int) {cout << "mistake A:out of range!" << endl;
				cout << "you have make a wrong input \"" << index << "\" here, please try again." <<endl;
				exit(-1);}
	}
	void clean()//������顣
	{	delete [] a;
		last = 0;
		a = new T[0];
	}
	
	int get_size()//����MyList��Ԫ�ص�������
	{	return last;
			
	}
	
	void erase(int start, int end) //ɾ��MyList�е�start����endλ��Ԫ�أ��������ߡ�
	{	try	{ 	if (start>= (-1)*last && start<last && end >= (-1) * last && end<last)
				{	int i;
					for (i=start;i<last-end+start-1;++i) a[i] = a[i+end-start+1];
					int x = i;
					for (i=x;i<last;++i) a[i] = 0;
					last = last - end + start - 1;
				}
				else throw 1;
			}
		catch(int){cout << "mistake B:out of range!" <<endl;
				cout << "you have make a wrong input here, please try again." <<endl;
				exit(-1);}
	}
	
	T get_item(int index)//���ص�index��Ԫ�ء�
	{	try	{	if(index>=(-1)*last&&index<last) {return a[index];}
				else throw 1;
			}
		catch(int) {cout << "mistake C:out of range!" << endl;
			cout << "you have make a wrong input \"" << index << "\" here, please try again." <<endl;
			exit(-1);}
			
	}
	
	MyList get_item(int start, int end)//����MyList�е�start����endλ��Ԫ�أ��������ߡ��˴���Ҫ��pythonһ�����ܸ�������������Դ��롣
	{	try	{	if (start>= (-1)*last && start<last && end >= (-1)*last && end<last)
				{	if (start<0)	start = last + start;
					if (end<0)		end = last + end;
					if (start>end)
					{	T tmp[0];
						MyList tmpp(tmp,0);
						return tmpp;
					}
					T tmp[end-start+1];
					for (int i=0;i<end-start+1;++i) tmp[i] = a[start+i];
					MyList tmpp(tmp,end-start+1);
					return tmpp;
				}
				else throw 1;
			}
		catch (int) {cout << "mistake D:out of range!" << endl;
			cout << "you have make a wrong input here, please try again." <<endl;
			exit(-1);}
	}
	int count(const T &item)//����MyList�к�item��ȵ�Ԫ�صĸ�����
	{	int count;
		for (int i=0;i<last;++i)
		{	if (a[i] == item) ++count;
		}
		return count;
	}
	void remove(const T &item)//ɾ��MyList�е�һ����item��ȵ�Ԫ�ء�
	{	bool flag = false;
		int i;
		for (i = 0;i<last;++i)
		{	if (a[i] == item) 
			{	flag = true;
				break;
			}
		}
		if (!flag) return;
		else
		{	int x=i;
			for (i=x;i<last-1;++i) a[i] = a[i+1];
			--last;
			return;
		}
	}



	MyList &operator = (const MyList &l)//��ֵ
	{	if (this == &l) return *this;
		last = l.last;
		delete [] a;
		a = new T [last];
		for (int i=0;i<last;++i) a[i] = l.a[i];
		return *this;
	}
	
	
	MyList &operator += (const T &item)//ͬpush(T item)
	{	if (last>=size) double_space();
		a[last] = item;
		++last;
		return *this;
	}
	
	
	MyList &operator += (const MyList &l)//��һ��MyList���뵽����MyList֮��
	{	int k=last;
		last = l.last + k;
		for (int i=k;i<last;++i) 
		{	if (size <= last) double_space();
			a[i] = l.a[i-k];
		}
		return *this;
	}
	T &operator [](int index)//���ص�index��Ԫ�ء�
	{	try	{	if(index>=(-1)*last&&index<last) {return a[index];}
				else throw 1;
			}
		catch(int) {
		cout << "mistake E:out of range!" << endl;
		cout << "you have make a wrong input \"" << index << "\" here, please try again." <<endl;
		exit(-1);}
			
	}

	void sort(bool less=true)//ʵ��һ�����������鲢���򣬶�֧�ֱȽ��������>=<�������������
	{	quicksort (a,0,last);
		if (!less)
			{	int b[last];
				for (int i=0;i<last;++i)	b[i] = a[last-i];
				for (int i=0;i<last;++i)	a[i] = b[i];
			}
	}

	void reverse()
	{	T *b;
		b = new T[last];
		for (int i=0;i<last;++i)	b[i] = a[last-i];
		delete [] a;
		a = b;
	}//��MyList��Ԫ�ص�������

	~MyList(){delete [] a;}
};



int main(){
	MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i)
		a.push(i);
    // a = [0, 1, 2, 3, 4]
	a[3] = 15; // a = [0, 1, 2, 15, 4]
	a.sort(); // a = [0, 1, 2, 4, 15]
	a.reverse(); // a = [15, 4, 2, 1, 0]
	a += 12; // a = [15, 4, 2, 1, 0, 12]
	
//	cout << a[1000];

	for (i=0; i<a.get_size(); ++i)
		cout<<a[i]<<endl;
    b = a.get_item(4, -3); // b = [] *��start > end�����ؿ�����
	b = a.get_item(3, -1); // b = [1, 0, 12] 
	a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a.get_item(i)<<endl;
	cout<<a.count(5)<<endl;
	b.clean(); // b = []
	cout<<b.get_size()<<endl;
	a.erase(2, 5); // a = [15, 4, 1, 0, 12]
	
	b = a + a; // b = [15, 4, 1, 0, 12, 15, 4, 1, 0, 12]

	b.insert(3, 116); // b = [15, 4, 1, 116,  0, 12, 15, 4, 1, 0, 12]
	b.remove(4); // b = [15, 1, 116, 0 ,...]
	cout<<b<<endl;
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout<<c.get_item(100, 105)<<endl;
	
	return 0;
}

