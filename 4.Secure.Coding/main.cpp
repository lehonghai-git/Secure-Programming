#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
using namespace std;

#define MAX 100

void NhapMangNgauNhien(int[], int, int, int);
void XuatMang(int[], int);
void TachMang(int[], int, int[], int, int[], int &);
int BitCount(uint64_t);
bool KiemTraToanSo(string);
bool KiemTraCoChuSo(string);
bool KiemTraSoDienThoai(string);
bool KiemTraTapConCuaChuoi(string, string);
char* NoiHaiChuoi(string, string);
char* ChenChuoiKyTu(string, string, char);
int DemMotKyTu(string, char);
void ThemMotKyTu(char *, int, char);

int main()
{
#if 0 // Program 1

	int a[MAX], b[MAX], na, nb;
	do
	{
		cout << "Nhap na: ";
		cin >> na;
		if (na < 10 || na > 20)
			cout << "Nhap lai na" << endl;
	} while (na < 10 || na > 20);

	NhapMangNgauNhien(a, na, 10, 500);

	do
	{
		cout << "Nhap nb: ";
		cin >> nb;

		if (nb < 10 || nb > 20)
			cout << "Nhap lai nb" << endl;
	} while (nb < 10 || nb > 20);

	NhapMangNgauNhien(b, nb, 10, 500);

	// Xuất mảng
	cout << "Mang a : ";
	XuatMang(a, na);
	cout << "Mang b : ";
	XuatMang(b, nb);

	// Lưu phần tử chẵn trong A và lẻ trong B vào C
	int c[MAX], nc = 0;
	TachMang(a, na, b, nb, c, nc);
	cout << "Mang c : ";
	XuatMang(c, nc);

	// Tích các phần tử trong C
	uint64_t result = 1;
	bool flag = true;
	for (int i = 0; i < nc; i++)
	{
		result *= c[i];
		if (BitCount(result) > 32)
		{
			flag = false;
			break;
		}
	}
	if (!flag)
		cout << "Integer Overflow!" << endl;
	else
		cout << "Result: M = " << result << endl;

#endif // 1 // Program 1

#if 1 // Program 2
	string s1, s2;

	// 1. 
	cout << "s1 = "; getline(cin, s1);
	do
	{
		cout << "s2 = "; getline(cin, s2);
		if (!KiemTraToanSo(s2))
			cout << "Input Validation!" << endl;
	} while (!KiemTraToanSo(s2));

	// 2. Kiểm tra có chữ số hay không
	KiemTraCoChuSo(s1) ? cout << "s1 co ton tai chu so" << endl : cout << "s1 khong ton tai chu so" << endl;

	// 3. Số điện thoại
	KiemTraSoDienThoai(s2) ? cout << "s2 la so dien thoai" << endl : cout << "s2 khong la so dien thoai" << endl;

	// 4. Tập con
	// test  s1 = Secure coding6789, s2 =  87654321
	// test  s1 = Secure coding6789, s2 =  6789876
	KiemTraTapConCuaChuoi(s1, s2) ? cout << "s2 la tap con cua s1" << endl : cout << "s2 khong phai tap con cua s1" << endl;
	// 5. Nối chuỗi
	string s3 = NoiHaiChuoi(s1, s2);
	cout << "Chuoi s3 sau khi noi: " << s3 << endl;

	// 6. Chèn chuỗi
	cout << "Chen chuoi \"Buffer_Overflow\" vao sau ky tu: ";
	char chr = getchar();
	char *s4 = ChenChuoiKyTu(s3, "Buffer_Overflow", chr);
	cout << "s4: " << s4 << endl;
#endif // 1 // Program 2

	system("pause");
}

void XuatMang(int a[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d   ", a[i]);
	printf("\n");
}
void NhapMangNgauNhien(int arr[], int length, int min, int max)
{
	srand(time(0));
	for (int i = 0; i < length; i++)
	{
		for (int i = 0; i < length; i++)
			arr[i] = min + rand() % (max - min + 1);
	}
}
void TachMang(int a[], int na, int b[], int nb, int c[], int &nc)
{
	for (int i = 0; i < na; i++)
		if (a[i] % 2 == 0)
			c[nc++] = a[i];

	for (int i = 0; i < nb; i++)
		if (b[i] % 2 != 0)
			c[nc++] = b[i];
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
bool KiemTraToanSo(string str)
{
	if (str.length() < 1) return false;
	for (int i = 0; i < str.length(); i++)
		if (str[i] < '0' || str[i] > '9')
			return false;
	return true;
}
bool KiemTraCoChuSo(string str)
{
	if (str.length() < 1) return false;
	for (int i = 0; i < str.length(); i++)
		if (str[i] >= '0' && str[i] <= '9')
			return true;
	return false;
}
bool KiemTraSoDienThoai(string str)
{
	// 090xxxxxxx
	if (str.length() != 10)
		return false;
	if (str[0] != '0' || str[1] != '9' || str[2] != '0')
		return false;
	for (int i = 3; i < str.length(); i++)
		if (str[i] < '0' || str[i] > '9')
			return false;
	return true;
}
bool KiemTraTapConCuaChuoi(string str1, string str2)
{
	int nstr1 = str1.length();
	int nstr2 = str2.length();

	for (int i = 0; i < nstr1; i++)
	{
		if (str1[i] == str2[0])
		{
			int idxstr1 = i;
			bool flag = true;
			for (int j = 0; j < nstr2; j++)
			{
				if (str2[j] != str1[idxstr1++])
				{
					flag = false;
					break; //*
				}
			}
			if (flag)
				return true;
		}
	}

	return false;
}
char* NoiHaiChuoi(string str1, string str2)
{
	// str3 = str1 + str2
	int nstr3 = str1.length() + str2.length();
	char *str3 = (char *)malloc((nstr3 + 1) * sizeof(char));
	int index = 0;

	for (int i = 0; i < str1.length(); i++)
		str3[index++] = str1[i];
	for (int i = 0; i < str2.length(); i++)
		str3[index++] = str2[i];
	str3[index] = '\0';

	return str3;
}
int DemMotKyTu(string str, char key)
{
	int dem = 0;
	for (int i = 0; i < str.length(); i++)
		if (str[i] == key)
			dem++;
	return dem;
}
void ThemMotKyTu(char *s, int vt, char gt)
{
	int n = strlen(s);
	for (int i = n - 1; i >= vt; i--)
		s[i + 1] = s[i];
	s[vt] = gt;
	s[n + 1] = '\0'; // Dịch ký tự kết thúc chuỗi sang phải 1 ký tự
}
char* ChenChuoiKyTu(string str, string bof, char key)
{
	int nstr = str.length();
	int nbof = bof.length();
	int nKey = DemMotKyTu(str, key);

	if (nKey != 0)
	{
		char *str4 = (char *)malloc((nstr + (nKey * nbof) + 1) * sizeof(char));
		//char *str4 = strdup((char *)str.c_str()); //string strx = str;
		strcpy(str4, (char *)str.c_str());
		int nstr4 = strlen(str4);

		for (int i = 0; i < nstr4; i++)
		{
			if (str4[i] == key)
			{
				int idxBof = 0;
				for (int j = 0; j < nbof; j++)
				{
					ThemMotKyTu(str4, i + 1, bof[idxBof++]);
					i++;
					nstr4++;
				}
			}
		}
		return str4;
	}
	else // Chèn vào cuối chuỗi
		return NoiHaiChuoi(str, bof);

	return nullptr;
}