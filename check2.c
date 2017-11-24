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

	setSign(a, 1);
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
	int copy;

	for(i = 0; i < KETA; i++)
		b->n[i] = a->n[i];

	copy = getSign(a);
	setSign(b, copy);
}

//絶対値を返す関数
void getAbs(struct NUMBER *a, struct NUMBER *b)
{
	int i;

	for(i = 0; i < KETA; i++)
		b->n[i] = a->n[i];

	setSign(a, 1);
}

//ゼロか否かの判定　ゼロなら０を返し、それ以外は-1を返す
int isZero(struct NUMBER *a)
{
	int i;
	int ret = 0;     //return用の関数

	if(getSign(a) < 0)
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

//多倍長変数を交換する関数
void swap(struct NUMBER *a, struct NUMBER *b)
{
	int temp;   //値の保持用
	int i;

	for (int i = 0; i < KETA; i++)
	{
		temp = a->n[i];
		a->n[i] = b->n[i];
		b->n[i] = temp;
	}

	temp = getSign(a);
	setSign(a, getSign(b));
	setSign(b, temp);
}

//多倍長変数にint型変数の値を設定
int setInt(struct NUMBER *a, int x)
{
	int i;
	int rem;   //余りを格納
	int ret = 0;   //return用
	int check = 0;   //桁数のチェック

	clearByZero(a);

	if(x < 0)
	{
		setSign(a, -1);
		x = abs(x);
	}

	for (int i = 0; i < KETA; i++)
	{
		rem = x % 10;
		x = x / 10;
		a->n[KETA - i - 1] = rem;
		check++;
	}

	if(check > KETA)
		ret = -1;

	return ret;
}

//int型変数に多倍長変数の値を設定
int getInt(struct NUMBER *a, int *x)
{
	*x = 0;
	int i;
	int ret = 0;   //return用
	int check = 0;   //桁数のチェック
	int checkX = 0;   //ｘの符号

	if(getSign(a) == -1)
		checkX = -1;

	for(i = 0; i < KETA; i++)
	{
		*x += a->n[i];
		*x *= 10;
	}
	*x /= 10;

	if(checkX == -1)
		*x *= checkX;

	if(x < -2147483648 || x > 2147483647)
		ret = -1;

	return ret;
}

//多倍長変数の符号を s=1で正に、s=-1で負にする
void setSign(struct NUMBER *a, int s)
{
	if(s == 1)
		a->sign = 1;
	if(s == -1)
		a->sign = -1;
}

//符号が正なら 1 、負なら -1 を返す
int getSign(struct NUMBER *a)
{
	int ret;

	if(a->sign >= 0 )
		ret = 1;
	if(a->sign < 0)
		ret = -1;

	return ret;
}

//２つの多倍長変数の大小比較
int numComp(struct NUMBER *a, struct NUMBER *b)
{
	int ret;
	int i;

	// a > 0 && b < 0 
	if(getSign(a) == 1 && getSign(b) == -1)
		ret = 1;

	// a < 0 && b > 0
	if(getSign(a) == -1 && getSign(b) == 1)
		ret = -1;

	// a > 0 && b > 0
	if(getSign(a) == 1 && getSign(b) == 1)
	{
		for(i = KETA - 1; i >= 0; i--)
		{
			if(a->n[i] > b->n[i])
			{
				ret = 1;
				break;
			}
		}
	}

	// a < 0 && b < 0
	if(getSign(a) == -1 && getSign(b) == -1)
	{
		for(i = KETA - 1; i >=	 0; i--)
		{
			if(a->n[i] < b->n[i])
			{
				ret = -1;
				break;
			}
		}
	}

	return ret;
}

int main(int argc, char **argv)
{
	struct NUMBER a, b;
	int r;

	//setInt() Test
	setInt(&a, -12345);
	printf("a = ");
	dispNumber(&a);
	printf("\n");

	//setSign() Test
	copyNumber(&a,&b);
	setSign(&b, 1);
	printf("b = ");
	dispNumber(&b);
	printf("\n");

	//getInt() Test
	r = getSign(&b);
	printf("getSign() = %d\n", r);

	//numComp() Test
	r = numComp(&a,&b);
	printf("numComp() = %d\n", r);

	return 0;	
}