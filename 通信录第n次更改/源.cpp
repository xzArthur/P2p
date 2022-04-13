#include <iostream>
#include <string>
#include <fstream>                                  //读写文件的头文件
using namespace std;

struct ElementType;                                 //元素类型
struct Node;                                        //节点
struct Queue;                                       //队列
typedef struct Queue* MyQueue;                      //定义新名称；myqueue

struct ElementType {                                //结构体类型包括类型
	int id;
	string name;
	int num;
};

struct Node {                                      //节点结构体 包含数据 ，定义 节点指针
	ElementType data;
	Node* next;                                     //链表节点
};

struct Queue {                                     //queue 结构体包含node头指针和尾指针。
	Node* front;
	Node* rear;
};

//声明变量
MyQueue Init(MyQueue& q);                          //初始化表列
bool IsEmpty(MyQueue q);                           //判断队列是否为空
bool Insert(ElementType x, MyQueue q);             //将数据插入到队列的末尾
bool Delete(const int message, MyQueue q);         //在队列中找到一些数据，然后删除相应的节点
void Print(const Node* q);                         //打印一个节点的信息
void PrintAll(const MyQueue q);                    //打印所有节点的信息
bool FindByName(const string massage, const MyQueue q);//查找名字
void Input(MyQueue q);                             //当地址为空时，重新在地址中输入信息 
void Write(MyQueue q);                             //将队列中的信息写入文档 
MyQueue Read();                                    //将队列中的信息写入文档
MyQueue ReadOrClear(MyQueue& q);                     //是否清空所有信息
void Swap(ElementType& x, ElementType& y);          //设置一个交换函数的结构体
MyQueue BubbleSort(MyQueue q);                     //根据工号排序
void Menu(MyQueue q);                              //主菜单

//初始化队列 
MyQueue Init(MyQueue& q) {                         //初始化队列，新建一个动态结构体q，如果，结构体是空的返回空，，
	q = new Queue();                               //不为空则将头尾指针都设为空
	if (q == NULL) return NULL;           
	q->front = NULL;
	q->rear = NULL;
	return q;
}

//查看队列是否为空 
bool IsEmpty(MyQueue q) {                           //当指针为空时，返回指针q为空
	return q->front == NULL;
}

//添加信息   使用new将动态分配内存
bool Insert(ElementType x, MyQueue q) {               //返回结构体x,和指针q
	Node* temp = new Node();                          //定义一个新的指向Node结构体指针temp
	if (temp == NULL) return false;                   //如果temp指向地址为空，返回错误（node)储存结构体信息
	temp->data = x;                                   //这里需要改成需要的内容，赋值的时候调用函数，打印的时候也调用函数
	temp->next = NULL;                                //新的节点调用结束，将temp指针中数据已经存在node中的date
	if (IsEmpty(q)) {                             														
		q->front = temp;                              //判断队列是否存满，满，则终止存储。不满则继续存储給尾节点。
		q->rear = temp;
		return true;
	}
	else {
		q->rear->next = temp;
		q->rear = temp;
		return true;
	}
}

//删除功能 
bool Delete(const int message, MyQueue q) {                        
	Node* temp = new Node(); 
	if (temp == NULL) return false;                                 //空间为空，返回错误
	bool pd = 0;
	                                                                //先是找到这个id再进行删除
 //先判断是不是头节点，若不是再把头节点当首节点进行使用
	if (q->front->data.id == message) {                            //如果是头节点
		temp = q->front;
		q->front = q->front->next;                              //将下个节点赋给头结点，并释放temp在栈内的存储空间
		delete temp;
		temp = NULL;
		pd = 1;
	}
	else if (q->rear->data.id == message) {                            //如果删除尾节点
	                                                                //先找到尾节点的前一个结点
		temp = q->front;
		while (temp->next->data.id != message) temp = temp->next;
		q->rear = temp;
		q->rear->next = NULL;
		pd = 1;
	}
	else {//如果删除中间节点
		temp = q->front;
		while (temp->next != NULL && temp->next->data.id != message) temp = temp->next;
		if (temp->next == NULL) return false;                   //判断是不是没有找到，没有找到返回false
		Node* mp = new Node();
		mp = temp->next;
		temp->next = temp->next->next;                       //将下个节点的信息赋给上一个节点
		delete mp;
		mp = NULL;
		pd = 1;
	}
	if (pd == 1) {                                              // 条件为真则直接删除联系人信息
		Write(q);
		cout << "已成功删除该联系人信息！" << endl;
		return true;
	}
}

//通过姓名进行查找 
bool FindByName(const string massage, const MyQueue q) {//此函数只有查找功能，没有打印功能，打印功能在另一个函数
	Node* temp = new Node();
	//bool pd = 0;
	if (q->front->data.name == massage) {                    //找到联系人
		temp = q->front;
		Print(temp);
		return true;
	}
	else {                                                   //通过节点指针访问数据遍历存储，
		temp = q->front;
		while (temp->next != NULL && temp->next->data.name != massage) temp = temp->next;
		if (temp->next == NULL) return false;//没有找到这个人的姓名，返回false
		Print(temp->next);
		return true;
	}
}

//单个进行打印 
void Print(const Node* q) {
	cout << "该联系人的信息为：" << endl;
	cout << "工号： " << q->data.id << " 姓名：" << q->data.name << " 电话号码：" << q->data.num << endl;
}

//打印全部的联系人信息 
void PrintAll(const MyQueue q) {
	cout << "工号";
	for (int i = 0; i < 10; i++) {
		cout << "-";
	}
	cout << "姓名";
	for (int i = 0; i < 10; i++) {
		cout << "-";
	}
	cout << "电话号码" << endl;

	Node* temp;
	temp = q->front;
	while (temp != NULL) {
		cout << " " << temp->data.id << "	      " << temp->data.name << "           " << temp->data.num << endl;
		temp = temp->next;
	}
	//cout << endl;
}

//实现互换功能函数 
void Swap(ElementType& x, ElementType& y) {
	ElementType temp;
	temp = x;
	x = y;
	y = temp;
}

MyQueue BubbleSort(MyQueue q) {                                    
	if (q->front == NULL || q->front->next == NULL) return NULL;
	for (Node* i = q->front; i->next != NULL; i = i->next) {         //排序功能的函数
		for (Node* j = q->front; j->next != NULL; j = j->next) {
			if (j->data.id > j->next->data.id) {
				Swap(j->data, j->next->data);
			}
		}
	}
	return q;
}

//把全部信息存入到文档中
void Write(MyQueue q) {
	                                                      //先根据工号进行排序，再进行存储
	q = BubbleSort(q);
	ofstream writeIt;
	writeIt.open("data.txt");                                 //打开写入文件
	if (writeIt.fail()) {                                      //失败打印
		cout << "该文件没有找到！" << endl;
		cout << "程序已退出！" << endl;
		exit(1);
	}

	Node* temp = new Node();                                    //写入文件数据
	if (q != NULL) {
		temp = q->front;
		while (temp != NULL) {
			writeIt << temp->data.id << " " << temp->data.name << " " << temp->data.num << endl;;
			temp = temp->next;
		}
	}
	writeIt.close();
}

//从文档中读出所有的信息
MyQueue Read() {                  
	ifstream readIt("data.txt");
	if (readIt.fail()) {                          //失败则打印以下内容
		cout << "该文件没有找到！" << endl;
		cout << "程序已退出！" << endl;
		exit(1);
	}
	int id1;
	string name1;
	int num1;
	MyQueue q = new Queue();
	ElementType x;
	while (!readIt.eof()) {                       //读取数据直到文件尾
		readIt >> id1 >> name1 >> num1;
		if (readIt.eof()) break;
		x.id = id1;
		x.name = name1;
		x.num = num1;
		Insert(x, q);                             //添加联系人信息
	}
	readIt.close();
	return q;
}

//读入文档中的信息
MyQueue ReadOrClear(MyQueue& q) {
	q = Read();
	return q;
}

//使整个队列置空
void MakeEmpty(MyQueue& q) {
	while (q->front != NULL) {
		Node* temp = new Node();
		temp = q->front;
		q->front = q->front->next;
		delete temp;                  //使用delete释放文件信息
	}
}

//主菜单
void Menu(MyQueue q) {
	q = ReadOrClear(q);
	while (1) {
		cout << endl;
		cout << "|--------------------联系人通讯录系统---------------------|" << endl;
		cout << "|--------------------1 添加联系人信息---------------------|" << endl;
		cout << "|--------------------2 删除联系人信息---------------------|" << endl;
		cout << "|--------------------3 显示联系人信息---------------------|" << endl;
		cout << "|--------------------4 查询联系人信息---------------------|" << endl;
		cout << "|--------------------5 联系人信息排序---------------------|" << endl;
		cout << "|--------------------6 清空屏幕信息---------------------|" << endl;
		cout << "|--------------------7 清空文档信息---------------------|" << endl;
		cout << "|--------------------8 退出管理系统---------------------|" << endl;
		cout << "|-------------------------------------------------------|" << endl;
		int n;
		cout << "输入您的选择：" << endl;
		cin >> n;
		switch (n) {
		case 1: {
			ElementType x;
			cout << "请输入该联系人的信息：工号 姓名 电话号码" << endl;
			cin >> x.id >> x.name >> x.num;
			Insert(x, q);                                        //添加信息
			Write(q);                                              
			cout << "已成功添加该联系人信息!" << endl; 
			break;
		}
		case 2: {
			cout << "请输入该联系人的工号：" << endl;
			int num1;
			cin >> num1;
			if (!Delete(num1, q)) {
				cout << "该系统中不存在该联系人！" << endl;
			};
			break;
		}
		case 3: {
			cout << "正在打印全部联系人信息中.......请稍等!" << endl;
			cout << "全部联系人的信息为：" << endl;
			PrintAll(q);
			break;
		}
		case 4: {
			cout << "请输入联系人的姓名：" << endl;
			string name1;
			cin >> name1;
			if (!FindByName(name1, q)) {
				cout << "该系统中不存在该联系人！" << endl;
			}
			break;
		}
		case 5: {
			cout << "正在根据联系人的工号对学生进行排序....." << endl;
			cout << "排完序后，结果为：" << endl;
			BubbleSort(q);
			PrintAll(q);
			break;
		}
		case 6: {
			system("cls");
			break;
		}
		case 7: {
			cout << "请您在三确认是否要清空文档中的全部联系人信息！清空请输入“yes”,不清空请输入“no”。" << endl;
			string s;
			cin >> s;
			if (s == "yes") {
				//先把队列中的全部节点都delete掉，再进行写入文档中
				MakeEmpty(q);
				q = Init(q);
				Write(q);
				cout << "已经成功清空文档中的全部联系人信息！" << endl;
			}
			break;
		}
		case 8: {
			cout << "退出成功！" << endl;
			exit(0);
		}
		default:
			cout << "输入的选项序号有误，请重新输入!" << endl;
		}
	}
}

int main() {
	MyQueue q;                                       //链表的头指针和尾指针
	q = Init(q);                                     //初始化队列
	Menu(q);                                         //主菜单
	return 0;
}
