//�������� ����. �������������� ���������� ������� ����������
//�������� ������ � �������. ��������� ChatBot'�. ������� ��
//���� ������. ���������� �������� �� ��������� �������� false
//��� ������ �� ���� ����. ������� �� ��������� false ��� ������ 
//�� ���� �����.
#include <stdlib.h>
#include "command_module.h"
#include <iostream>

auto main() -> int
{
	system("chcp 1251");
	system("cls");
	srand((unsigned int) time(0));
	CommandModule unworkableChat;
	unworkableChat.InitChatBot();
	unworkableChat.InitAutoDict();
	std::cout << "����� ���������� � ������������ ���!" << std::endl;
	while (unworkableChat.worksChat_)
	{
		unworkableChat.LoginMenu();
		while (unworkableChat.worksUser_)
		{
			unworkableChat.PrintHistory();
			unworkableChat.ChatMenu();
		}
	}
	return 0;
}
