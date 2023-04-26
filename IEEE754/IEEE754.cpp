#include <iostream>

using namespace std;

#pragma region Function
// Lấy bit dấu
void getSign(double dNumber);

// Lấy phần định trị
void getMantissa(double dNumber);

// Đếm phần mũ 
int countExponent(double dNumber);

// Lấy phần mũ
void getExponent(double dNumber);

// Number có là 0
void isZero(double dNumber);
#pragma endregion

int main() 
{
	double dNumber;
	cout << "Enter your number: ";
	cin >> dNumber;

	cout << "IEEE 754 of this number is:" << endl;
	if (dNumber == 0) 
	{
		isZero(dNumber);
	}
	else 
	{
		getSign(dNumber);
		getExponent(dNumber);
		getMantissa(dNumber);
	}

	return 0;
}

void getSign(double dNumber)
{
	// Nếu số dương thì bit dấu là 0
	if (dNumber >= 0) 
	{
		cout << 0;
	}
	// Nếu số âm thì bit dấu là 1
	else 
	{
		cout << 1;
	}
}

void getMantissa(double dNumber)
{
	// Nếu số âm thì chuyển về dương (để dễ làm việc)
	if (dNumber < 0) 
	{
		dNumber = abs(dNumber);
	}

	// Lấy ra phần nguyên của dNumber
	int nNumber = (int)dNumber;

	// Lấy ra phần sau dấu chấm của dNumber
	double dAfter = dNumber;
	if (dNumber >= 1) 
	{
		dAfter = dNumber - nNumber;
	}

	// Chuuyển đổi số từ hệ 10 -> hệ 2
	int binaryBefore[32];
	int iBefore = 0;
	while (nNumber > 0) 
	{
		binaryBefore[iBefore] = nNumber % 2;
		nNumber /= 2;
		iBefore++;
	}

	// Trường hợp dNumber lớn hơn hoặc bằng 1
	if (dNumber >= 1) 
	{
		int countBitOfM = 23; // Để đếm ngược và chạy đủ số bit là 24
		int countE = 0; // Để đếm phần mũ E

		for (int jBefore = iBefore - 2; jBefore >= 0; jBefore--) 
		{ // j = i - 2 để lấy m là phần lẻ của M = 1.m
			cout << binaryBefore[jBefore];
			countBitOfM--;
			countE++;
		}

		int binaryAfter[32];
		int iAfter;
		for (iAfter = 0; countBitOfM >= 0; iAfter++, countBitOfM--)
		{
			dAfter *= 2;
			binaryAfter[iAfter] = (int)dAfter;
			if (dAfter >= 1) 
			{
				dAfter -= 1;
			}
		}

		for (int jAfter = 0; jAfter < iAfter - 1; jAfter++) 
		{
			cout << binaryAfter[jAfter];
		}
	}

	// Trường hợp dNumber nhỏ hơn 1
	else {
		int countE = abs(countExponent(dNumber));
		int countBitOfM = 23 + countE; // Để đếm ngược và chạy đủ số bit

		for (int jBefore = iBefore - 2; jBefore >= 0; jBefore--)
		{ // j = i - 2 để lấy m là phần lẻ của M = 1.m
			cout << binaryBefore[jBefore];
			countBitOfM--;
		}

		int binaryAfter[256];
		int iAfter;
		for (iAfter = 0; countBitOfM >= 0; iAfter++, countBitOfM--) 
		{
			dAfter *= 2;
			binaryAfter[iAfter] = (int)dAfter;
			if (dAfter >= 1) 
			{
				dAfter -= 1;
			}
		}

		for (int jAfter = countE; jAfter < iAfter - 1; jAfter++) 
		{
			cout << binaryAfter[jAfter];
		}
	}
}

int countExponent(double dNumber) 
{
	// Nếu số âm thì chuyển về dương
	if (dNumber < 0) 
	{
		dNumber = abs(dNumber);
	}

	// Lấy ra phần nguyên của dNumber
	int nNumber = (int)dNumber;

	// Trường hợp dNumber lớn hơn hoặc bằng 1
	if (dNumber >= 1) 
	{
		// Chuuyển đổi số từ hệ 10 -> hệ 2
		int binaryBefore[32];
		int i = 0;
		while (nNumber > 0) 
		{
			binaryBefore[i] = nNumber % 2;
			nNumber /= 2;
			i++;
		}

		int countE = 0; // Để đếm E
		for (int j = i - 2; j >= 0; j--) 
		{
			countE++;
		}
		return countE;
	}

	// Trường hợp dNumber nhỏ hơn 1
	else
	{
		// Lấy ra phần sau dấu chấm của dNumber
		double dAfter = dNumber;
		if (dNumber >= 1) 
		{
			dAfter = dNumber - nNumber;
		}

		int binaryAfter[32];
		int iAfter;
		for (iAfter = 0; iAfter < 24; iAfter++) 
		{
			dAfter *= 2;
			binaryAfter[iAfter] = (int)dAfter;
			if (dAfter >= 1) 
			{
				dAfter -= 1;
			}
		}

		int countE = 0; // Để đếm E
		for (int jAfter = 0; jAfter < iAfter - 1; jAfter++) 
		{
			countE++;
			if (binaryAfter[jAfter] == 1) 
			{
				break;
			}
		}
		return -countE;
	}
}

void getExponent(double dNumber) 
{
	int countE = countExponent(dNumber);

	int nExponent = countE + 127; // E = countE

	int binary[8];
	int i = 0;
	while (i < 8) 
	{
		binary[i] = nExponent % 2;
		nExponent /= 2;
		i++;
	}
	for (int j = i - 1; j >= 0; j--)
	{
		cout << binary[j];
	}
}

void isZero(double dNumber) 
{
	int nZero = 0;
	for (int iZero = 0; iZero < 32; iZero++) 
	{
		cout << nZero;
	}
}