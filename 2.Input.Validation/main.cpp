#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <fstream>
using namespace std;

#define ELEMENT 10

void Show(string[], int);
void inputName(string[], int);
int getPick();
string outputName(int, string[]);

bool floatValidation(string);
float StringToFloat(char *);
bool integerValidation(string);
int StringToInteger(char *);
void StringGenerator(char*, int);

int main()
{
#if 0 // Program 1
	int pick;
	string names[ELEMENT];
	inputName(names, ELEMENT);
	cout << "--------------------" << endl;
	Show(names, ELEMENT);

	pick = getPick();

	string oName = outputName(pick, names);
	cout << "You chose name: " << oName << endl;
#endif // 1 // Program 1

#if 1 // Program 2
	string strGia, strSoLuong;
	bool flag1 = false, flag2 = false;

lb_input:
	cout << "Nhap gia: ";
	getline(cin, strGia);

	cout << "So luong hang se mua: ";
	getline(cin, strSoLuong);

	flag1 = floatValidation(strGia);
	flag2 = integerValidation(strSoLuong);

	if (!flag1 || !flag2)
	{
		cout << "Nhap lai." << endl;
		goto lb_input;
	}
	else
	{
		float Gia; unsigned int SoLuong;
		Gia = StringToFloat((char *)strGia.c_str());
		SoLuong = StringToInteger((char *)strSoLuong.c_str());

		cout << "----------------" << endl;
		cout << "Gia se mua: " << Gia << endl;
		cout << "So luong se mua: " << SoLuong << endl;
	}
#endif // 1 // Program 2

#if 0 // Program 2 (Mở rộng)
	string strGia, strSoLuong;
	double Gia; int SoLuong;
	bool check1 = false, check2 = false, success = false;
	int dem = 0, SoLanKiemTra;
	cout << "Nhap so lan toi da co the kiem tra: "; cin >> SoLanKiemTra;
	SoLanKiemTra *= 2;
	srand(time(0));
	for (int i = 0; i < SoLanKiemTra; i++)
	{
		int size = 1 + rand() % 8; // Random: 1..7 => x = a + rand() % (b - a + 1)
		char* str1 = new char[size + 1];
		StringGenerator(str1, size);

		if (i % 2 == 0)
		{
			cout << endl << "Round " << (i / 2) + 1 << ": " << endl;
			cout << "-------" << endl;
		}

		if (i % 2 == 0)
		{
			strGia = str1;
			cout << "Gia = " << str1 << endl;
			dem++;
		}
		else
		{
			strSoLuong = str1;
			cout << "SL = " << str1 << endl;
			dem++;
		}
		if (dem == 2)
		{
			check1 = floatValidation(strGia);
			check2 = integerValidation(strSoLuong);

			if (!check1 || !check2)
			{
				cout << "Nhap lai!" << endl;
				dem = 0;
				continue;
			}
			else
			{
				Gia = StringToFloat((char *)strGia.c_str());
				SoLuong = StringToInteger((char *)strSoLuong.c_str());
				//fstream
				ofstream of;
				of.open("Input Validated.log", ios::app);
				of << "Gia cua mat hang se mua: " << Gia << endl;
				of << "So luong mat hang se mua: " << SoLuong << endl;
				of << "----------------------------" << endl;
				of.close();

				cout << "----------------" << endl;
				cout << "Gia cua mat hang se mua: " << Gia << endl;
				cout << "So luong mat hang se mua: " << SoLuong << endl;
				//break;
			}

			dem = 0;
		}

		_sleep(20);
		delete[]str1;
	}
#endif // 1 // Program 2 (Mở rộng)

	system("pause");
	return 0;
}

void Show(string str[], int length)
{
	for (int i = 0; i < length; i++)
	{
		cout << "Name # " << i + 1 << ": ";
		cout << str[i] << endl;
	}
}
void inputName(string names[], int e)
{
	for (int i = 0; i < e; i++)
	{
		cout << "Name # " << i + 1 << ": ";
		getline(cin, names[i]);
	}
}
int getPick()
{
	string str_x;
	int ix;

lb_input:
	cout << "Pick the perfectname (1..10): ";
	cin >> str_x;
	ix = atoi((char *)str_x.c_str());

	if (ix < 1 || ix > 10 || str_x.length() > 2 || !integerValidation(str_x))
		goto lb_input;

	return ix;
}
string outputName(int n, string outputName[])
{
	return outputName[n - 1];
}

bool floatValidation(string str)
{
	// float: +/- 3.4e +/- 38 (~7 digits)
	if ((str.length() == 1 && str.at(0) == '.') || str.length() > 7)
		return false;

	int SoDauCham = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str.at(i) == '.')
		{
			SoDauCham++;
			continue;
		}

		if (str.at(i) < '0' || str.at(i) > '9' || str.at(i) == ',' || SoDauCham > 1)
			return false;
	}

	return true;
}
bool integerValidation(string str)
{
	// unsigned int: 0..4294967295
	if (str.length() > 10) return false;

	for (int i = 0; i < str.length(); i++)
		if (str.at(i) < '0' || str.at(i) > '9')
			return false;

	// Số nhập vào phải ít nhất là 1
	double num = atof((char *)str.c_str());
	if (num < 1)
		return false;

	return true;
}
float StringToFloat(char *s)
{
	char PhanNguyen[10];
	char PhanThuc[10];
	int index = 0, flag = 1; // Biến flag kiểm tra xem đang duyệt phần nguyên hay phần thực
	int length = strlen(s);

	for (int i = 0; i < length; i++)
	{
		if (flag)
			PhanNguyen[index++] = s[i];
		else
			PhanThuc[index++] = s[i];

		if (s[i] == '.')
		{
			flag = 0; // Khi gặp dấu chấm thì chuyển cờ hiệu
			index = 0; // Reset lại index
		}
	}

	return StringToInteger(PhanNguyen) + StringToInteger(PhanThuc) / pow((double)10, index);
}
int StringToInteger(char *s)
{
	int length = strlen(s);
	int idx = length;
	int iNumber = 0;

	// Trường hợp chuỗi "123abc" => chỉ lấy số 123
	// Vòng lặp kiểm tra độ dài chỉ với những ký tự là số
	for (int i = 0; i < length; i++)
	{
		if (s[i] < '0' || s[i] > '9')
		{
			idx = i;
			break;
		}
	}

	int somu = idx;
	for (int i = 0; i < idx; i++)
		iNumber += (s[i] - 48) * pow((double)10, --somu);

	return iNumber;
}
void StringGenerator(char* str, int length)
{
	char* box = "abc_def@0183746592.,?:";
	int boxLength = strlen(box);

	for (int i = 0; i < length; i++)
		str[i] = box[rand() % boxLength];

	str[length] = '\0';
}