//��������� ��� �������������� �������, ��������������� ����������.
//���� ����� � ���: �����������, ��������������, ����� �� ���������.
//���� ����: �������� ��������� ����, ���������� ������������,
//�������� ������� ���������� ������������, ����� �� ��������.
//�������� ���������. ���������� ������� ���������. 
//ChatBot - ������� �������, ��������� �� ��� ��������� � ����, � ���� ���
//���������. ������ ������. ��������� ����� ���������, �� �������� ���������� 
//����� ���. ����� �� �������� ���������� AI ChatGPT (���� ������� �� �������).
//������ 2.0: ������ ������������ ������� ������ ������� ����� �������� 
//���������� ������. ��������� ������� �������������� ���� �� ��������.
#pragma once
#include "message.h"
#include "user.h"
#include "autocomplete_dictionary.h"

class CommandModule
{
	std::vector<User<std::string, std::vector<std::string>>> users_;
	User<std::string, std::vector<std::string>>* user_ = nullptr;
	Message* message_ = nullptr;
	std::vector<std::string> chatBotAnswers_;
	size_t currentUser_ = 0; 
	AutocompleteDictionary* autoDict_ = new AutocompleteDictionary;
	char wordConstructor_[100] = {};
	char symbol_ = {};
	size_t position_ = 0;
	std::string prefix_;

	void Registration();
	auto LogIn() -> bool;
	void MessageToAll();
	void MessageToUser();
	void PrintUsers();
	void UserInfo();
	void AnswerChatBot();

public:
	bool worksChat_ = true;
	bool worksUser_ = false;
	bool autocompleteEnable_ = false;

	CommandModule() = default;
	~CommandModule() = default;
	auto LoginMenu() -> bool;
	void InitChatBot();
	auto ChatMenu() -> bool;
	void PrintHistory();
	void InitAutoDict();
	auto characterInput(std::string const text) -> std::string;
};