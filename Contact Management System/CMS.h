#pragma once
#include <string>
#include <iostream>

const int MAXSIZE = 1000;
extern bool in_flag;

struct person {
    std::string name;
    std::string sex;
    int age;
    std::string phone;
    std::string address;
};

struct contact {
    person personArray[MAXSIZE];
    int size = 0;
};

void clean_input_buffer();
bool add(contact* conptr);
void show(contact* conptr);
bool deleteperson(contact* conptr);
bool find(contact* conptr);
bool modify(contact* conptr);
void clear(contact* conptr);
void showmenu();
void exit_system();  // 重命名，避免与标准库函数冲突
void menu_invaild_input();
