#define _CRT_SECURE_NO_WARNINGS
#define FOREGROUND_RED       0x0004 // text color contains red.
#include "Windows.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include"head.h"


record* head = NULL;
double totalmoney = 0;//医院运营资金
int  checkn(int min, int max) {    //min最小值，max最大值，用于检验是否输入数字及数字范围是否正确，正确返回输入值
	int  i, m, k, j = 1;
	char a[1001];                 //构建一个容量为1001的空字符数组存储输入的选择
	while (j == 1) {
		m = 0, k = 0;
		for (i = 0; i < 1000; i++)      //输入字符
		{
			scanf_s("%c", &a[i], 1);
			if (a[i] != '\n')
				m++;                  //m为字符串长度
			else
				break;               //遇回车截止，输入结束
		}
		a[i] = '\0';                 //'\0'截止字符串，最后一位存储
		if (a[0] == '#')
		{
			return -1;
		}
		if (a[0] != '\0') {
			for (i = 0; i < m; i++)
			{
				if (a[i] < 48 || a[i]>57)     //若输入字符不是数字，报错，重新输入
				{
					printf("输入错误，请输入数字:");
					j = 1;
					break;
				}
				else                         //将字符数字转化为整型数字
				{
					j = 0;
					k = k * 10 + (a[i] - 48);
				}
			}
			if ((k <min || k > max) && j != 1) {             //检验是否在输入范围，否则报错重输
				printf("请输入正确范围的数字:");
				j = 1;
			}
		}
	}
	return k;      //返回整型数字
}

//输入入院、出院时间
void shili(date* d) {
	printf("月(范围1-12)：");
	d->month = checkn(1, 12);
	printf("日：");
	if (d->month == 1 || d->month == 3 || d->month == 5 || d->month == 7 || d->month == 8 || d->month == 10 || d->month == 12) {
		d->day = checkn(1, 31);
	}
	if (d->month == 4 || d->month == 6 || d->month == 9 || d->month == 11) {
		d->day = checkn(1, 30);
	}
	if (d->month == 2) {
		d->day = checkn(1, 29);
	}
	printf("时（0—24）：");
	d->hour = checkn(0, 24);
	printf("分（0—59）：");
	d->minute = checkn(0, 59);
}
void free_ptr(record* ptr)
{
	if (ptr != NULL)
	{
		Diag d = ptr->diag;
		struct Check* d_check = d.check;
		struct Medicine* d_medicine = d.medicine;
		while (d_check != NULL)
		{
			struct Check* temp = d_check;
			d_check = d_check->next;
			free(temp);
		}
		while (d_medicine != NULL)
		{
			struct Medicine* temp = d_medicine;
			d_medicine = d_medicine->next;
			free(temp);
		}
		free(ptr);
	}

}

int write_ch(check* head, double* a)
{
	char cmd = 'N';
	*a = 0;//记录金额
	int num = 0;
	head->next = NULL;
	printf("该患者需要检查吗？（Y|N）");
	getchar();//清除缓冲区
	scanf("%c", &cmd);
	if (cmd == 'Y' || cmd == 'y')
	{
		printf("输入检查项目：");
		scanf("%s", head->name);//这里也有问题
		printf("输入检查费用（如55元1角8分，即输入55.18）：");
		scanf("%lf", &head->money);
		//金额正确输入的判断
		while (head->money <= 0.0 || head->money > 100000.0 || fmod(head->money * 100, 1.0) > 0)//是否多于三位小数,是否不在0~10万
		{
			printf("错误输入，请输入money\n");
			printf("如55元1角8分，即输入55.18\n");
			scanf("%lf", &head->money);
		}
		num++; *a = *a + head->money;

		printf("是否录入下一项检查信息？（）");
		getchar();//清除缓冲区
		scanf("%c", &cmd);
		while (cmd == 'Y' || cmd == 'y')
		{
			num++;
			check* temp = (check*)malloc(sizeof(check));
			temp->next = NULL;
			printf("输入检查项目");
			scanf("%s", temp->name);
			printf("输入money");
			scanf("%lf", &temp->money);
			//金额正确输入的判断
			while (temp->money <= 0.0 || temp->money > 100000.0 || fmod(temp->money * 100, 1.0) > 0)//是否多于三位小数,是否不在0~10万
			{
				printf("错误输入，请输入money\n");
				printf("如55元1角8分，即输入55.18\n");
				scanf("%lf", &temp->money);
			}
			*a = *a + temp->money;
			//printf("是否有下一个");
			check* p = head;
			while (p->next != NULL) {
				p = p->next;
			}
			p->next = temp;
			printf("是否录入下一项检查信息？（）");
			getchar();//清除缓冲区
			scanf("%c", &cmd);
		}
	}
	else
	{
		head = NULL;
	}
	return num;
}

int write_me(medi* head, double* a)
{
	char cmd = 'N';
	*a = 0;
	int num = 0;
	head->next = NULL;
	printf("该患者需要开药吗？（Y|N）");
	getchar();//清除缓冲区
	scanf("%c", &cmd);
	if (cmd == 'Y' || cmd == 'y')
	{
		printf("输入药品名");
		scanf("%s", head->name);
		printf("输入数量");
		scanf("%d", &head->ammount);
		//药品数量检查
		while (!(head->ammount <= 100 && head->ammount >= 1)) {
			printf("错误输入：患者每次开药应在1~100 盒\n");
			printf("输入数量");
			scanf("%d", &head->ammount);
		}
		printf("输入money");
		scanf("%lf", &head->money);
		//金额正确输入的判断
		while (head->money <= 0.0 || head->money > 100000.0 || fmod(head->money * 100, 1.0) > 0)//是否多于三位小数,是否不在0~10万
		{
			printf("错误输入，请输入money\n");
			printf("如55元1角8分，即输入55.18\n");
			scanf("%lf", &head->money);
		}
		num++; *a = *a + head->money * head->ammount;
		printf("是否录入下一项药品信息？（）");
		getchar();//清除缓冲区
		scanf("%c", &cmd);
		while (cmd == 'Y' || cmd == 'y')
		{
			num++;
			medi* temp = (medi*)malloc(sizeof(medi));
			temp->next = NULL;
			printf("请输入药品名：");
			scanf("%s", temp->name);
			printf("请输入数量：");
			scanf("%d", &temp->ammount);
			printf("请输入药品单价：");
			scanf("%lf", &temp->money);
			//金额正确输入的判断
			while (temp->money <= 0.0 || temp->money > 100000.0 || fmod(temp->money * 100, 1.0) > 0)//是否多于三位小数,是否不在0~10万
			{
				printf("错误输入，请输入药品单价\n");
				printf("如55元1角8分，即输入55.18\n");
				scanf("%lf", &temp->money);
			}
			*a = *a + temp->money * temp->ammount;
			//printf("是否有下一个");
			medi* p = head;
			while (p->next != NULL) {
				p = p->next;
			}
			p->next = temp;
			printf("是否有下一个（Y|N）");
			getchar();//清除缓冲区
			scanf("%c", &cmd);
		}
	}
	else
	{
		head = NULL;
	}
	return num;
}
//ID唯一性检查
int insure_ID(record* temp) {
	record* p;
	p = head;
	while (p != NULL) {
		if (strcmp(temp->pati.ID, p->pati.ID) == 0)
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}
//医生工号唯一性检查
int insure_num(record* temp) {
	record* p;
	p = head;
	while (p != NULL) {
		if (strcmp(temp->doct.num, p->doct.num) == 0)
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}
//从键盘录入数据
void wirte() {
	decorate();
	char cmd = 'N';
	do {
		record* temp = (record*)malloc(sizeof(record));
		temp->next = NULL;

		printf("请输入患者姓名：");
		scanf("%s", temp->pati.name);
		printf("请输入患者ID[001-100]之间：");
		scanf("%s", temp->pati.ID);
		//ID范围检查
		while (insure_ID(temp) == 1 || (!(strcmp(temp->pati.ID, "001") >= 0 && strcmp(temp->pati.ID, "100") <= 0)))
		{
			if (insure_ID(temp) == 1)
				printf("错误输入，ID已存在\n");
			else
			{
				printf("错误输入，ID不在[001-100]之间\n");
			}
			printf("请重新输入患者ID：");
			scanf("%s", temp->pati.ID);
		}


		printf("请输入患者年龄：");
		scanf("%d", &temp->pati.age);
		printf("请输入患者挂号时间：");
		date regi_time;
		shili(&regi_time);
		//scanf("%s", &temp->pati.registration);

		printf("请输入医生姓名：");
		scanf("%s", temp->doct.name);
		//选择医生级别
		int choice = 0;
		printf("请输入级别：\n");
		printf("               1.主任医师 \n");
		printf("               2.副主任医师 \n");
		printf("               3.主治医师 \n");
		printf("               4.住院医师 \n");
		scanf("%d", &choice);
		//scanf("%s", temp->doct.profession);
		while (!(choice == 1 || choice == 2 || choice == 3 || choice == 4)) {
			printf("               ╮(╯▽╰)╭无此选项，请重新输入 \n");
			scanf("%d", &choice);
		}
		switch (choice)
		{
		case 1:
			strcpy(temp->doct.profession, "主任医师");
			break;
		case 2:
			strcpy(temp->doct.profession, "主任医师");
			break;
		case 3:
			strcpy(temp->doct.profession, "主任医师");
			break;
		case 4:
			strcpy(temp->doct.profession, "主任医师");
			break;
		}
		printf("输入工号,[01-30]之间)：");
		scanf("%s", temp->doct.num);
		while ((strlen(temp->doct.num) != 2))
		{
			printf("请重新输入工号,[01-30]之间)：");
			scanf("%s", temp->doct.num);
		}
		while (insure_num(temp) == 1 || (!(strcmp(temp->doct.num, "01") >= 0 && strcmp(temp->doct.num, "30") <= 0)))
		{
			if (insure_num(temp) == 1)
				printf("错误输入，工号已存在\n");
			else
			{
				printf("错误输入，工号不在[01-30]之间\n");
			}
			printf("请重新输入医生工号：");
			scanf("%s", temp->doct.num);
		}
		//此处自动生成挂号号码：患者ID+医生工号+挂号时间
		char x[3] = "\0", y[3] = "\0", q[3] = "\0", p[3] = "\0";
		if (regi_time.month < 10) { sprintf(x, "0%d", regi_time.month); }
		else { sprintf(x, "%d", regi_time.month); }
		if (regi_time.day < 10) { sprintf(y, "0%d", regi_time.day); }
		else { sprintf(y, "%d", regi_time.day); }
		if (regi_time.hour < 10) { sprintf(q, "0%d", regi_time.hour); }
		else { sprintf(q, "%d", regi_time.hour); }
		if (regi_time.minute < 10) { sprintf(p, "0%d", regi_time.minute); }
		else { sprintf(p, "%d", regi_time.minute); }

		sprintf(temp->pati.registration, "%s%s%s%s%s%s", temp->pati.ID, temp->doct.num, x, y, q, p);

		printf("输入医生科室：");
		scanf("%s", temp->doct.room_num);
		printf("输入出诊时间：\n");
		printf("（例如周一、周三出诊，则输入13）\n");
		int a = 0;
		int b = 0;
		int day = 1;
		for (int i = 0; i < 8; i++) {
			temp->doct.work_time[i] = 0;//0是不出诊
		}
		scanf("%d", &a);
		//检查出诊时间输入合法周一到周7
		int flag = 0;
		while (flag == 0) {
			int check7 = a;
			while (check7 > 0) {
				if (check7 % 10 > 7) {
					printf("请输入正确出诊时间：\n");
					printf("（例如周一、周三出诊，则输入13）\n");
					scanf("%d", &a);
					flag = 0;//有超过7的日期
					break;
				}
				check7 = check7 / 10;
				flag = 1;//无超过7的日期
			}
		}
		while (a > 10) {
			b = a % 10;
			a = a / 10;
			day++;
			temp->doct.work_time[b] = 1;//1是出诊
		}
		temp->doct.work_time[a] = 1;
		temp->doct.work_time[0] = day;//工作了几天
		//下面是住院信息
		char cmd_hosp = 'N';
		printf("该患者需要住院吗？（Y|N）");
		getchar();//清除缓冲区
		scanf("%c", &cmd_hosp);
		if (cmd_hosp == 'Y' || cmd_hosp == 'y')
		{

			date d1;
			printf("请输入住院日期：\n");

			shili(&d1);//住院日期
			printf("请输入出院日期：\n");

			printf("提示：出院日期至少应在住院日期一天以后！\n");
			date d2;
			shili(&d2);//出院日期
			while (!(d2.month > d1.month || (d2.month == d1.month && d2.day > d1.day))) {

				printf("错误的输入：出院日期至少应在住院日期一天以后！\n");

				printf("请输入住院日期：\n");
				shili(&d1);//住院日期
				printf("请输入出院日期：\n");
				shili(&d2);//出院日期
			}
			temp->diag.hospital.start = d1;
			temp->diag.hospital.end = d2;
			//计算住院天数、住院押金
			int hosp_day = 0;
			if (d1.month == d2.month) {//当月出院
				hosp_day = d2.day - d1.day + 1;
			}
			else {//不是当月出院
				hosp_day = (dayofmon[d1.month] - d1.day + 1) + d2.day;
				for (int i = d1.month + 1; i < d2.month; i++) {
					hosp_day = hosp_day + dayofmon[i];
				}
			}

			if (d2.hour <= 7) {//若出院日期在当天早八点之前，减一天
				hosp_day--;
			}

			temp->diag.hospital.money = hosp_day * 200.00;
			//押金至少1000元
			if (temp->diag.hospital.money < 1000) {
				temp->diag.hospital.money = 1000.00;
			}
		}
		else
		{
			temp->diag.hospital.money = 0.00;
		}
		//下面是检查和药品
		temp->diag.check = (check*)malloc(sizeof(check));
		temp->diag.num_c = write_ch(temp->diag.check, &temp->diag.money_ch);//记录有几项检查内容

		temp->diag.medicine = (medi*)malloc(sizeof(medi));
		temp->diag.num_m = write_me(temp->diag.medicine, &temp->diag.money_me);//记录买了几个药

		if (head == NULL) {
			head = temp;
		}
		else {
			record* p = head;
			while (p->next != NULL) {
				p = p->next;
			}
			p->next = temp;
		}
		printf("是否还要录入诊疗记录？（）");
		getchar();//清除缓冲区
		scanf("%c", &cmd);
	} while (cmd == 'Y' || cmd == 'y');
}

int sumday(Date d) {
	int m = 0;
	int monthday[13] = { 0,31,29,31,30,31,30,31,31,30,31,30,31 };
	int i;
	for (i = 0; i < d.month; i++) {
		m += monthday[i];
	}
	m += d.day;
	return m;
}
int caldates(Date d1, Date d2) {
	int a;
	int monthday[13] = { 0,31,29,31,30,31,30,31,31,30,31,30,31 };
	int i, j;
	i = sumday(d1);
	j = sumday(d2);
	a = j - i;
	if (d2.hour >= 0 && d2.hour <= 7) {
		a = a - 1;
	}
	if (d2.hour == 8 && d2.minute == 0) {
		a = a - 1;
	}
	return a;
}
void print_Record(record* h)//输出一条诊疗记录
{
	//if (h->pati != NULL)  这里假设一条诊疗信息对应一个病人，如果有多个病人，把if改成do,while控制
	{
		printf("   ---------------------------------------------------------------------------------------------------------\n");
		printf("   | 患者ID    | 名字      | 年龄      | 患者挂号            |医生工号   | 名字      | 科室      | 医生职称  |\n");
		printf("    ---------------------------------------------------------------------------------------------------------\n");
		printf("   | %-10s| %-10s| %-10d| %-20s| %-10s| %-10s| %-10s| %-10s|\n", h->pati.ID, h->pati.name, h->pati.age, h->pati.registration, h->doct.num, h->doct.name, h->doct.room_num, h->doct.profession);
		printf("    ---------------------------------------------------------------------------------------------------------\n");
	}
	//if (h->doctordetail != NULL) 这里假设一条诊疗信息对应一个医生，如果有多个医生，把if改成do,while控制
	{
		//printf("医生工作时间（如09：00-21：00）:%d", h->doctordetail->job_time);
	}
	//if (h->diag != NULL)
	{
		if (h->diag.num_c > 0) //有检查项目
		{
			printf("患者名字：%s ID: %s 检查记录如下：\n", h->pati.name, h->pati.ID);
			printf("    -----------------------------------\n");
			printf("   | 检查项目            | 价格        |\n");
			printf("    -----------------------------------\n");
			check* temp = h->diag.check;
			while (temp != NULL)
			{
				printf("   | %-20s| %.2lf       |\n", temp->name, temp->money);
				printf("    -----------------------------------\n");
				temp = temp->next;
			}
			printf("检查费用总计为：%.2lf\n", h->diag.money_ch);
		}
		else
		{
			printf("\n本次诊疗患者无检查项目");
		}
		if (h->diag.num_m > 0) //药物信息
		{
			printf("患者名字：%s ID: %s 药品记录如下：\n", h->pati.name, h->pati.ID);
			printf("    --------------------------------------------------\n");
			printf("   | 药品名称            | 药品数量  | 药品单价       |\n");
			printf("    --------------------------------------------------\n");
			medi* temp = h->diag.medicine;
			while (temp != NULL)
			{
				printf("   | %-20s| %-10d| %.2lf          |\n", temp->name, temp->ammount, temp->money);
				printf("    --------------------------------------------------\n");

				temp = temp->next;
			}
			printf("药品费用总计为：%.2lf\n", h->diag.money_me);
		}
		else
		{
			printf("\n本次诊疗患者未开药");
		}
		if (h->diag.hospital.money > 0.00)
		{
			int dates;
			double fee;
			dates = caldates(h->diag.hospital.start, h->diag.hospital.end);
			fee = 200.0 * dates;
			printf("患者名字：%s ID: %s 住院记录如下：\n", h->pati.name, h->pati.ID);
			//hosp* temp = h->diag.hospital;
			//while (temp != NULL)
			{
				printf("    --------------------------------------------------------------------\n");
				printf("   | 起始时间            | 结束时间            | 住院押金   |住院费用   |\n");
				printf("    --------------------------------------------------------------------\n");
				printf("   |%d月%d日%d时%d分      |%d月%d日%d时%d分     | %.2lf    | %.2lf   |\n", h->diag.hospital.start.month, h->diag.hospital.start.day, h->diag.hospital.start.hour, h->diag.hospital.start.minute, h->diag.hospital.end.month, h->diag.hospital.end.day, h->diag.hospital.end.hour, h->diag.hospital.end.minute, h->diag.hospital.money, fee);
				printf("    --------------------------------------------------------------------\n");
			}
		}
		else
		{
			printf("\n本次诊疗患者毋须住院");
		}
		//printf("\n总的检查价格为%.2lf", h->total_checkprice);
		//printf("\n总的药物价格为%.2lf", h->total_medicineprice);
	}
}
void print_all() {//输出所有记录
	record* p = head;
	if (p == NULL) {
		printf("一条记录也没有！\n");
	}
	while (p != NULL) {
		print_Record(p);
		p = p->next;
	}
}
//保存到文件
void save() {
	FILE* fp;
	fp = fopen("data.txt", "w");

	record* h = head;//只写了一条记录，有待完善--解决了
	while (h != NULL)
	{
		fprintf(fp, "%s %s %d %s\n %s %s %s %s\n",
			h->pati.name, h->pati.ID, h->pati.age, h->pati.registration,
			h->doct.num, h->doct.name, h->doct.room_num, h->doct.profession
		);
		for (int i = 0; i < 7; i++) {
			fprintf(fp, "%d ", h->doct.work_time[i]);
		}
		fprintf(fp, "%d\n", h->doct.work_time[7]);

		fprintf(fp, "%d\n", h->diag.num_c);//没有检查项目也会写0
		if (h->diag.num_c > 0) //有检查项目
		{
			//printf("\n诊断信息为:");

			check* temp = h->diag.check;

			while (temp != NULL)
			{
				fprintf(fp, "%s %.2lf\n", temp->name, temp->money);
				temp = temp->next;
			}
		}
		fprintf(fp, "%.2lf\n", h->diag.money_ch);//检查费用，没有检查项目也会写0

		fprintf(fp, "%d\n", h->diag.num_m);

		if (h->diag.num_m > 0) //药物信息
		{
			//printf("\n药物信息为:");

			medi* temp = h->diag.medicine;
			while (temp != NULL)
			{
				fprintf(fp, "%s %d %.2lf\n", temp->name, temp->ammount, temp->money);

				temp = temp->next;
			}
		}

		fprintf(fp, "%.2lf\n", h->diag.money_me);
		//下面保存住院信息到txt
		fprintf(fp, "%.2lf\n", h->diag.hospital.money);
		if (h->diag.hospital.money > 0) {
			fprintf(fp, "%d %d %d %d\n", h->diag.hospital.start.month, h->diag.hospital.start.day, h->diag.hospital.start.hour, h->diag.hospital.start.minute);
			fprintf(fp, "%d %d %d %d\n", h->diag.hospital.end.month, h->diag.hospital.end.day, h->diag.hospital.end.hour, h->diag.hospital.end.minute);
		}

		//fprintf(fp, "+-------+------------+------------+---------------------+------------+------+-------------+----------------+--------+---------------------------------------------------+\n");
		h = h->next;
	}
	fclose(fp);
	decorate();
	printf("保存成功\n");
	system("pause");
}
//读取txt文件信息
void read() {
	FILE* fp;
	fp = fopen("data.txt", "r");
	while (!feof(fp))
	{
		record* h = (record*)malloc(sizeof(record));
		h->next = NULL;
		h->diag.check = NULL;
		h->diag.medicine = NULL;

		fscanf(fp, "%s %s %d %s %s %s %s %s",
			h->pati.name, h->pati.ID, &h->pati.age, &h->pati.registration,
			h->doct.num, h->doct.name, h->doct.room_num, h->doct.profession
		);
		for (int i = 0; i < 8; i++) {
			fscanf(fp, "%d", &h->doct.work_time[i]);//载入出诊信息
		}
		// (h->diag.check != NULL) //有检查项目
			//printf("\n诊断信息为:");
		fscanf(fp, "%d", &h->diag.num_c);
		for (int i = 0; i < h->diag.num_c; i++)//如果是0就不写
		{
			check* temp_c = (check*)malloc(sizeof(check));
			temp_c->next = NULL;
			fscanf(fp, "%s %lf", temp_c->name, &(temp_c->money));//
			check* p = h->diag.check;
			if (h->diag.check == NULL)
			{
				h->diag.check = temp_c;
			}
			else
			{
				while (p->next != NULL)
				{
					p = p->next;
				}
				p->next = temp_c;
			}
		}
		fscanf(fp, "%lf", &h->diag.money_ch);

		fscanf(fp, "%d", &h->diag.num_m);
		for (int j = 0; j < h->diag.num_m; j++)//如果是0就不写
		{
			medi* temp_m = (medi*)malloc(sizeof(medi));
			temp_m->next = NULL;
			fscanf(fp, "%s %d %lf", temp_m->name, &temp_m->ammount, &temp_m->money);
			medi* p = h->diag.medicine;
			if (h->diag.medicine == NULL)
			{
				h->diag.medicine = temp_m;
			}
			else
			{
				while (p->next != NULL)
				{
					p = p->next;
				}
				p->next = temp_m;
			}
		}
		fscanf(fp, "%lf", &h->diag.money_me);
		//下面读取txt的住院信息
		fscanf(fp, "%lf\n", &h->diag.hospital.money);
		if (h->diag.hospital.money > 0.00) {
			fscanf(fp, "%d %d %d %d ", &h->diag.hospital.start.month, &h->diag.hospital.start.day, &h->diag.hospital.start.hour, &h->diag.hospital.start.minute);
			fscanf(fp, "%d %d %d %d ", &h->diag.hospital.end.month, &h->diag.hospital.end.day, &h->diag.hospital.end.hour, &h->diag.hospital.end.minute);
		}
		if (head == NULL) {
			head = h;
		}
		else {
			record* p = head;
			while (p->next != NULL) {
				p = p->next;
			}
			p->next = h;
		}
	}
	fclose(fp);

	decorate();
	printf("载入成功\n");
	system("pause");
}
//删除记录 返回头节点指针
void delete_Record()
{
	if (head == NULL)
	{
		printf("没有记录，无法删除");
		getchar();
		return;
	}
	int nn = 1;//表示第一条输出
	record* temp = (record*)malloc(sizeof(record));
	record* temp_head = (record*)malloc(sizeof(record));
	temp_head = head;
	temp = head;
	while (temp != NULL)
	{
		printf("第%d条记录", nn); //显示输出，来选择删除第几条
		print_Record(temp);
		nn++;
		printf("\n");
		temp = temp->next;
	}
	temp = head;
	printf("要删除第几条记录？");
	int mm = 0;
	scanf("%d", &mm);
	if (mm >= nn || mm <= 0)
	{
		printf("删除输入错误..");
		return;
	}
	nn = 1;
	record* temp_front = (record*)malloc(sizeof(record));
	temp_front = temp;
	if (mm == 1) //若删除第一个则返回第一个的地址
	{
		head = head->next; //头指针指向下一个地址
		free_ptr(temp_head); // free第一条地址（正常不应该这样直接，应该把指针里的所有地址都free
	}
	else
	{
		temp = temp->next;  //可能有问题，如果有问题直接操作head指针，然后把temp_head赋值给head
		nn++;
		while (nn != mm)
		{
			temp = temp->next;
			temp_front = temp_front->next;
			nn++;
		}
		temp_front->next = temp->next;
		free_ptr(temp); //释放temp的空间
	}
}

void wirte_single(record* temp) {
	printf("错误的诊疗记录已撤销。。。\n");
	printf("请补充添加正确的诊疗记录：\n");
	printf("请输入患者姓名：");
	scanf("%s", temp->pati.name);
	printf("请输入患者ID[001-100]之间：");
	scanf("%s", temp->pati.ID);
	//ID范围检查
	while (insure_ID(temp) == 1 || (!(strcmp(temp->pati.ID, "001") >= 0 && strcmp(temp->pati.ID, "100") <= 0)))
	{
		if (insure_ID(temp) == 1)
			printf("错误输入，ID已存在\n");
		else
		{
			printf("错误输入，ID不在[001-100]之间\n");
		}
		printf("请重新输入患者ID：");
		scanf("%s", temp->pati.ID);
	}


	printf("请输入患者年龄：");
	scanf("%d", &temp->pati.age);
	printf("请输入患者挂号时间：");
	date regi_time;
	shili(&regi_time);
	//scanf("%s", &temp->pati.registration);

	printf("请输入医生姓名：");
	scanf("%s", temp->doct.name);
	//选择医生级别
	int choice = 0;
	printf("请输入级别：\n");
	printf("               1.主任医师 \n");
	printf("               2.副主任医师 \n");
	printf("               3.主治医师 \n");
	printf("               4.住院医师 \n");
	scanf("%d", &choice);
	//scanf("%s", temp->doct.profession);
	while (!(choice == 1 || choice == 2 || choice == 3 || choice == 4)) {
		printf("               ╮(╯▽╰)╭无此选项，请重新输入 \n");
		scanf("%d", &choice);
	}
	switch (choice)
	{
	case 1:
		strcpy(temp->doct.profession, "主任医师");
		break;
	case 2:
		strcpy(temp->doct.profession, "主任医师");
		break;
	case 3:
		strcpy(temp->doct.profession, "主任医师");
		break;
	case 4:
		strcpy(temp->doct.profession, "主任医师");
		break;
	}
	printf("输入工号,[01-30]之间)：");
	scanf("%s", temp->doct.num);
	while (insure_num(temp) == 1 || (!(strcmp(temp->doct.num, "01") >= 0 && strcmp(temp->doct.num, "30") <= 0)))
	{
		if (insure_num(temp) == 1)
			printf("错误输入，工号已存在\n");
		else
		{
			printf("错误输入，工号不在[01-30]之间\n");
		}
		printf("请重新输入医生工号：");
		scanf("%s", temp->doct.num);
	}
	//此处自动生成挂号号码：患者ID+医生工号+挂号时间
	char x[3] = "\0", y[3] = "\0", q[3] = "\0", p[3] = "\0";
	if (regi_time.month < 10) { sprintf(x, "0%d", regi_time.month); }
	else { sprintf(x, "%d", regi_time.month); }
	if (regi_time.day < 10) { sprintf(y, "0%d", regi_time.day); }
	else { sprintf(y, "%d", regi_time.day); }
	if (regi_time.hour < 10) { sprintf(q, "0%d", regi_time.hour); }
	else { sprintf(q, "%d", regi_time.hour); }
	if (regi_time.minute < 10) { sprintf(p, "0%d", regi_time.minute); }
	else { sprintf(p, "%d", regi_time.minute); }

	sprintf(temp->pati.registration, "%s%s%s%s%s%s", temp->pati.ID, temp->doct.num, x, y, q, p);

	printf("输入医生科室：");
	scanf("%s", temp->doct.room_num);
	printf("输入出诊时间：\n");
	printf("（例如周一、周三出诊，则输入13）\n");
	int a = 0;
	int b = 0;
	int day = 1;
	for (int i = 0; i < 8; i++) {
		temp->doct.work_time[i] = 0;//0是不出诊
	}
	scanf("%d", &a);
	//检查出诊时间输入合法周一到周7
	int flag = 0;
	while (flag == 0) {
		int check7 = a;
		while (check7 > 0) {
			if (check7 % 10 > 7) {
				printf("请输入正确出诊时间：\n");
				printf("（例如周一、周三出诊，则输入13）\n");
				scanf("%d", &a);
				flag = 0;//有超过7的日期
				break;
			}
			check7 = check7 / 10;
			flag = 1;//无超过7的日期
		}
	}
	while (a > 10) {
		b = a % 10;
		a = a / 10;
		day++;
		temp->doct.work_time[b] = 1;//1是出诊
	}
	temp->doct.work_time[a] = 1;
	temp->doct.work_time[0] = day;//工作了几天
	//下面是住院信息
	char cmd_hosp = 'N';
	printf("该患者需要住院吗？（Y|N）");
	getchar();//清除缓冲区
	scanf("%c", &cmd_hosp);
	if (cmd_hosp == 'Y' || cmd_hosp == 'y')
	{

		date d1;
		printf("请输入住院日期：\n");

		shili(&d1);//住院日期
		printf("请输入出院日期：\n");

		printf("提示：出院日期至少应在住院日期一天以后！\n");
		date d2;
		shili(&d2);//出院日期
		while (!(d2.month > d1.month || (d2.month == d1.month && d2.day > d1.day))) {

			printf("错误的输入：出院日期至少应在住院日期一天以后！\n");

			printf("请输入住院日期：\n");
			shili(&d1);//住院日期
			printf("请输入出院日期：\n");
			shili(&d2);//出院日期
		}
		temp->diag.hospital.start = d1;
		temp->diag.hospital.end = d2;
		//计算住院天数、住院押金
		int hosp_day = 0;
		if (d1.month == d2.month) {//当月出院
			hosp_day = d2.day - d1.day + 1;
		}
		else {//不是当月出院
			hosp_day = (dayofmon[d1.month] - d1.day + 1) + d2.day;
			for (int i = d1.month + 1; i < d2.month; i++) {
				hosp_day = hosp_day + dayofmon[i];
			}
		}

		if (d2.hour <= 7) {//若出院日期在当天早八点之前，减一天
			hosp_day--;
		}

		temp->diag.hospital.money = hosp_day * 200.00;
		//押金至少1000元
		if (temp->diag.hospital.money < 1000) {
			temp->diag.hospital.money = 1000.00;
		}
	}
	else
	{
		temp->diag.hospital.money = 0.00;
	}
	//下面是检查和药品
	temp->diag.check = (check*)malloc(sizeof(check));
	temp->diag.num_c = write_ch(temp->diag.check, &temp->diag.money_ch);//记录有几项检查内容

	temp->diag.medicine = (medi*)malloc(sizeof(medi));
	temp->diag.num_m = write_me(temp->diag.medicine, &temp->diag.money_me);//记录买了几个药
}
//修改记录 --有bug
void modify_Record() //写入一条，然后在删除的地址上插入
{
	int nn = 1;//表示第一条输出
	record* temp = (record*)malloc(sizeof(record));
	temp = head;
	while (temp != NULL)
	{
		printf("\n第%d条记录", nn);
		print_Record(temp);
		nn++;
		temp = temp->next;
	}
	temp = head;
	printf("\n要修改第几条记录？");
	int mm = 0;
	scanf("%d", &mm);
	if (mm >= nn || mm <= 0)
	{
		printf("修改输入错误..");
		return;
	}
	nn = 1;
	record* ww = (record*)malloc(sizeof(record));
	wirte_single(ww);//修改
	if (mm == nn) //如果修改第一条记录
	{
		ww->next = temp->next;
		head = ww;
		free_ptr(temp);
	}
	while (mm != nn)
	{
		if (nn + 1 == mm) //如果下一个是要修改的记录的话
		{
			ww->next = temp->next->next;
			free_ptr(temp->next);
			temp->next = ww;
			break;
		}
		temp = temp->next;
		nn++;
	}
	getchar();
	getchar();
}

void changecheck(check* p, record* pr) {

	printf("请输入新的检查名称：\n");
	scanf_s("%[^\n]", p->name, 20);
	pr->total_checkprice = pr->total_checkprice - p->money;
	printf("请输入新的检查金额：\n");
	p->money = checkn(1, 1000000);
	pr->total_checkprice = pr->total_checkprice + p->money;

}
void changemedicine(medi* p, record* pr) {
	printf("请输入修改项： 1.修改名称  2.修改单价  3.修改数量 \n");
	int w;
	w = checkn(1, 3);
	if (w == 1) {
		printf("请输入新的药品名称：\n");
		scanf_s("%[^\n]", p->name, 20);
		printf("名称修改完毕");
	}
	if (w == 2) {
		pr->total_medicineprice = pr->total_medicineprice - p->money * p->ammount;
		printf("请输入新的药品单价：\n");
		p->money = checkn(1, 1000000);
		pr->total_medicineprice = pr->total_medicineprice + p->money * p->ammount;
	}
	if (w == 3) {
		pr->total_medicineprice = pr->total_medicineprice - p->money * p->ammount;
		printf("请输入新的药品数量：\n");
		p->ammount = checkn(1, 1000);
		pr->total_medicineprice = pr->total_medicineprice + p->money * p->ammount;
	}

}
void changehosp(record* p) {
	printf("请输入修改项： 1.修改开始时间  2.修改结束时间  3.修改押金 \n");
	int h;
	int monthday[13] = { 0,31,29,31,30,31,30,31,31,30,31,30,31 };
	int dates, newmoney;
	h = checkn(1, 3);
	if (h == 1) {

		int a, b, c, d;
		printf("请输入开始月份：范围为1—12\n");
		a = checkn(1, 12);
		printf("请输入开始日期：\n");
		b = checkn(1, monthday[a]);
		printf("请输入开始小时：范围为0—23\n");
		c = checkn(0, 23);
		printf("请输入开始分钟：范围为0—59\n");
		d = checkn(0, 59);
		p->diag.hospital.start.month = a;
		p->diag.hospital.start.day = b;
		p->diag.hospital.start.hour = c;
		p->diag.hospital.start.minute = d;
		dates = caldates(p->diag.hospital.start, p->diag.hospital.end);
		if (dates <= 5) {
			if (p->diag.hospital.money < 1000) {
				printf("押金小于1000，重新输入：\n");
				newmoney = checkn(999, 10000000);
				while (newmoney % 100 != 0) {
					printf("押金不符合100整数倍,重新输入\n");
					newmoney = checkn(999, 10000000);
				}
				printf("开始时间修改完毕\n");
			}
		}
		else {
			if (p->diag.hospital.money < dates * 200) {
				printf("押金小于200*天数，请输入新的押金：\n");
				int r = dates * 200;
				newmoney = checkn(r, 10000000);
				while (newmoney % 100 != 0) {
					printf("押金不符合100整数倍,重新输入\n");
					newmoney = checkn(r, 10000000);
				}
			}
			printf("开始时间修改完毕\n");
		}
	}
	if (h == 2) {
		int e, f, g, h;
		printf("请输入结束月份：范围为1—12\n");
		e = checkn(1, 12);
		printf("请输入结束日期：\n");
		f = checkn(1, monthday[e]);
		printf("请输入结束小时：范围为0—23\n");
		g = checkn(0, 23);
		printf("请输入结束分钟：范围为0—59\n");
		h = checkn(0, 59);
		p->diag.hospital.end.month = e;
		p->diag.hospital.end.day = f;
		p->diag.hospital.end.hour = g;
		p->diag.hospital.end.minute = h;
		dates = caldates(p->diag.hospital.start, p->diag.hospital.end);
		if (dates <= 5) {
			if (p->diag.hospital.money < 1000) {
				printf("押金小于1000，重新输入：\n");
				newmoney = checkn(999, 10000000);
				while (newmoney % 100 != 0) {
					printf("押金不符合100整数倍,重新输入\n");
					newmoney = checkn(999, 10000000);
				}
				printf("开始时间修改完毕\n");
			}
		}
		else {
			if (p->diag.hospital.money < dates * 200) {
				printf("请输入新的押金：\n");
				int l = dates * 200;
				newmoney = checkn(l, 10000000);
				while (newmoney % 100 != 0) {
					printf("押金不符合100整数倍,重新输入\n");
					newmoney = checkn(l, 10000000);
				}
			}
			printf("结束时间修改完毕\n");
		}
	}
	if (h == 3) {
		printf("当前押金为：%.2f\n", p->diag.hospital.money);
		printf("输入新的押金：\n");
		dates = caldates(p->diag.hospital.start, p->diag.hospital.end);
		if (dates <= 5) {
			if (p->diag.hospital.money < 1000) {
				printf("押金小于1000，重新输入：\n");
				newmoney = checkn(999, 10000000);
				while (newmoney % 100 != 0) {
					printf("押金不符合100整数倍,重新输入\n");
					newmoney = checkn(999, 10000000);
				}
				printf("押金修改完毕\n");
			}
		}
		else {
			if (p->diag.hospital.money < dates * 200) {
				printf("请输入新的押金：\n");
				int o = dates * 200;
				newmoney = checkn(o, 10000000);
				while (newmoney % 100 != 0) {
					printf("押金不符合100整数倍,重新输入\n");
					newmoney = checkn(o, 10000000);
				}
				printf("押金修改完毕\n");
			}
		}
	}
}

void modification(record* p, int n) {//修改信息
	/*typedef doctor* doc;//类型定义doctor*为doc
	doc r, r0;//声明两个变量
	r0 = NULL; r = dhead;//r0为空指针，r为头指针*/
	if (n == 1) //患者信息修改
	{
		int flag = 0;//标记变量
		for (; flag != -1;) {
			printf_s("       ‘(*>﹏<*)′ ~(@^_^@)~ （*+﹏+*）~ (^_^)∠※‘(*>﹏<*)′\n\n");
			printf_s("          -----------------------------------------------\n");
			printf_s("         |   请选择你所要修改的信息类型：                |\n");
			printf_s("         |1：修改患者姓名                                |\n");
			printf_s("         |2：修改患者年龄                                |\n");
			printf_s("         |3：修改患者ID                                  |\n");
			printf_s("          -----------------------------------------------\n");
			printf_s("              请选择操作（输入1、2或3）：");
			int a;
			a = checkn(1, 3);
			switch (a) {
			case 1: {
				printf("患者当前名字为%s\n", p->pati.name);
				printf("请输入患者姓名：");
				scanf_s("%[^\n]", p->pati.name, 20);
				getchar();
				printf("姓名修改成功,是否修改患者其他信息？ 1.继续修改 2.放弃修改\n");
				int bxw;
				bxw = checkn(1, 2);
				if (bxw == 1)break;
				if (bxw == 2) {
					flag = -1;
					break;
				}

			}
			case 2: {
				printf("当前年龄为%d\n", p->pati.age);
				printf("请输入患者年龄：");
				p->pati.age = checkn(0, 250);
				printf("年龄修改成功,是否修改患者其他信息？ 1.继续修改 2.放弃修改\n");
				int wzx;
				wzx = checkn(1, 2);
				if (wzx == 1)break;
				if (wzx == 2) {
					flag = -1;
					break;
				}
			}
			case 3: {
				printf("当前ID为%s\n", p->pati.ID);
				printf("请输入患者ID：");
				scanf_s("%[^\n]", p->pati.ID, 20);
				printf("ID修改成功,是否修改患者其他信息？ 1.继续修改 2.放弃修改\n");
				int tj;
				tj = checkn(1, 2);
				if (tj == 1)break;
				if (tj == 2) {
					flag = -1;
					break;
				}
			}
			}
		}

	}
	if (n == 2) {
		int mark = 0;
		for (; mark != -1;) {
			printf_s("        ‘(*>﹏<*)′ ~(@^_^@)~ （*+﹏+*）~ (^_^)∠※‘(*>﹏<*)′\n\n");
			printf_s("          ---------------------------------------------------\n");
			printf_s("         |   请选择你所要修改的信息类型：                    |\n");
			printf_s("         |1：修改医生姓名                                    |\n");
			printf_s("         |2：修改医生级别                                    |\n");
			printf_s("         |3：修改医生科室                                    |\n");
			printf_s("         |4：修改医生工号                                    |\n");
			printf_s("         |5：修改出诊时间                                    |\n");
			printf_s("          ---------------------------------------------------\n");
			printf_s("              请选择操作（输入1、2、3、4或5）：");
			int b;
			b = checkn(1, 5);
			switch (b) {
			case 1: {
				printf("医生当前名字为%s\n", p->doct.name);
				printf("请输入医生名称：");
				scanf_s("%[^\n]", p->doct.name, 20);
				getchar();
				printf("姓名修改成功,是否修改医生其他信息？ 1.继续修改 2.放弃修改\n");
				int bxw;
				bxw = checkn(1, 2);
				if (bxw == 1)break;
				if (bxw == 2) {
					mark = -1;
					break;
				}
			}
			case 2: {
				printf("医生当前级别为%s\n", p->doct.profession);
				printf("请输入医生级别：");
				scanf_s("%[^\n]", p->doct.profession, 20);
				printf("级别修改成功,是否修改医生其他信息？ 1.继续修改 2.放弃修改\n");
				int wzx;
				wzx = checkn(1, 2);
				if (wzx == 1)break;
				if (wzx == 2) {
					mark = -1;
					break;
				}
			}
			case 3: {
				printf("医生当前科室为%s\n", p->doct.room_num);
				printf("请选择医生科室：\n");
				printf("1.呼吸科   2.神经科   3心外科   4.妇产科\n");
				printf("5.骨科   6.儿科   7.泌尿科   8.眼科\n");
				int c;
				c = checkn(1, 8);
				switch (c)
				{
				case 1:p->doct.room_num[0] = { '1' };
				case 2:p->doct.room_num[0] = { '2' };
				case 3:p->doct.room_num[0] = { '3' };
				case 4:p->doct.room_num[0] = { '4' };
				case 5:p->doct.room_num[0] = { '5' };
				case 6:p->doct.room_num[0] = { '6' };
				case 7:p->doct.room_num[0] = { '7' };
				case 8:p->doct.room_num[0] = { '8' };
				default:
					break;
				}
				printf("科室修改成功,是否修改医生其他信息？ 1.继续修改 2.放弃修改\n");
				int tj;
				tj = checkn(1, 2);
				if (tj == 1)break;
				if (tj == 2) {
					mark = -1;
					break;
				}
			}
			case 4: {
				printf("当前工号为%s\n", p->doct.num);
				printf("请输入医生工号：");
				scanf_s("%[^\n]", p->doct.num, 20);
				printf("工号修改成功,是否修改医生其他信息？ 1.继续修改 2.放弃修改\n");
				int zkj;
				zkj = checkn(1, 2);
				if (zkj == 1)break;
				if (zkj == 2) {
					mark = -1;
					break;
				}
			}
			case 5: {
				printf("请选择出诊时间：\n");
				printf("星期一：1.出诊   2.不出诊\n");
				int aa;
				aa = checkn(1, 2);
				if (aa == 1) {
					p->doct.work_time[1] = '1';
				}
				if (aa == 2) {
					p->doct.work_time[1] = '0';
				}
				printf("星期二：1.出诊   2.不出诊\n");
				int bb;
				bb = checkn(1, 2);
				if (bb == 1) {
					p->doct.work_time[2] = '1';
				}
				if (bb == 2) {
					p->doct.work_time[2] = '0';
				}

				printf("星期三：1.出诊   2.不出诊\n");
				int cc;
				cc = checkn(1, 2);
				if (cc == 1) {
					p->doct.work_time[3] = '1';
				}
				if (cc == 2) {
					p->doct.work_time[3] = '0';
				}

				printf("星期四：1.出诊   2.不出诊、n");
				int dd;
				dd = checkn(1, 2);
				if (dd == 1) {
					p->doct.work_time[4] = '1';
				}
				if (dd == 2) {
					p->doct.work_time[4] = '0';
				}

				printf("星期五：1.出诊   2.不出诊 \n");
				int ee;
				ee = checkn(1, 2);
				if (ee == 1) {
					p->doct.work_time[5] = '1';
				}
				if (ee == 2) {
					p->doct.work_time[5] = '0';
				}

				printf("星期六：1.出诊   2.不出诊\n");
				int ff;
				ff = checkn(1, 2);
				if (ff == 1) {
					p->doct.work_time[6] = '1';
				}
				if (ff == 2) {
					p->doct.work_time[6] = '0';
				}

				printf("星期日：1.出诊   2.不出诊\n");
				int gg;
				gg = checkn(1, 2);
				if (gg == 1) {
					p->doct.work_time[7] = '1';
				}
				if (gg == 2) {
					p->doct.work_time[7] = '0';
				}
				printf("出诊时间修改成功,是否修改医生其他信息？ 1.继续修改 2.放弃修改\n");
				int djs;
				djs = checkn(1, 2);
				if (djs == 1)break;
				if (djs == 2) {
					mark = -1;
					break;
				}
			}
			}
		}
	}
	if (n == 3) {//改诊疗记录
		int t = 0;
		while (t != -1) {
			check* pc1;
			check* pc0;//两个指针，pc为头指针，pc0为空指针，下同
			medi* pm1;
			medi* pm0;
			pc0 = NULL, pc1 = p->diag.check;
			pm0 = NULL, pm1 = p->diag.medicine;
			printf_s("       ‘(*>﹏<*)′ ~(@^_^@)~ （*+﹏+*）~ (^_^)∠※‘(*>﹏<*)′\n\n");
			printf_s("          ---------------------------------------------------\n");
			printf_s("         |   请选择你所要修改的诊疗记录类型：                |\n");
			printf_s("         |1：修改检查记录                                    |\n");
			printf_s("         |2：修改开药记录                                    |\n");
			printf_s("         |3：修改住院记录                                    |\n");
			printf_s("          ---------------------------------------------------\n");
			printf_s("              请选择操作（输入1、2或3）：");
			int d;
			d = checkn(1, 3);
			switch (d) {
			case 1: {
				while (pc1->next != NULL) {
					printf("当前检查名称：%s\n", pc1->name);
					printf("当前检查金额：%.2f\n", pc1->money);
					printf("是否修改: 1.修改  2.不变\n");
					int aaa;
					aaa = checkn(1, 2);
					if (aaa == 1) {
						changecheck(pc1, p);
						printf("修改成功\n");
						printf("是否继续修改本条记录？ 1.修改  2.不变\n");
						int aaaa;
						aaaa = checkn(1, 2);
						if (aaaa == 1) {
							changecheck(pc1, p);
						}
						else {
							printf("本记录修改结束\n");
						}

						pc0 = pc1;
						pc1 = pc1->next;

					}
					else {
						pc0 = pc1;
						pc1 = pc1->next;
					}
				}
				printf("是否修改该患者其他诊疗记录？ 1.继续修改  2.放弃修改\n");
				int m;
				m = checkn(1, 2);
				if (m == 1)break;
				if (m == 2) {
					t = -1;
					break;
				}

			}
			case 2: {
				while (pm1->next != NULL) {
					printf("当前药品名称：%s\n", pm1->name);
					printf("当前药品金额：%.2f\n", pm1->money);
					printf("是否修改: 1.修改  2.不变\n");
					int bbb;
					bbb = checkn(1, 2);
					if (bbb == 1) {
						changemedicine(pm1, p);
						printf("修改成功\n");
						printf("是否继续修改本条记录？ 1.修改  2.不变\n");
						int aaaa;
						aaaa = checkn(1, 2);
						if (aaaa == 1) {
							changemedicine(pm1, p);
						}
						else {
							printf("本记录修改结束\n");
						}
						pm0 = pm1;
						pm1 = pm1->next;
					}
					else {
						pm0 = pm1;
						pm1 = pm1->next;
					}
				}
				printf("是否修改该患者其他诊疗记录？ 1.继续修改  2.放弃修改\n");
				int m;
				m = checkn(1, 2);
				if (m == 1)break;
				if (m == 2) {
					t = -1;
					break;
				}


			}
			case 3: {
				printf("当前住院记录开始时间：%d月%d日%d时%d分\n", p->diag.hospital.start.month, p->diag.hospital.start.day, p->diag.hospital.start.hour, p->diag.hospital.start.minute);
				printf("当前住院记录结束时间：%d月%d日%d时%d分\n", p->diag.hospital.end.month, p->diag.hospital.end.day, p->diag.hospital.end.hour, p->diag.hospital.end.minute);
				printf("当前住院记录押金：%.2f\n", p->diag.hospital.money);
				printf("是否修改本条记录: 1.修改  2.不变");
				int h;
				h = checkn(1, 2);
				if (h == 1) {
					changehosp(p);
					printf("修改成功\n");
					printf("是否继续修改本条记录？ 1.修改  2.不变\n");
					int hhhh;
					hhhh = checkn(1, 2);
					if (hhhh == 1) {
						changehosp(p);
					}
					else {
						printf("本记录修改结束\n");
					}
				}
				else {
					printf("本记录修改结束\n");
				}
				printf("是否修改该患者其他诊疗记录？ 1.继续修改  2.放弃修改\n");
				int m;
				m = checkn(1, 2);
				if (m == 1)break;
				if (m == 2) {
					t = -1;
					break;
				}
			}
			}
		}

	}
}
void change_record() {                  //修改记录函数

	char patiID[20];
	printf("请输入患者ID：\n");
	scanf("%s", patiID);
	record* p;
	record* p0; //声明两个变量
	p0 = NULL; p = head;//p0为空指针，p为头指针

	/*typedef doctor* doc;//类型定义doctor*为doc
	doc r, r0;//声明两个变量
	r0 = NULL; r = dhead;//r0为空指针，r为头指针*/

	while (p != NULL && (strcmp(p->pati.ID, patiID) != 0)) {   // 找到需修改的那条记录对应的节点
		p0 = p; p = p->next;
	}

	if (p != NULL) {
		int s;
		print_Record(p);
		printf("该患者的记录已找到，您是否要修改记录（1为修改，2为不变）：\n");
		s = checkn(1, 2);
		switch (s) {
		case 1: {
			int x = 0;
			int q;
			for (; x != -1;) {
				printf_s("      ‘(*>﹏<*)′ ~(@^_^@)~ （*+﹏+*）~ (^_^)∠※‘(*>﹏<*)′\n\n");
				printf_s("          -----------------------------------------------\n");
				printf_s("         |   请选择你所要修改的信息类型：                |\n");
				printf_s("         |1：修改患者身份信息                            |\n");
				printf_s("         |2：修改医生身份信息                            |\n");
				printf_s("         |3：修改诊疗记录                                |\n");
				printf_s("          -----------------------------------------------\n");
				printf_s("              请选择操作（输入1、2或3）：");

				int a;
				a = checkn(1, 3);
				modification(p, a);
				printf("是否要继续修改本记录中信息？ 1.继续修改 2.修改结束\n ");
				q = checkn(1, 2);
				if (q == 1) break;
				if (q == 2) {
					x = -1;
					break;
				}
			}
			int t;
			printf("请输入1为继续修改其他患者的记录信息，2为结束修改:\n");
			t = checkn(1, 2);
			if (t == 1) change_record();
			else {
				printf("修改操作结束\n");
				save();//将链表中的诊疗记录输出到文件中去
				return;
			}
		}
		case 2: {
			printf("修改结束\n");
			return;
		}
		}
	}
	else {
		printf("输入错误\n");
		int s;
		printf("请输入1为继续修改，2为结束修改:");
		s = checkn(1, 2);
		if (s == 1) change_record();
		else {
			printf("修改结束\n");
			return;
		}
	}
}

//修改记录函数



//统计营业额
double sum_Total(record* head)
{
	double sum = 0;


	return sum;
}


// 统计医生工作天数和时间
void print_Doc_day(record* head)
{
	char job_id_array[100][20]; //假设最多有100个医生
	int index = 0;
	record* tempptr = (record*)malloc(sizeof(record)); //用于第二遍遍历
	tempptr = head;
	while (tempptr != NULL) //将所有医生id放进数组job_id_array
	{
		char temp[20];
		strcpy(temp, tempptr->doct.num);
		int add_flag = 1;
		for (int i = 0; i < index; i++)
		{
			if (strcmp(job_id_array[i], temp) == 0)  //如果找到了相等的就跳过
			{
				add_flag = 0; break;
			}
		}
		if (add_flag)
		{
			strcpy(job_id_array[index++], temp); //把字符串temp拷贝进job_id_array
		}
		tempptr = tempptr->next;
	}
	tempptr = head;
	int s_index = 0;//控制第二遍遍历
	printf("\n--------------------医生信息--------------\n");
	while (tempptr != NULL)
	{
		if (strcmp(tempptr->doct.num, job_id_array[s_index]) == 0)
		{
			printf("第%d位医生\n", s_index + 1);
			printf("医生工号:%s\n", tempptr->doct.num);
			printf("医生名字:%s\n", tempptr->doct.name);
			printf("医生诊室:%s\n", tempptr->doct.room_num);
			printf("医生等级:%s\n", tempptr->doct.profession);
			//printf("医生工作时间（如09：00-21：00）:%d", tempptr->doct.job_time);
			printf("医生工作天数:");
			for (int i = 1; i < 8; i++)
			{
				if (tempptr->doct.work_time[i])
				{
					printf("周%d ", i);
				}
				//printf("%d", tempptr->doct.work_time[i]);
			}
			printf("上班\n");
			s_index++;
		}
		tempptr = tempptr->next;
	}
	getchar();
}
void searchRoom(record* head)
{
	printf("请输入要查找的科室:");
	char s_room[11];
	scanf("%s", &s_room);
	char room_id[100][11]; //假设100个科室
	int nn = 1;//表示第一条输出
	while (head != NULL)
	{
		if (strcmp(head->doct.room_num, s_room) == 0)
		{
			printf("%d :", nn);
			print_Record(head);
			nn++;
		}
		head = head->next;
	}
	if (nn == 1)
	{
		printf("\n该科室不存在，或该科室没有医生出诊，按Enter返回...\n");
	}
}
void searchDoctor(record* head) //这里最好提供工号来确定唯一医生，不过用名字更直观，后期再说
{
	printf("请输入要查找的医生:");
	char s_doc[20];
	scanf("%s", &s_doc);
	printf("请输入该医生的工号(防止重名),若不知道输入0:");
	char s_num[11];
	scanf("%s", &s_num);
	int nn = 1;//表示第一条输出
	while (head != NULL)
	{
		if (s_num[0] == '0')
		{
			if (strcmp(head->doct.name, s_doc) == 0)
			{
				printf("%d", nn);
				print_Record(head);
				nn++;
			}
		}
		else
		{
			if ((strcmp(head->doct.name, s_doc) == 0) && strcmp(head->doct.num, s_num) == 0)
			{
				printf("%d", nn);
				print_Record(head);
				nn++;
			}
		}
		head = head->next;
	}
	if (nn == 1)
	{
		printf("没有找到符合条件的医生...");
	}
}
void searchPat(record* head)
{
	printf("请输入要查找的病人:");
	char s_pat[20];
	scanf("%s", &s_pat);
	printf("请输入该病人的ID:若不知道输入0:");
	char regnumber[20];
	scanf("%s", &regnumber);
	int nn = 1;//表示第一条输出
	while (head != NULL)
	{
		if (regnumber[0] == '0' && strcmp(head->pati.name, s_pat) == 0)
		{
			printf("%d", nn);
			print_Record(head);
			nn++;
		}
		else if (strcmp(head->pati.name, s_pat) == 0 && strcmp(head->pati.ID, regnumber) == 0)
		{
			printf("%d", nn);
			print_Record(head);
			nn++;
		}
		head = head->next;
	}
	if (nn == 1)
	{
		printf("没有找到符合条件的病人..");
	}
}

//找寻一段时间的挂号信息
void out_Timerange(record* head)
{
	int flag = 1;
	char begin[20];
	char end[10];
	while (flag)
	{
		printf("请输入要查找的起始时间：如10041112 表示10月4日11时12分的挂号信息（需要规范一下一目了然）\n");
		scanf("%s", &begin);
		flag = 0;
		if (strlen(begin) > 8)
		{
			flag = 1;
			printf("\n输入有误，请重新输入..\n");
			continue;
		}
		for (int i = 0; i < 8; i++)//检验输入是否合法
		{
			if (begin[i] < '0' || begin[i]>'9')
			{
				flag = 1;
				printf("\n输入有误，请重新输入..\n");
				break;
			}
		}
		int month = (begin[0] - '0') * 10 + begin[1] - '0';//提取月份
		int day = (begin[2] - '0') * 10 + begin[3] - '0';  //提取日期
		int hour = (begin[4] - '0') * 10 + begin[5] - '0';  //提取时
		int min = (begin[6] - '0') * 10 + begin[7] - '0';  //提取时
		if (!(month <= 12 && month >= 1)) {
			flag = 1;
			printf("错误输入：月份应在1~12 \n"); continue;
		}
		if (!(day <= dayofmon[month] && day >= 1)) {
			flag = 1;
			printf("错误输入：该月无此日期 \n"); continue;
		}
		if (!(hour <= 23 && hour >= 0)) {
			flag = 1;
			printf("错误输入：小时应在0~23 \n"); continue;
		}
		if (!(min <= 59 && min >= 0)) {
			flag = 1;
			printf("错误输入：小时应在0~59 \n"); continue;
		}

	}
	flag = 1;
	while (flag)
	{
		printf("请输入要查找的中止时间：如10041213 表示10月4日12时13分的挂号信息（需要规范一下一目了然）\n");
		scanf("%s", &end);
		flag = 0;
		if (strlen(end) > 8)
		{
			flag = 1;
			printf("\n输入有误，请重新输入..\n");
			continue;
		}
		for (int i = 0; i < 8; i++)//检验输入是否合法
		{
			if (end[i] < '0' || end[i]>'9')
			{
				flag = 1;
				printf("\n输入有误，请重新输入..\n");
				break;
			}
		}
		int month = (end[0] - '0') * 10 + end[1] - '0';//提取月份
		int day = (end[2] - '0') * 10 + end[3] - '0';  //提取日期
		int hour = (end[4] - '0') * 10 + end[5] - '0';  //提取时
		int min = (end[6] - '0') * 10 + end[7] - '0';  //提取时
		if (!(month <= 12 && month >= 1)) {
			flag = 1;
			printf("错误输入：月份应在1~12 \n"); continue;
		}
		if (!(day <= dayofmon[month] && day >= 1)) {
			flag = 1;
			printf("错误输入：该月无此日期 \n"); continue;
		}
		if (!(hour <= 23 && hour >= 0)) {
			flag = 1;
			printf("错误输入：小时应在0~23 \n"); continue;
		}
		if (!(min <= 59 && min >= 0)) {
			flag = 1;
			printf("错误输入：小时应在0~59 \n"); continue;
		}
	}

	int index = 1;//输出的条数
	while (head != NULL)
	{
		char reg[10];
		for (int i = 0; i < 8; i++)
		{
			reg[i] = head->pati.registration[5 + i];//提取挂号月日时分
		}
		reg[8] = '\0';
		if (strcmp(reg, begin) > 0 && strcmp(reg, end) < 0)
		{
			printf("%d", index++);
			print_Record(head);
		}
		head = head->next;
	}
	if (index == 1)
	{
		printf("没有找到相关的诊疗信息,请尝试再次查询...");
	}
}

/*void statistics_money() {                        //统计营业额，生成住院报表
	totalmoney = 0;
	record* p;
	p = head;
	while (p != NULL) {
		totalmoney = (totalmoney + p->diag.money_ch + p->diag.money_me + p->diag.hospital.money);
		p = p->next;
	}
	decorate();
	int d = totalmoney * 100;
	int c = d % 10; d = d / 10;//分
	int b = d % 10; d = d / 10;//角
	printf("运营资金为：%d元%d角%d分\n", d, b, c);  //打印营业额
}*/

void statistics_1() {        //生成住院报表

	Record* p, *p0;  //声明两个变量
	p0 = NULL;
	p = head;  //p0为空指针，p为头指针
	int days = 0;//住院天数
	int start, end;
	int time_t;
	int month, day, hour, minute;

	while (p != NULL) {
		days = caldates(p->diag.hospital.start, p->diag.hospital.end);
		totalmoney = (totalmoney + p->diag.money_ch + p->diag.money_me + days * 200);
		p0 = p;
		p = p->next;
	}
	printf("营业额为：%.2lf\n", totalmoney);  //打印营业额
	int i;  //定义一个变量作为是否打印住院报表的根据
	printf("是否生成住院报表？（输入1为是，输入2为否）：\n");
	i = checkn(1, 2); //输入i
	if (i == 1) {  //如果i=1
		printf("请输当前时间:\n");
		printf("月：");
		month = checkn(1, 12);
		printf("日：");
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
			day = checkn(1, 31);
		}
		if (month == 4 || month == 6 || month == 9 || month == 11) {
			day = checkn(1, 30);
		}
		if (month == 2) {
			day = checkn(1, 29);
		}
		printf("时：");
		hour = checkn(0, 23);
		printf("分：");
		minute = checkn(0, 59);
		time_t = month * 1000000 + day * 10000 + hour * 100 + minute;//存储当前时间
		Record* r, *r0;//声明两个变量
		r0 = NULL; r = head;//r0为空指针，r为头指针
		printf("    ---------------------------------------------------------------------------------------------------------\n");
		printf("   |患者ID    |名字       |年龄   | 挂号              | 起始时间            | 结束时间             |金额     | \n");
		printf("    ---------------------------------------------------------------------------------------------------------\n");  //打印住院报表，顺序为ID，名字，挂号，时间，金额
		while (r != NULL) {
			if (((r->diag.hospital.start.month * 1000000 + r->diag.hospital.start.day * 10000 + r->diag.hospital.start.hour * 100 + r->diag.hospital.start.minute) <= time_t) && (time_t <= (r->diag.hospital.end.month * 1000000 + r->diag.hospital.end.day * 10000 + r->diag.hospital.end.hour * 100 + r->diag.hospital.end.minute))) {

				days = 0;
				days = caldates(r->diag.hospital.start, r->diag.hospital.end);
				printf("   | %-8s | %-10s| %-4d  | %-15s   |%d月%d日%d时%d分      |%d月%d日%d时%d分      |%.2lf   |\n", r->pati.ID, r->pati.name, r->pati.age, r->pati.registration, r->diag.hospital.start.month, r->diag.hospital.start.day, r->diag.hospital.start.hour, r->diag.hospital.start.minute, r->diag.hospital.end.month, r->diag.hospital.end.day, r->diag.hospital.end.hour, r->diag.hospital.end.minute, 200.00 * days);
				r0 = r;
				r = r->next;
				printf("    ---------------------------------------------------------------------------------------------------------\n");
				continue;
			}
			r = r->next;
		}
		getchar();
	}

}
void SetColorfore(unsigned short ForeColor)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, (ForeColor % 16) | (0 % 16 * 16));
}
void SetColorback(unsigned short backColor)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, (7 % 16) | (backColor % 16 * 16));
}
void window() {
	int i = 63, a, b = 1;
	printf("\n\n\n\n\n\n");
	SetColorback(0);
	printf("                          ");
	SetColorback(3);
	printf("                                                                   \n");
	SetColorback(0);
	printf("                          ");
	printf(" ");
	SetColorback(7);
	printf("                      ");
	SetColorback(0);
	printf(" 健 康 是 快 乐 之 源 ");
	SetColorback(2);
	printf("                      \n");
	while (i > 0) {
		SetColorback(0);
		printf("                          ");
		for (a = 0; a <= 63 - i + 1; a++)
			printf(" ");
		SetColorback(i);
		for (a = 0; a <= 63 - 2 * (63 - i + 1); a++)
			printf(" ");
		printf("\n");
		i = i - 3;
	}
	SetColorback(0);
}


/*void menu() {
	int choice = 2020;
	while (choice != 0)
	{
		system("cls");
		decorate();
		printf("               请选择您要执行的功能？ \n");
		printf("               1.录入诊疗记录 \n");
		printf("               2.载入文件 \n");
		printf("               3.保存文件 \n");
		printf("               4.输出所有信息 \n");
		printf("               5.删除诊疗记录 \n");
		printf("               6.修改诊疗记录 \n");
		printf("               7.统计医生工作天数 \n");
		printf("               8.查找科室 \n");
		printf("               9.查找医生信息 \n");
		printf("               10.查找病人信息 \n");
		printf("               11.查找一段时间的诊疗信息 \n");
		printf("               12.统计运营资金 \n");
		printf("               0.退出系统 \n");
		scanf("%d", &choice);
		while (choice < 0 || choice>12) {
			printf("               ╮(╯▽╰)╭ 无此选项，请重新输入 \n");
			scanf("%d", &choice);
		}
		if (choice == 1) {
			system("cls");
			wirte();
		}
		if (choice == 2) {
			system("cls");
			read();
		}
		if (choice == 3) {
			system("cls");
			save();
		}
		if (choice == 4) {
			system("cls");
			print_all();
			getchar();
			getchar();
		}
		if (choice == 5) {
			system("cls");
			delete_Record();
			getchar();
			getchar();
		}
		if (choice == 6)
		{
			system("cls");
			modify_Record();
			getchar();
			getchar();
		}
		if (choice == 7)
		{
			system("cls");
			print_Doc_day(head);
			getchar();
			getchar();
		}
		if (choice == 8)
		{
			system("cls");
			searchRoom(head);
			getchar();
			getchar();
		}
		if (choice == 9)
		{
			system("cls");
			searchDoctor(head);
			getchar();
			getchar();
		}
		if (choice == 10)
		{
			system("cls");
			searchPat(head);
			getchar();
			getchar();
		}
		if (choice == 11)
		{
			system("cls");
			out_Timerange(head);
			getchar();
			getchar();
		}
		if (choice == 12)
		{
			system("cls");
			statistics_money();
			getchar();
			getchar();
		}
	}
	system("cls");
	decorate();
	printf("               感谢您使用本系统！ \n");
}

void main()
{
	//read();//打开系统，先读入文件数据
	decorate();
	menu();
	//wirte();
	//save();
	system("pause");
	getchar();
	getchar();
	free(head);

}*/


int main()
{
	record* p1 = NULL;
	record* p2 = NULL;


	int n = 0;//n代表操作
	window();
	Sleep(2000);
	system("cls");
	decorate();
	while (1)
	{
		n = 0;
		decorate();
		SetColorfore(10);
		printf_s("***************************************************\n");
		SetColorfore(3);
		printf_s(" *     *     *     *     *     *     *     *     *    \n");
		printf_s("  *   * *   * *   * *   * *   * *   * *   * *   *    \n");
		printf_s("   * *   * *   * *   * *   * *   * *   * *   * *      \n");
		printf_s("    *     *     *     *     *     *     *     *    \n");
		SetColorfore(10);
		printf_s("     *****************************************\n");
		SetColorfore(15);
		printf_s("          ---------------------------\n");
		printf_s("         |  请选择操作内容           |\n");
		printf_s("         |1：查询信息                |\n");
		printf_s("         |2：精确修改记录            |\n");
		printf_s("         |3：逐项修改记录            |\n");
		printf_s("         |4：增加记录/删除记录       |\n");
		printf_s("         |5：统计信息                |\n");
		printf_s("         |6：保存信息                |\n");
		printf_s("         |7：读取信息                |\n");
		printf_s("         |#：退出程序                |\n");
		printf_s("          ---------------------------\n");
		printf_s("          请选择操作（输入1、2或#）：");//输入#返回-1
		int m;
		m = checkn(1, 7);

		switch (m)
		{
			//m=1查询信息
		case 1:
		{
			printf_s("\n\n~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~\n");
			printf_s("~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~\n");
			printf_s("\n                携手共建健康未来!\n\n");
			printf_s("~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~\n");
			printf_s("~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~\n\n");
			int n1 = 0;
			for (; n1 != -1;)
			{
				n1 = 0;
				printf_s("          ---------------------------\n");
				printf_s("         |  请选择操作               |\n");
				printf_s("         |1：查询患者诊疗记录        |\n");
				printf_s("         |2：查询科室诊疗信息        |\n");
				printf_s("         |3：查询医生诊疗信息        |\n");
				printf_s("         |#：返回上一步              |\n");
				printf_s("          ---------------------------\n");
				printf_s("           请选择操作（输入1、2、3或#）：");
				n = checkn(1, 3);
				switch (n)
				{
				case 1:
				{
					system("cls");
					searchPat(head);
					getchar();
					break;//跳出switchn
				}
				case 2:
				{
					system("cls");
					searchRoom(head);
					getchar();
					break;
				}
				case 3:
				{
					system("cls");
					searchDoctor(head);
					getchar();
					break;
				}
				case -1:
				{
					n1 = -1;
					break;//跳出switchn
				}
				}
			}
			break;//跳出switchm
		}
		//------------------------------------------------------------------------------------------------
		//m=2 修改
		case 2:
		{
			printf(" 请输入密码或输入#返回上一步(密码为提交报告时间：20201018)：");
			int mi;
			mi = checkn(20201018, 20201018);
			if (mi == -1)
			{
				break;
			}
			system("cls");
			change_record();
			break;
		}
		case 3: {
			printf(" 请输入密码或输入#返回上一步(密码为提交报告时间：20201018)：");
			int mii;
			mii = checkn(20201018, 20201018);
			if (mii == -1)
			{
				break;
			}
			system("cls");
			modify_Record();
			break;


		}
		case 4:
		{
			printf("请输入密码或输入#返回上一步(密码为提交报告时间：20201018)：");
			int key;
			key = checkn(20201018, 20201018);
			if (key == -1)
			{
				break;
			}
			int mm = 0;
			for (; key == 20201018 && mm != -1;) {
				mm = 0;
				int q2 = 0;//该层switch操作语句
				//输出不同数字代表不同操作   结束标志符
				printf_s("********************************************************\n");
				printf_s("‘(*>﹏<*)′ ~(@^_^@)~ （*+﹏+*）~ (^_^)∠※‘(*>﹏<*)′\n\n");
				printf_s("          ---------------------------\n");
				printf_s("         |  请选择操作:               |\n");
				printf_s("         |1：增加记录                 |\n");
				printf_s("         |2：删除记录                 |\n");
				printf_s("         |#：返回上一步               |\n");
				printf_s("          ---------------------------\n");
				printf_s("         请选择操作（输入1、2或#）：");
				printf_s("\n  -(=@__@=)--(=@__@=)--(=@__@=)--(=@__@=)--(=@__@=)-\n\n");
				//|\n|1：增加|\n|3：删除|\n|-1：返回上一步/结束程序|\
				//检验是否输入了正确的数字
				q2 = checkn(1, 2);
				//按选择的操作运行
				switch (q2) {
				case 1: {
					system("cls");
					wirte();
					printf("操作成功，是否要继续操作：  1.继续  2.结束\n");
					int u;
					u = checkn(1, 2);
					if (u == 1) {
						break;
					}
					else {
						mm = -1;
						break;
					}
				}
				case 2: {
					system("cls");
					delete_Record();
					printf("操作成功，是否要继续操作：  1.继续  2.结束\n");
					int v;
					v = checkn(1, 2);
					if (v == 1) {
						break;
					}
					else {
						mm = -1;
						break;
					}

				}
				case -1:
				{
					mm = -1;
					break;
				}


				}
			}
			break;
		}
		case 5: {
			int nn = 0;
			for (; nn != -1;) {
				nn = 0;
				int q4 = 0;
				printf_s("********************************************************\n");
				printf_s("‘(*>﹏<*)′ ~(@^_^@)~ （*+﹏+*）~ (^_^)∠※‘(*>﹏<*)′\n\n");
				printf_s("          --------------------------------------\n");
				printf_s("         |  请选择操作:                         |\n");
				printf_s("         |1：统计营业额并生成住院报表           |\n");
				printf_s("         |2：统计医生出诊情况及繁忙度           |\n");
				printf_s("         |3：统计某段时间范围的诊疗情况         |\n");
				printf_s("         |#：返回上一步                         |\n");
				printf_s("          --------------------------------------\n");
				printf_s("         请选择操作（输入1、2、3或#）：");
				printf_s("\n  -(=@__@=)--(=@__@=)--(=@__@=)--(=@__@=)--(=@__@=)-\n\n");
				q4 = checkn(1, 3);
				switch (q4) {
				case 1: {
					system("cls");
					statistics_1();
					printf("操作成功！\n");
					nn = -1;
					break;
				}
				case 2: {
					system("cls");
					print_Doc_day(head);
					printf("操作成功！\n");
					nn = -1;
					break;
				}
				case 3: {
					system("cls");
					out_Timerange(head);
					printf("操作成功，是否要继续统计别的范围：  1.继续  2.结束\n");
					int y;
					y = checkn(1, 2);
					if (y == 1) {
						break;
					}
					else {
						nn = -1;
						break;
					}
				}
				case -1: {
					nn = -1;
					break;
				}

				}





			}
			break;


		}
		case 6: {
			system("cls");
			save();
			break;
		}
		case 7: {
			system("cls");
			read();
			break;
		}
				//-1时退出程序
		case -1:
		{
			//释放链表节点
			p1 = head->next;     //释放记录链表节点
			while (p1 != NULL)
			{
				p2 = p1;
				p1 = p1->next;
				free(p2);
			}
			exit(0);
		}
		}//switchm
	}

	//释放链表节点
	p1 = head->next;     //释放历史记录链表节点
	while (p1 != NULL)
	{
		p2 = p1;
		p1 = p1->next;
		free(p2);
	}
	system("pause");
	return 0;
}






