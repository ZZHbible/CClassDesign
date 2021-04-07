#pragma once
#include "Windows.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
int dayofmon[13] = { 0,31,29,31,30,31,30,31,31,30,31,30,31 };//2020��ÿ�����м���
void decorate() {
	printf("	            '|@@||@@!`                     \n");
	printf("                  `!@@@@@@@@@@!`                   \n");
	printf("                .!@@@@@@@@@@@@@@!.                 \n");
	printf("             .;@@|:  .......'|@@@;.               \n");
	printf("             `|@@@|'         `|@@@@!`              \n");
	printf("         `!:.`!@@|'         `|@@@;`:!'            \n");
	printf("        '|@@@@;.'||'         `|@;.:@@@@|'          \n");
	printf("      '|@@@@@@@@;.'`         `'.:|@@@@@@@|:        \n");
	printf("    :|@@@!:'::::::.           .':::::':;|@@|:      \n");
	printf("   '|@@@@@'        ҽ�ƹ���ϵͳ        '|@@@@@:    \n");
	printf("   `|@@@@@'                             '|@@@@|'    \n");
	printf("   '|@@@@@'           2020              '|@@@@|'    \n");
	printf("   '|@@@@@'                             '|@@@@|'    \n");
	printf("    `|@@@:                             '|@@|'      \n");
	printf("      `!@@@@@@@@!`'`         `'`;@@@@@@@@!`        \n");
	printf("        .;@@@@;.'||'         `|@;`;@@@@!.          \n");
	printf("           '' `!@@|'         `|@@@;.`'             \n");
	printf("             `|@@@|'         `|@@@@!`              \n");
	printf("              .;@@|:.........'|@@@;.               \n");
	printf("                .!@@@@@@@@@@@@@@!.                 \n");
	printf("                  `!@@@@@@@@@@!.                   \n");
	printf("                    '|@@||@@!` \n");
}
typedef struct Date
{
	int month;
	int day;
	int hour;
	int minute;
} date;

typedef struct Patient
{
	char name[20];
	char ID[20];
	int age;
	char registration[20];  //�Һ�Ψһ����ô��֤Ψһ������

}pati;

typedef struct Doctor {
	char name[20];					/*ҽ������*/
	char profession[15];			/*ҽ������*/
	char room_num[11];			/*ҽ������*/
	char num[11];					/*����ר�ҹ���Ψһ*///��ô��֤Ψһ������
	int work_time[8];//����ʱ����ôд������
	//struct Doctor* next;			/*����ָ����һ��ר����Ϣ��ָ��*/
}doct;
typedef struct Check
{
	char name[20]; //�������
	double money;
	struct Check* next;  //����һ����¼���Ŷ������¼
}check;
typedef struct Medicine
{
	char name[20];
	int ammount; //����
	double money;
	struct Medicine* next;  //����һ����¼���Ŷ��ҩƷ��¼
}medi;
//סԺ��
typedef struct Hosp
{
	struct Date start;
	struct Date end;
	double money;//סԺѺ��
}hosp;
typedef struct Diag
{

	struct Check* check;
	double money_ch;//�ܵļ��۸�
	struct Medicine* medicine;
	double money_me;//�ܵ�ҩƷ�۸�
	struct Hosp hospital;//
	int num_m;
	int num_c;
}diag;
//ÿ�����Ƽ�¼����������Ϣ��ҽ����Ϣ���������������
typedef struct Record
{
	struct Patient pati;
	struct Doctor doct;
	struct Diag diag;
	double total_checkprice;  //�ܵļ��۸�
	double total_medicineprice; //�ܵ�ҩƷ�۸�
	struct Record* next;
}record;

