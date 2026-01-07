#include "CMS.h"
#include <iostream>
#include <limits>
using std::cin;
using std::cout;
using std::getline;
using std::numeric_limits;
using std::string;
using std::endl;
using std::streamsize;

bool in_flag = true;

void clean_input_buffer() {
	cin.clear(); // 清除错误标志
	//原型：cin.ignore(要忽略的最大字符数, 终止字符);
	 /*从输入缓冲区中逐个读取并丢弃字符，直到满足以下任一条件：
	1.已经丢弃了 “最大字符数” 个字符；
	2.遇到了 “终止字符”（终止字符也会被丢弃）。*/
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //清空输入缓冲区中从当前位置到换行符的所有字符（也就是清空用户本次输入的整行错误数据）。
	
	
}

bool add(contact* conptr) {
	if (conptr->size >= MAXSIZE)
	{
		cout << "Contact is full, cannot add more person!" << endl;
		system("pause");
		system("cls");
		return false;
	}

	else {
		//add 中先用 getline 读姓名，所以在调用它之前如果主循环用 cin >> choice，缓冲区还残留着上一轮输入后的换行符。
		//getline 看到这个换行符就立刻返回空字符串，导致姓名提示后马上跳到性别提示。
		//解决办法是在从数字输入切换到 getline 之前丢弃残留的换行符*/
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清掉换行
		cout << "Please enter the name: ";
		getline(cin, conptr->personArray[conptr->size].name);
		for (int i = 0; i < conptr->size; ++i) {
			if (conptr->personArray[conptr->size].name == conptr->personArray[i].name) {
				cout << "This person is already in the contact, cannot add again!\n";
				system("pause");
				system("cls");
				return false;
			}
		}

		cout << "Please enter the sex(M/F):";
		while (cin >> conptr->personArray[conptr->size].sex) {
			if ((conptr->personArray[conptr->size].sex == "M") || (conptr->personArray[conptr->size].sex == "F")) {
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;

			}
			else {
				clean_input_buffer();
				cout << "Invalid input, please enter again!\nPlease enter the sex(M/F):";
			}
		}
		//	cin >> age; while (!cin >> age) 实际上是先读一次，再用括号优先级导致的 while (!(cin >> age))，而且 fail 状态没有在成功后清理。
		/*cout << "Please enter the age:";
		cin >> conptr->personArray[conptr->size].age;
		while (!cin >> conptr->personArray[conptr->size].age) {
			if (conptr->personArray[conptr->size].age > 0 && conptr->personArray[conptr->size].age < 150) {
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;

			}
			else {
				cout << "Invalid input, please enter again!\nPlease enter the age:";
				clean_input_buffer();
				continue;
			}
		}*/
		//解决方案：用单个循环同时做输入和范围校验，成功后清空换行；失败时清理流并重新提示。
		int age = 0;
		cout << "Please enter the age:";
		while (true) {
			if (cin >> age && age > 0 && age < 150) {
				conptr->personArray[conptr->size].age = age;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			}
			cout << "Invalid input, please enter again!\nPlease enter the age:";
			clean_input_buffer();
		}


		cout << "Please enter the phone number:";
		getline(cin, conptr->personArray[conptr->size].phone);
		cout << "Please enter the address:";
		getline(cin, conptr->personArray[conptr->size].address);
		cout << conptr->personArray[conptr->size].name << "has been added successfully\n";
		++conptr->size;

		system("pause");
		system("cls");
		return true;
	}

}

void show(contact* conptr) {
	if (conptr->size == 0) {
		cout << "The contact is empty.\n";
	}
	else {
		for (int i = 0; i < conptr->size; ++i) {
			cout << "*********************************************\n";
			cout << "Name:" << conptr->personArray[i].name << "\n";
			cout << "Sex:" << conptr->personArray[i].sex << "\n";
			cout << "Age:" << conptr->personArray[i].age << "\n";
			cout << "Phone:" << conptr->personArray[i].phone << "\n";
			cout << "Home Address:" << conptr->personArray[i].address << "\n";
			cout << "*********************************************\n\n";
		}

	}
	system("pause");
	system("cls");
}


bool deleteperson(contact* conptr) {
	if (conptr->size == 0) {
		cout << "The contact is empty.\n";
		return false;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string delete_person;
	cout << "Who do you want to delete:";
	getline(cin, delete_person);
	for (int i = 0; i < conptr->size; ++i) {
		if (delete_person == conptr->personArray[i].name) {
			for (int j = i; j < conptr->size - 1; ++j) {
				conptr->personArray[j] = conptr->personArray[j + 1];
			}
			cout << "Delete successfully!\n";
			--conptr->size;
			return true;
		}


	};
	cout << delete_person << " isn't in the contact.\n";
	system("pause");
	system("cls");
	return false;

}


bool find(contact* conptr) {
	if (conptr->size == 0) {
		cout << "The contact is empty.\n";
		return false;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string find_person;
	cout << "Who do you want to find（Enter the name）:";
	getline(cin, find_person);
	cout << "*********************************************\n";
	for (int i = 0; i < conptr->size; ++i) {
		if (find_person == conptr->personArray[i].name) {
			cout << "Find successfully!\n";
			cout << "Name:" << conptr->personArray[i].name << "\n";
			cout << "Sex:" << conptr->personArray[i].sex << "\n";
			cout << "Age:" << conptr->personArray[i].age << "\n";
			cout << "Phone:" << conptr->personArray[i].phone << "\n";
			cout << "Home Address:" << conptr->personArray[i].address << "\n";
			cout << "*********************************************\n\n";
			system("pause");
			system("cls");
			return true;
		}

	}
	cout << find_person << " isn't in the contact.\n";
	system("pause");
	system("cls");
	return false;
};



bool modify(contact* conptr) {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string modify_person;
	cout << "Who do you want to modify:";
	getline(cin, modify_person);
	for (int i = 0; i < conptr->size; ++i) {
		if (modify_person == conptr->personArray[i].name) {
			cout << "Name:" << conptr->personArray[i].name << "\n";
			cout << "Sex:" << conptr->personArray[i].sex << "\n";
			cout << "Age:" << conptr->personArray[i].age << "\n";
			cout << "Phone:" << conptr->personArray[i].phone << "\n";
			cout << "Home Address:" << conptr->personArray[i].address << "\n";

			int m_choice = 1;
			while (m_choice) {
				cout << "What infomation do you want to modify?\n";
				cout << "1:Name\t2.Sex\t3.Age\n4.PhoneNumber\t5.HomeAddress\t0.Exit modify system\n";
				cin >> m_choice;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				switch (m_choice) {
				case 1: {
					string new_name;
					cout << "Enter the new name:";
					getline(cin, new_name);
					conptr->personArray[i].name = new_name;
					cout << "Modify successfully!\n\n";
					break;
				}
					  //在case中声明变量时，必须使用大括号创建局部作用域，否则编译器会报错
					  //即使在case中只有一行代码，也需要用大括号包裹
					  //这种做法有助于管理资源生命周期
				case 2: {
					string new_sex;
					cout << "Please enter the new sex(M/F):";
					while (true) {
						getline(cin, new_sex);
						if ((new_sex == "M") || (new_sex == "F")) {
							conptr->personArray[i].sex = new_sex;
							cout << "Modify successfully!\n\n";
							break;

						}
						else {
							clean_input_buffer();
							cout << "Invalid input, please enter again!\nPlease enter the sex(M/F):";
						}
					}
					break;

				}

				case 3: {
					cout << "Please enter the new age:";
					//错误示范
					/*while (cin >> new_age) {
						if (new_age > 0 && new_age < 130) {
							conptr->personArray[i].age = new_age;
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							cout << "Modify successfully!\n";
							break;

						}
						else {
							clean_input_buffer();
							cout << "Invalid input, please enter again!\nEnter the age:";
						}
					}*/
					//解决方案：用单个循环同时做输入和范围校验，成功后清空换行；失败时清理流并重新提示。
					int new_age = 0;
					while (true) {
						if (cin >> new_age && new_age > 0 && new_age < 150) {
							conptr->personArray[i].age = new_age;
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							cout << "Modify successfully!\n\n";
							break;
						}
						cout << "Invalid input, please enter again!\nPlease enter the age:";
						clean_input_buffer();
					}
					break;
				}

				case 4: {
					string new_phone;
					cout << "Enter the new phone number:";
					getline(cin, new_phone);
					conptr->personArray[i].phone = new_phone;
					cout << "Modify successfully!\n\n";
					break;

				}

				case 5: {
					string new_address;
					cout << "Enter the new address:";
					getline(cin, new_address);
					conptr->personArray[i].address = new_address;
					cout << "Modify successfully!\n\n";
					break;
				}
				case 0: cout << "\n\n"; break;

				}
			}
			system("pause");
			system("cls");
			return true;
		}

	}
	cout << modify_person << "isn't in the contact.\n\n";
	system("pause");
	system("cls");
	return false;
}


void clear(contact* conptr) {
	conptr->size = 0;
	cout << "Clear successfully!\n";
	system("pause");
	system("cls");
}

void showmenu() {
	cout << "*********************************" << "\n";
	cout << "Welcome to use the contact system!" << "\n";
	cout << "1:Add person\n2.Show contact system\n3.Delete person\n4.Find peroson\n5.Modify person\n6.Clear contact system\n0.Exit\n";
	cout << "*********************************" << "\n";
	cout << "Please enter your choice(0~6):";
}



void exit_system() {
	cout << "Exit successfully.Welcome back next time!\n";
	in_flag = false;
}

void menu_invaild_input() {
	system("cls");
	cout << "Invalid input, please enter again!\n";
	clean_input_buffer();
}
