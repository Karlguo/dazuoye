/*
 * 实现一个list类命名为MyList，其功能与python数组类似。可以用数组实现，也可以用链表实现。
 * 必须使用template <class T>，不允许使用<iostream>以外的库。
 * 需要实现的功能与测试代码见下。请务必搞清楚每一项的意义，比如什么时候需要用友元函数什么时候需要const什么时候需要&。
 * 当某些由用户正常操作可能产生的run time error（如pop一个空数组，或访问一个超出下标的元素），
 * 请使用try-catch-throw处理错误。
 * 以下类定义不保证完全正确，请根据实际需求修改，以实现样例功能为主。
 */

/* 
 * 本练习不涉及到虚类和类继承，但是期末考试我就不知道了。如果有时间可以用书上的shape类来练习。
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
	friend MyList<T> operator + <>(const MyList<T> &, const MyList<T> &);//合并两个MyList
    friend MyList<T> operator + <>(const MyList<T> &, const T &); //同push(T item)，但不修改l1，返回一个新数组
    friend ostream &operator<< <>(ostream &, const MyList<T> &);//如果T是可以直接cout的类的话（比如int），按Python数组的格式输出MyList中的每一个元素，例如：
    // [1, 2, 5, 4, 1]
    
private:
	int last;
	T *a;
	int size;

	void double_space()//数组大小不够的时候将数组大小翻倍的操作。
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
	MyList(int num, const T &item)//将item重复num次填入数组中。
	{	a = new T [num+1];
		size = num;
		last = num;
		for (int i=0;i<num;++i)a[i] = item;
	}
	MyList(const MyList &l)//深复制另外一个MyList。
	{	a = new T [l.last+1];
		size = l.last;
		last = l.last;
		for (int i=0;i<l.last;++i)	a[i] = l.a[i];
	}
    MyList(T *arr, int len)//以arr的前len个元素构造数组
    {	a = new T [len+1];
    	size = len;
    	last = len;
		for (int i=0;i<len;++i)	a[i] = arr[i];
	}

	void push(const T &item)//将item添加在MyList最后。
	{	if (last>=size) double_space();
		a[last] = item;
		++last;
	}
	T pop()//将MyList中最后一个元素删除，并返回这个删除的元素。
	{	int k=a[last];
		a[last] = NULL;
		--last;
		return k; 
	}
	
	void insert(int index, const T &item)//将item插入到place处。
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
	void clean()//清空数组。
	{	delete [] a;
		last = 0;
		a = new T[0];
	}
	
	int get_size()//返回MyList中元素的数量。
	{	return last;
			
	}
	
	void erase(int start, int end) //删除MyList中第start到第end位的元素，包括两边。
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
	
	T get_item(int index)//返回第index个元素。
	{	try	{	if(index>=(-1)*last&&index<last) {return a[index];}
				else throw 1;
			}
		catch(int) {cout << "mistake C:out of range!" << endl;
			cout << "you have make a wrong input \"" << index << "\" here, please try again." <<endl;
			exit(-1);}
			
	}
	
	MyList get_item(int start, int end)//返回MyList中第start到第end位的元素，包括两边。此处需要像python一样接受负数，具体见测试代码。
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
	int count(const T &item)//返回MyList中和item相等的元素的个数。
	{	int count;
		for (int i=0;i<last;++i)
		{	if (a[i] == item) ++count;
		}
		return count;
	}
	void remove(const T &item)//删除MyList中第一个和item相等的元素。
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



	MyList &operator = (const MyList &l)//赋值
	{	if (this == &l) return *this;
		last = l.last;
		delete [] a;
		a = new T [last];
		for (int i=0;i<last;++i) a[i] = l.a[i];
		return *this;
	}
	
	
	MyList &operator += (const T &item)//同push(T item)
	{	if (last>=size) double_space();
		a[last] = item;
		++last;
		return *this;
	}
	
	
	MyList &operator += (const MyList &l)//将一个MyList加入到本个MyList之后。
	{	int k=last;
		last = l.last + k;
		for (int i=k;i<last;++i) 
		{	if (size <= last) double_space();
			a[i] = l.a[i-k];
		}
		return *this;
	}
	T &operator [](int index)//返回第index个元素。
	{	try	{	if(index>=(-1)*last&&index<last) {return a[index];}
				else throw 1;
			}
		catch(int) {
		cout << "mistake E:out of range!" << endl;
		cout << "you have make a wrong input \"" << index << "\" here, please try again." <<endl;
		exit(-1);}
			
	}

	void sort(bool less=true)//实现一个快速排序或归并排序，对支持比较运算符（>=<）的类进行排序。
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
	}//将MyList的元素倒过来。

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
    b = a.get_item(4, -3); // b = [] *若start > end，返回空数组
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

