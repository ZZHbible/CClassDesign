#define _CRT_SECURE_NO_WARNINGS
#define FOREGROUND_RED       0x0004 // text color contains red.
#include "Windows.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include"head.h"


record* head = NULL;
double totalmoney = 0;//ҽԺ��Ӫ�ʽ�
int  checkn(int min, int max) {    //min��Сֵ��max���ֵ�����ڼ����Ƿ��������ּ����ַ�Χ�Ƿ���ȷ����ȷ��������ֵ
	int  i, m, k, j = 1;
	char a[1001];                 //����һ������Ϊ1001�Ŀ��ַ�����洢�����ѡ��
	while (j == 1) {
		m = 0, k = 0;
		for (i = 0; i < 1000; i++)      //�����ַ�
		{
			scanf_s("%c", &a[i], 1);
			if (a[i] != '\n')
				m++;                  //mΪ�ַ�������
			else
				break;               //���س���ֹ���������
		}
		a[i] = '\0';                 //'\0'��ֹ�ַ��������һλ�洢
		if (a[0] == '#')
		{
			return -1;
		}
		if (a[0] != '\0') {
			for (i = 0; i < m; i++)
			{
				if (a[i] < 48 || a[i]>57)     //�������ַ��������֣�������������
				{
					printf("�����������������:");
					j = 1;
					break;
				}
				else                         //���ַ�����ת��Ϊ��������
				{
					j = 0;
					k = k * 10 + (a[i] - 48);
				}
			}
			if ((k <min || k > max) && j != 1) {             //�����Ƿ������뷶Χ�����򱨴�����
				printf("��������ȷ��Χ������:");
				j = 1;
			}
		}
	}
	return k;      //������������
}

//������Ժ����Ժʱ��
void shili(date* d) {
	printf("��(��Χ1-12)��");
	d->month = checkn(1, 12);
	printf("�գ�");
	if (d->month == 1 || d->month == 3 || d->month == 5 || d->month == 7 || d->month == 8 || d->month == 10 || d->month == 12) {
		d->day = checkn(1, 31);
	}
	if (d->month == 4 || d->month == 6 || d->month == 9 || d->month == 11) {
		d->day = checkn(1, 30);
	}
	if (d->month == 2) {
		d->day = checkn(1, 29);
	}
	printf("ʱ��0��24����");
	d->hour = checkn(0, 24);
	printf("�֣�0��59����");
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
	*a = 0;//��¼���
	int num = 0;
	head->next = NULL;
	printf("�û�����Ҫ����𣿣�Y|N��");
	getchar();//���������
	scanf("%c", &cmd);
	if (cmd == 'Y' || cmd == 'y')
	{
		printf("��������Ŀ��");
		scanf("%s", head->name);//����Ҳ������
		printf("��������ã���55Ԫ1��8�֣�������55.18����");
		scanf("%lf", &head->money);
		//�����ȷ������ж�
		while (head->money <= 0.0 || head->money > 100000.0 || fmod(head->money * 100, 1.0) > 0)//�Ƿ������λС��,�Ƿ���0~10��
		{
			printf("�������룬������money\n");
			printf("��55Ԫ1��8�֣�������55.18\n");
			scanf("%lf", &head->money);
		}
		num++; *a = *a + head->money;

		printf("�Ƿ�¼����һ������Ϣ������");
		getchar();//���������
		scanf("%c", &cmd);
		while (cmd == 'Y' || cmd == 'y')
		{
			num++;
			check* temp = (check*)malloc(sizeof(check));
			temp->next = NULL;
			printf("��������Ŀ");
			scanf("%s", temp->name);
			printf("����money");
			scanf("%lf", &temp->money);
			//�����ȷ������ж�
			while (temp->money <= 0.0 || temp->money > 100000.0 || fmod(temp->money * 100, 1.0) > 0)//�Ƿ������λС��,�Ƿ���0~10��
			{
				printf("�������룬������money\n");
				printf("��55Ԫ1��8�֣�������55.18\n");
				scanf("%lf", &temp->money);
			}
			*a = *a + temp->money;
			//printf("�Ƿ�����һ��");
			check* p = head;
			while (p->next != NULL) {
				p = p->next;
			}
			p->next = temp;
			printf("�Ƿ�¼����һ������Ϣ������");
			getchar();//���������
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
	printf("�û�����Ҫ��ҩ�𣿣�Y|N��");
	getchar();//���������
	scanf("%c", &cmd);
	if (cmd == 'Y' || cmd == 'y')
	{
		printf("����ҩƷ��");
		scanf("%s", head->name);
		printf("��������");
		scanf("%d", &head->ammount);
		//ҩƷ�������
		while (!(head->ammount <= 100 && head->ammount >= 1)) {
			printf("�������룺����ÿ�ο�ҩӦ��1~100 ��\n");
			printf("��������");
			scanf("%d", &head->ammount);
		}
		printf("����money");
		scanf("%lf", &head->money);
		//�����ȷ������ж�
		while (head->money <= 0.0 || head->money > 100000.0 || fmod(head->money * 100, 1.0) > 0)//�Ƿ������λС��,�Ƿ���0~10��
		{
			printf("�������룬������money\n");
			printf("��55Ԫ1��8�֣�������55.18\n");
			scanf("%lf", &head->money);
		}
		num++; *a = *a + head->money * head->ammount;
		printf("�Ƿ�¼����һ��ҩƷ��Ϣ������");
		getchar();//���������
		scanf("%c", &cmd);
		while (cmd == 'Y' || cmd == 'y')
		{
			num++;
			medi* temp = (medi*)malloc(sizeof(medi));
			temp->next = NULL;
			printf("������ҩƷ����");
			scanf("%s", temp->name);
			printf("������������");
			scanf("%d", &temp->ammount);
			printf("������ҩƷ���ۣ�");
			scanf("%lf", &temp->money);
			//�����ȷ������ж�
			while (temp->money <= 0.0 || temp->money > 100000.0 || fmod(temp->money * 100, 1.0) > 0)//�Ƿ������λС��,�Ƿ���0~10��
			{
				printf("�������룬������ҩƷ����\n");
				printf("��55Ԫ1��8�֣�������55.18\n");
				scanf("%lf", &temp->money);
			}
			*a = *a + temp->money * temp->ammount;
			//printf("�Ƿ�����һ��");
			medi* p = head;
			while (p->next != NULL) {
				p = p->next;
			}
			p->next = temp;
			printf("�Ƿ�����һ����Y|N��");
			getchar();//���������
			scanf("%c", &cmd);
		}
	}
	else
	{
		head = NULL;
	}
	return num;
}
//IDΨһ�Լ��
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
//ҽ������Ψһ�Լ��
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
//�Ӽ���¼������
void wirte() {
	decorate();
	char cmd = 'N';
	do {
		record* temp = (record*)malloc(sizeof(record));
		temp->next = NULL;

		printf("�����뻼��������");
		scanf("%s", temp->pati.name);
		printf("�����뻼��ID[001-100]֮�䣺");
		scanf("%s", temp->pati.ID);
		//ID��Χ���
		while (insure_ID(temp) == 1 || (!(strcmp(temp->pati.ID, "001") >= 0 && strcmp(temp->pati.ID, "100") <= 0)))
		{
			if (insure_ID(temp) == 1)
				printf("�������룬ID�Ѵ���\n");
			else
			{
				printf("�������룬ID����[001-100]֮��\n");
			}
			printf("���������뻼��ID��");
			scanf("%s", temp->pati.ID);
		}


		printf("�����뻼�����䣺");
		scanf("%d", &temp->pati.age);
		printf("�����뻼�߹Һ�ʱ�䣺");
		date regi_time;
		shili(&regi_time);
		//scanf("%s", &temp->pati.registration);

		printf("������ҽ��������");
		scanf("%s", temp->doct.name);
		//ѡ��ҽ������
		int choice = 0;
		printf("�����뼶��\n");
		printf("               1.����ҽʦ \n");
		printf("               2.������ҽʦ \n");
		printf("               3.����ҽʦ \n");
		printf("               4.סԺҽʦ \n");
		scanf("%d", &choice);
		//scanf("%s", temp->doct.profession);
		while (!(choice == 1 || choice == 2 || choice == 3 || choice == 4)) {
			printf("               �r(�s���t)�q�޴�ѡ����������� \n");
			scanf("%d", &choice);
		}
		switch (choice)
		{
		case 1:
			strcpy(temp->doct.profession, "����ҽʦ");
			break;
		case 2:
			strcpy(temp->doct.profession, "����ҽʦ");
			break;
		case 3:
			strcpy(temp->doct.profession, "����ҽʦ");
			break;
		case 4:
			strcpy(temp->doct.profession, "����ҽʦ");
			break;
		}
		printf("���빤��,[01-30]֮��)��");
		scanf("%s", temp->doct.num);
		while ((strlen(temp->doct.num) != 2))
		{
			printf("���������빤��,[01-30]֮��)��");
			scanf("%s", temp->doct.num);
		}
		while (insure_num(temp) == 1 || (!(strcmp(temp->doct.num, "01") >= 0 && strcmp(temp->doct.num, "30") <= 0)))
		{
			if (insure_num(temp) == 1)
				printf("�������룬�����Ѵ���\n");
			else
			{
				printf("�������룬���Ų���[01-30]֮��\n");
			}
			printf("����������ҽ�����ţ�");
			scanf("%s", temp->doct.num);
		}
		//�˴��Զ����ɹҺź��룺����ID+ҽ������+�Һ�ʱ��
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

		printf("����ҽ�����ң�");
		scanf("%s", temp->doct.room_num);
		printf("�������ʱ�䣺\n");
		printf("��������һ���������������13��\n");
		int a = 0;
		int b = 0;
		int day = 1;
		for (int i = 0; i < 8; i++) {
			temp->doct.work_time[i] = 0;//0�ǲ�����
		}
		scanf("%d", &a);
		//������ʱ������Ϸ���һ����7
		int flag = 0;
		while (flag == 0) {
			int check7 = a;
			while (check7 > 0) {
				if (check7 % 10 > 7) {
					printf("��������ȷ����ʱ�䣺\n");
					printf("��������һ���������������13��\n");
					scanf("%d", &a);
					flag = 0;//�г���7������
					break;
				}
				check7 = check7 / 10;
				flag = 1;//�޳���7������
			}
		}
		while (a > 10) {
			b = a % 10;
			a = a / 10;
			day++;
			temp->doct.work_time[b] = 1;//1�ǳ���
		}
		temp->doct.work_time[a] = 1;
		temp->doct.work_time[0] = day;//�����˼���
		//������סԺ��Ϣ
		char cmd_hosp = 'N';
		printf("�û�����ҪסԺ�𣿣�Y|N��");
		getchar();//���������
		scanf("%c", &cmd_hosp);
		if (cmd_hosp == 'Y' || cmd_hosp == 'y')
		{

			date d1;
			printf("������סԺ���ڣ�\n");

			shili(&d1);//סԺ����
			printf("�������Ժ���ڣ�\n");

			printf("��ʾ����Ժ��������Ӧ��סԺ����һ���Ժ�\n");
			date d2;
			shili(&d2);//��Ժ����
			while (!(d2.month > d1.month || (d2.month == d1.month && d2.day > d1.day))) {

				printf("��������룺��Ժ��������Ӧ��סԺ����һ���Ժ�\n");

				printf("������סԺ���ڣ�\n");
				shili(&d1);//סԺ����
				printf("�������Ժ���ڣ�\n");
				shili(&d2);//��Ժ����
			}
			temp->diag.hospital.start = d1;
			temp->diag.hospital.end = d2;
			//����סԺ������סԺѺ��
			int hosp_day = 0;
			if (d1.month == d2.month) {//���³�Ժ
				hosp_day = d2.day - d1.day + 1;
			}
			else {//���ǵ��³�Ժ
				hosp_day = (dayofmon[d1.month] - d1.day + 1) + d2.day;
				for (int i = d1.month + 1; i < d2.month; i++) {
					hosp_day = hosp_day + dayofmon[i];
				}
			}

			if (d2.hour <= 7) {//����Ժ�����ڵ�����˵�֮ǰ����һ��
				hosp_day--;
			}

			temp->diag.hospital.money = hosp_day * 200.00;
			//Ѻ������1000Ԫ
			if (temp->diag.hospital.money < 1000) {
				temp->diag.hospital.money = 1000.00;
			}
		}
		else
		{
			temp->diag.hospital.money = 0.00;
		}
		//�����Ǽ���ҩƷ
		temp->diag.check = (check*)malloc(sizeof(check));
		temp->diag.num_c = write_ch(temp->diag.check, &temp->diag.money_ch);//��¼�м���������

		temp->diag.medicine = (medi*)malloc(sizeof(medi));
		temp->diag.num_m = write_me(temp->diag.medicine, &temp->diag.money_me);//��¼���˼���ҩ

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
		printf("�Ƿ�Ҫ¼�����Ƽ�¼������");
		getchar();//���������
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
void print_Record(record* h)//���һ�����Ƽ�¼
{
	//if (h->pati != NULL)  �������һ��������Ϣ��Ӧһ�����ˣ�����ж�����ˣ���if�ĳ�do,while����
	{
		printf("   ---------------------------------------------------------------------------------------------------------\n");
		printf("   | ����ID    | ����      | ����      | ���߹Һ�            |ҽ������   | ����      | ����      | ҽ��ְ��  |\n");
		printf("    ---------------------------------------------------------------------------------------------------------\n");
		printf("   | %-10s| %-10s| %-10d| %-20s| %-10s| %-10s| %-10s| %-10s|\n", h->pati.ID, h->pati.name, h->pati.age, h->pati.registration, h->doct.num, h->doct.name, h->doct.room_num, h->doct.profession);
		printf("    ---------------------------------------------------------------------------------------------------------\n");
	}
	//if (h->doctordetail != NULL) �������һ��������Ϣ��Ӧһ��ҽ��������ж��ҽ������if�ĳ�do,while����
	{
		//printf("ҽ������ʱ�䣨��09��00-21��00��:%d", h->doctordetail->job_time);
	}
	//if (h->diag != NULL)
	{
		if (h->diag.num_c > 0) //�м����Ŀ
		{
			printf("�������֣�%s ID: %s ����¼���£�\n", h->pati.name, h->pati.ID);
			printf("    -----------------------------------\n");
			printf("   | �����Ŀ            | �۸�        |\n");
			printf("    -----------------------------------\n");
			check* temp = h->diag.check;
			while (temp != NULL)
			{
				printf("   | %-20s| %.2lf       |\n", temp->name, temp->money);
				printf("    -----------------------------------\n");
				temp = temp->next;
			}
			printf("�������ܼ�Ϊ��%.2lf\n", h->diag.money_ch);
		}
		else
		{
			printf("\n�������ƻ����޼����Ŀ");
		}
		if (h->diag.num_m > 0) //ҩ����Ϣ
		{
			printf("�������֣�%s ID: %s ҩƷ��¼���£�\n", h->pati.name, h->pati.ID);
			printf("    --------------------------------------------------\n");
			printf("   | ҩƷ����            | ҩƷ����  | ҩƷ����       |\n");
			printf("    --------------------------------------------------\n");
			medi* temp = h->diag.medicine;
			while (temp != NULL)
			{
				printf("   | %-20s| %-10d| %.2lf          |\n", temp->name, temp->ammount, temp->money);
				printf("    --------------------------------------------------\n");

				temp = temp->next;
			}
			printf("ҩƷ�����ܼ�Ϊ��%.2lf\n", h->diag.money_me);
		}
		else
		{
			printf("\n�������ƻ���δ��ҩ");
		}
		if (h->diag.hospital.money > 0.00)
		{
			int dates;
			double fee;
			dates = caldates(h->diag.hospital.start, h->diag.hospital.end);
			fee = 200.0 * dates;
			printf("�������֣�%s ID: %s סԺ��¼���£�\n", h->pati.name, h->pati.ID);
			//hosp* temp = h->diag.hospital;
			//while (temp != NULL)
			{
				printf("    --------------------------------------------------------------------\n");
				printf("   | ��ʼʱ��            | ����ʱ��            | סԺѺ��   |סԺ����   |\n");
				printf("    --------------------------------------------------------------------\n");
				printf("   |%d��%d��%dʱ%d��      |%d��%d��%dʱ%d��     | %.2lf    | %.2lf   |\n", h->diag.hospital.start.month, h->diag.hospital.start.day, h->diag.hospital.start.hour, h->diag.hospital.start.minute, h->diag.hospital.end.month, h->diag.hospital.end.day, h->diag.hospital.end.hour, h->diag.hospital.end.minute, h->diag.hospital.money, fee);
				printf("    --------------------------------------------------------------------\n");
			}
		}
		else
		{
			printf("\n�������ƻ�������סԺ");
		}
		//printf("\n�ܵļ��۸�Ϊ%.2lf", h->total_checkprice);
		//printf("\n�ܵ�ҩ��۸�Ϊ%.2lf", h->total_medicineprice);
	}
}
void print_all() {//������м�¼
	record* p = head;
	if (p == NULL) {
		printf("һ����¼Ҳû�У�\n");
	}
	while (p != NULL) {
		print_Record(p);
		p = p->next;
	}
}
//���浽�ļ�
void save() {
	FILE* fp;
	fp = fopen("data.txt", "w");

	record* h = head;//ֻд��һ����¼���д�����--�����
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

		fprintf(fp, "%d\n", h->diag.num_c);//û�м����ĿҲ��д0
		if (h->diag.num_c > 0) //�м����Ŀ
		{
			//printf("\n�����ϢΪ:");

			check* temp = h->diag.check;

			while (temp != NULL)
			{
				fprintf(fp, "%s %.2lf\n", temp->name, temp->money);
				temp = temp->next;
			}
		}
		fprintf(fp, "%.2lf\n", h->diag.money_ch);//�����ã�û�м����ĿҲ��д0

		fprintf(fp, "%d\n", h->diag.num_m);

		if (h->diag.num_m > 0) //ҩ����Ϣ
		{
			//printf("\nҩ����ϢΪ:");

			medi* temp = h->diag.medicine;
			while (temp != NULL)
			{
				fprintf(fp, "%s %d %.2lf\n", temp->name, temp->ammount, temp->money);

				temp = temp->next;
			}
		}

		fprintf(fp, "%.2lf\n", h->diag.money_me);
		//���汣��סԺ��Ϣ��txt
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
	printf("����ɹ�\n");
	system("pause");
}
//��ȡtxt�ļ���Ϣ
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
			fscanf(fp, "%d", &h->doct.work_time[i]);//���������Ϣ
		}
		// (h->diag.check != NULL) //�м����Ŀ
			//printf("\n�����ϢΪ:");
		fscanf(fp, "%d", &h->diag.num_c);
		for (int i = 0; i < h->diag.num_c; i++)//�����0�Ͳ�д
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
		for (int j = 0; j < h->diag.num_m; j++)//�����0�Ͳ�д
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
		//�����ȡtxt��סԺ��Ϣ
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
	printf("����ɹ�\n");
	system("pause");
}
//ɾ����¼ ����ͷ�ڵ�ָ��
void delete_Record()
{
	if (head == NULL)
	{
		printf("û�м�¼���޷�ɾ��");
		getchar();
		return;
	}
	int nn = 1;//��ʾ��һ�����
	record* temp = (record*)malloc(sizeof(record));
	record* temp_head = (record*)malloc(sizeof(record));
	temp_head = head;
	temp = head;
	while (temp != NULL)
	{
		printf("��%d����¼", nn); //��ʾ�������ѡ��ɾ���ڼ���
		print_Record(temp);
		nn++;
		printf("\n");
		temp = temp->next;
	}
	temp = head;
	printf("Ҫɾ���ڼ�����¼��");
	int mm = 0;
	scanf("%d", &mm);
	if (mm >= nn || mm <= 0)
	{
		printf("ɾ���������..");
		return;
	}
	nn = 1;
	record* temp_front = (record*)malloc(sizeof(record));
	temp_front = temp;
	if (mm == 1) //��ɾ����һ���򷵻ص�һ���ĵ�ַ
	{
		head = head->next; //ͷָ��ָ����һ����ַ
		free_ptr(temp_head); // free��һ����ַ��������Ӧ������ֱ�ӣ�Ӧ�ð�ָ��������е�ַ��free
	}
	else
	{
		temp = temp->next;  //���������⣬���������ֱ�Ӳ���headָ�룬Ȼ���temp_head��ֵ��head
		nn++;
		while (nn != mm)
		{
			temp = temp->next;
			temp_front = temp_front->next;
			nn++;
		}
		temp_front->next = temp->next;
		free_ptr(temp); //�ͷ�temp�Ŀռ�
	}
}

void wirte_single(record* temp) {
	printf("��������Ƽ�¼�ѳ���������\n");
	printf("�벹�������ȷ�����Ƽ�¼��\n");
	printf("�����뻼��������");
	scanf("%s", temp->pati.name);
	printf("�����뻼��ID[001-100]֮�䣺");
	scanf("%s", temp->pati.ID);
	//ID��Χ���
	while (insure_ID(temp) == 1 || (!(strcmp(temp->pati.ID, "001") >= 0 && strcmp(temp->pati.ID, "100") <= 0)))
	{
		if (insure_ID(temp) == 1)
			printf("�������룬ID�Ѵ���\n");
		else
		{
			printf("�������룬ID����[001-100]֮��\n");
		}
		printf("���������뻼��ID��");
		scanf("%s", temp->pati.ID);
	}


	printf("�����뻼�����䣺");
	scanf("%d", &temp->pati.age);
	printf("�����뻼�߹Һ�ʱ�䣺");
	date regi_time;
	shili(&regi_time);
	//scanf("%s", &temp->pati.registration);

	printf("������ҽ��������");
	scanf("%s", temp->doct.name);
	//ѡ��ҽ������
	int choice = 0;
	printf("�����뼶��\n");
	printf("               1.����ҽʦ \n");
	printf("               2.������ҽʦ \n");
	printf("               3.����ҽʦ \n");
	printf("               4.סԺҽʦ \n");
	scanf("%d", &choice);
	//scanf("%s", temp->doct.profession);
	while (!(choice == 1 || choice == 2 || choice == 3 || choice == 4)) {
		printf("               �r(�s���t)�q�޴�ѡ����������� \n");
		scanf("%d", &choice);
	}
	switch (choice)
	{
	case 1:
		strcpy(temp->doct.profession, "����ҽʦ");
		break;
	case 2:
		strcpy(temp->doct.profession, "����ҽʦ");
		break;
	case 3:
		strcpy(temp->doct.profession, "����ҽʦ");
		break;
	case 4:
		strcpy(temp->doct.profession, "����ҽʦ");
		break;
	}
	printf("���빤��,[01-30]֮��)��");
	scanf("%s", temp->doct.num);
	while (insure_num(temp) == 1 || (!(strcmp(temp->doct.num, "01") >= 0 && strcmp(temp->doct.num, "30") <= 0)))
	{
		if (insure_num(temp) == 1)
			printf("�������룬�����Ѵ���\n");
		else
		{
			printf("�������룬���Ų���[01-30]֮��\n");
		}
		printf("����������ҽ�����ţ�");
		scanf("%s", temp->doct.num);
	}
	//�˴��Զ����ɹҺź��룺����ID+ҽ������+�Һ�ʱ��
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

	printf("����ҽ�����ң�");
	scanf("%s", temp->doct.room_num);
	printf("�������ʱ�䣺\n");
	printf("��������һ���������������13��\n");
	int a = 0;
	int b = 0;
	int day = 1;
	for (int i = 0; i < 8; i++) {
		temp->doct.work_time[i] = 0;//0�ǲ�����
	}
	scanf("%d", &a);
	//������ʱ������Ϸ���һ����7
	int flag = 0;
	while (flag == 0) {
		int check7 = a;
		while (check7 > 0) {
			if (check7 % 10 > 7) {
				printf("��������ȷ����ʱ�䣺\n");
				printf("��������һ���������������13��\n");
				scanf("%d", &a);
				flag = 0;//�г���7������
				break;
			}
			check7 = check7 / 10;
			flag = 1;//�޳���7������
		}
	}
	while (a > 10) {
		b = a % 10;
		a = a / 10;
		day++;
		temp->doct.work_time[b] = 1;//1�ǳ���
	}
	temp->doct.work_time[a] = 1;
	temp->doct.work_time[0] = day;//�����˼���
	//������סԺ��Ϣ
	char cmd_hosp = 'N';
	printf("�û�����ҪסԺ�𣿣�Y|N��");
	getchar();//���������
	scanf("%c", &cmd_hosp);
	if (cmd_hosp == 'Y' || cmd_hosp == 'y')
	{

		date d1;
		printf("������סԺ���ڣ�\n");

		shili(&d1);//סԺ����
		printf("�������Ժ���ڣ�\n");

		printf("��ʾ����Ժ��������Ӧ��סԺ����һ���Ժ�\n");
		date d2;
		shili(&d2);//��Ժ����
		while (!(d2.month > d1.month || (d2.month == d1.month && d2.day > d1.day))) {

			printf("��������룺��Ժ��������Ӧ��סԺ����һ���Ժ�\n");

			printf("������סԺ���ڣ�\n");
			shili(&d1);//סԺ����
			printf("�������Ժ���ڣ�\n");
			shili(&d2);//��Ժ����
		}
		temp->diag.hospital.start = d1;
		temp->diag.hospital.end = d2;
		//����סԺ������סԺѺ��
		int hosp_day = 0;
		if (d1.month == d2.month) {//���³�Ժ
			hosp_day = d2.day - d1.day + 1;
		}
		else {//���ǵ��³�Ժ
			hosp_day = (dayofmon[d1.month] - d1.day + 1) + d2.day;
			for (int i = d1.month + 1; i < d2.month; i++) {
				hosp_day = hosp_day + dayofmon[i];
			}
		}

		if (d2.hour <= 7) {//����Ժ�����ڵ�����˵�֮ǰ����һ��
			hosp_day--;
		}

		temp->diag.hospital.money = hosp_day * 200.00;
		//Ѻ������1000Ԫ
		if (temp->diag.hospital.money < 1000) {
			temp->diag.hospital.money = 1000.00;
		}
	}
	else
	{
		temp->diag.hospital.money = 0.00;
	}
	//�����Ǽ���ҩƷ
	temp->diag.check = (check*)malloc(sizeof(check));
	temp->diag.num_c = write_ch(temp->diag.check, &temp->diag.money_ch);//��¼�м���������

	temp->diag.medicine = (medi*)malloc(sizeof(medi));
	temp->diag.num_m = write_me(temp->diag.medicine, &temp->diag.money_me);//��¼���˼���ҩ
}
//�޸ļ�¼ --��bug
void modify_Record() //д��һ����Ȼ����ɾ���ĵ�ַ�ϲ���
{
	int nn = 1;//��ʾ��һ�����
	record* temp = (record*)malloc(sizeof(record));
	temp = head;
	while (temp != NULL)
	{
		printf("\n��%d����¼", nn);
		print_Record(temp);
		nn++;
		temp = temp->next;
	}
	temp = head;
	printf("\nҪ�޸ĵڼ�����¼��");
	int mm = 0;
	scanf("%d", &mm);
	if (mm >= nn || mm <= 0)
	{
		printf("�޸��������..");
		return;
	}
	nn = 1;
	record* ww = (record*)malloc(sizeof(record));
	wirte_single(ww);//�޸�
	if (mm == nn) //����޸ĵ�һ����¼
	{
		ww->next = temp->next;
		head = ww;
		free_ptr(temp);
	}
	while (mm != nn)
	{
		if (nn + 1 == mm) //�����һ����Ҫ�޸ĵļ�¼�Ļ�
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

	printf("�������µļ�����ƣ�\n");
	scanf_s("%[^\n]", p->name, 20);
	pr->total_checkprice = pr->total_checkprice - p->money;
	printf("�������µļ���\n");
	p->money = checkn(1, 1000000);
	pr->total_checkprice = pr->total_checkprice + p->money;

}
void changemedicine(medi* p, record* pr) {
	printf("�������޸�� 1.�޸�����  2.�޸ĵ���  3.�޸����� \n");
	int w;
	w = checkn(1, 3);
	if (w == 1) {
		printf("�������µ�ҩƷ���ƣ�\n");
		scanf_s("%[^\n]", p->name, 20);
		printf("�����޸����");
	}
	if (w == 2) {
		pr->total_medicineprice = pr->total_medicineprice - p->money * p->ammount;
		printf("�������µ�ҩƷ���ۣ�\n");
		p->money = checkn(1, 1000000);
		pr->total_medicineprice = pr->total_medicineprice + p->money * p->ammount;
	}
	if (w == 3) {
		pr->total_medicineprice = pr->total_medicineprice - p->money * p->ammount;
		printf("�������µ�ҩƷ������\n");
		p->ammount = checkn(1, 1000);
		pr->total_medicineprice = pr->total_medicineprice + p->money * p->ammount;
	}

}
void changehosp(record* p) {
	printf("�������޸�� 1.�޸Ŀ�ʼʱ��  2.�޸Ľ���ʱ��  3.�޸�Ѻ�� \n");
	int h;
	int monthday[13] = { 0,31,29,31,30,31,30,31,31,30,31,30,31 };
	int dates, newmoney;
	h = checkn(1, 3);
	if (h == 1) {

		int a, b, c, d;
		printf("�����뿪ʼ�·ݣ���ΧΪ1��12\n");
		a = checkn(1, 12);
		printf("�����뿪ʼ���ڣ�\n");
		b = checkn(1, monthday[a]);
		printf("�����뿪ʼСʱ����ΧΪ0��23\n");
		c = checkn(0, 23);
		printf("�����뿪ʼ���ӣ���ΧΪ0��59\n");
		d = checkn(0, 59);
		p->diag.hospital.start.month = a;
		p->diag.hospital.start.day = b;
		p->diag.hospital.start.hour = c;
		p->diag.hospital.start.minute = d;
		dates = caldates(p->diag.hospital.start, p->diag.hospital.end);
		if (dates <= 5) {
			if (p->diag.hospital.money < 1000) {
				printf("Ѻ��С��1000���������룺\n");
				newmoney = checkn(999, 10000000);
				while (newmoney % 100 != 0) {
					printf("Ѻ�𲻷���100������,��������\n");
					newmoney = checkn(999, 10000000);
				}
				printf("��ʼʱ���޸����\n");
			}
		}
		else {
			if (p->diag.hospital.money < dates * 200) {
				printf("Ѻ��С��200*�������������µ�Ѻ��\n");
				int r = dates * 200;
				newmoney = checkn(r, 10000000);
				while (newmoney % 100 != 0) {
					printf("Ѻ�𲻷���100������,��������\n");
					newmoney = checkn(r, 10000000);
				}
			}
			printf("��ʼʱ���޸����\n");
		}
	}
	if (h == 2) {
		int e, f, g, h;
		printf("����������·ݣ���ΧΪ1��12\n");
		e = checkn(1, 12);
		printf("������������ڣ�\n");
		f = checkn(1, monthday[e]);
		printf("���������Сʱ����ΧΪ0��23\n");
		g = checkn(0, 23);
		printf("������������ӣ���ΧΪ0��59\n");
		h = checkn(0, 59);
		p->diag.hospital.end.month = e;
		p->diag.hospital.end.day = f;
		p->diag.hospital.end.hour = g;
		p->diag.hospital.end.minute = h;
		dates = caldates(p->diag.hospital.start, p->diag.hospital.end);
		if (dates <= 5) {
			if (p->diag.hospital.money < 1000) {
				printf("Ѻ��С��1000���������룺\n");
				newmoney = checkn(999, 10000000);
				while (newmoney % 100 != 0) {
					printf("Ѻ�𲻷���100������,��������\n");
					newmoney = checkn(999, 10000000);
				}
				printf("��ʼʱ���޸����\n");
			}
		}
		else {
			if (p->diag.hospital.money < dates * 200) {
				printf("�������µ�Ѻ��\n");
				int l = dates * 200;
				newmoney = checkn(l, 10000000);
				while (newmoney % 100 != 0) {
					printf("Ѻ�𲻷���100������,��������\n");
					newmoney = checkn(l, 10000000);
				}
			}
			printf("����ʱ���޸����\n");
		}
	}
	if (h == 3) {
		printf("��ǰѺ��Ϊ��%.2f\n", p->diag.hospital.money);
		printf("�����µ�Ѻ��\n");
		dates = caldates(p->diag.hospital.start, p->diag.hospital.end);
		if (dates <= 5) {
			if (p->diag.hospital.money < 1000) {
				printf("Ѻ��С��1000���������룺\n");
				newmoney = checkn(999, 10000000);
				while (newmoney % 100 != 0) {
					printf("Ѻ�𲻷���100������,��������\n");
					newmoney = checkn(999, 10000000);
				}
				printf("Ѻ���޸����\n");
			}
		}
		else {
			if (p->diag.hospital.money < dates * 200) {
				printf("�������µ�Ѻ��\n");
				int o = dates * 200;
				newmoney = checkn(o, 10000000);
				while (newmoney % 100 != 0) {
					printf("Ѻ�𲻷���100������,��������\n");
					newmoney = checkn(o, 10000000);
				}
				printf("Ѻ���޸����\n");
			}
		}
	}
}

void modification(record* p, int n) {//�޸���Ϣ
	/*typedef doctor* doc;//���Ͷ���doctor*Ϊdoc
	doc r, r0;//������������
	r0 = NULL; r = dhead;//r0Ϊ��ָ�룬rΪͷָ��*/
	if (n == 1) //������Ϣ�޸�
	{
		int flag = 0;//��Ǳ���
		for (; flag != -1;) {
			printf_s("       ��(*>�n<*)�� ~(@^_^@)~ ��*+�n+*��~ (^_^)�ϡ���(*>�n<*)��\n\n");
			printf_s("          -----------------------------------------------\n");
			printf_s("         |   ��ѡ������Ҫ�޸ĵ���Ϣ���ͣ�                |\n");
			printf_s("         |1���޸Ļ�������                                |\n");
			printf_s("         |2���޸Ļ�������                                |\n");
			printf_s("         |3���޸Ļ���ID                                  |\n");
			printf_s("          -----------------------------------------------\n");
			printf_s("              ��ѡ�����������1��2��3����");
			int a;
			a = checkn(1, 3);
			switch (a) {
			case 1: {
				printf("���ߵ�ǰ����Ϊ%s\n", p->pati.name);
				printf("�����뻼��������");
				scanf_s("%[^\n]", p->pati.name, 20);
				getchar();
				printf("�����޸ĳɹ�,�Ƿ��޸Ļ���������Ϣ�� 1.�����޸� 2.�����޸�\n");
				int bxw;
				bxw = checkn(1, 2);
				if (bxw == 1)break;
				if (bxw == 2) {
					flag = -1;
					break;
				}

			}
			case 2: {
				printf("��ǰ����Ϊ%d\n", p->pati.age);
				printf("�����뻼�����䣺");
				p->pati.age = checkn(0, 250);
				printf("�����޸ĳɹ�,�Ƿ��޸Ļ���������Ϣ�� 1.�����޸� 2.�����޸�\n");
				int wzx;
				wzx = checkn(1, 2);
				if (wzx == 1)break;
				if (wzx == 2) {
					flag = -1;
					break;
				}
			}
			case 3: {
				printf("��ǰIDΪ%s\n", p->pati.ID);
				printf("�����뻼��ID��");
				scanf_s("%[^\n]", p->pati.ID, 20);
				printf("ID�޸ĳɹ�,�Ƿ��޸Ļ���������Ϣ�� 1.�����޸� 2.�����޸�\n");
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
			printf_s("        ��(*>�n<*)�� ~(@^_^@)~ ��*+�n+*��~ (^_^)�ϡ���(*>�n<*)��\n\n");
			printf_s("          ---------------------------------------------------\n");
			printf_s("         |   ��ѡ������Ҫ�޸ĵ���Ϣ���ͣ�                    |\n");
			printf_s("         |1���޸�ҽ������                                    |\n");
			printf_s("         |2���޸�ҽ������                                    |\n");
			printf_s("         |3���޸�ҽ������                                    |\n");
			printf_s("         |4���޸�ҽ������                                    |\n");
			printf_s("         |5���޸ĳ���ʱ��                                    |\n");
			printf_s("          ---------------------------------------------------\n");
			printf_s("              ��ѡ�����������1��2��3��4��5����");
			int b;
			b = checkn(1, 5);
			switch (b) {
			case 1: {
				printf("ҽ����ǰ����Ϊ%s\n", p->doct.name);
				printf("������ҽ�����ƣ�");
				scanf_s("%[^\n]", p->doct.name, 20);
				getchar();
				printf("�����޸ĳɹ�,�Ƿ��޸�ҽ��������Ϣ�� 1.�����޸� 2.�����޸�\n");
				int bxw;
				bxw = checkn(1, 2);
				if (bxw == 1)break;
				if (bxw == 2) {
					mark = -1;
					break;
				}
			}
			case 2: {
				printf("ҽ����ǰ����Ϊ%s\n", p->doct.profession);
				printf("������ҽ������");
				scanf_s("%[^\n]", p->doct.profession, 20);
				printf("�����޸ĳɹ�,�Ƿ��޸�ҽ��������Ϣ�� 1.�����޸� 2.�����޸�\n");
				int wzx;
				wzx = checkn(1, 2);
				if (wzx == 1)break;
				if (wzx == 2) {
					mark = -1;
					break;
				}
			}
			case 3: {
				printf("ҽ����ǰ����Ϊ%s\n", p->doct.room_num);
				printf("��ѡ��ҽ�����ң�\n");
				printf("1.������   2.�񾭿�   3�����   4.������\n");
				printf("5.�ǿ�   6.����   7.�����   8.�ۿ�\n");
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
				printf("�����޸ĳɹ�,�Ƿ��޸�ҽ��������Ϣ�� 1.�����޸� 2.�����޸�\n");
				int tj;
				tj = checkn(1, 2);
				if (tj == 1)break;
				if (tj == 2) {
					mark = -1;
					break;
				}
			}
			case 4: {
				printf("��ǰ����Ϊ%s\n", p->doct.num);
				printf("������ҽ�����ţ�");
				scanf_s("%[^\n]", p->doct.num, 20);
				printf("�����޸ĳɹ�,�Ƿ��޸�ҽ��������Ϣ�� 1.�����޸� 2.�����޸�\n");
				int zkj;
				zkj = checkn(1, 2);
				if (zkj == 1)break;
				if (zkj == 2) {
					mark = -1;
					break;
				}
			}
			case 5: {
				printf("��ѡ�����ʱ�䣺\n");
				printf("����һ��1.����   2.������\n");
				int aa;
				aa = checkn(1, 2);
				if (aa == 1) {
					p->doct.work_time[1] = '1';
				}
				if (aa == 2) {
					p->doct.work_time[1] = '0';
				}
				printf("���ڶ���1.����   2.������\n");
				int bb;
				bb = checkn(1, 2);
				if (bb == 1) {
					p->doct.work_time[2] = '1';
				}
				if (bb == 2) {
					p->doct.work_time[2] = '0';
				}

				printf("��������1.����   2.������\n");
				int cc;
				cc = checkn(1, 2);
				if (cc == 1) {
					p->doct.work_time[3] = '1';
				}
				if (cc == 2) {
					p->doct.work_time[3] = '0';
				}

				printf("�����ģ�1.����   2.�����n");
				int dd;
				dd = checkn(1, 2);
				if (dd == 1) {
					p->doct.work_time[4] = '1';
				}
				if (dd == 2) {
					p->doct.work_time[4] = '0';
				}

				printf("�����壺1.����   2.������ \n");
				int ee;
				ee = checkn(1, 2);
				if (ee == 1) {
					p->doct.work_time[5] = '1';
				}
				if (ee == 2) {
					p->doct.work_time[5] = '0';
				}

				printf("��������1.����   2.������\n");
				int ff;
				ff = checkn(1, 2);
				if (ff == 1) {
					p->doct.work_time[6] = '1';
				}
				if (ff == 2) {
					p->doct.work_time[6] = '0';
				}

				printf("�����գ�1.����   2.������\n");
				int gg;
				gg = checkn(1, 2);
				if (gg == 1) {
					p->doct.work_time[7] = '1';
				}
				if (gg == 2) {
					p->doct.work_time[7] = '0';
				}
				printf("����ʱ���޸ĳɹ�,�Ƿ��޸�ҽ��������Ϣ�� 1.�����޸� 2.�����޸�\n");
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
	if (n == 3) {//�����Ƽ�¼
		int t = 0;
		while (t != -1) {
			check* pc1;
			check* pc0;//����ָ�룬pcΪͷָ�룬pc0Ϊ��ָ�룬��ͬ
			medi* pm1;
			medi* pm0;
			pc0 = NULL, pc1 = p->diag.check;
			pm0 = NULL, pm1 = p->diag.medicine;
			printf_s("       ��(*>�n<*)�� ~(@^_^@)~ ��*+�n+*��~ (^_^)�ϡ���(*>�n<*)��\n\n");
			printf_s("          ---------------------------------------------------\n");
			printf_s("         |   ��ѡ������Ҫ�޸ĵ����Ƽ�¼���ͣ�                |\n");
			printf_s("         |1���޸ļ���¼                                    |\n");
			printf_s("         |2���޸Ŀ�ҩ��¼                                    |\n");
			printf_s("         |3���޸�סԺ��¼                                    |\n");
			printf_s("          ---------------------------------------------------\n");
			printf_s("              ��ѡ�����������1��2��3����");
			int d;
			d = checkn(1, 3);
			switch (d) {
			case 1: {
				while (pc1->next != NULL) {
					printf("��ǰ������ƣ�%s\n", pc1->name);
					printf("��ǰ����%.2f\n", pc1->money);
					printf("�Ƿ��޸�: 1.�޸�  2.����\n");
					int aaa;
					aaa = checkn(1, 2);
					if (aaa == 1) {
						changecheck(pc1, p);
						printf("�޸ĳɹ�\n");
						printf("�Ƿ�����޸ı�����¼�� 1.�޸�  2.����\n");
						int aaaa;
						aaaa = checkn(1, 2);
						if (aaaa == 1) {
							changecheck(pc1, p);
						}
						else {
							printf("����¼�޸Ľ���\n");
						}

						pc0 = pc1;
						pc1 = pc1->next;

					}
					else {
						pc0 = pc1;
						pc1 = pc1->next;
					}
				}
				printf("�Ƿ��޸ĸû����������Ƽ�¼�� 1.�����޸�  2.�����޸�\n");
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
					printf("��ǰҩƷ���ƣ�%s\n", pm1->name);
					printf("��ǰҩƷ��%.2f\n", pm1->money);
					printf("�Ƿ��޸�: 1.�޸�  2.����\n");
					int bbb;
					bbb = checkn(1, 2);
					if (bbb == 1) {
						changemedicine(pm1, p);
						printf("�޸ĳɹ�\n");
						printf("�Ƿ�����޸ı�����¼�� 1.�޸�  2.����\n");
						int aaaa;
						aaaa = checkn(1, 2);
						if (aaaa == 1) {
							changemedicine(pm1, p);
						}
						else {
							printf("����¼�޸Ľ���\n");
						}
						pm0 = pm1;
						pm1 = pm1->next;
					}
					else {
						pm0 = pm1;
						pm1 = pm1->next;
					}
				}
				printf("�Ƿ��޸ĸû����������Ƽ�¼�� 1.�����޸�  2.�����޸�\n");
				int m;
				m = checkn(1, 2);
				if (m == 1)break;
				if (m == 2) {
					t = -1;
					break;
				}


			}
			case 3: {
				printf("��ǰסԺ��¼��ʼʱ�䣺%d��%d��%dʱ%d��\n", p->diag.hospital.start.month, p->diag.hospital.start.day, p->diag.hospital.start.hour, p->diag.hospital.start.minute);
				printf("��ǰסԺ��¼����ʱ�䣺%d��%d��%dʱ%d��\n", p->diag.hospital.end.month, p->diag.hospital.end.day, p->diag.hospital.end.hour, p->diag.hospital.end.minute);
				printf("��ǰסԺ��¼Ѻ��%.2f\n", p->diag.hospital.money);
				printf("�Ƿ��޸ı�����¼: 1.�޸�  2.����");
				int h;
				h = checkn(1, 2);
				if (h == 1) {
					changehosp(p);
					printf("�޸ĳɹ�\n");
					printf("�Ƿ�����޸ı�����¼�� 1.�޸�  2.����\n");
					int hhhh;
					hhhh = checkn(1, 2);
					if (hhhh == 1) {
						changehosp(p);
					}
					else {
						printf("����¼�޸Ľ���\n");
					}
				}
				else {
					printf("����¼�޸Ľ���\n");
				}
				printf("�Ƿ��޸ĸû����������Ƽ�¼�� 1.�����޸�  2.�����޸�\n");
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
void change_record() {                  //�޸ļ�¼����

	char patiID[20];
	printf("�����뻼��ID��\n");
	scanf("%s", patiID);
	record* p;
	record* p0; //������������
	p0 = NULL; p = head;//p0Ϊ��ָ�룬pΪͷָ��

	/*typedef doctor* doc;//���Ͷ���doctor*Ϊdoc
	doc r, r0;//������������
	r0 = NULL; r = dhead;//r0Ϊ��ָ�룬rΪͷָ��*/

	while (p != NULL && (strcmp(p->pati.ID, patiID) != 0)) {   // �ҵ����޸ĵ�������¼��Ӧ�Ľڵ�
		p0 = p; p = p->next;
	}

	if (p != NULL) {
		int s;
		print_Record(p);
		printf("�û��ߵļ�¼���ҵ������Ƿ�Ҫ�޸ļ�¼��1Ϊ�޸ģ�2Ϊ���䣩��\n");
		s = checkn(1, 2);
		switch (s) {
		case 1: {
			int x = 0;
			int q;
			for (; x != -1;) {
				printf_s("      ��(*>�n<*)�� ~(@^_^@)~ ��*+�n+*��~ (^_^)�ϡ���(*>�n<*)��\n\n");
				printf_s("          -----------------------------------------------\n");
				printf_s("         |   ��ѡ������Ҫ�޸ĵ���Ϣ���ͣ�                |\n");
				printf_s("         |1���޸Ļ��������Ϣ                            |\n");
				printf_s("         |2���޸�ҽ�������Ϣ                            |\n");
				printf_s("         |3���޸����Ƽ�¼                                |\n");
				printf_s("          -----------------------------------------------\n");
				printf_s("              ��ѡ�����������1��2��3����");

				int a;
				a = checkn(1, 3);
				modification(p, a);
				printf("�Ƿ�Ҫ�����޸ı���¼����Ϣ�� 1.�����޸� 2.�޸Ľ���\n ");
				q = checkn(1, 2);
				if (q == 1) break;
				if (q == 2) {
					x = -1;
					break;
				}
			}
			int t;
			printf("������1Ϊ�����޸��������ߵļ�¼��Ϣ��2Ϊ�����޸�:\n");
			t = checkn(1, 2);
			if (t == 1) change_record();
			else {
				printf("�޸Ĳ�������\n");
				save();//�������е����Ƽ�¼������ļ���ȥ
				return;
			}
		}
		case 2: {
			printf("�޸Ľ���\n");
			return;
		}
		}
	}
	else {
		printf("�������\n");
		int s;
		printf("������1Ϊ�����޸ģ�2Ϊ�����޸�:");
		s = checkn(1, 2);
		if (s == 1) change_record();
		else {
			printf("�޸Ľ���\n");
			return;
		}
	}
}

//�޸ļ�¼����



//ͳ��Ӫҵ��
double sum_Total(record* head)
{
	double sum = 0;


	return sum;
}


// ͳ��ҽ������������ʱ��
void print_Doc_day(record* head)
{
	char job_id_array[100][20]; //���������100��ҽ��
	int index = 0;
	record* tempptr = (record*)malloc(sizeof(record)); //���ڵڶ������
	tempptr = head;
	while (tempptr != NULL) //������ҽ��id�Ž�����job_id_array
	{
		char temp[20];
		strcpy(temp, tempptr->doct.num);
		int add_flag = 1;
		for (int i = 0; i < index; i++)
		{
			if (strcmp(job_id_array[i], temp) == 0)  //����ҵ�����ȵľ�����
			{
				add_flag = 0; break;
			}
		}
		if (add_flag)
		{
			strcpy(job_id_array[index++], temp); //���ַ���temp������job_id_array
		}
		tempptr = tempptr->next;
	}
	tempptr = head;
	int s_index = 0;//���Ƶڶ������
	printf("\n--------------------ҽ����Ϣ--------------\n");
	while (tempptr != NULL)
	{
		if (strcmp(tempptr->doct.num, job_id_array[s_index]) == 0)
		{
			printf("��%dλҽ��\n", s_index + 1);
			printf("ҽ������:%s\n", tempptr->doct.num);
			printf("ҽ������:%s\n", tempptr->doct.name);
			printf("ҽ������:%s\n", tempptr->doct.room_num);
			printf("ҽ���ȼ�:%s\n", tempptr->doct.profession);
			//printf("ҽ������ʱ�䣨��09��00-21��00��:%d", tempptr->doct.job_time);
			printf("ҽ����������:");
			for (int i = 1; i < 8; i++)
			{
				if (tempptr->doct.work_time[i])
				{
					printf("��%d ", i);
				}
				//printf("%d", tempptr->doct.work_time[i]);
			}
			printf("�ϰ�\n");
			s_index++;
		}
		tempptr = tempptr->next;
	}
	getchar();
}
void searchRoom(record* head)
{
	printf("������Ҫ���ҵĿ���:");
	char s_room[11];
	scanf("%s", &s_room);
	char room_id[100][11]; //����100������
	int nn = 1;//��ʾ��һ�����
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
		printf("\n�ÿ��Ҳ����ڣ���ÿ���û��ҽ�������Enter����...\n");
	}
}
void searchDoctor(record* head) //��������ṩ������ȷ��Ψһҽ�������������ָ�ֱ�ۣ�������˵
{
	printf("������Ҫ���ҵ�ҽ��:");
	char s_doc[20];
	scanf("%s", &s_doc);
	printf("�������ҽ���Ĺ���(��ֹ����),����֪������0:");
	char s_num[11];
	scanf("%s", &s_num);
	int nn = 1;//��ʾ��һ�����
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
		printf("û���ҵ�����������ҽ��...");
	}
}
void searchPat(record* head)
{
	printf("������Ҫ���ҵĲ���:");
	char s_pat[20];
	scanf("%s", &s_pat);
	printf("������ò��˵�ID:����֪������0:");
	char regnumber[20];
	scanf("%s", &regnumber);
	int nn = 1;//��ʾ��һ�����
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
		printf("û���ҵ����������Ĳ���..");
	}
}

//��Ѱһ��ʱ��ĹҺ���Ϣ
void out_Timerange(record* head)
{
	int flag = 1;
	char begin[20];
	char end[10];
	while (flag)
	{
		printf("������Ҫ���ҵ���ʼʱ�䣺��10041112 ��ʾ10��4��11ʱ12�ֵĹҺ���Ϣ����Ҫ�淶һ��һĿ��Ȼ��\n");
		scanf("%s", &begin);
		flag = 0;
		if (strlen(begin) > 8)
		{
			flag = 1;
			printf("\n������������������..\n");
			continue;
		}
		for (int i = 0; i < 8; i++)//���������Ƿ�Ϸ�
		{
			if (begin[i] < '0' || begin[i]>'9')
			{
				flag = 1;
				printf("\n������������������..\n");
				break;
			}
		}
		int month = (begin[0] - '0') * 10 + begin[1] - '0';//��ȡ�·�
		int day = (begin[2] - '0') * 10 + begin[3] - '0';  //��ȡ����
		int hour = (begin[4] - '0') * 10 + begin[5] - '0';  //��ȡʱ
		int min = (begin[6] - '0') * 10 + begin[7] - '0';  //��ȡʱ
		if (!(month <= 12 && month >= 1)) {
			flag = 1;
			printf("�������룺�·�Ӧ��1~12 \n"); continue;
		}
		if (!(day <= dayofmon[month] && day >= 1)) {
			flag = 1;
			printf("�������룺�����޴����� \n"); continue;
		}
		if (!(hour <= 23 && hour >= 0)) {
			flag = 1;
			printf("�������룺СʱӦ��0~23 \n"); continue;
		}
		if (!(min <= 59 && min >= 0)) {
			flag = 1;
			printf("�������룺СʱӦ��0~59 \n"); continue;
		}

	}
	flag = 1;
	while (flag)
	{
		printf("������Ҫ���ҵ���ֹʱ�䣺��10041213 ��ʾ10��4��12ʱ13�ֵĹҺ���Ϣ����Ҫ�淶һ��һĿ��Ȼ��\n");
		scanf("%s", &end);
		flag = 0;
		if (strlen(end) > 8)
		{
			flag = 1;
			printf("\n������������������..\n");
			continue;
		}
		for (int i = 0; i < 8; i++)//���������Ƿ�Ϸ�
		{
			if (end[i] < '0' || end[i]>'9')
			{
				flag = 1;
				printf("\n������������������..\n");
				break;
			}
		}
		int month = (end[0] - '0') * 10 + end[1] - '0';//��ȡ�·�
		int day = (end[2] - '0') * 10 + end[3] - '0';  //��ȡ����
		int hour = (end[4] - '0') * 10 + end[5] - '0';  //��ȡʱ
		int min = (end[6] - '0') * 10 + end[7] - '0';  //��ȡʱ
		if (!(month <= 12 && month >= 1)) {
			flag = 1;
			printf("�������룺�·�Ӧ��1~12 \n"); continue;
		}
		if (!(day <= dayofmon[month] && day >= 1)) {
			flag = 1;
			printf("�������룺�����޴����� \n"); continue;
		}
		if (!(hour <= 23 && hour >= 0)) {
			flag = 1;
			printf("�������룺СʱӦ��0~23 \n"); continue;
		}
		if (!(min <= 59 && min >= 0)) {
			flag = 1;
			printf("�������룺СʱӦ��0~59 \n"); continue;
		}
	}

	int index = 1;//���������
	while (head != NULL)
	{
		char reg[10];
		for (int i = 0; i < 8; i++)
		{
			reg[i] = head->pati.registration[5 + i];//��ȡ�Һ�����ʱ��
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
		printf("û���ҵ���ص�������Ϣ,�볢���ٴβ�ѯ...");
	}
}

/*void statistics_money() {                        //ͳ��Ӫҵ�����סԺ����
	totalmoney = 0;
	record* p;
	p = head;
	while (p != NULL) {
		totalmoney = (totalmoney + p->diag.money_ch + p->diag.money_me + p->diag.hospital.money);
		p = p->next;
	}
	decorate();
	int d = totalmoney * 100;
	int c = d % 10; d = d / 10;//��
	int b = d % 10; d = d / 10;//��
	printf("��Ӫ�ʽ�Ϊ��%dԪ%d��%d��\n", d, b, c);  //��ӡӪҵ��
}*/

void statistics_1() {        //����סԺ����

	Record* p, *p0;  //������������
	p0 = NULL;
	p = head;  //p0Ϊ��ָ�룬pΪͷָ��
	int days = 0;//סԺ����
	int start, end;
	int time_t;
	int month, day, hour, minute;

	while (p != NULL) {
		days = caldates(p->diag.hospital.start, p->diag.hospital.end);
		totalmoney = (totalmoney + p->diag.money_ch + p->diag.money_me + days * 200);
		p0 = p;
		p = p->next;
	}
	printf("Ӫҵ��Ϊ��%.2lf\n", totalmoney);  //��ӡӪҵ��
	int i;  //����һ��������Ϊ�Ƿ��ӡסԺ����ĸ���
	printf("�Ƿ�����סԺ����������1Ϊ�ǣ�����2Ϊ�񣩣�\n");
	i = checkn(1, 2); //����i
	if (i == 1) {  //���i=1
		printf("���䵱ǰʱ��:\n");
		printf("�£�");
		month = checkn(1, 12);
		printf("�գ�");
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
			day = checkn(1, 31);
		}
		if (month == 4 || month == 6 || month == 9 || month == 11) {
			day = checkn(1, 30);
		}
		if (month == 2) {
			day = checkn(1, 29);
		}
		printf("ʱ��");
		hour = checkn(0, 23);
		printf("�֣�");
		minute = checkn(0, 59);
		time_t = month * 1000000 + day * 10000 + hour * 100 + minute;//�洢��ǰʱ��
		Record* r, *r0;//������������
		r0 = NULL; r = head;//r0Ϊ��ָ�룬rΪͷָ��
		printf("    ---------------------------------------------------------------------------------------------------------\n");
		printf("   |����ID    |����       |����   | �Һ�              | ��ʼʱ��            | ����ʱ��             |���     | \n");
		printf("    ---------------------------------------------------------------------------------------------------------\n");  //��ӡסԺ����˳��ΪID�����֣��Һţ�ʱ�䣬���
		while (r != NULL) {
			if (((r->diag.hospital.start.month * 1000000 + r->diag.hospital.start.day * 10000 + r->diag.hospital.start.hour * 100 + r->diag.hospital.start.minute) <= time_t) && (time_t <= (r->diag.hospital.end.month * 1000000 + r->diag.hospital.end.day * 10000 + r->diag.hospital.end.hour * 100 + r->diag.hospital.end.minute))) {

				days = 0;
				days = caldates(r->diag.hospital.start, r->diag.hospital.end);
				printf("   | %-8s | %-10s| %-4d  | %-15s   |%d��%d��%dʱ%d��      |%d��%d��%dʱ%d��      |%.2lf   |\n", r->pati.ID, r->pati.name, r->pati.age, r->pati.registration, r->diag.hospital.start.month, r->diag.hospital.start.day, r->diag.hospital.start.hour, r->diag.hospital.start.minute, r->diag.hospital.end.month, r->diag.hospital.end.day, r->diag.hospital.end.hour, r->diag.hospital.end.minute, 200.00 * days);
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
	printf(" �� �� �� �� �� ֮ Դ ");
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
		printf("               ��ѡ����Ҫִ�еĹ��ܣ� \n");
		printf("               1.¼�����Ƽ�¼ \n");
		printf("               2.�����ļ� \n");
		printf("               3.�����ļ� \n");
		printf("               4.���������Ϣ \n");
		printf("               5.ɾ�����Ƽ�¼ \n");
		printf("               6.�޸����Ƽ�¼ \n");
		printf("               7.ͳ��ҽ���������� \n");
		printf("               8.���ҿ��� \n");
		printf("               9.����ҽ����Ϣ \n");
		printf("               10.���Ҳ�����Ϣ \n");
		printf("               11.����һ��ʱ���������Ϣ \n");
		printf("               12.ͳ����Ӫ�ʽ� \n");
		printf("               0.�˳�ϵͳ \n");
		scanf("%d", &choice);
		while (choice < 0 || choice>12) {
			printf("               �r(�s���t)�q �޴�ѡ����������� \n");
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
	printf("               ��л��ʹ�ñ�ϵͳ�� \n");
}

void main()
{
	//read();//��ϵͳ���ȶ����ļ�����
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


	int n = 0;//n�������
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
		printf_s("         |  ��ѡ���������           |\n");
		printf_s("         |1����ѯ��Ϣ                |\n");
		printf_s("         |2����ȷ�޸ļ�¼            |\n");
		printf_s("         |3�������޸ļ�¼            |\n");
		printf_s("         |4�����Ӽ�¼/ɾ����¼       |\n");
		printf_s("         |5��ͳ����Ϣ                |\n");
		printf_s("         |6��������Ϣ                |\n");
		printf_s("         |7����ȡ��Ϣ                |\n");
		printf_s("         |#���˳�����                |\n");
		printf_s("          ---------------------------\n");
		printf_s("          ��ѡ�����������1��2��#����");//����#����-1
		int m;
		m = checkn(1, 7);

		switch (m)
		{
			//m=1��ѯ��Ϣ
		case 1:
		{
			printf_s("\n\n~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~\n");
			printf_s("~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~\n");
			printf_s("\n                Я�ֹ�������δ��!\n\n");
			printf_s("~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~\n");
			printf_s("~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~~(@^_^@)~\n\n");
			int n1 = 0;
			for (; n1 != -1;)
			{
				n1 = 0;
				printf_s("          ---------------------------\n");
				printf_s("         |  ��ѡ�����               |\n");
				printf_s("         |1����ѯ�������Ƽ�¼        |\n");
				printf_s("         |2����ѯ����������Ϣ        |\n");
				printf_s("         |3����ѯҽ��������Ϣ        |\n");
				printf_s("         |#��������һ��              |\n");
				printf_s("          ---------------------------\n");
				printf_s("           ��ѡ�����������1��2��3��#����");
				n = checkn(1, 3);
				switch (n)
				{
				case 1:
				{
					system("cls");
					searchPat(head);
					getchar();
					break;//����switchn
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
					break;//����switchn
				}
				}
			}
			break;//����switchm
		}
		//------------------------------------------------------------------------------------------------
		//m=2 �޸�
		case 2:
		{
			printf(" ���������������#������һ��(����Ϊ�ύ����ʱ�䣺20201018)��");
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
			printf(" ���������������#������һ��(����Ϊ�ύ����ʱ�䣺20201018)��");
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
			printf("���������������#������һ��(����Ϊ�ύ����ʱ�䣺20201018)��");
			int key;
			key = checkn(20201018, 20201018);
			if (key == -1)
			{
				break;
			}
			int mm = 0;
			for (; key == 20201018 && mm != -1;) {
				mm = 0;
				int q2 = 0;//�ò�switch�������
				//�����ͬ���ִ���ͬ����   ������־��
				printf_s("********************************************************\n");
				printf_s("��(*>�n<*)�� ~(@^_^@)~ ��*+�n+*��~ (^_^)�ϡ���(*>�n<*)��\n\n");
				printf_s("          ---------------------------\n");
				printf_s("         |  ��ѡ�����:               |\n");
				printf_s("         |1�����Ӽ�¼                 |\n");
				printf_s("         |2��ɾ����¼                 |\n");
				printf_s("         |#��������һ��               |\n");
				printf_s("          ---------------------------\n");
				printf_s("         ��ѡ�����������1��2��#����");
				printf_s("\n  -(=@__@=)--(=@__@=)--(=@__@=)--(=@__@=)--(=@__@=)-\n\n");
				//|\n|1������|\n|3��ɾ��|\n|-1��������һ��/��������|\
				//�����Ƿ���������ȷ������
				q2 = checkn(1, 2);
				//��ѡ��Ĳ�������
				switch (q2) {
				case 1: {
					system("cls");
					wirte();
					printf("�����ɹ����Ƿ�Ҫ����������  1.����  2.����\n");
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
					printf("�����ɹ����Ƿ�Ҫ����������  1.����  2.����\n");
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
				printf_s("��(*>�n<*)�� ~(@^_^@)~ ��*+�n+*��~ (^_^)�ϡ���(*>�n<*)��\n\n");
				printf_s("          --------------------------------------\n");
				printf_s("         |  ��ѡ�����:                         |\n");
				printf_s("         |1��ͳ��Ӫҵ�����סԺ����           |\n");
				printf_s("         |2��ͳ��ҽ�������������æ��           |\n");
				printf_s("         |3��ͳ��ĳ��ʱ�䷶Χ���������         |\n");
				printf_s("         |#��������һ��                         |\n");
				printf_s("          --------------------------------------\n");
				printf_s("         ��ѡ�����������1��2��3��#����");
				printf_s("\n  -(=@__@=)--(=@__@=)--(=@__@=)--(=@__@=)--(=@__@=)-\n\n");
				q4 = checkn(1, 3);
				switch (q4) {
				case 1: {
					system("cls");
					statistics_1();
					printf("�����ɹ���\n");
					nn = -1;
					break;
				}
				case 2: {
					system("cls");
					print_Doc_day(head);
					printf("�����ɹ���\n");
					nn = -1;
					break;
				}
				case 3: {
					system("cls");
					out_Timerange(head);
					printf("�����ɹ����Ƿ�Ҫ����ͳ�Ʊ�ķ�Χ��  1.����  2.����\n");
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
				//-1ʱ�˳�����
		case -1:
		{
			//�ͷ�����ڵ�
			p1 = head->next;     //�ͷż�¼����ڵ�
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

	//�ͷ�����ڵ�
	p1 = head->next;     //�ͷ���ʷ��¼����ڵ�
	while (p1 != NULL)
	{
		p2 = p1;
		p1 = p1->next;
		free(p2);
	}
	system("pause");
	return 0;
}






