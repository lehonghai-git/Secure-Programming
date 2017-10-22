#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

#define inputSize 10
#define MAX 20

string inputString();
void copyString(string, char[]);
void subString(char[], char[]);
void getString(int, int, char[], char[]);

void NhapMang(int[], int);
void XuatMang(int[], int);
void NhapMangNgauNhien(int[], int, int, int);
void ThemMotPhanTu(int[], int &, int, int);
int copyArr(int[], int, int, int, int[], int&, int);

int main()
{
#if 0 // Program 1
	char strs[inputSize];
	char sub[inputSize];
	string s1 = inputString();

	copyString(s1, strs);
	subString(strs, sub);
	cout << "Sub string: " << sub << endl;

#endif // 1 // Program 1

#if 1 // Program 2
	/*
	Test:
	- na = 15, nb = 20, startA = 5, endA = 10, vtChen = 1
	- na = nb = 15, startA = 10, endA = 16
	- na = 15, nb = 17, startA = 5, endA = 11, vtChen = 3
	*/
	int arrA[MAX], arrB[MAX], lengthA, lengthB;
	do
	{
		cout << "Nhap so phan tu mang A: ";
		cin >> lengthA;
		if (lengthA <= 0 || lengthA > MAX)
			cout << "Nhap lai so phan tu mang A" << endl;
	} while (lengthA <= 0 || lengthA > MAX);
	NhapMangNgauNhien(arrA, lengthA, 1, 99);
	//NhapMang(arrA, lengthA);

	do
	{
		cout << "Nhap so phan tu mang B: ";
		cin >> lengthB;

		if (lengthB <= 0 || lengthB > MAX)
			cout << "Nhap lai so phan tu mang B" << endl;
	} while (lengthB <= 0 || lengthB > MAX);
	NhapMangNgauNhien(arrB, lengthB, 1, 99);
	//NhapMang(arrB, lengthB);

	cout << "Mang A : ";
	XuatMang(arrA, lengthA);
	cout << "Mang B : ";
	XuatMang(arrB, lengthB);

	int startA, endA;
	do
	{
		cout << "Vi tri bat dau mang A: ";
		cin >> startA;
		cout << "Vi tri ket thuc mang A: ";
		cin >> endA;
	} while (startA < 0 || startA >= lengthA || endA < startA || endA >= lengthA || endA - startA >= lengthA);

	int vtChen;
	do
	{
		cout << "Vi tri chen: ";
		cin >> vtChen;
	} while (vtChen < 0 || vtChen >= lengthB);

	copyArr(arrA, lengthA, startA, endA, arrB, lengthB, vtChen);
	cout << "Mang b sau khi chen: ";
	XuatMang(arrB, lengthB);
#endif // 1 // Program 2

	system("pause");
	return 0;
}

string inputString()
{
	string str;
	cout << "Type a string: "; getline(cin, str);
	return str;
}
void copyString(string s, char strs[])
{
	int i = 0;
	int n = 0;

	// Chiều dài tối đa cho phép = inputSize = 10;
	if (s.length() < inputSize)
		n = s.length();
	else
		n = inputSize;

	// Thực hiện copy từng ký tự
	for (i = 0; i < n - 1; i++)
		strs[i] = s.at(i);
	strs[i] = '\0';
}
void getString(int start, int end, char strs[], char newStrs[])
{
	int len = end - start + 1;
	int i = 0;
	for (i = 0; i < len - 1; i++)
		newStrs[i] = strs[start + i];
	newStrs[i] = '\0';
}
void subString(char strs[], char newStrs[])
{
	string strStart, strEnd;
lb_input:
	cout << "Starting point: ";
	getline(cin, strStart);
	cout << "Ending point: ";
	getline(cin, strEnd);

	int numStart = atoi((char*)strStart.c_str());
	int numEnd = atoi((char*)strEnd.c_str());

	// Xử lý khi dữ liệu nhập không hợp lệ
	if (numStart < 0 || numStart >= inputSize || numEnd < numStart || numEnd - numStart >= inputSize)
		goto lb_input;

	// Thực hiện cắt chuỗi
	getString(numStart, numEnd, strs, newStrs);
}

void NhapMang(int arr[], int length)
{
	for (int i = 0; i < length; i++)
	{
		printf("Nhap arr[%d] = ", i);
		scanf("%d", &arr[i]);
	}
}
void XuatMang(int arr[], int length)
{
	for (int i = 0; i < length; i++)
		printf("%d   ", arr[i]);
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
void ThemMotPhanTu(int arr[], int &length, int vitri, int giatri)
{
	for (int i = length; i > vitri; i--)
		arr[i] = arr[i - 1];
	arr[vitri] = giatri;
	length++;
}
int copyArr(int arrA[], int lengthA, int startA, int endA, int arrB[], int &lengthB, int startB)
{
	int n = 0;
	for (int i = startA; i <= endA; i++)
	{
		if (lengthB < MAX)
		{
			ThemMotPhanTu(arrB, lengthB, startB++, arrA[i]);
			n++;
		}
		else
			return n;
	}

	return n;
}