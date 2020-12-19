#include <iostream>
#include <string>
using namespace std;

struct BullsAndCows
{
	char CompArray[4]; //в этом массиве число загаданное компьютером
	char UserArray[4]; //в этом массиве число введенное пользователем
	string UserDigit;	//число, введенное пользователем
	int Bools, Cows;

	// Выводим загаданное число в консоли
	void ArrayPrint(char array[])
	{
		for (int i = 0; i < 4; i++)
			printf("%c", array[i]);
	}

	// Записываем цифры из числа digit в массив array
	void NumbArray(int digit, char array[])
	{
		for (int i = 3; i >= 0; i--) //записываем в массив с конца, т.к. остаток от деленеия
		{
			array[i] = '0' + digit % 10; // приводим int к char
			digit = digit / 10;     // отбрасываем последнюю цифру числа
		}
	}

	// Генерируем случайное число и записываем его в массив
	void NumbGeneration(char array[]) // 
	{
		NumbArray(rand() % 9999, array);
	}

	// Сравниваем цифры в загаданном числе или введенном числе пользователя, чтобы они не повторялись
	bool CompareDigits(char array[])
	{
		int count = 0; //счетчик совпадающих цифр
		for (int i = 0; i < 4; i++)
			for (int j = i + 1; j < 4; j++) // сравниваем число со следующим
			{
				if (array[i] == array[j])
					count++;
			}

		return (count != 0); //если сопадающие цифры есть то возвращаем true
	}

	void Run()
	{
		setlocale(LC_ALL, "Russian");
		srand(time(NULL));	// установка базы генератора псевдослучайных чисел

		int count = 0;
		cout << "Быки и коровы, компьютер загадал число ...." << endl;
		cout << "Для выхода из игры введите exit и нажмите ENTER" << endl;

		// повторяем пока не будет сгенерировано число с разными цифрами
		do {
			NumbGeneration(CompArray);
		} while (CompareDigits(CompArray));

		do {

			// Заставляем пользователя ввести целое число из 4-х различных цифр

			cout << "Введите число из 4-х цифр: " << endl;
			cin >> UserDigit;

			if (UserDigit == "exit")
			{
				cout << "Конец игры" << endl;
				break;
			}
			
			if (UserDigit == "test")
			{
				// Выводим загаданное компьютером число в консоли
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
				//Говорим, что можно вводить только числа
				cout << "Нельзя вводить буквы и различные символы, только 4-х значное число! Например 0123" << endl;
				continue;
			}
			catch (...)
			{
				//Если будет выброшено какое-то исключение, которое не обработано выше, то говорим, что возникла неизвестная ошибка
				cout << "Неизвестная ошибка!" << endl;
				continue;
			}

			if (stoi(UserDigit) > 9876)
			{
				cout << "Вы ввели слишком большое число" << endl;
				continue;
			}
			if (stoi(UserDigit) < 123)
			{
				cout << "Вы ввели слишком маленькое число" << endl;
				continue;
			}

			// Заносим введенное число в массив UserArray
			NumbArray(stoi(UserDigit), UserArray);

			// Cравниваем цифры введеные пользователем, если совпадают, то выводим сообщение и просим ввести новое число
			if (CompareDigits(UserArray))
			{
				cout << "Нельзя вводить одинаковые цифры!" << endl;
				continue;
			}

			// пользователь ввел число 
			// которое удовлетворяет всем условиям

			count++; // счетчик попыток угадывания числа

			// считаем быков и коров, обнуляем, потому что пользователь вводит при каждой попытке новое число
			Bools = 0; // быки
			Cows = 0;  // коровы
			for (int i = 0; i < 4; i++)
			{
				if (CompArray[i] == UserArray[i])
					Bools++;
				for (int j = 0; j < 4; j++)
					if (CompArray[i] == UserArray[j])
						Cows++;
			}
			Cows = Cows - Bools; // в коровах есть быки, поэтому убираем быков

			cout << "Попытка №" << count << ": Быков " << Bools << "; Коров " << Cows << endl;
			
			if (Bools == 4)
			{
				cout << "Число угадано!" << endl;
			}
			// если не угадали - переходим к запросу следующего числа у пользователя
		} while (Bools != 4);			
	}
};