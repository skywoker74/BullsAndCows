#include <iostream>
#include <string>
using namespace std;

struct BullsAndCows
{
	char CompArray[4]; //� ���� ������� ����� ���������� �����������
	char UserArray[4]; //� ���� ������� ����� ��������� �������������
	string UserDigit;	//�����, ��������� �������������
	int Bools, Cows;

	// ������� ���������� ����� � �������
	void ArrayPrint(char array[])
	{
		for (int i = 0; i < 4; i++)
			printf("%c", array[i]);
	}

	// ���������� ����� �� ����� digit � ������ array
	void NumbArray(int digit, char array[])
	{
		for (int i = 3; i >= 0; i--) //���������� � ������ � �����, �.�. ������� �� ��������
		{
			array[i] = '0' + digit % 10; // �������� int � char
			digit = digit / 10;     // ����������� ��������� ����� �����
		}
	}

	// ���������� ��������� ����� � ���������� ��� � ������
	void NumbGeneration(char array[]) // 
	{
		NumbArray(rand() % 9999, array);
	}

	// ���������� ����� � ���������� ����� ��� ��������� ����� ������������, ����� ��� �� �����������
	bool CompareDigits(char array[])
	{
		int count = 0; //������� ����������� ����
		for (int i = 0; i < 4; i++)
			for (int j = i + 1; j < 4; j++) // ���������� ����� �� ���������
			{
				if (array[i] == array[j])
					count++;
			}

		return (count != 0); //���� ���������� ����� ���� �� ���������� true
	}

	void Run()
	{
		setlocale(LC_ALL, "Russian");
		srand(time(NULL));	// ��������� ���� ���������� ��������������� �����

		int count = 0;
		cout << "���� � ������, ��������� ������� ����� ...." << endl;
		cout << "��� ������ �� ���� ������� exit � ������� ENTER" << endl;

		// ��������� ���� �� ����� ������������� ����� � ������� �������
		do {
			NumbGeneration(CompArray);
		} while (CompareDigits(CompArray));

		do {

			// ���������� ������������ ������ ����� ����� �� 4-� ��������� ����

			cout << "������� ����� �� 4-� ����: " << endl;
			cin >> UserDigit;

			if (UserDigit == "exit")
			{
				cout << "����� ����" << endl;
				break;
			}
			
			if (UserDigit == "test")
			{
				// ������� ���������� ����������� ����� � �������
				ArrayPrint(CompArray);
				cout << endl;
				continue;
			}

			try
			{
				stoi(UserDigit);
			}
			catch (invalid_argument)
			{
				//�������, ��� ����� ������� ������ �����
				cout << "������ ������� ����� � ��������� �������, ������ 4-� ������� �����! �������� 0123" << endl;
				continue;
			}
			catch (...)
			{
				//���� ����� ��������� �����-�� ����������, ������� �� ���������� ����, �� �������, ��� �������� ����������� ������
				cout << "����������� ������!" << endl;
				continue;
			}

			if (stoi(UserDigit) > 9876)
			{
				cout << "�� ����� ������� ������� �����" << endl;
				continue;
			}
			if (stoi(UserDigit) < 123)
			{
				cout << "�� ����� ������� ��������� �����" << endl;
				continue;
			}

			// ������� ��������� ����� � ������ UserArray
			NumbArray(stoi(UserDigit), UserArray);

			// C��������� ����� �������� �������������, ���� ���������, �� ������� ��������� � ������ ������ ����� �����
			if (CompareDigits(UserArray))
			{
				cout << "������ ������� ���������� �����!" << endl;
				continue;
			}

			// ������������ ���� ����� 
			// ������� ������������� ���� ��������

			count++; // ������� ������� ���������� �����

			// ������� ����� � �����, ��������, ������ ��� ������������ ������ ��� ������ ������� ����� �����
			Bools = 0; // ����
			Cows = 0;  // ������
			for (int i = 0; i < 4; i++)
			{
				if (CompArray[i] == UserArray[i])
					Bools++;
				for (int j = 0; j < 4; j++)
					if (CompArray[i] == UserArray[j])
						Cows++;
			}
			Cows = Cows - Bools; // � ������� ���� ����, ������� ������� �����

			cout << "������� �" << count << ": ����� " << Bools << "; ����� " << Cows << endl;
			
			if (Bools == 4)
			{
				cout << "����� �������!" << endl;
			}
			// ���� �� ������� - ��������� � ������� ���������� ����� � ������������
		} while (Bools != 4);			
	}
};