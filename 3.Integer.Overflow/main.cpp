#include <iostream>
#include <string>
#include <climits>
using namespace std;

bool shortValidation(string);
int BitCount(uint64_t);
bool Addition_Is_Safe(uint64_t, uint64_t, const int);
bool short_Addition_Is_Safe(short, short);

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


// Ref: https://stackoverflow.com/questions/199333/how-to-detect-integer-overflow