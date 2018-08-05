#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"Adjust.h"

typedef struct {
	int ID;
	char Name[30];
	int Act_Point;
	int Gr_ID;
}Member;

void Menu();
void WriteFile(Member **ListMember, int Number_of_record);
Member **ReadFile(int *Number_of_record);
void Sort_Name(Member *fullname1, Member *fullname2);
void Add_Member(Member ***ListMember, int add, int *Number_of_record);
void Edit_Member_Info(Member ***ListMember, int Number_of_record);
void Del_Member(Member ***ListMember, int *Number_of_record);
void Show_All_Member(Member **ListMember, int Number_of_record);
void Find_Member(Member **ListMember, int Number_of_record);

int main(){
    int Number_of_record = 0;
    Member **ListMember;
    ListMember = ReadFile(&Number_of_record);
	int i , j;
	int choice , add ;
	do{
		Menu();
		printf("Moi nhap vao lua chon: ");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				printf("Moi nhap vao so luong thanh vien can them : ");
				scanf("%d", &add);
				if(Number_of_record == 0){
					ListMember = (Member** ) malloc(sizeof(Member* ) * add);
					for (j = 0; j < add; j++){
						ListMember[j]=(Member* ) malloc(sizeof(Member));
					}
				}
				else{
					ListMember = (Member **) realloc(ListMember, (Number_of_record + add));
					for (j = Number_of_record; j < Number_of_record + add; j++){
						ListMember[j]=(Member* ) malloc(sizeof(Member));
					}
				}
				Add_Member(&ListMember, add, &Number_of_record);
				break;
			case 2:
				Edit_Member_Info(&ListMember, Number_of_record);
				break;
			case 3:
				Del_Member(&ListMember, &Number_of_record);
				break;
			case 4:
				Show_All_Member(ListMember, Number_of_record);
				break;
			case 5:
				Find_Member(ListMember, Number_of_record);
				break;
			case 6:
				printf("Ban da chon che do thoat khoi chuong trinh\n");break;
			default:
				system("cls");
				printf("Moi ban nhap lai lua chon! \n");
		}
	}while (choice!=6);
	return 0;
}

void Menu(){
	printf("Chuong trinh Quan ly thanh vien doi SVTN vien CNTT & Truyen Thong\n");
		printf("Menu\n");
		printf("1. Them thanh vien\n");
		printf("2. Sua thong tin thanh vien\n");
		printf("3. Xoa thanh vien\n");
		printf("4. In thong tin tat ca cac thanh vien\n");
		printf("5. Tim kiem thong tin thanh vien\n");
		printf("6. Thoat khoi chuong trinh\n");
}
void WriteFile(Member **ListMember, int Number_of_record){
    FILE *fptr;
    fptr = fopen("vidu.txt", "w+");
    for(int i = 0; i < Number_of_record; i++){
        fprintf(fptr, ListMember[i]->Name);
        fprintf(fptr, "\n");
        fprintf(fptr, "%d", ListMember[i]->ID);
        fprintf(fptr, " ");
        fprintf(fptr, "%d", ListMember[i]->Gr_ID);
        fprintf(fptr, " ");
        fprintf(fptr, "%d", ListMember[i]->Act_Point);
        fprintf(fptr, "\n");
    }
    fclose(fptr);
}
Member **ReadFile(int *Number_of_record){
    FILE *fptr;
    char c;//read a char from file when need
    int Num_temp = 0;
    Member **ListMember;
    fptr = fopen("vidu.txt","r");
    while((c = fgetc(fptr)) != EOF){
        if(c == '\n') Num_temp++;
    }
    if(Num_temp>0){
		Num_temp = (Num_temp - 1) / 2 + 1;
    	ListMember = (Member **) malloc(sizeof(Member *) * Num_temp);
    	for(int i = 0; i < Num_temp; i++){
    		*(ListMember + i) = (Member*) malloc(sizeof(Member));
		}
    	rewind(fptr);
    	//read record to ListMember
    	int Asd_var = 0;
    	while(Asd_var < Num_temp){
        	fgets(ListMember[Asd_var]->Name, 30, (FILE *)fptr);
        	Adjust(ListMember[Asd_var]->Name);
        	fscanf(fptr, "%d", &ListMember[Asd_var]->ID);
        	fscanf(fptr, "%d", &ListMember[Asd_var]->Gr_ID);
        	fscanf(fptr, "%d", &ListMember[Asd_var]->Act_Point);
        	c = fgetc(fptr);//ignore '\n' after Act_point
			Asd_var++;
    	}
    	fclose(fptr);
    	(*Number_of_record) = Num_temp;
    	return ListMember;
    }
    else return ListMember;
}
void Sort_Name(Member *fullname1, Member *fullname2){
	char name1[30], name2[30];
	int i, j, k = 0, flag = 0;
	for(i = 0; i < strlen(fullname1->Name); i++){
		if(fullname1->Name[i] == ' ') {
			flag = 1;
			break;
		}
	}
	if(flag == 0)
		strcpy(name1, fullname1->Name);
	else{
		for(i = strlen(fullname1->Name)-1; i > 0; i--){
			if(fullname1->Name[i] == ' ') {
				j = i+1;
				break;
			}
		}
		for(i = j; i < strlen(fullname1->Name); i++){
			name1[k] = fullname1->Name[i];
			k++;
		}
		name1[k] = '\0';
	}

	k = 0; flag = 0;
	for(i = 0; i < strlen(fullname2->Name); i++){
		if(fullname2->Name[i]==' ') {
			flag=1;
			break;
		}
	}
	if(flag == 0)
		strcpy(name2,fullname2->Name);
	else{
		for(i = strlen(fullname2->Name)-1; i>=0; i--){
			if(fullname2->Name[i]==' ') {
				j=i+1;
				break;
			}
		}
		for(i = j; i < strlen(fullname2->Name); i++){
			name2[k] = fullname2->Name[i];
			k++;
		}
		name2[k] = '\0';
	}
		if(strcmp(name1, name2) < 0) {
				Member mem;
				mem = *fullname1;
				*fullname1 = *fullname2;
				*fullname2 = mem;
			}
		else if(strcmp(name1, name2)==0){
			if(strcmp(fullname1->Name, fullname2->Name)){
				Member mem;
				mem = *fullname1;
				*fullname1 = *fullname2;
				*fullname2 = mem;
			}
		}
}
void Add_Member(Member ***ListMember, int add, int *Number_of_record){ //pointer error
	system("cls");
	int  i , j , flag = 1 , id ;
	do{
		for(i = *Number_of_record; i < add + *Number_of_record; i++){
			printf("Nhap vao ID: ");
			scanf("%d", &id);
			if(id <= 0) {
				printf("Moi nhap lai ID!\n");
				i--;
			}
			else{
				for(j = 0; j < i; j++){
					if(id == (*ListMember)[j]->ID) {flag = 0; break;}
					else flag=1;
				}
				if(flag==0) {
					printf("ID bi trung. Moi nhap lai!\n");
					i--;
				}
				else{
					(*ListMember)[i]->ID=id;
					printf("Nhap vao ten thanh vien: ");
					fflush(stdin);
					gets((*ListMember)[i]->Name);
					Adjust((*ListMember)[i]->Name);
					printf("Nhap vao diem hoat dong: ");
					scanf("%d", &(*ListMember)[i]->Act_Point);
					printf("Nhap vao Group ID: ");
					scanf("%d", &(*ListMember)[i]->Gr_ID);
					fflush(stdin);
				}
			}
		}
	}while ((flag!=1))	;
	(*Number_of_record)+=add;
	for(i = 0; i < *Number_of_record; i++){
		for(j=0; j<i; j++){
			Sort_Name((*ListMember)[i], (*ListMember)[j]);
		}
	}
	WriteFile(*ListMember , *Number_of_record);
}
void Edit_Member_Info(Member ***ListMember, int Number_of_record){//kiem tra dieu kien ID
	system("cls");
	int id, flag=0,i,j;
	int ch;
	if(Number_of_record==0) printf("Danh sach trong!\n");
	else{
		do{
			printf("Nhap vao ID cua thanh vien can sua thong tin: ");
			scanf("%d", &id);
			for(i=0; i<Number_of_record; i++){
				if(id == (*ListMember)[i]->ID) {flag=1; break;}
				else flag=0;
			}
			if(flag==0) printf("Khong tim thay ID\n");
			else{
				printf("1. Chinh sua ID\n");
				printf("2. Chinh sua ten thanh vien\n");
				printf("3. Chinh sua diem\n");
				printf("4. Chinh sua group ID\n");
				printf("Moi nhap vao lua chon: ");
				scanf("%d", &ch);
				switch(ch){
					case 1:
						do{
							printf("Nhap vao ID: ");
							scanf("%d", &id);
								for(j=0; j<Number_of_record; j++){
									if(id==(*ListMember)[j]->ID) {flag=0; break;}
									else flag =1;
								}
								if(flag==0) printf("Moi nhap lai!\n");
								else if(id<=0) break;
								else (*ListMember)[i]->ID = id;
						}while (flag!=1);
						break;
					case 2:
						printf("Nhap lai ten thanh vien: ");
						fflush(stdin);
						gets((*ListMember)[i]->Name);
						Adjust((*ListMember)[i]->Name);
						//sap xep lai theo ten
						for(i=0; i<Number_of_record; i++){
							for(j=0; j<i; j++){
								Sort_Name((*ListMember)[i], (*ListMember)[j]);
							}
						}
						break;
					case 3: 
						printf("Nhap lai diem: ");
						scanf("%d", &(*ListMember)[i]->Act_Point);
						break;
					case 4: 
						printf("Nhap lai group ID: ");
						scanf("%d", &(*ListMember)[i]->Gr_ID);
						break;
					default:
						break;
					break;
				}
			}
		} while(flag!=1);
		WriteFile(*ListMember, Number_of_record);
	}
}
void Del_Member(Member ***ListMember, int *Number_of_record){
	//system("cls");
	int id, flag=0,i,j;
	if(*Number_of_record==0)	printf("Danh sach trong\n");
	else{
		printf("Nhap vao ID thanh vien muon xoa: ");
		scanf("%d", &id);
		for( i=0 ; i< *Number_of_record ; i++){
			if(id==(*ListMember)[i]->ID) {flag=1; break;}
			else flag=0;
		}
		if(flag==0) printf("Khong tim thay ID\n");
		else{
			for( j=i ; j< *Number_of_record - 1 ; j++){
				(*ListMember)[j]->Act_Point=(*ListMember)[j+1]->Act_Point;
				(*ListMember)[j]->Gr_ID=(*ListMember)[j+1]->Gr_ID;
				strcpy((*ListMember)[j]->Name, (*ListMember)[j+1]->Name);
				(*ListMember)[j]->ID=(*ListMember)[j+1]->ID;
			}
			//I edited here
			Member *LastMember = (*ListMember)[*Number_of_record - 1];
			free(LastMember);
			(*Number_of_record)--;
			(*ListMember) = (Member **) realloc(*ListMember, *Number_of_record );
			printf("Da xoa thong tin thanh vien!\n");
			WriteFile(*ListMember, *Number_of_record);
			//=============
		}
	}
}
void Show_All_Member(Member **ListMember, int Number_of_record){
	system("cls");
	if(Number_of_record==0) printf("Danh sach trong\n");
	else{
		int i;
  		printf("%-5s\t%-35s\t%-12s\t%-7s\n","ID", "Ho ten", "Group_ID", "Diem");
  		for (i=0; i<Number_of_record; i++)
    	printf("%-5d\t%-35s\t%-12d\t%-7d\n",
		 	ListMember[i]->ID, ListMember[i]->Name, ListMember[i]->Gr_ID, ListMember[i]->Act_Point);
	}
}
void Find_Member(Member **ListMember, int Number_of_record){
	system("cls");
	int count=0;
	if(Number_of_record==0) printf("Danh sach trong\n");
	else{
	int id, flag=0,i, ch, group;
	char name[30];
	printf("1. Tim kiem theo ID\n");
	printf("2. Tim kiem theo Group_ID\n");
	printf("3. Tim kiem theo ten\n");
	printf("Moi nhap vao lua chon: ");
	scanf("%d", &ch);
	switch(ch){
		case 1:
			do{
				printf("Nhap vao ID cua thanh vien can tim: ");
				scanf("%d", &id);
				for(i=0; i<Number_of_record; i++){
					if(id==ListMember[i]->ID) {flag=1; break;}
					else flag=0;
				}
				if(flag==0) printf("Khong tim thay ID\n");
				else{
					printf("Thong tin thanh vien co ID %d:\n", id);
					printf("Ho va ten: %s\n", ListMember[i]->Name);
					printf("Nhom hoat dong: %d\n", ListMember[i]->Gr_ID);
					printf("Diem hoat dong: %d\n", ListMember[i]->Act_Point);
				}
			} while(flag!=1);
			break;
		case 2:
			do{
				printf("Nhap vao Group-Id: ");
				scanf("%d", &group);
				for(i=0; i<Number_of_record; i++){
				if(group==ListMember[i]->Gr_ID) {flag=1; break;}
				else flag=0;
				}
				if(flag==0) printf("Moi nhap lai Group_ID\n");
				else{
					printf("Danh sach cac thanh vien nhom %d\n", group);
					printf("%-5s\t%-35s\t%-12s\t%-7s\n","ID", "Ho ten", "Group_ID", "Diem");
					for(i=0; i<Number_of_record; i++){
						if(group==ListMember[i]->Gr_ID)
   						printf("%-5d\t%-35s\t%-12d\t%-7d\n",
						ListMember[i]->ID, ListMember[i]->Name, ListMember[i]->Gr_ID, ListMember[i]->Act_Point);
					}
				}
			}while (flag!=1);
			break;
		case 3:
			printf("Nhap vao ten: ");
			fflush(stdin);
			gets(name);
			Adjust(name);
			printf("Ket qua tim kiem: \n");
			for(i=0; i<Number_of_record; i++)
				if (strstr(ListMember[i]->Name, name)) count++;
			printf("Tim thay %d ket qua: \n", count);
			if(count!=0){
				printf("%-5s\t%-35s\t%-12s\t%-7s\n","ID", "Ho ten", "Group_ID", "Diem");
				for(i=0; i<Number_of_record; i++){
					if (strstr(ListMember[i]->Name, name))
   					printf("%-5d\t%-35s\t%-12d\t%-7d\n",
					ListMember[i]->ID, ListMember[i]->Name, ListMember[i]->Gr_ID, ListMember[i]->Act_Point);
				}
			}
			break;
		}

	}
}

