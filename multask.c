#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

#define KETA  251
#define RADIX 10000

struct timeval tv;
double tstart, tend;

struct{
	int n[KETA];     //各桁の値
} typedef NUMBER;

// ゼロクリアする関数
//   a： ゼロクリアしたい多倍長変数
void clearByZero(NUMBER *a){
	int i;

	for(i = 0; i < KETA; i++)
	{
		a->n[i] = 0;
	}
}

// ゼロか否かの判定(ゼロのとき：０　それ以外：－１)
//   a： 判定したい多倍長変数
int isZero(NUMBER *a){
	int i;

	for(i = 0; i < KETA; i++)
	{
		if(a->n[i] != 0)
			return -1;
	}

	return 0;
}

// 表示用の関数
//   a： 表示したい多倍長変数
void dispNumber(NUMBER *a){
	int i;

	printf("ans = %04d.\n", a->n[KETA-1]);
	for(i = KETA - 2; i >= 0; i--)
	{
		printf(" %04d", a->n[i]);
	}
}

// ２つの多倍長変数の大小比較(aが大きい：１　ｂが大きい：－１　一緒：０)
//   a： 比較する多倍長変数
//   b： 比較する多倍長変数
int numComp(NUMBER *a, NUMBER *b){
	int i;

	for(i = KETA - 1; i >= 0; i--)
	{
		if(a->n[i] > b->n[i])
		{
			return 1;
		}
		else if(a->n[i] < b->n[i])
		{
			return -1;
		}
	}

	return 0;
}

// 桁数の確認(返り値：桁数)
//   a： 確認したい多倍長変数
int KETAcheck(NUMBER *a){
	int i;   //ループ用

	for(i = 0; i < KETA - 1; i++){
		if(i < KETA - 3){
			if(a->n[i] == 0 && a->n[i + 1] == 0 && a->n[i + 2] == 0)
				return i;
		}else if(i == KETA - 2){
			if(a->n[i] == 0 && a->n[i + 1] == 0)
				return i;
		}else if(i == KETA - 1){
			if(a->n[i] == 0)
				return i;
		}
	}
	return -1;
}

// 多倍長変数に int 型変数の値を設定
//   a： 設定したい多倍長変数
//   x： 設定したい int 型変数
int setInt(NUMBER *a, int x)
{
	int i;
	int rem;   //余りを格納
	int ret = 0;   //return用
	int check = 0;   //桁数のチェック

	clearByZero(a);

	for (i = 0; i < KETA; i++)
	{
		rem = x % RADIX;
		x = x / RADIX;
		a->n[i] = rem;
		check++;
	}

	if(check > KETA)
		ret = -1;

	return ret;
}

// コピーを行う関数
//   a： コピー元の多倍長変数
//   b： コピー先の多倍長変数
void copyNumber(NUMBER *a, NUMBER *b){
	int i;

	for(i = 0; i < KETA; i++)
		b->n[i] = a->n[i];
}


// 多倍超変数の加算(成功：１　失敗：－１)/
//   a： 足される側の多倍長変数
//   b： 足す側の多倍長変数
//   c： ふたつの多倍長変数の和
int add (NUMBER *a, NUMBER *b, NUMBER *c)
{
	int i;   //forループ用
	int keta = 0;   //桁上がり
	int ret = 1;   //return用

    //初期化
	clearByZero(c);

	//最上位を足して10を超えれば終了
	if(a->n[KETA-1] + b->n[KETA-1] >= RADIX)
	{
		ret = -1;
		return ret;
	}

	//最下位の桁から足し算
	for(i = 0; i < KETA; i++){
		c->n[i] = a->n[i] + b->n[i] + keta;

		//桁上がり
		if(c->n[i] >= RADIX){
			keta = 1;
			c->n[i] -= RADIX;
		}
		else{
			keta = 0;
		}

		if(c->n[KETA-1] >= RADIX)
		{
			ret = -1;
			return ret;
		}
	}
	return ret;
}

// 多倍長変数の減算　両方正のみ(成功：１　失敗：－１)
//   a： 計算する値
//   b： 計算する値
//   c： 差
int sub(NUMBER *a, NUMBER *b, NUMBER *c)
{
	int i;   //forループ用
	int keta = 0;   //桁下がり用

	//cの初期化
	clearByZero(c);

	// a = b
	if(numComp(a, b) == 0 || numComp(a,b) == -1){
		return -1;
	}

	//最下位の桁から引き算
	for(i = 0; i < KETA; i++){
		c->n[i] = a->n[i] - b->n[i] - keta;

		//桁下がり
		if(c->n[i] < 0){
			keta = 1;
			c->n[i] += RADIX;
		}
		else{
			keta = 0;
		}
	}
	return 1;
}

// 多倍長変数の１０倍を行う(正常終了：０　オーバーフロー：－１)
//   a： かける前の多倍長変数
int mulBy10(NUMBER *a)
{
	int i;
	int keta = 0;

	if(a->n[KETA-1] >= 1000)
		return -1;

	for(i = 0; i <= KETA-1; i++)
	{
		a->n[i] = a->n[i] * 10 + keta;
		keta = 0;
		
		if(a->n[i] >= RADIX)
		{
			keta = a->n[i] / RADIX;
			a->n[i] %= RADIX;
		}
	}
	return 0;
}

// 多倍超変数の10分の1倍を行う関数(正常終了：０)
//  a： 多倍長変数
int divBy10(NUMBER *a)
{
	int i;
	int keta = 0;
	int keep;

	for(i = KETA-1; i >= 0; i--)
	{
		keep = a->n[i] % 10;
		a->n[i] = a->n[i] / 10 + keta * 1000;
		keta = keep;
	}
	return 0;
}

// 多倍長変数の除算(成功：１　失敗・０で割る：－１)
//   a ： 割られる側 
//   b ： 割る側
//   c ： 商
int divide(NUMBER *a, NUMBER *b, NUMBER *c, NUMBER *d)
{
	NUMBER sa, e, tmp;

	clearByZero(c);

	if (isZero(b) == 0)
		return -1;

	copyNumber(a, &sa);

	while (1)
	{
		if (numComp(&sa, b) == -1)
			break;
		copyNumber(b, d);
		setInt(&e, 1);
		while (1) {
			mulBy10(d);
			mulBy10(&e);
			//a>dが成り立ったら
			if (numComp(&sa, d) == -1)
				break;
		}
		divBy10(d);	
		divBy10(&e);	
		sub(&sa, d, &tmp);		copyNumber(&tmp, &sa);
		add(c, &e, &tmp);		copyNumber(&tmp, c);
	}

	copyNumber(&sa, d);



	return 0;
}

// フィナボッチ係数の計算
//   a ： ふたつ前
//   b ： ひとつ前
//   c ： 値の保持
void FinaCal(NUMBER *a, NUMBER *b){
	NUMBER temp;

	// 次の値を求める
	add(a, b, &temp);

	// 多倍長配列にコピー
	copyNumber(b, a);
	copyNumber(&temp , b);
}

int main(void)
{
	gettimeofday(&tv, NULL);
	tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;

	NUMBER a, b;     // フィボナッチ係数を格納
	NUMBER shiftB;   // シフトさせたbを格納  
	NUMBER amari;    // 余りを格納
	NUMBER div;      // 商を格納
	NUMBER ans;      // 逆数和を格納
	NUMBER temp;     // 値の保持用

	int i;
	int count = 0;

	clearByZero(&temp);
	clearByZero(&ans);

	// フィボナッチ数列の最初の２項をセット
	setInt(&a, 1);
	setInt(&b, 1);

	// 割る数を最大桁までシフト
	setInt(&c, 1);
	for(i = 0; i < KETA * 4 - 1; i++)
	{
		mulBy10(&c);
	}

	// 計
	while(1)
	{
		divide(&c, &a, &div, &amari );

		add(&ans, &div, &temp);
		copyNumber(&temp, &ans);

		FinaCal(&a, &b);
		count ++;

		if(isZero(&div) == 0)
			break;
		if(count % 50 == 0){
			dispNumber(&ans);
			gettimeofday(&tv, NULL);
			tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
			printf("[%f s], i = %d\n", tend - tstart, count);
		}
	}

	gettimeofday(&tv, NULL);
	tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
	dispNumber(&ans);
	printf("[%f s], i = %d\n", tend -tstart, count);
	return 0;
}