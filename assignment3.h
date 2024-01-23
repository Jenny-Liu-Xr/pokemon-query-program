
// FILE studentList.h

#ifndef HEADER_ASSIGNMENT3
#define HEADER_ASSIGNMENT3

/************************************************/
// structures

FILE *fp = NULL;

char TextName_s[50] = "";

// structure Type
typedef struct
{
	char name[50];
}Type;

// structure new file name
typedef struct
{
	char name[50];
}TextName;

// structure history of searching type and new file
struct histroy
{
	Type *Tdata;
	TextName* Textdata;
	int Type_size_Max;
	int Text_size_Max;
	int Type_size_index;
	int Text_size_index;
}Histroy;

void Init_his();
void Create_size(struct histroy *his, int Type_size, int Text_size);
void Insert_Type(Type data);
void Insert_TextName(TextName data);

// structure pokemon data
typedef struct
{
	int num;
	char name[50];
	char Type_1[20];
	char Type_2[20];
	int Total;
	int HP;
	int Attack;
	int Defense;
	int Sp_Atk;
	int Sp_Def;
	int Speed;
	int Generation;
	char Legendary[10];
}Pokemon;

// structure Node
typedef struct node
{
	Pokemon data;
	struct node *next;
}Node;

// structure List
typedef struct List
{
	Node *headNode;
	int size; // record the number of nodes
}list;

// Allocates memory for a new list and initializes it 
list * CreateList()
{
	list* mylist = (list*)malloc(sizeof(list));
	mylist->headNode = NULL; // pointer initialization
	mylist->size = 0; // parameter initialization
	return mylist;
}

// Allocates memory for a new list Node
Node *CreateNode(Pokemon posData)
{
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->data = posData; // store data in the node field
	newNode->next = NULL;
	return newNode;
}

void InsertByTail(list *mylist,Pokemon posData);

void Save_Data(list *mylist,char* str);

int Get_Num(char* str);

void Open_CSV();

void Read_CSV(list *mylist,char * Type);

void list_Clear(list* mylist);

void Print_his();

void Meun();
void Keyon(list *mylist);

#endif
