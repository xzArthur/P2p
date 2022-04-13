#include <iostream>
#include <string>
#include <fstream>                                  //��д�ļ���ͷ�ļ�
using namespace std;

struct ElementType;                                 //Ԫ������
struct Node;                                        //�ڵ�
struct Queue;                                       //����
typedef struct Queue* MyQueue;                      //���������ƣ�myqueue

struct ElementType {                                //�ṹ�����Ͱ�������
	int id;
	string name;
	int num;
};

struct Node {                                      //�ڵ�ṹ�� �������� ������ �ڵ�ָ��
	ElementType data;
	Node* next;                                     //����ڵ�
};

struct Queue {                                     //queue �ṹ�����nodeͷָ���βָ�롣
	Node* front;
	Node* rear;
};

//��������
MyQueue Init(MyQueue& q);                          //��ʼ������
bool IsEmpty(MyQueue q);                           //�ж϶����Ƿ�Ϊ��
bool Insert(ElementType x, MyQueue q);             //�����ݲ��뵽���е�ĩβ
bool Delete(const int message, MyQueue q);         //�ڶ������ҵ�һЩ���ݣ�Ȼ��ɾ����Ӧ�Ľڵ�
void Print(const Node* q);                         //��ӡһ���ڵ����Ϣ
void PrintAll(const MyQueue q);                    //��ӡ���нڵ����Ϣ
bool FindByName(const string massage, const MyQueue q);//��������
void Input(MyQueue q);                             //����ַΪ��ʱ�������ڵ�ַ��������Ϣ 
void Write(MyQueue q);                             //�������е���Ϣд���ĵ� 
MyQueue Read();                                    //�������е���Ϣд���ĵ�
MyQueue ReadOrClear(MyQueue& q);                     //�Ƿ����������Ϣ
void Swap(ElementType& x, ElementType& y);          //����һ�����������Ľṹ��
MyQueue BubbleSort(MyQueue q);                     //���ݹ�������
void Menu(MyQueue q);                              //���˵�

//��ʼ������ 
MyQueue Init(MyQueue& q) {                         //��ʼ�����У��½�һ����̬�ṹ��q��������ṹ���ǿյķ��ؿգ���
	q = new Queue();                               //��Ϊ����ͷβָ�붼��Ϊ��
	if (q == NULL) return NULL;           
	q->front = NULL;
	q->rear = NULL;
	return q;
}

//�鿴�����Ƿ�Ϊ�� 
bool IsEmpty(MyQueue q) {                           //��ָ��Ϊ��ʱ������ָ��qΪ��
	return q->front == NULL;
}

//�����Ϣ   ʹ��new����̬�����ڴ�
bool Insert(ElementType x, MyQueue q) {               //���ؽṹ��x,��ָ��q
	Node* temp = new Node();                          //����һ���µ�ָ��Node�ṹ��ָ��temp
	if (temp == NULL) return false;                   //���tempָ���ַΪ�գ����ش���node)����ṹ����Ϣ
	temp->data = x;                                   //������Ҫ�ĳ���Ҫ�����ݣ���ֵ��ʱ����ú�������ӡ��ʱ��Ҳ���ú���
	temp->next = NULL;                                //�µĽڵ���ý�������tempָ���������Ѿ�����node�е�date
	if (IsEmpty(q)) {                             														
		q->front = temp;                              //�ж϶����Ƿ��������������ֹ�洢������������洢�oβ�ڵ㡣
		q->rear = temp;
		return true;
	}
	else {
		q->rear->next = temp;
		q->rear = temp;
		return true;
	}
}

//ɾ������ 
bool Delete(const int message, MyQueue q) {                        
	Node* temp = new Node(); 
	if (temp == NULL) return false;                                 //�ռ�Ϊ�գ����ش���
	bool pd = 0;
	                                                                //�����ҵ����id�ٽ���ɾ��
 //���ж��ǲ���ͷ�ڵ㣬�������ٰ�ͷ�ڵ㵱�׽ڵ����ʹ��
	if (q->front->data.id == message) {                            //�����ͷ�ڵ�
		temp = q->front;
		q->front = q->front->next;                              //���¸��ڵ㸳��ͷ��㣬���ͷ�temp��ջ�ڵĴ洢�ռ�
		delete temp;
		temp = NULL;
		pd = 1;
	}
	else if (q->rear->data.id == message) {                            //���ɾ��β�ڵ�
	                                                                //���ҵ�β�ڵ��ǰһ�����
		temp = q->front;
		while (temp->next->data.id != message) temp = temp->next;
		q->rear = temp;
		q->rear->next = NULL;
		pd = 1;
	}
	else {//���ɾ���м�ڵ�
		temp = q->front;
		while (temp->next != NULL && temp->next->data.id != message) temp = temp->next;
		if (temp->next == NULL) return false;                   //�ж��ǲ���û���ҵ���û���ҵ�����false
		Node* mp = new Node();
		mp = temp->next;
		temp->next = temp->next->next;                       //���¸��ڵ����Ϣ������һ���ڵ�
		delete mp;
		mp = NULL;
		pd = 1;
	}
	if (pd == 1) {                                              // ����Ϊ����ֱ��ɾ����ϵ����Ϣ
		Write(q);
		cout << "�ѳɹ�ɾ������ϵ����Ϣ��" << endl;
		return true;
	}
}

//ͨ���������в��� 
bool FindByName(const string massage, const MyQueue q) {//�˺���ֻ�в��ҹ��ܣ�û�д�ӡ���ܣ���ӡ��������һ������
	Node* temp = new Node();
	//bool pd = 0;
	if (q->front->data.name == massage) {                    //�ҵ���ϵ��
		temp = q->front;
		Print(temp);
		return true;
	}
	else {                                                   //ͨ���ڵ�ָ��������ݱ����洢��
		temp = q->front;
		while (temp->next != NULL && temp->next->data.name != massage) temp = temp->next;
		if (temp->next == NULL) return false;//û���ҵ�����˵�����������false
		Print(temp->next);
		return true;
	}
}

//�������д�ӡ 
void Print(const Node* q) {
	cout << "����ϵ�˵���ϢΪ��" << endl;
	cout << "���ţ� " << q->data.id << " ������" << q->data.name << " �绰���룺" << q->data.num << endl;
}

//��ӡȫ������ϵ����Ϣ 
void PrintAll(const MyQueue q) {
	cout << "����";
	for (int i = 0; i < 10; i++) {
		cout << "-";
	}
	cout << "����";
	for (int i = 0; i < 10; i++) {
		cout << "-";
	}
	cout << "�绰����" << endl;

	Node* temp;
	temp = q->front;
	while (temp != NULL) {
		cout << " " << temp->data.id << "	      " << temp->data.name << "           " << temp->data.num << endl;
		temp = temp->next;
	}
	//cout << endl;
}

//ʵ�ֻ������ܺ��� 
void Swap(ElementType& x, ElementType& y) {
	ElementType temp;
	temp = x;
	x = y;
	y = temp;
}

MyQueue BubbleSort(MyQueue q) {                                    
	if (q->front == NULL || q->front->next == NULL) return NULL;
	for (Node* i = q->front; i->next != NULL; i = i->next) {         //�����ܵĺ���
		for (Node* j = q->front; j->next != NULL; j = j->next) {
			if (j->data.id > j->next->data.id) {
				Swap(j->data, j->next->data);
			}
		}
	}
	return q;
}

//��ȫ����Ϣ���뵽�ĵ���
void Write(MyQueue q) {
	                                                      //�ȸ��ݹ��Ž��������ٽ��д洢
	q = BubbleSort(q);
	ofstream writeIt;
	writeIt.open("data.txt");                                 //��д���ļ�
	if (writeIt.fail()) {                                      //ʧ�ܴ�ӡ
		cout << "���ļ�û���ҵ���" << endl;
		cout << "�������˳���" << endl;
		exit(1);
	}

	Node* temp = new Node();                                    //д���ļ�����
	if (q != NULL) {
		temp = q->front;
		while (temp != NULL) {
			writeIt << temp->data.id << " " << temp->data.name << " " << temp->data.num << endl;;
			temp = temp->next;
		}
	}
	writeIt.close();
}

//���ĵ��ж������е���Ϣ
MyQueue Read() {                  
	ifstream readIt("data.txt");
	if (readIt.fail()) {                          //ʧ�����ӡ��������
		cout << "���ļ�û���ҵ���" << endl;
		cout << "�������˳���" << endl;
		exit(1);
	}
	int id1;
	string name1;
	int num1;
	MyQueue q = new Queue();
	ElementType x;
	while (!readIt.eof()) {                       //��ȡ����ֱ���ļ�β
		readIt >> id1 >> name1 >> num1;
		if (readIt.eof()) break;
		x.id = id1;
		x.name = name1;
		x.num = num1;
		Insert(x, q);                             //�����ϵ����Ϣ
	}
	readIt.close();
	return q;
}

//�����ĵ��е���Ϣ
MyQueue ReadOrClear(MyQueue& q) {
	q = Read();
	return q;
}

//ʹ���������ÿ�
void MakeEmpty(MyQueue& q) {
	while (q->front != NULL) {
		Node* temp = new Node();
		temp = q->front;
		q->front = q->front->next;
		delete temp;                  //ʹ��delete�ͷ��ļ���Ϣ
	}
}

//���˵�
void Menu(MyQueue q) {
	q = ReadOrClear(q);
	while (1) {
		cout << endl;
		cout << "|--------------------��ϵ��ͨѶ¼ϵͳ---------------------|" << endl;
		cout << "|--------------------1 �����ϵ����Ϣ---------------------|" << endl;
		cout << "|--------------------2 ɾ����ϵ����Ϣ---------------------|" << endl;
		cout << "|--------------------3 ��ʾ��ϵ����Ϣ---------------------|" << endl;
		cout << "|--------------------4 ��ѯ��ϵ����Ϣ---------------------|" << endl;
		cout << "|--------------------5 ��ϵ����Ϣ����---------------------|" << endl;
		cout << "|--------------------6 �����Ļ��Ϣ---------------------|" << endl;
		cout << "|--------------------7 ����ĵ���Ϣ---------------------|" << endl;
		cout << "|--------------------8 �˳�����ϵͳ---------------------|" << endl;
		cout << "|-------------------------------------------------------|" << endl;
		int n;
		cout << "��������ѡ��" << endl;
		cin >> n;
		switch (n) {
		case 1: {
			ElementType x;
			cout << "���������ϵ�˵���Ϣ������ ���� �绰����" << endl;
			cin >> x.id >> x.name >> x.num;
			Insert(x, q);                                        //�����Ϣ
			Write(q);                                              
			cout << "�ѳɹ���Ӹ���ϵ����Ϣ!" << endl; 
			break;
		}
		case 2: {
			cout << "���������ϵ�˵Ĺ��ţ�" << endl;
			int num1;
			cin >> num1;
			if (!Delete(num1, q)) {
				cout << "��ϵͳ�в����ڸ���ϵ�ˣ�" << endl;
			};
			break;
		}
		case 3: {
			cout << "���ڴ�ӡȫ����ϵ����Ϣ��.......���Ե�!" << endl;
			cout << "ȫ����ϵ�˵���ϢΪ��" << endl;
			PrintAll(q);
			break;
		}
		case 4: {
			cout << "��������ϵ�˵�������" << endl;
			string name1;
			cin >> name1;
			if (!FindByName(name1, q)) {
				cout << "��ϵͳ�в����ڸ���ϵ�ˣ�" << endl;
			}
			break;
		}
		case 5: {
			cout << "���ڸ�����ϵ�˵Ĺ��Ŷ�ѧ����������....." << endl;
			cout << "������󣬽��Ϊ��" << endl;
			BubbleSort(q);
			PrintAll(q);
			break;
		}
		case 6: {
			system("cls");
			break;
		}
		case 7: {
			cout << "��������ȷ���Ƿ�Ҫ����ĵ��е�ȫ����ϵ����Ϣ����������롰yes��,����������롰no����" << endl;
			string s;
			cin >> s;
			if (s == "yes") {
				//�ȰѶ����е�ȫ���ڵ㶼delete�����ٽ���д���ĵ���
				MakeEmpty(q);
				q = Init(q);
				Write(q);
				cout << "�Ѿ��ɹ�����ĵ��е�ȫ����ϵ����Ϣ��" << endl;
			}
			break;
		}
		case 8: {
			cout << "�˳��ɹ���" << endl;
			exit(0);
		}
		default:
			cout << "�����ѡ�������������������!" << endl;
		}
	}
}

int main() {
	MyQueue q;                                       //�����ͷָ���βָ��
	q = Init(q);                                     //��ʼ������
	Menu(q);                                         //���˵�
	return 0;
}
