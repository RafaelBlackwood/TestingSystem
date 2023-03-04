#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<Windows.h>

/*
Реализовать полнофункциональную систему тестирования.

В системе должны быть  2 режима: Администратор и Тестируемый.
Описание режима работы для Тестируемого (в дальнейшем Гость).
- Для входа в систему Гость должен зарегистрироваться. Данная процедура выполняется один раз, при дальнейших
входах в систему доступ идет по логину и паролю.
- При регистрации нужно указывать ФИО, телефон.
- Важно, чтобы логины для пользователей были уникальными.
- После входа Гость имеет возможность просмотреть свои предыдущие результаты тестирования, сдать новое
тестирование.
Тестирование  может  осуществляться  по  различным  категориям. Например:
- Математика:
	- Тест 1
	- Тест 2
- Программирование:
	- Тест 1
	- Тест 2
- После  сдачи  теста  Гость  видит  результат  тестирования,  количество  правильных ответов, процент
правильных ответов и полученную оценку.
- Гость имеет возможность прервать тестирование и продолжить его тогда, когда ему это будет удобно.
- Оценивание нужно вести на основании 12-ти балльной системы, привязанной к количеству вопросов теста.
- Пароли гостей хранятся в зашифрованном виде

Описание режима работа для Администратора (в дальнейшем Админ).
- В системе может быть только один Админ, логин и пароль Админа задается при первом входе в программу.
- В  дальнейшем  пароль  и  логин  можно  изменить (у Гостя должна быть аналогичная возможность)
- Пароль необходимо хранить только в зашифрованном виде.
- При работе с системой Админ имеет следующие возможности:
- управление  пользователями  –  создание,  удаление,  модификация  пользователей;
- просмотр  статистики  –  количество пройденных тестов в системе в общем и по категориям.
- Управление тестированием – Админ имеет возможность добавлять категории, тесты, вопросы к тестам,
задавать правильные и неправильные ответы

Код  должен  быть  читабельным,  хорошо  прокомментированным,  и  использовать единую систему именования
идентификаторов.
*/


// Стурктура для хранение инфомарции о тесторах и Админе
struct UserData
{
	std::string login;
	std::string password;
	std::string name;
	std::string surname;
	std::string fathers_name;
	std::vector<std::pair<int, int>> mark;  // Первый элемент-номер теста , второй элемент-оценка по тесту
	std::vector<std::pair<int, int>> progress;  // Первый элемент-номер теста , второй элемент -прогресс пользователя по тесту

};


// Структура для храние тестов 
struct TestData
{
	std::string question;
	std::string first_variant;
	std::string second_variant;
	std::string third_variant;
	std::string forth_variant;
	size_t answer; //если делать int то по итогу выдавать ошибку в некоторых местах будет
};



// Функция для шифрования строки 
std::string passwordEncryption(std::string& userPassword)
{
	std::string result;
	for (int i = 0; i < userPassword.length(); i++)
	{
		result += userPassword[i] + i + 1;
	}
	return result;
}

// Функция для дешифрования строки 
std::string passwordDecryption(std::string& userPassword)
{
	std::string result;
	for (size_t i = 0; i < userPassword.length() ; i++)
	{
		result += userPassword[i] - i- 1;
	}

	return result;
}


// Класс для регстрирации админа , а так же гостей
class  UserReg
{
	UserData* user = nullptr;
	UserData admin;
	size_t size = 0;

public:
	// Метод позволяющий регестрировать пользователя
	//добавляю в конец новых юзеров 
	void RegisterPerson(std::string& name, std::string& surname, std::string& fathers_name, std::string& login, std::string& password) {

		UserData* new_user = new UserData[size + 1];

		for (int i = 0; i < size; i++)
		{
			new_user[i].name = user[i].name;
			new_user[i].surname = user[i].surname;
			new_user[i].fathers_name = user[i].fathers_name;
			new_user[i].login = user[i].login;
			new_user[i].password = user[i].password;
			new_user[i].mark.swap(user[i].mark);//меняет местами указатели,я как бы присваиваю к марку новому указатель который указывал на старый марк,чтобы не копировать его поэлементно
			new_user[i].progress.swap(user[i].progress);

		}

		new_user[size].name = name;
		new_user[size].surname = surname;
		new_user[size].fathers_name = fathers_name;
		new_user[size].login = login;
		new_user[size].password = password;

		delete[]user;
		user = new_user;
		size++;
	}

	void DeleteUser(int element)
	{
		UserData* new_user = new UserData[size - 1];

		for (int a = 0, b = 0; a < size; a++, b++)
		{
			if (a == element)//посылаем в этот метод номер который хотим удалить,как только до него доходим,просто перескакиваем через него и все
			{
				a++;
			}
			if (a < size)
			{
				new_user[b].name = user[a].name;
				new_user[b].surname = user[a].surname;
				new_user[b].fathers_name = user[a].fathers_name;
				new_user[b].login = user[a].login;
				new_user[b].password = user[a].password;
				new_user[b].mark.swap(user[a].mark);
				new_user[b].progress.swap(user[a].progress);
			}
		}
		delete[]user;
		user = new_user;
		size--;
	}

	//метод для одноразового регестрирования админа
	void AdminRegistration(std::string& name, std::string& surname, std::string& fathers_name, std::string& login, std::string& password)
	{
		admin.name = name;
		admin.surname = surname;
		admin.fathers_name = fathers_name;
		admin.login = login;
		admin.password = password;
	}

	UserData* GetUser()
	{
		return user;
	}

	UserData& GetAdmin()
	{
		return admin;
	}

	size_t& GetUserSize()
	{
		return size;
	}
};


// Классдля создать тестов по одной теме
class CreateTest
{
	TestData* test = nullptr;
	size_t test_size = 0;
	std::string test_name;

public:

	void Create(std::string& question, std::string& first_variant, std::string& second_variant, std::string& third_variant, std::string& forth_variant, size_t& ansewer)
	{
		TestData* new_test = new TestData[test_size + 1];

		for (int i = 0; i < test_size; i++)
		{
			new_test[i].question = test[i].question;
			new_test[i].first_variant = test[i].first_variant;
			new_test[i].second_variant = test[i].second_variant;
			new_test[i].third_variant = test[i].third_variant;
			new_test[i].forth_variant = test[i].forth_variant;
			new_test[i].answer = test[i].answer;
		}

		new_test[test_size].question = question;
		new_test[test_size].first_variant = first_variant;
		new_test[test_size].second_variant = second_variant;
		new_test[test_size].third_variant = third_variant;
		new_test[test_size].forth_variant = forth_variant;
		new_test[test_size].answer = ansewer;

		delete[] test;
		test = new_test;
		test_size++;

	}

	void SetTestName(const std::string& test_name)
	{
		this->test_name = test_name;
	}

	void SetTest(TestData* test) // на прямую записываю значение
	{
		this->test = test;
	}

	void SetTestSize(const size_t& test_size)
	{
		this->test_size = test_size;
	}

	TestData* GetTest()
	{
		return test;
	}

	size_t GetTestSize()
	{
		return test_size;
	}

	std::string& GetTestName()
	{
		return test_name;
	}

};


// Класс для создания подтестсов
class Tests
{
	CreateTest* new_test = nullptr;
	size_t various_test_size = 0;

public:

	void VariousTests(std::string& test_name)
	{
		CreateTest* new_test2 = new CreateTest[various_test_size + 1];

		for (int i = 0; i < various_test_size; i++)
		{
			new_test2[i].SetTest(new_test[i].GetTest());
			new_test2[i].SetTestSize(new_test[i].GetTestSize());
			new_test2[i].SetTestName(new_test[i].GetTestName());
		}

		new_test2[various_test_size].SetTestName(test_name);
		delete[]new_test;
		new_test = new_test2;
		various_test_size++;
	}

	CreateTest* GetTests()
	{
		return new_test;
	}

	size_t& GetTestsSize()
	{
		return various_test_size;
	}

};


//Информация админа
bool ReadInFileAdminInformation(UserReg& users)
{
	UserData user;
	std::string user_password;

	std::ios::openmode mode = std::ios::in;
	std::ifstream file("Admin.txt", mode);
	{
		if (file.is_open())
		{
			getline(file, user.name);
			getline(file, user.surname);
			getline(file, user.fathers_name);
			getline(file, user.login);
			getline(file, user_password);
			user.password = passwordDecryption(user_password);
			users.AdminRegistration(user.name, user.surname, user.fathers_name, user.login, user.password);

			return false;
		}
		file.close();

		return true;
	}
}


//Регистрация админа
void AdminRegistration(UserReg& users) {

	if (ReadInFileAdminInformation(users)) {

		UserData user;
		UserData check_password;

		std::cout << "\nEnter Name" << std::endl;
		std::getline(std::cin, user.name);

		std::cout << "\nEnter Surname" << std::endl;
		std::getline(std::cin, user.surname);

		std::cout << "\nEnter Fathers Name" << std::endl;
		std::getline(std::cin, user.fathers_name);

		std::cout << "\nEnter Login" << std::endl;
		std::cin >> user.login;
		if (user.login.size() <= 3 && user.login.size() >= 15)
		{
			std::cout << "\nThe login is too short or too long!\n";
		}

		bool check = true;
		do
		{

			std::cout << "\nEnter Password" << std::endl;
			std::cin >> user.password;
			if (user.password.size() <= 3 && user.password.size() >= 15)
			{
				std::cout << "\nPassword is too short or too long!\n";
			}
			std::cout << "\nReturn Password" << std::endl;
			std::cin >> check_password.password;
			if (check_password.password.size() <= 3 && check_password.password.size() >= 15)
			{
				std::cout << "\nPassword is too short or too long!\n";
			}

			if (user.password == check_password.password)
			{
				users.AdminRegistration(user.name, user.surname, user.fathers_name, user.login, user.password);
				check = false;
			}
			else
			{
				std::cout << " \nPassword is not correct. " << std::endl;
			}
		} while (check);
	}

}


//Вход Админа
bool AdminLogin(UserReg& users)
{
	UserData user;

	bool check = true;
	do
	{
		std::cout << "\nEnter Login" << std::endl;
		std::cin >> user.login;
		if (user.login.size() <= 3 && user.login.size() >= 15)
		{
			std::cout << "\nLogin is too short or too long\n";
		}

		std::cout << "\nEnter Password" << std::endl;
		std::cin >> user.password;
		if (user.password.size() <= 3 && user.password.size() >= 15)
		{
			std::cout << "\nPassword is too short or too long\n";
		}

		if (user.login == users.GetAdmin().login)
		{
			std::cout << user.password << " " << users.GetAdmin().password;
			if (user.password == users.GetAdmin().password)
			{
				{
					system("cls");
					std::cout << "Hello " << users.GetAdmin().name << " " << users.GetAdmin().surname << " " << users.GetAdmin().fathers_name << std::endl;
					Sleep(1000);
					return true;
				}
			}
		}
		else
		{
			std::cout << "\nIncorrect login or password. Try again!\n" << std::endl;
		}
		return false;

	} while (check);
}


//Редактирование данных админа
void EditAdmin(UserReg& users)
{

	UserData user;
	UserData check_password;

	std::cout << "1. Edit Name\n";
	std::cout << "2. Edit Surname\n";
	std::cout << "3. Fathers Name\n";
	std::cout << "4. Login\n";
	std::cout << "5. Password\n";
	std::cout << "6. Exit\n";

	int choose;
	std::cin >> choose;
	switch (choose)
	{
	case 1:
		std::cout << "\nEnter Name" << std::endl;
		std::getline(std::cin, user.name);
		users.GetAdmin().name = user.name;
		break;

	case 2:
		std::cout << "\nEnter Surname" << std::endl;
		std::getline(std::cin, user.surname);
		users.GetAdmin().surname = user.surname;
		break;

	case 3:
		std::cout << "\nEnter Fathers Name" << std::endl;
		std::getline(std::cin, user.fathers_name);
		users.GetAdmin().fathers_name = user.fathers_name;
		break;

	case 4:
		std::cout << "\nEnter Login " << std::endl;
		std::cin >> user.login;

		if (user.login.size() <= 3 && user.login.size() >= 15)
		{
			std::cout << "\nLogin is too short or too long!\n";
		}
		users.GetAdmin().login = user.login;
		break;

	case 5:
		std::cout << "\nEnter Password" << std::endl;
		std::cin >> user.password;
		if (user.password.size() <= 3 && user.password.size() >= 15)
		{
			std::cout << "\nLogin is too short or too long!\n";
		}

		std::cout << "\nReturn Password" << std::endl;
		std::cin >> check_password.password;
		if (check_password.password.size() == 1)
		{
			std::cout << "\nLogin is too short or too long!\n";
		}

		if (user.password == check_password.password)
		{
			users.GetAdmin().password = user.password;
		}

		else
		{
			std::cout << "\nPassword is not correct.Try again!" << std::endl;
		}
		break;
	}

}


//Регестрация тестеров
void TesterRegistration(UserReg& users)
{
	UserData user;
	UserData check_password;

	system("cls");
	std::cout << "___________________________________________________________________________" << std::endl << std::endl;
	std::cin.ignore();
	std::cout << "\nEnter Name" << std::endl;
	std::getline(std::cin, user.name);


	std::cout << "\nEnter Surname" << std::endl;
	std::getline(std::cin, user.surname);


	std::cout << "\nEnter Fathers Name" << std::endl;
	std::getline(std::cin, user.fathers_name);


	bool trying = true;
	bool check_login = true;

	do
	{

		std::cout << "\nEnter Login" << std::endl;
		std::cin >> user.login;

		if (user.login.size() <= 3 && user.login.size() >= 15)
		{
			std::cout << "\nLogin is too short or too long!\n";
			continue;
		}

		for (int i = 0; i < users.GetUserSize(); i++)
		{
			if (user.login == users.GetUser()[i].login)
			{
				check_login = false;
			}
		}
		if (check_login)
		{
			std::cout << "\nEnter Password" << std::endl;
			std::cin >> user.password;
			if (user.password.length() <= 3 && user.password.length() >= 15)
			{
				std::cout << "\nLogin is too short or too long!\n";
				continue;
			}

			std::cout << "\nReturn Password" << std::endl;
			std::cin >> check_password.password;
			if (check_password.password.length() <= 3 && check_password.password.length() >= 15)
			{
				std::cout << "\nLogin is too short or too long!\n";
				continue;
			}

			if (user.password == check_password.password)
			{
				users.RegisterPerson(user.name, user.surname, user.fathers_name, user.login, user.password);
				trying = false;
			}
		}
		else
		{
			std::cout << "\nLogin is already exist!\n";
			continue;

		}

	} while (trying);
}


//Вход тестров
int TesterLogin(UserReg& users)
{
	UserData user;

	std::cout << "\nEnter Login" << std::endl;
	std::cin >> user.login;
	std::cout << "\nEnter Password" << std::endl;
	std::cin >> user.password;

	if (user.login.size() <= 3 && user.login.size() >= 15 || user.password.size() <= 3 && user.password.size() >= 15)
	{
		std::cout << "\nIncorrect login or password" << std::endl;
	}

	for (int i = 0; i < users.GetUserSize(); i++)
	{
		if (user.login == users.GetUser()[i].login)
		{
			if (user.password == users.GetUser()[i].password)
			{
				std::cout << "\nCorrect Password\n";
				Sleep(1500);
				system("cls");
				std::cout << "Hello " << users.GetUser()[i].name << " " << users.GetUser()[i].surname << " " << users.GetUser()[i].fathers_name << std::endl;
				Sleep(500);
				return i;
			}
		}
	}
	return -1;
}


// Редактирование данных пользователей
void TesterEdit(UserReg& users)
{

	UserData user;
	UserData check_password;
	int num;
	bool check = true;
	bool login_check = true;

	std::cout << "\nWhich user do you want to edit?" << std::endl;
	for (int i = 0; i < users.GetUserSize(); i++)
	{
		std::cout << i + 1 <<" "<< users.GetUser()[i].login << std::endl;
	}
	std::cin >> num;

	if (num <= users.GetUserSize())
	{
		
			std::cout << "\n1. Edit Name\n";
			std::cout << "2. Edit Surname\n";
			std::cout << "3. Fathers Name\n";
			std::cout << "4. Login\n";
			std::cout << "5. Password\n";
			std::cout << "6. Exit\n";

			int choose;
			std::cin >> choose;

			switch (choose)
			{
			case 1:
				std::cout << "\nEnter Name" << std::endl;
				std::cin.ignore();
				std::getline(std::cin, user.name);
				users.GetUser()[num - 1].name = user.name;
				break;

			case 2:
				std::cout << "\nEnter Surname" << std::endl;
				std::cin.ignore();
				std::getline(std::cin, user.surname);
				users.GetUser()[num - 1].surname = user.surname;
				break;

			case 3:
				std::cout << "\nEnter Fathers Name" << std::endl;
				std::cin.ignore();
				std::getline(std::cin, user.fathers_name);
				users.GetUser()[num - 1].fathers_name = user.fathers_name;
				break;

			case 4:
				std::cout << "\nEnter Login " << std::endl;
				std::cin.ignore();
				std::cin >> user.login;
				if (user.login.size() <= 3 && user.login.size() >= 15)
				{
					std::cout << "\nLogin is too short or too long!\n";
				}

				for (int i = 0; i < users.GetUserSize(); i++)
				{
					if (user.login == users.GetUser()[i].login) //избегаю дублирование логинов
					{
						std::cout << "\nThis login is already exist. Try again\n" << std::endl;
						login_check = false;
					}
					if (login_check)
					{
						users.GetUser()[num - 1].login = user.login;
					}
				}
				break;

			case 5:
				std::cout << "\nEnter Password" << std::endl;
				std::cin.ignore();
				std::cin >> user.password;
				if (user.password.size() <= 3 && user.password.size() >= 15)
				{
					std::cout << "\Password is too short or too long!\n";
				}

				std::cout << "\nReturn Password" << std::endl;
				std::cin.ignore();
				std::cin >> check_password.password;
				if (check_password.password.size() <= 3 && check_password.password.size() >= 15)
				{
					std::cout << "\Password is too short or too long!\n";
				}

				if (user.password == check_password.password)
				{
					users.GetUser()[num - 1].password = user.password;
				}

				else
				{
					std::cout << "\nPassword is not correct. Try again!\n" << std::endl;
				}
				break;

			case 6:
				break;
			}
		
	}

	else
	{
		std::cout << "\nThere is no user like this" << std::endl;
		system("pause");
	}

}


//Удаление пользователей
void DeleteTester(UserReg& users) {

	std::cout << "\nChoose User which you want to delete\n" << std::endl;

	for (int i = 0; i < users.GetUserSize(); i++)
	{
		std::cout << i + 1 << " : " << users.GetUser()[i].login << std::endl;
	}
	int num;
	std::cin >> num;

	if (num == 0)
	{
		std::cout << "\nThere is no number like this!";
	}

	if (num <= users.GetUserSize())
	{
		users.DeleteUser(num - 1);
	}

	else
	{
		std::cout << "\nThere is no number like this!\n";
		system("pause");
	}
}

//Оценки 
void TesterMark(UserReg& users, int tester, int test_index, int test_mark)
{
	bool check = true;
	for (int i = 0; i < users.GetUser()[tester].mark.size(); i++)
	{
		if (users.GetUser()[tester].mark[i].first == test_index) // если под этим индексом уже есть оценка и тестер его перепроходит то просто оценка перезаписывается
		{
			users.GetUser()[tester].mark[i].second = test_mark;
			check = false;
		}
	}

	if (check)// если тест проходит в первый раз то тут записывается оценка и индекс ,индекс нужен для определения какой это тест,чтобы потом можно было понять какие тесты перепроходить нужно
	{
		users.GetUser()[tester].mark.push_back(std::make_pair(test_index, test_mark));
		check = false;
	}
}

//Прогресс для возможности потом продожлить
void TesterProgress(UserReg& users, int tester, int test_index, int test_progress)
{
	bool check = true;
	for (int i = 0; i < users.GetUser()[tester].progress.size(); i++)
	{
		if (users.GetUser()[tester].progress[i].first == test_index) // если под этим индексом уже есть прогресс и тестер его перепроходит то просто прогресс перезаписывается
		{
			users.GetUser()[tester].progress[i].second = test_progress;
			check = false;
		}
	}

	if (check)// если тест проходит в первый раз то тут записывается прогресс и индекс ,индекс нужен для определения какой это тест,чтобы потом можно было понять какие тесты перепроходить нужно
	{
		users.GetUser()[tester].progress.push_back(std::make_pair(test_index, test_progress));
	}
}

//Вывод оценок пользователя
void PrintTesterMark(UserReg& users, int number)
{
	for (int i = 0; i < users.GetUser()[number].mark.size(); i++)
	{
		if (users.GetUser()[number].mark[i].second < 20000) // 200000 это своего рода проверка на то ,пройден ли тесты на половину. тесты которые не пройдены полностью
														  // их среднеарифм-ое я умножаю на 20000,это делается чтобы различать какой пройден и какой нет тест
														  // если меньше 20000 значит тест завершен и он выводит оценки,те что больше 20000 он просто не выведит
		{
			std::cout << "\nTest : " << users.GetUser()[number].mark[i].first << std::endl;
			std::cout << "Mark : " << users.GetUser()[number].mark[i].second << std::endl;
		}
	}
}


//Создание тестов по новой теме 
void CreateNewTestName(Tests& test)
{

	std::string test_name;
	std::cin.ignore();
	std::cout << "Enter Test Name" << std::endl;
	std::getline(std::cin, test_name);

	if (test_name.size() <= 3)
	{
		std::cout << "\nYou cannt create a test with a short name\n";
	}
	test.VariousTests(test_name);
}

//Заполнения тестов определенной темы
void FillTheTest(Tests& exam)
{
	int choose_subject;
	bool check = true;
	TestData test;

	std::cout << "Select a subject to edit" << std::endl;
	for (int i = 0; i < exam.GetTestsSize(); i++)
	{
		std::cout << i + 1 << " : " << exam.GetTests()[i].GetTestName() << std::endl;
	}
	std::cin >> choose_subject;

	if (choose_subject <= exam.GetTestsSize())
	{
		do
		{
			std::cout << "1.Add Question" << std::endl;
			std::cout << "2.Exit" << std::endl;
			int choose;
			std::cin >> choose;

			switch (choose)
			{
			case 1:
				std::cin.ignore();
				std::cout << "Question: \n";
				std::getline(std::cin, test.question);
				std::cout << "A) ";
				std::getline(std::cin, test.first_variant);
				std::cout << "\nB) ";
				std::getline(std::cin, test.second_variant);
				std::cout << "\nC) ";
				std::getline(std::cin, test.third_variant);
				std::cout << "\nD) ";
				std::getline(std::cin, test.forth_variant);
				std::cout << "\nAnsewer: ";
				std::cin >> test.answer;

				exam.GetTests()[choose_subject - 1].Create(test.question, test.first_variant, test.second_variant, test.third_variant, test.forth_variant, test.answer);
				break;

			case 2:
				check = false;
				break;
			}
		} while (check);
	}
	else
	{
		std::cout << "\nThere is no tests like this" << std::endl;
		system("pause");
	}

}

//Работа с тестами
void TestWork(Tests& test, UserReg& users, int user_number)
{
	int choose;
	int true_ansewer = 0;
	int variant;
	int right_answer;
	int test_progress = 0;

	for (int i = 0; i < test.GetTestsSize(); i++)
	{
		std::cout << i + 1 << " : " << test.GetTests()[i].GetTestName() << std::endl;
	}
	std::cin >> choose;



	if (choose <= test.GetTestsSize())
	{
		for (int i = 0; i < users.GetUser()[user_number].mark.size(); i++) // Цикл проверяющий и который берет оценкци пользователя по данному тесту
		{
			if (users.GetUser()[user_number].mark[i].first == choose)
			{
				if (users.GetUser()[user_number].mark[i].second >= 20000)
				{
					true_ansewer = users.GetUser()[user_number].mark[i].second / 20000; //когда записываю в файл ,умножаю на 20к ,когда делю я определеяю сколько правильных ответов получается
				}																//умножаю я на 20к ,чтобы разделить количество правильных ответов от оценки,ведь сама оценка не может достичь этого результата
																				// это дает мне возможность разделить оценки от незовершенных тестов и при этом в его поле сохранилось количество верных ответов
			}
		}


		for (int i = 0; i < users.GetUser()[user_number].progress.size(); i++)// Цикл проверяющий и выкачиюващий прогресс пользователя по данному тесту
		{

			if (users.GetUser()[user_number].progress[i].first == choose)
			{
				test_progress = users.GetUser()[user_number].progress[i].second;
			}

		}
		system("cls");


		for (test_progress; test_progress < test.GetTests()[choose - 1].GetTestSize(); test_progress++) {


			std::cout << test.GetTests()[choose - 1].GetTest()[test_progress].question << std::endl;
			std::cout << "A) " << test.GetTests()[choose - 1].GetTest()[test_progress].first_variant << std::endl;
			std::cout << "B) " << test.GetTests()[choose - 1].GetTest()[test_progress].second_variant << std::endl;
			std::cout << "C) " << test.GetTests()[choose - 1].GetTest()[test_progress].third_variant << std::endl;
			std::cout << "D) " << test.GetTests()[choose - 1].GetTest()[test_progress].forth_variant << std::endl;
			std::cout << "Ansewer: ";
			std::cin >> variant;
			if (test.GetTests()[choose - 1].GetTest()[test_progress].answer == variant)
			{
				true_ansewer++;
			}

			else if (variant == 0)
			{
				break;
			}
			system("cls");
		}

		if (test_progress == test.GetTests()[choose - 1].GetTestSize())
		{
			right_answer = ((true_ansewer * 10) / test.GetTests()[choose - 1].GetTestSize());
			std::cout << "Correct Ansewers : " << true_ansewer << std::endl;
			std::cout << "Incorrect Ansewers : " << test.GetTests()[choose - 1].GetTestSize() - true_ansewer << std::endl;
			std::cout << "Overall procentage : " << ((true_ansewer * 100) / test.GetTests()[choose - 1].GetTestSize()) << "%" << std::endl;
			std::cout << " 10 ball " << right_answer << std::endl;
			test_progress = 0;
			TesterProgress(users, user_number, choose, test_progress);
			TesterMark(users, user_number, choose, right_answer);
			system("pause");
		}
		else {
			TesterProgress(users, user_number, choose, test_progress);
			TesterMark(users, user_number, choose, true_ansewer * 20000);
		}
	}
	else
	{
		std::cout << "Such test doesnt exists" << std::endl;
		system("pause");
	}



}

//Запись данных в файлы 
namespace FileData
{
	// Функция для записи в файл информации о администраторе
	void WriteToFileAdminData(UserReg& users)
	{
		std::ios::openmode mode = std::ios::trunc | std::ios::out;
		std::ofstream file("Admin.txt", mode);
		std::string new_password = passwordEncryption(users.GetAdmin().password);

		if (file.is_open())
		{
			file << users.GetAdmin().name << std::endl;
			file << users.GetAdmin().surname << std::endl;
			file << users.GetAdmin().fathers_name << std::endl;
			file << users.GetAdmin().login << std::endl;
			file << new_password << std::endl;
		}
		file.close();
	}

	// Функция для записи в файл информации о пользователе
	void WriteToFileUserData(UserReg& users)
	{
		std::ios::openmode mode = std::ios::trunc | std::ios::out;
		std::ofstream file("User.txt", mode);

		if (file.is_open())
		{
			file << users.GetUserSize() << std::endl;//записываем количество юзеров ,это в дальнейшем нужно будет когда читать данные из файла будем
			for (int i = 0; i < users.GetUserSize(); i++) {
				file << users.GetUser()[i].name << std::endl;
				file << users.GetUser()[i].surname << std::endl;
				file << users.GetUser()[i].fathers_name << std::endl;
				file << users.GetUser()[i].login << std::endl;
				file << passwordEncryption(users.GetUser()[i].password) << std::endl;
			}
		}
		file.close();
	}

	// Функция для записи в файл информации о тестах
	void WriteToFileTestInfo(Tests& test)
	{
		std::ios::openmode mode = std::ios::trunc | std::ios::out;
		std::ofstream file("Test.txt", mode);

		if (file.is_open())
		{
			file << test.GetTestsSize() << std::endl;//записываем количество тестов ,это в дальнейшем нужно будет когда читать данные из файла будем
			for (int i = 0; i < test.GetTestsSize(); i++)
			{
				file << test.GetTests()[i].GetTestSize() << std::endl; //есть тест ,допустим математика и у него есть подтест ,то есть в разделе математика может быть еще тесты
				file << test.GetTests()[i].GetTestName() << std::endl;

				for (int j = 0; j < test.GetTests()[i].GetTestSize(); j++)
				{
					file << test.GetTests()[i].GetTest()[j].question << std::endl;
					file << test.GetTests()[i].GetTest()[j].first_variant << std::endl;
					file << test.GetTests()[i].GetTest()[j].second_variant << std::endl;
					file << test.GetTests()[i].GetTest()[j].third_variant << std::endl;
					file << test.GetTests()[i].GetTest()[j].forth_variant << std::endl;
					file << test.GetTests()[i].GetTest()[j].answer << std::endl;
				}
			}
		}
		file.close();
	}

	// Функция для записи в файл информации о прогрессе пользователей (оценки и моменты остановки )
	void WriteToFileProgressInfo(UserReg& users)
	{
		std::ios::openmode mode = std::ios::trunc | std::ios::out;
		std::ofstream file("Progress.txt", mode);

		if (file.is_open())
		{
			file << users.GetUserSize() << std::endl;//записываем количество тесторов ,это в дальнейшем нужно будет когда читать данные из файла будем
			for (int i = 0; i < users.GetUserSize(); i++)
			{
				file << users.GetUser()[i].mark.size() << std::endl; //есть тест ,допустим математика и у него есть оценка ,записывается и то и другое
				for (int j = 0; j < users.GetUser()[i].mark.size(); j++)
				{
					file << users.GetUser()[i].mark[j].first << std::endl; // test number
					file << users.GetUser()[i].mark[j].second << std::endl; // test mark
					file << users.GetUser()[i].progress[j].first << std::endl; // test number
					file << users.GetUser()[i].progress[j].second << std::endl; // test progress
				}
			}
		}
		file.close();
	}

	// Функция для чтения из файл информации о пользователях
	void ReadInFileUserInfo(UserReg& users)
	{
		std::ios::openmode mode = std::ios::in;
		std::ifstream file("User.txt", mode);

		UserData user;
		size_t size1;
		std::string user_number;
		std::string crypto_password;

		if (file.is_open())
		{
			getline(file, user_number); // до этого я записывал количество юзеров в файл,сейчас в сайзе хранится первая строчка ,то есть размер
			size1 = atoi(user_number.c_str());// тут из символа он становится интом ,дабы мы знали сколько юзеров всего 
			for (int i = 0; i < size1; i++)
			{
				getline(file, user.name);
				getline(file, user.surname);
				getline(file, user.fathers_name);
				getline(file, user.login);
				getline(file, crypto_password);
				user.password = passwordDecryption(crypto_password);
				users.RegisterPerson(user.name, user.surname, user.fathers_name, user.login, user.password);
			}
		}
		file.close();
	}

	// Функция для чтения из файл информации о тестах
	void ReadInFileTestInfo(Tests& tests)
	{
		std::ios::openmode mode = std::ios::in;
		std::ifstream file("Test.txt", mode);

		TestData test;
		size_t size_test;
		size_t various_tests_size;
		std::string answer_string;
		std::string test_number;
		std::string test_various;
		std::string test_name;

		if (file.is_open())
		{
			getline(file, test_number);// до этого я записывал количество тестов в файл,сейчас в сайзе хранится первая строчка ,то есть размер
			size_test = atoi(test_number.c_str());// тут из символа он становится интом ,дабы мы знали сколько тестов есть всего 

			for (int i = 0; i < size_test; i++)
			{
				getline(file, test_various);// у каждого теста есть свои подтесты ,тут хранится символьное количество
				various_tests_size = atoi(test_various.c_str());// тут из символа мы получаем интовое число,оно показывает количество подтестов

				getline(file, test_name);
				tests.VariousTests(test_name);
				for (int j = 0; j < various_tests_size; j++)
				{
					getline(file, test.question);
					getline(file, test.first_variant);
					getline(file, test.second_variant);
					getline(file, test.third_variant);
					getline(file, test.forth_variant);
					getline(file, answer_string);
					test.answer = atoi(answer_string.c_str());
					tests.GetTests()[i].Create(test.question, test.first_variant, test.second_variant, test.third_variant, test.forth_variant, test.answer);
				}
			}
		}
		file.close();
	}

	// Функция для чтения из файл информации  о прогрессе пользователей (оценки и моменты остановки )
	void ReadInProgressInfo(UserReg& users)
	{
		std::ios::openmode mode = std::ios::in;
		std::ifstream file("Progress.txt", mode);

		size_t tester_size;
		size_t mark_size;
		std::string tester_number;
		std::string mark_number;
		std::string index_mark;
		std::string index_progress;
		std::string mark1;
		int mark;
		std::string progress1;
		int progress;
		int index_1;
		int index_2;

		if (file.is_open())
		{
			getline(file, tester_number);
			tester_size = atoi(tester_number.c_str());

			for (int i = 0; i < tester_size; i++)
			{
				getline(file, mark_number);
				mark_size = atoi(mark_number.c_str());
				for (int j = 0; j < mark_size; j++)
				{
					getline(file, index_mark);
					getline(file, mark1);

					index_1 = atoi(index_mark.c_str());
					mark = atoi(mark1.c_str());

					getline(file, index_progress);
					getline(file, progress1);
					index_2 = atoi(index_progress.c_str());
					progress = atoi(progress1.c_str());
					users.GetUser()[i].mark.push_back(std::make_pair(index_1, mark)); // test number and mark for the test
					users.GetUser()[i].progress.push_back(std::make_pair(index_2, progress)); // test number and progress for the test

				}
			}
		}
		file.close();
	}
}

//Меню для администратора 
void MenuAdmin(UserReg& users, Tests& test)
{
	int choose;

	if (AdminLogin(users))
	{
		system("cls");
		std::cout << "___________________Choose Option____________________\n";
		std::cout << "1.Edit Admin \n";
		std::cout << "2.Create Tester\n";
		std::cout << "3.Delete Tester\n";
		std::cout << "4.Edit Tester\n";
		std::cout << "5.Information about tests\n";
		std::cout << "6.Create test topic\n";
		std::cout << "7.Add question in test\n";
		std::cout << "8.Exit" << std::endl;
		std::cin >> choose;

		switch (choose)
		{
		case 1:
			system("cls");
			EditAdmin(users);
			break;

		case 2:
			system("cls");
			TesterRegistration(users);
			break;

		case 3:
			system("cls");
			DeleteTester(users);
			break;

		case 4:
			system("cls");
			TesterEdit(users);
			break;

		case 5:
			system("cls");
			for (int i = 0; i < users.GetUserSize(); i++)
			{
				std::cout << "User " << i + 1 << std::endl;
				PrintTesterMark(users, i);
			}
			system("pause");
			break;

		case 6:
			system("cls");
			CreateNewTestName(test);
			break;

		case 7:
			system("cls");
			FillTheTest(test);
			break;
		}
	}
}

//Меню для тестера
void MenuTester(UserReg& users, Tests& test)
{
	int  user_number;
	int choose;
	bool menu_work = true;

	user_number = TesterLogin(users);
	system("cls");

	if (user_number >= 0)
	{
		system("cls");
		std::cout << "___________________Choose Option____________________\n";
		std::cout << "1.Start Test" << std::endl;
		std::cout << "2.Previous results" << std::endl;
		std::cout << "3.Exit" << std::endl;
		std::cin >> choose;

		switch (choose)
		{
		case 1:
			system("cls");
			TestWork(test, users, user_number);
			break;
		case 2:
			PrintTesterMark(users, user_number);
			system("cls");
			break;
		case 3:
			menu_work = false;
			break;

		}
	}
}

//Главное меню
void Application()
{
	UserReg users;
	Tests test;

	FileData::ReadInFileUserInfo(users);
	FileData::ReadInFileTestInfo(test);
	FileData::ReadInProgressInfo(users);
	AdminRegistration(users);

	system("cls");
	int choose;
	std::cout << "___________________Choose Option____________________\n";
	std::cout << "1. Admin Login" << std::endl;
	std::cout << "2. Tester Login" << std::endl;
	std::cout << "3. Tester registration" << std::endl;
	std::cout << "4. Exit" << std::endl;
	std::cin >> choose;

	switch (choose)
	{

	case 1:
		system("cls");
		MenuAdmin(users, test);

		break;
	case 2:
		system("cls");
		MenuTester(users, test);

		break;
	case 3:
		system("cls");
		TesterRegistration(users);
		break;
	}

	FileData::WriteToFileAdminData(users);
	FileData::WriteToFileUserData(users);
	FileData::WriteToFileTestInfo(test);
	FileData::WriteToFileProgressInfo(users);
}


int main()
{
	Application();
}