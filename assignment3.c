#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "assignment3.h"

// initialize history
void Init_his()
{
	 Histroy.Text_size_index = 0;
	 Histroy.Type_size_index = 0;
	 Histroy.Text_size_Max = 1;
	 Histroy.Type_size_Max = 1;
	 Histroy.Tdata = (Type*)calloc(Histroy.Type_size_Max, sizeof(Type));
	 Histroy.Textdata = (TextName*)calloc(Histroy.Text_size_Max, sizeof(TextName));
}

void Create_size(struct histroy *his, int Type_size, int Text_size)
{
	 if (Text_size == 0)
	 {
		 (*his).Tdata = (Type*)realloc((*his).Tdata, sizeof(Type)*Type_size);
	 }
	 else if (Type_size == 0)
	 {
		 (*his).Textdata = (TextName*)realloc((*his).Textdata, sizeof(TextName)*Text_size);
	 }
}

void Insert_Type(Type data)
{
	 if (Histroy.Type_size_index == Histroy.Type_size_Max)
		 Create_size(&Histroy, ++Histroy.Type_size_Max, 0);
	 Histroy.Tdata[Histroy.Type_size_index++] = data;
}

void Insert_TextName(TextName data)
{
	 if (Histroy.Text_size_index == Histroy.Text_size_Max)
		 Create_size(&Histroy,0, ++Histroy.Text_size_Max);
	 Histroy.Textdata[Histroy.Text_size_index++] = data;
}

// Insert node into linked list
void InsertByTail(list *mylist,Pokemon posData)
{
	Node *newNode = CreateNode(posData); // create a node
	Node *pMove = mylist->headNode;
	if (mylist->headNode == NULL) //If List is null, add node
	{
		mylist->headNode = newNode;
		mylist->size++;
		return;
	}
	while (pMove->next != NULL) // if next node is null
	{
		pMove = pMove->next; // move pMove to the next
	}
	pMove->next = newNode;
	mylist->size++; // record the number of nodes
}

// save pokemon data
void Save_Data(list *mylist,char* str)
{
	fp = fopen(str, "w"); // create file
	char Str[2000] = " "; 
	Node *pMove = mylist->headNode;
	fprintf(fp,"#,name,Type_1,Type_2,Total,HP,Attack,Defense,Sp.Atk,Sp.Def,Speed,Generation,Legendary\n"); // save header to first line
	while (pMove) // check if pMove is null
	{
		sprintf(Str, "%d,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s\n", pMove->data.num,
			pMove->data.name, pMove->data.Type_1, pMove->data.Type_2,
			pMove->data.Total, pMove->data.HP, pMove->data.Attack, pMove->data.Defense,
			pMove->data.Sp_Atk, pMove->data.Sp_Def, pMove->data.Speed, pMove->data.Generation, pMove->data.Legendary);
		fwrite(Str, 1, sizeof(Str), fp); // write this line of data to the file
		memset(Str, 0, 2000); // initialize Str to avoid garbage values
		pMove = pMove->next;
	}
	fclose(fp);
}


int Get_Num(char* str)
{
	int len = strlen(str);
	int num = 0;
	for (int i = 0; i < len; i++)
	{
		num += str[i] - '0';
		if(len-i!=1)
		num *= 10;
	}
	return num;
}

// open pokemon file
void Open_CSV()
{
	char ch;
loop:	fp = fopen(TextName_s, "r"); // open file
	if (fp == NULL)
	{
		getchar();
		printf("Pokemon file is not found. Please enter the name of the file again.\n");
	loop1:
		printf("Please enter Y to type the name again. If you want to exit, please enter N\n");
		scanf("%c", &ch);
		if (ch == 'Y' || ch == 'y')
		{
			printf("Please enter the file name(including suffix):\n");
			scanf("%s", TextName_s);
			goto loop;
		}
		else if (ch == 'N' || ch == 'n')
		{
			exit(0);
		}
		else
		{
			printf("Error! Please enter the file name again: \n");
			goto loop1;
		}
	}

}

// read pokemon file
void Read_CSV(list *mylist,char * Type)
{
	Open_CSV();
	char *line = NULL, *record = NULL; 
	char Str[2000] = " ";
	Pokemon temp_pet = { 0 }; // initialize variables
	fseek(fp, 88L, SEEK_SET);
	while ((line = fgets(Str, sizeof(Str), fp)) != NULL) // when the end of file is not read, the loop continues
	{
		record = strtok(line, ",");
		temp_pet.num = Get_Num(record); // save the current data to the corresponding attribute member, the same operation as below
		record = strtok(NULL, ",");
		strcpy(temp_pet.name, record);
		record = strtok(NULL, ",");
		strcpy(temp_pet.Type_1, record);
		if (strcmp(temp_pet.Type_1, Type))
			continue;
		record = strtok(NULL, ",");
		if (record[1] >= '0'&&record[1] <= '9') // check the current data type
		{
			strcpy(temp_pet.Type_2, "     ");
		}
		else
		{
			strcpy(temp_pet.Type_2, record);
			record = strtok(NULL, ",");
		}
		temp_pet.Total = Get_Num(record);
		record = strtok(NULL, ",");
		temp_pet.HP = Get_Num(record);
		record = strtok(NULL, ",");
		temp_pet.Attack = Get_Num(record);
		record = strtok(NULL, ",");
		temp_pet.Defense = Get_Num(record);
		record = strtok(NULL, ",");
		temp_pet.Sp_Atk = Get_Num(record);
		record = strtok(NULL, ",");
		temp_pet.Sp_Def = Get_Num(record);
		record = strtok(NULL, ",");
		temp_pet.Speed = Get_Num(record);
		record = strtok(NULL, ",");
		temp_pet.Generation = Get_Num(record);
		record = strtok(NULL, ",");
		if (record != NULL)
		{
			int len = strlen(record);
			record[len - 1] = '\0';
		}
		strcpy(temp_pet.Legendary, record);
		memset(Str, 0, 2000);
		InsertByTail(mylist, temp_pet); // insert data into the linked list
	}
	fclose(fp);
}

// clear
void list_Clear(list* mylist)
{
	Node* pMove = NULL;
	Node* Front = NULL;
loop:pMove = mylist->headNode;
	if (pMove == NULL)
	{
		return;
	}
	if (pMove->next == NULL)
	{
		mylist->headNode = NULL;
		mylist->size--;
		free(pMove);
		return;
	}
	while (pMove->next)
	{
		Front = pMove;
		pMove = Front->next;
	}
	Front->next = NULL;
	mylist->size--;
	free(pMove);
	goto loop;
}

// print data
void Print_his()
{
	printf("Successful query: \nType Search: ");
	int n = 0;
	for (n = 0; n < Histroy.Type_size_index; n++)
	{
		if (n == Histroy.Type_size_index - 1)
		{
			printf("%s", Histroy.Tdata[n].name);
		}
		else
			printf("%s ,", Histroy.Tdata[n].name);
	}
	printf("\nSuccessful results saving: \nNew documents name:\n");
	for (n = 0; n < Histroy.Text_size_index; n++)
	{
		if (n == Histroy.Text_size_index - 1)
		{
			printf("%s", Histroy.Textdata[n].name);
		}
		else {
			printf("%s ,", Histroy.Textdata[n].name);
		}
	}
	printf("\n");
}

void Meun()
{	
	printf("*******【Pokemon Query Program】*******\n");
	printf("1-Type Search\n");
	printf("2-Save results\n");
	printf("3-Exit the query program\n");
	printf("*******【Pokemon Query Program】*******\n");
	printf("Please enter 1~3\n");
}

void Keyon(list *mylist)
{
	int keys = 0;
loop2:	scanf("%d", &keys);
	switch (keys)
	{
	case 1: // query by type and save into the memory
	{
		Type temp;
		printf("Please enter Pokemon Type:\n");
		scanf("%s", temp.name);
		Read_CSV(mylist, temp.name);
		Insert_Type(temp);
			break;
	}
	case 2:
	{
		TextName temp;
		printf("Please enter new file name:\n");
	loop3:	scanf("%s", temp.name);
		if (temp.name == NULL) // check if the file name has been entered
		{
			printf("Unable to create the new file. Please enter the name of the file again:\n");
				goto loop3;
		}
		Save_Data(mylist, temp.name); // save data into a custome file
		list_Clear(mylist);
		Insert_TextName(temp);
		break;
	}
	case 3:
		Print_his();
		exit(0);
		break;
	default:
		printf("Please enter again: \n");
		goto loop2;
		break;
	}
}

int main()
{
	list* mylist = CreateList();
	printf("Please enter the file name(including suffix):\n");
	scanf("%s", TextName_s);
	while (1)
	{
		Meun();
		Keyon(mylist);
	}
	return 0;
}
