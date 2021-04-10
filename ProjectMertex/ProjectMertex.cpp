// ProjectMertex.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <String>
#include <regex>

using namespace std;

struct MyToDo
{
	string description;
	string date;

	void print() {
		cout << date << " - " << description << endl;
	}
};

int check(vector<MyToDo> ToDoList, string act, int flag) {
	int location = 0;
	for (size_t i = 0; i < ToDoList.size(); i++) {
		if (ToDoList[i].date == act.substr(act.length() - 16) && flag == 1) {
			location = i + 1;
			break;
		}
		else if (ToDoList[i].date < act.substr(act.length() - 16) && flag == 2) {
			location += 1;
		}
		else if (ToDoList[i].date > act.substr(act.length() - 16) && flag == 3) {
			location = i + 1;
			break;
		}
		else if (ToDoList[i].date <= act.substr(act.length() - 16) && flag == 4) {
			location += 1;
		}
		else if (ToDoList[i].date >= act.substr(act.length() - 16) && flag == 5) {
			location += 1;
		}
	}
	return location;
};

int main()
{
	setlocale(LC_ALL, "ru");

	cout << "Вас приветствует консольное приложение To Do List." << endl;
	bool exitToDo = false;

	vector<MyToDo> ToDoList;
	string act;
	regex regular_add("(add) ([\\w\\s\\d\\Q.?()+{}*^'\\E\\\\\"\\/\\|\\!\\$\\[\\],;:-_-@#№%&<>=])* (\\d{4})-(0[1-9]|1[0-2])-(3[0-1]|[1-2][0-9]|0[1-9]) ([0-1][0-9]|2[0-3]):([0-5][0-9])");
	regex regular_update("(update) ([\\w\\s\\d\\Q.?()+{}*^'\\E\\\\\"\\/\\|\\!\\$\\[\\],;:-_-@#№%&<>=])* (\\d{4})-(0[1-9]|1[0-2])-(3[0-1]|[1-2][0-9]|0[1-9]) ([0-1][0-9]|2[0-3]):([0-5][0-9])");
	regex regular_delete("(delete) (\\d{4})-(0[1-9]|1[0-2])-(3[0-1]|[1-2][0-9]|0[1-9]) ([0-1][0-9]|2[0-3]):([0-5][0-9])");
	regex regular_select_date("(select) (where date) (<|>|=|<=|>=) (\\d{4})-(0[1-9]|1[0-2])-(3[0-1]|[1-2][0-9]|0[1-9]) ([0-1][0-9]|2[0-3]):([0-5][0-9])");
	regex regular_select_descriptor("(select) (where descriptor hase) ([\\w\\s\\d\\Q.?()+{}*^'\\E\\\\\"\\/\\|\\!\\$\\[\\],;:-_-@#№%&<>=])*");
	regex regular_select("(select \\*)");
	regex regular_help("(help)");
	regex regular_exit("(exit)");

	while (!exitToDo) {
		
		cout << "Доступны следующие команды: add, delete, update, select, help, exit." << endl 
			<< "Формат даты и времени(гггг-мм-дд 00:00)." << endl << endl;
		getline(cin, act);
		cout << endl;
	
		if (regex_match(act.c_str(), regular_add)) {  
			act.erase(0, 4);

			if (ToDoList.empty() == true || check(ToDoList, act, 1) == 0) {
				MyToDo m;
				m.date = act.substr(act.length() - 16);
				m.description = act.substr(0, act.length() - 16); 
				ToDoList.insert(ToDoList.cbegin() + check(ToDoList, act, 2), m);
				act.clear();
				cout << "Задача создана!" << endl;
			}
			else {
				cout << "Задача с указанными датой и временем уже создана, пожалуйста введите другую дату и время." << endl 
					<< "Или измените существующую задачу." << endl;
			}
		}

		else if (regex_match(act.c_str(), regular_update)) {
			act.erase(0, 7);

			if (check(ToDoList, act, 1) > 0) {
				ToDoList[check(ToDoList, act, 1) - 1].description = act.substr(0, act.length() - 16); 
				act.clear();
				cout << "Задача обновлена!" << endl;
			}
			else { cout << "За указзанную дату и время активных задач не найдено." << endl; }
		}

		else if (regex_match(act.c_str(), regular_delete)) {
			act.erase(0, 7);

			if (check(ToDoList, act, 1) > 0) {
				ToDoList.erase(ToDoList.cbegin() + check(ToDoList, act, 1) - 1);
				act.clear();
				cout << "Задача удалена!" << endl;
			}
			else { cout << "За указзанную дату и время активных задач не найдено." << endl; }
		}

		else if (regex_match(act.c_str(), regular_select_date)) {
			act.erase(0, 7);

			if (act.substr(act.length() - 19, 2) == " =") {
				if (check(ToDoList, act, 1) != 0) {
					ToDoList[check(ToDoList, act, 1) - 1].print();
				}
				else { cout << "Нет задач соответствующих выбранным условиям." << endl; }
			}

			else if (act.substr(act.length() - 18, 1) == "<") {
				if (check(ToDoList, act, 2) != 0) {
					for (int i = 0; i < check(ToDoList, act, 2); i++) {
						ToDoList[i].print();
					}
				}
				else { cout << "Нет задач соответствующих выбранным условиям." << endl; }
			}

			else if (act.substr(act.length() - 18, 1) == ">") {
				if (check(ToDoList, act, 3) != 0) {
					for (size_t i = check(ToDoList, act, 3) - 1; i < ToDoList.size(); i++) {
						ToDoList[i].print();
					}
				}
				else { cout << "Нет задач соответствующих выбранным условиям." << endl; }
			}

			else if (act.substr(act.length() - 19, 2) == "<=") {
				if (check(ToDoList, act, 4) != 0) {
					for (int i = 0; i < check(ToDoList, act, 4); i++) {
						ToDoList[i].print();
					}
				}
				else { cout << "Нет задач соответствующих выбранным условиям." << endl; }
			}

			else if (act.substr(act.length() - 19, 2) == ">=") {
				if (check(ToDoList, act, 5) != 0) {
					for (size_t i = check(ToDoList, act, 5) - 1; i < ToDoList.size(); i++) {
						ToDoList[i].print();
					}
				}
				else { cout << "Нет задач соответствующих выбранным условиям." << endl; }
			}
			else { cout << "Нет задач соответствующих выбранным условиям." << endl; }
		}

		else if (regex_match(act.c_str(), regular_select_descriptor)) {
			int c = 0;
			if (ToDoList.empty() != true) {
				for (size_t i = 0; i < ToDoList.size(); i++) {
					if (ToDoList[i].description.find(act.substr(29)) != string::npos) {
						ToDoList[i].print();
						c++;
					}
				}
			}
			else { cout << "Список задач пуст." << endl; }
			if (c == 0) { cout << "Задач с таким содержимым нет." << endl; }
		}

		else if (regex_match(act.c_str(), regular_select)) {
			
			if (ToDoList.empty() != true) {
				for (size_t i = 0; i < ToDoList.size(); i++) {
					ToDoList[i].print();
				}
			}
			else { cout << "Список задач пуст." << endl; }
		}

		else if (regex_match(act.c_str(), regular_help)) {
			cout << "Команды вводятся в следующем формате:" << endl;
			cout << "add: add descriptor date (add text 2020-12-12 00:00) - добавить задачу на дату 2020-12-12 00:00" << endl;
			cout << "update: update descriptor date (update text 2020-12-12 00:00) - обновить задачу за дату 2020-12-12 00:00" << endl;
			cout << "delete: delete date (delete 2020-12-12 00:00) - удалить задачу за дату 2020-12-12 00:00" << endl;
			cout << "select: select * - вывод всех задач" << endl;
			cout << "select: select where date <; >; =; <=; >= date (select where date <= 2020-12-12 00:00) - вывод всех задач которые <= 2020-12-12 00:00" << endl;
			cout << "select: select where descriptor hase string (select where descriptor hase text) - вывод всех задач где в описании содержиться text" << endl;
			cout << "help: help - помощь" << endl;
			cout << "exit: exit - выход" << endl;
		}

		else if (regex_match(act.c_str(), regular_exit)) {
			cout << "Спасибо, за использование программы!" << endl;
			exitToDo = true;
		}

		else { cout << "Некорректный формат ввода или неверная команда." << endl; }
	}
}

