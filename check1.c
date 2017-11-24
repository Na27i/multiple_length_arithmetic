#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define KETA 30

struct NUMBER
{
	int n[KETA];     //各桁の値
	int sign;     //符号変数
};

//ゼロクリアする関数
void clearByZero(struct NUMBER *a)
{
	int i;

	for(i = 0; i < KETA; i++)
	{
		a->n[i] = 0;
	}

	a->sign = 1;
}

//表示用の関数
void dispNumber(struct NUMBER *a)
{
	int i;

	if(a->sign == 1)
		printf("+");
	else
		printf("-");

	for(i = 0; i < KETA; i++)
	{
		printf("%2d", a->n[i]);
	}
}

//ランダムで代入
void setRnd(struct NUMBER *a, int k)
{
	srand(time(NULL));

	int i;
	{
		for (i = 1; k + 1 > i; i++)
			a->n[KETA - i] = rand() % 10;
	}
}

//コピーを行う関数
void copyNumber(struct NUMBER *a, struct NUMBER *b)
{
	int i;

	for(i = 0; i < KETA; i++)
		b->n[i] = a->n[i];
}

//絶対値を返す関数
void getAbs(struct NUMBER *a, struct NUMBER *b)
{
	int i;

	for(i = 0; i < KETA; i++)
		b->n[i] = a->n[i];

	b->sign = 1;
}

//ゼロか否かの判定　ゼロなら０を返し、それ以外は-1を返す
int isZero(struct NUMBER *a)
{
	int i;
	int ret = 0;     //return用の関数

	if(a->sign < 0)
		return -1;

	for(i = 0; i < KETA; i++)
	{
		if(a->n[i] != 0)
			return -1;
	}

	return ret;
}

//多倍超変数の10倍を行う関数　正常終了で０、オーバーフローで-1
int mulBy10(struct NUMBER *a, struct NUMBER *b)
{
	int i;
	int ret = 0;     //return用の関数

	for(i = 0; i < KETA -1; i++)
	{
		if(a->n[0] != 0)
			ret = -1;

		b->n[i] = a->n[i + 1];
	}

	b->n[KETA - 1] = 0;

	return ret;
}

//多倍超変数の10分の1倍を行う関数　返り値は余り
int divBy10(struct NUMBER *a, struct NUMBER *b)
{
	int i;
	int ret = a->n[KETA - 1];     //return用の関数

	for(i = KETA - 1; i > 0; i--)
	{
		b->n[i] = a->n[i - 1];
	}

	b->n[0] = 0;

	return ret;
}

int main(void)
{

	struct NUMBER a,b,c,d,e;
	int r;     //チエック用の関数

	clearByZero(&a);
	printf("a = ");
	dispNumber(&a);
	printf("\n");

	clearByZero(&b);
	setRnd(&b, 10);
	printf("b = ");
	dispNumber(&b);
	printf("\n");


	copyNumber(&b, &c);
	printf("c = ");
	dispNumber(&c);
	printf("\n");

	r = mulBy10(&c, &d);
	printf("d = ");
	dispNumber(&d);
	printf(" ,r = %d\n" ,r);


	r = divBy10(&c, &e);
	printf("e = ");
	dispNumber(&e);
	printf(" ,r = %d\n" ,r);

	printf("a == 0? -->%d\n", isZero(&a));
	printf("b == 0? -->%d\n", isZero(&b));
	printf("c == 0? -->%d\n", isZero(&c));
	printf("d == 0? -->%d\n", isZero(&d));
	printf("e == 0? -->%d\n", isZero(&e));

	return 0;
}