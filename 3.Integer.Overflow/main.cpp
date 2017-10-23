#include <iostream>
#include <string>
#include <climits>
#include <cstring>
#include <cstdlib>
using namespace std;

bool shortValidation(string);
int BitCount(uint64_t);
bool Addition_Is_Safe(uint64_t, uint64_t, const int);
bool short_Addition_Is_Safe(short, short);

void addAnCharacter(char *, int, char);
char* ConvertNumber(unsigned int, unsigned int);
char* AxorB(char *, char *);
int StringToDecimal(char *s, int coso);
unsigned int myPow(unsigned int, unsigned int, bool &);
bool Multiplication_Is_Safe(uint64_t, uint64_t, const int);
bool uint32_Multiplication_Is_Safe(uint32_t, uint32_t);

int main()
{
#if 0 // Program 1
	uint64_t money, rate;

	cout << "Money: ";
	cin >> money;
	cout << "Rate (e.g: for 10% enter 10): ";
	cin >> rate;

	// Quy đổi ra %
	float InterestRate = static_cast<float>(rate) / 100;
	cout << "Interest Rate: " << InterestRate << "%" << endl;
	cout << "--------------------" << endl;
	cout << "Year\t\tGrowth\t\tNew balance" << endl;

	for (int i = 1; i <= 10; i++)
	{
		uint64_t increase = static_cast<uint64_t>(money * InterestRate);
		uint64_t newmoney = money + increase;

		cout << i << "\t\t" << increase << "\t\t" << newmoney << endl;
		money = newmoney;
	}
	cout << "Total: " << money << endl;
#endif // 1 // Program 1

#if 0 // Program 2
	// short (2 byte)			:	-32768 .. 32767
	// unsigned short (2 byte)	:	0 .. 65535

	string strMoney, strRate;

lb_input:
	do
	{
		cout << "Money: ";
		getline(cin, strMoney);
		cout << "Rate (e.g: for 10% enter 10): ";
		getline(cin, strRate);
	} while (!shortValidation(strMoney) || !shortValidation(strRate));

	short money = static_cast<short>(atoi((char *)strMoney.c_str()));
	short rate = static_cast<short>(atoi((char *)strRate.c_str()));

	float InterestRate = static_cast<float>(rate) / 100;
	cout << "Interest Rate: " << InterestRate << " %" << endl;
	cout << "---------------------------" << endl;

	cout << "Year\t\tGrowth\t\tNew balance" << endl;

#if 0 // Cách 1
	bool flag = true;
	for (int i = 1; i <= 10; i++)
	{
		short increase = static_cast<short>(money * InterestRate);
		short newmoney = money + increase;

		if (newmoney >= USHRT_MAX || newmoney < 0 || increase < 0 || increase >= USHRT_MAX)
		{
			flag = false;
			break;
		}

		cout << i << "\t\t" << increase << "\t\t" << newmoney << endl;
		money = newmoney;
	}

	if (!flag)
	{
		cout << "Warning: Integer Error...!!" << endl;
		goto lb_input;
	}

	cout << "Total: " << money << endl;
#endif // 1 // Cách 1

#if 0 // Cách 2
	bool flag = true;
	for (int i = 1; i <= 10; i++)
	{
		short increase = static_cast<short>(money * InterestRate);
		short newmoney = money + increase;

		if (!short_Addition_Is_Safe(money, increase))
		{
			flag = false;
			break;
		}

		cout << i << "\t\t" << increase << "\t\t" << newmoney << endl;
		money = newmoney;
	}

	if (!flag)
	{
		cout << "Warning: Integer Error...!!" << endl;
		goto lb_input;
	}

	cout << "Total: " << money << endl;
#endif // 1 // Cách 2

#if 0 // Cách 3
	bool flag = true;
	for (int i = 1; i <= 10; i++)
	{
		short increase = static_cast<short>(money * InterestRate);
		short newmoney = money + increase;
		// 32767 = 0111 1111 1111 1111
		if (!Addition_Is_Safe(money, increase, 15))
		{
			flag = false;
			break;
		}

		cout << i << "\t\t" << increase << "\t\t" << newmoney << endl;
		money = newmoney;
	}

	if (!flag)
	{
		cout << "Warning: Integer Error...!!" << endl;
		goto lb_input;
	}

	cout << "Total: " << money << endl;
#endif // 1 // Cách 3

#endif // 1 // Program 2

#if 1 // Program 3
	// unsigned int: 0 -> 4.294.967.295
	unsigned int x, y;

	cout << "x = "; cin >> x;
	cout << "y = "; cin >> y;
	cout << "------------------------" << endl;

#if 1 // Dec to Bin
	//unsigned int x = 1234, y = 10;
	char *bin_x1 = ConvertNumber(x, 2);
	char *bin_y1 = ConvertNumber(y, 2);
	cout << "DEC to BIN" << endl;
	cout << x << "\t:\t" << bin_x1 << endl;
	cout << y << "\t:\t" << bin_y1 << endl;
	cout << "------------------------" << endl;
	free(bin_x1);
	free(bin_y1);
#endif // 1 // Dec to Bin

#if 1 // X XOR Y
	char *bin_x2 = ConvertNumber(x, 2);
	char *bin_y2 = ConvertNumber(y, 2);
	char * xorStr = AxorB(bin_x2, bin_y2);

	cout << "X XOR Y" << endl;
	cout << "   x\t\t" << x << "\t" << bin_x2 << endl;
	cout << "   y\t\t" << y << "\t" << bin_y2 << endl;
	cout << "x xor y\t\t" << StringToDecimal(xorStr, 2) << "\t" << xorStr << endl;
	cout << "------------------------" << endl;
#endif // 1 // X XOR Y

#if 1 // POW
	//unsigned int x = 69, y = 5;
	// Test x = 1234, y = 10
	bool flag = true;
	cout << "POW(X, Y)" << endl;
	cout << "   x\t = \t" << x << endl;
	cout << "   y\t = \t" << y << endl;
	unsigned int z = myPow(x, y, flag);

	if (!flag)
		cout << "Warning: Integer Error..!!" << endl;
	cout << "------------------------" << endl;
#endif // 1 // POW

#endif // 1 // Program 3

	system("pause");
	return 0;
}

bool shortValidation(string str)
{
	// unsigned short: 0..65535
	if (str.length() > 5 || str.length() == 0)
		return false;

	for (int i = 0; i < str.length(); i++)
		if (str.at(i) < '0' || str.at(i) > '9')
			return false;

	// Số nhập vào phải ít nhất là 1
	double num = atof((char *)str.c_str());
	if (num < 1)
		return false;

	return true;
}
int BitCount(uint64_t a)
{
	int bits = 0;
	while (a != 0)
	{
		++bits;
		a >>= 1;
	};

	return bits;
}
bool Addition_Is_Safe(uint64_t a, uint64_t b, const int nBit)
{
	uint64_t x = a + b;
	int x_bits = BitCount(x);
	return (x_bits <= nBit);
}
bool short_Addition_Is_Safe(short a, short b)
{
	/*
	SHRT_MAX = 32767, SHRT_MIN = -32768

	- Giả sử: a = 32000
	- Cho phép thực hiện cộng khi: b <= 767 (tức là: 32767 - a)

	- Giả sử: a = -32000
	- Cho phép thực hiện cộng khi: b >= -768 (tức là: -32768 - (a) )
	*/

	// Tổng quát với kiểu short: -32768..32767
	if ((a > 0) && (b > SHRT_MAX - a))
		return false; // Tràn trên
	if ((a < 0) && (b < SHRT_MIN - a))
		return false; // Tràn dưới

	return true;
}

void addAnCharacter(char *s, int vt, char gt)
{
	int n = strlen(s);
	for (int i = n - 1; i >= vt; i--)
		s[i + 1] = s[i];
	s[vt] = gt;
	s[n + 1] = '\0';
}
char* ConvertNumber(unsigned int x, unsigned int radix)
{
	// Hàm chuyển đổi một số nguyên dương cơ số 10 sang các cơ số: 2, 8, 16, ...
	char s[45];
	unsigned int i = 0;
	while (x != 0)
	{
		unsigned int tmp = x % radix;
		if (tmp == 10)
			s[i] = 'A';
		else if (tmp == 11)
			s[i] = 'B';
		else if (tmp == 12)
			s[i] = 'C';
		else if (tmp == 13)
			s[i] = 'D';
		else if (tmp == 14)
			s[i] = 'E';
		else if (tmp == 15)
			s[i] = 'F';
		else
		{
			tmp += 48;
			s[i] = tmp;
		}

		x /= radix;
		i++;
	}
	s[i] = '\0';

	unsigned int index = 0, len = i;
	char *str = (char *)malloc((len + 1) * sizeof(char));

	for (int j = i - 1; j >= 0; j--)
		str[index++] = s[j];
	str[index] = '\0';

	return str;
}
char* AxorB(char *a, char *b)
{
	/*
	Phép XOR thực hiện trên hai dãy bit cùng độ dài
	A	B	A^B
	0	0	 0
	0	1	 1
	1	0	 1
	1	1	 0
	Chuẩn hóa hai chuỗi cùng độ dài trước khi XOR
	a = 10010110 => 8 ký tự
	b = 10110	 => 5 ký tự
	=> Cần phải thêm 3 ký tự vào chuỗi b
	*/

	int na = strlen(a);
	int nb = strlen(b);

	// Chuẩn hóa hai chuỗi
	if (na > nb)
		for (int i = 0; i < na - nb; i++)
			addAnCharacter(b, 0, '0');
	if (nb > na)
		for (int i = 0; i < nb - na; i++)
			addAnCharacter(a, 0, '0');

	// XOR
	int sizeXorStr = strlen(a) + 1;
	char *xorStr = (char *)malloc(sizeXorStr * sizeof(char));
	for (int i = 0; i < strlen(a); i++)
	{
		if (a[i] == b[i])
			xorStr[i] = '0';
		else
			xorStr[i] = '1';
	}
	xorStr[strlen(a)] = '\0';

	return xorStr;
}
int StringToDecimal(char *s, int coso)
{
	int n = 0;
	int length = strlen(s);
	int somu = length - 1;

	if (coso == 2 || coso == 8)
		for (int i = 0; i < length; i++)
			n += (s[i] - 48) * pow((double)coso, somu--);
	else if (coso == 16)
	{
		for (int i = 0; i < length; i++)
		{
			int so;
			if (s[i] == 'A' || s[i] == 'a')
				so = 10;
			else if (s[i] == 'B' || s[i] == 'b')
				so = 11;
			else if (s[i] == 'C' || s[i] == 'c')
				so = 12;
			else if (s[i] == 'D' || s[i] == 'd')
				so = 13;
			else if (s[i] == 'E' || s[i] == 'e')
				so = 14;
			else if (s[i] == 'F' || s[i] == 'f')
				so = 15;
			else if (s[i] > '0' && s[i] < '9')
				so = s[i] - 48;
			n += so * pow((double)coso, somu--);
		}
	}
	else
		return 0;

	return n;
}
unsigned int myPow(unsigned int x, unsigned int y, bool &flag)
{
	// Các trường hợp đặc biệt
	if (x == 0)
	{
		if (y != 0) return 0;
		else return 1;
	}
	if (y == 0) return 1;

	// POW
	uint64_t sum = 1;
	for (int i = 1; i <= y; i++)
	{
		if (!Multiplication_Is_Safe(sum, x, 32)) // uint32_Multiplication_Is_Safe(sum, x)
		{
			flag = false;
			break;
		}
		sum *= x;
		cout << x << " ^ " << i << "\t =\t" << sum << endl;
	}

	return sum;
}
bool Multiplication_Is_Safe(uint64_t a, uint64_t b, const int nBit)
{
	uint64_t x = a * b;
	size_t x_bits = BitCount(x);
	return (x_bits <= nBit);
}
bool uint32_Multiplication_Is_Safe(uint32_t a, uint32_t b)
{
	/*
	UINT32_MAX = 4294967295, UINT32_MIN = 0

	VD: MAX = 100
	- Giả sử: a = 25
	- Cho phép thực hiện phép nhân khi: b <= 4 (tức là: MAX / a)
	*/

	if (a > 0 && b > UINT32_MAX / a)
		return false;

	return true;
}

// Ref: https://stackoverflow.com/questions/199333/how-to-detect-integer-overflow