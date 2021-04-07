#pragma once
#include "Windows.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
int dayofmon[13] = { 0,31,29,31,30,31,30,31,31,30,31,30,31 };//2020年每个月有几天
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
	printf("   '|@@@@@'        医疗管理系统        '|@@@@@:    \n");
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
	char registration[20];  //挂号唯一，怎么保证唯一？？？

}pati;

typedef struct Doctor {
	char name[20];					/*医生姓名*/
	char profession[15];			/*医生级别*/
	char room_num[11];			/*医生科室*/
	char num[11];					/*保存专家工号唯一*///怎么保证唯一？？？
	int work_time[8];//出诊时间怎么写？？？
	//struct Doctor* next;			/*保存指向下一个专家信息的指针*/
}doct;
typedef struct Check
{
	char name[20]; //检查内容
	double money;
	struct Check* next;  //可能一条记录连着多个检查记录
}check;
typedef struct Medicine
{
	char name[20];
	int ammount; //数量
	double money;
	struct Medicine* next;  //可能一条记录连着多个药品记录
}medi;
//住院类
typedef struct Hosp
{
	struct Date start;
	struct Date end;
	double money;//住院押金
}hosp;
typedef struct Diag
{

	struct Check* check;
	double money_ch;//总的检查价格
	struct Medicine* medicine;
	double money_me;//总的药品价格
	struct Hosp hospital;//
	int num_m;
	int num_c;
}diag;
//每条诊疗记录包括患者信息、医生信息、诊疗情况三部分
typedef struct Record
{
	struct Patient pati;
	struct Doctor doct;
	struct Diag diag;
	double total_checkprice;  //总的检查价格
	double total_medicineprice; //总的药品价格
	struct Record* next;
}record;

