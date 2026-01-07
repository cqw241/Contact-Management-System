/**
 *项目名称：C++ 通讯录管理系统
 * 作者：[CQW]
 * 日期：2026-1-7
 * 描述：这是一个基于控制台的通讯录管理系统，实现了联系人的增删改查功能。
 * 技术点：结构体、指针、数组、流程控制、输入输出处理等。
 **/
#include "CMS.h"
#include <iostream>
#include <string>
#include <limits> // 必须添加这个头文件才能使用 numeric_limits
using std::cin;
using std::cout;
using std::getline;
using std::numeric_limits;
using std::string;
using std::endl;
using std::streamsize;


int main() {
	contact mycontact;
	contact* conptr = &mycontact;
	//menu
	while (in_flag)
	{
		int choice = 1;
		showmenu();
		if (cin >> choice) {
			switch (choice) {
			case 1: add(&mycontact); break;
			case 2: show(&mycontact); break;
			case 3: deleteperson(&mycontact); break;
			case 4: find(&mycontact); break;
			case 5: modify(&mycontact); break;
			case 6: clear(&mycontact); break;
			case 0: exit_system(); break;
			default: menu_invaild_input(); continue;
			}
		}
		else {
			menu_invaild_input(); continue;
		}
	}
}