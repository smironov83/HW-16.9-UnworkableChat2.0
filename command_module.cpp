//������ 2.0: ������ ������������ ������� ������ ������� ����� �������� 
//���������� ������. ��������� ������������.
#include "command_module.h"
#include "bad_range.h"
#include <iostream>
#include <conio.h>

//���� �����. ������������ ���� ������ �������, ���� ����������� �������� ��
//�����������. ���������� ����� � ���, ������������������ � ����, ����� �� 
//���������. ���������� �������� true ��� main - ��������� ��������.
//��� ����� ������� ������ - ���������� false � ���� � main �����������
//� ����������� ����������� ������ ���������.
auto CommandModule::LoginMenu()->bool
{
	std::cout << std::endl;
	size_t command = 0;
	std::cout << "��� ����������� ������ ������� ����� �������:" << std::endl;
	std::cout << "1 - ����� � ���" << std::endl;
	std::cout << "2 - ������������������ � ����:" << std::endl;
	std::cout << "3 - ����� �� ���������" << std::endl;
	while (!(std::cin >> command) || (std::cin.peek() != '\n') || !(command == 1
		|| command == 2 || command == 3))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "�� ����� �������� ����� �������. ����������, ��������� ����: "
			<< std::endl;
	}
	switch (command)
	{
	case 1:
		users_[currentUser_].online_ = LogIn();
		worksUser_ = users_[currentUser_].online_;
		break;
	case 2:
		Registration();
		break;
	case 3:
		std::cout << std::endl <<
			"����� ����, ��� �� ��������� ������������ ���! ��� ������ �����������!"
			<< std::endl;
		worksChat_ = false;
		autoDict_->Remove(autoDict_);
		delete autoDict_;
		break;
	}
	return worksChat_;
}

//������������ ChatBot'�. ���������� ��� � ���� �� �������� online.
// �������������� ��������� ����� ����.
void CommandModule::InitChatBot()
{
	user_ = new User<std::string, std::vector<std::string>>{ "ChatBot", "qwerty"
		, "Bot", true };
	users_.push_back(*user_);
	chatBotAnswers_ = { "����� ���-�� ����?",
		"���������� �����! ��� ����� ���� � ��� �� �����������!",
		"� ���� � ���������� ��� �������� �������!",
		"� � ��� ����� � ������ ���� ��������!",
		"� � ���� ���� �����! �������� �� �������� ��������?",
		"�� � ��� �� ����� �����?",
		"� � - ������� � ������� ChatBot ����� ������������� ����!",
		"� ��� �� �������!",
		"� �� ������ ��-������!" };
	delete user_;
}

//������������ ������ ������������. ���� ������: �����, ������ � ���.
//��������� ����� �� ������������ �� ���� ������������������ �������������.
//����� "exit" ��������� �� ��������� �������� ������, �.�. ���������������
//��� ������ �� ���� ����� � ���.
void CommandModule::Registration()
{
	std::cout << std::endl;
	user_ = new User<std::string, std::vector<std::string>>{};
	auto unique = true;
	std::cout << "������� �����: ";
	do
	{
		std::cin >> user_->login_;
		unique = true;
		for (auto& user : users_)
		{
			if ((user_->login_ == user.login_) || (user_->login_ == "exit"))
			{
				unique = false;
				std::cout << "����� �����. ������� ������ �����: ";
			}
		}
	} while (!(unique));
	std::cout << "������� ������: ";
	std::string passEnter;
	std::cin >> passEnter;
	user_->set_password(passEnter);
	std::cout << "������� ���� ���: ";
	std::cin >> user_->name_;
	user_->online_ = false;
	users_.push_back(*user_);
	std::cout << "����������� ������� ���������. ��� ����������� ������ ������� "
		"� ������������ ��� ��� ������ �������� �������!" << std::endl;
	delete user_;
}

//������������ ������������ �� ������ �����/������, ������� �� �������
//������������������ �������������. ������������ ����� � ���������� ����
//�� ��������� ����� "exit" �� ������, ���� ������������ ����� ������� ������.
//���������� �������� "true" ��� �������� ������� ������������ � ������� 
//����� ��������������� ������������ � ��� ��� main. ��������� �������� �������
//�������� �������, � ������� �������� ������ ������������, ������������ ���� �
// ���. ����� ����������� ���������� �������� ����� ��������������.
auto CommandModule::LogIn() -> bool
{
	std::cout << std::endl;
	user_ = new User<std::string, std::vector<std::string>>{};
	std::cout << "��� ����� � ������������ ��� ������� ���� ������� ������!"
		<< std::endl;
	auto unique = true;
	auto online = true;
	do
	{
		do
		{
			auto counter = 0;
			std::cout << "������� �����: ";
			std::cin >> user_->login_;
			for (auto& user : users_)
			{
				if (user_->login_ == user.login_)
				{
					unique = false;
					currentUser_ = counter;
				}
				if (unique && (counter == users_.size() - 1) && (user_->login_ != 
					"exit"))
				{
					std::cout << "����� �� ���������������. ��������� ���� ��� ������� "
						"exit ��� �������� � ���������� ����." << std::endl;
				}
				if (user_->login_ == "exit")
				{
					unique = false;
					online = false;
				}
				counter++;
			}
		} while (unique);
		if (user_->login_ != "exit")
		{
			std::cout << "������� ������: ";
			std::string passEnter;
			std::cin >> passEnter;
			if (user_->CheckPassword(passEnter) != users_[currentUser_].
				get_password())
			{
				std::cout << "������ ��������. ��������� ���� ������ � ������ ��� "
					"������� exit ��� �������� � ���������� ����." << std::endl;
				unique = true;
			}
		}
	} while (unique);
	delete user_;
	if (!online)
		return online;
	std::cout << std::endl;
	size_t command = 0;
	std::cout << "��� ��������� ������ �������������� ������� 1, ����� - 0" << 
		std::endl;
	while (!(std::cin >> command) || (std::cin.peek() != '\n') || !(command == 0
		|| command == 1))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << 
			"�� ����� �������� ����� �������. ����������, ��������� ����: "	
			<< std::endl;
	}
	if (command == 1)
	{
		autocompleteEnable_ = true;
		system("cls");
		std::cout << "������������!\n\n� ������ ��������� ���������� ����� � �����"
			"�� ��������� �������������� �� ���������� ��������.\n��������� ��������"
			" ������ � ��������� ��������� ������ ��������.\n������� ������� �������"
			"��. ��� ��������� ����� �� ��������� ����������� � �������.\n����������"
			"�� ����� ���������� ���������� �������������� �� �������� �������������"
			"� ��������� ����� � ������.\n������� ����� ����������� �������������� <"
			"- � ->, ��������������.\n��� ������ �������� �������� �������������� ��"
			"����� ������� �����.\n\nP.S.�� ������������� ����������� ��������� � ��"
			"����� ������ ������ �� �������� ���������.\n��������, Backspace. ������"
			"�� ������������� ��������� ���������.\n�� ��� �� �����!\n\n";
		system("pause");
	}
	else
		autocompleteEnable_ = false;
	return online;
}

//���� ����. ������������ ���� ������ �������, ���� ����������� �������� ��
//�����������. ���������� �������� ��������� ���� �������������, ���������� 
//������������ (������ ���������), ����������� ������� ���������� 
//������������, ���� ����� �� ��������. ���������� �������� true ��� main -
//������������ �����������, �������� ��������� ����.
//��� ����� ������� ������ - ���������� false � ��������� ���� � main 
//����������� � ����������� ��������� � ���� �����.
auto CommandModule::ChatMenu() -> bool
{
	size_t command = 0;
	std::cout << "�������� ��������:" << std::endl;
	std::cout << "1 - �������� ��������� ����" << std::endl;
	std::cout << "2 - �������� ���������� ������������:" << std::endl;
	std::cout << "3 - ����������� ������� ���������� ������������" << std::endl;
	std::cout << "4 - ����� �� ����" << std::endl;
	while (!(std::cin >> command) || (std::cin.peek() != '\n') || !(command == 1
		|| command == 2 || command == 3 || command == 4))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << 
			"�� ����� �������� ����� ��������. ����������, ��������� ����: "
			<< std::endl;
	}
	switch (command)
	{
	case 1:
		system("cls");
		MessageToAll();
		break;
	case 2:
		system("cls");
		MessageToUser();
		break;
	case 3:
		system("cls");
		UserInfo();
		break;
	case 4:
		system("cls");
		std::cout << "�� ����� �� ����!" << std::endl;
		worksUser_ = users_[currentUser_].online_ = false;
		break;
	}
	return worksUser_;
}

//������� ���������� ��������� ����. ��������� ����������� � ���� 
//������������������ �������������. ��������� ����� ChatBot � ��������� �� 
//����.
void CommandModule::MessageToAll()
{
	PrintHistory();
	std::string text{ "[" + users_[currentUser_].login_ + "]->[All] : " };
	std::cout << text;
	std::cin.ignore();
	if (autocompleteEnable_)
	{
		text = characterInput(text);
		text.erase(0, users_[currentUser_].login_.size() + 12);
		autoDict_->stream_.clear();
	}
	else std::getline(std::cin, text);
	message_ = new Message{ message_->TimeStamp(), users_[currentUser_].login_,
		"All", text };
	for (auto& user : users_)
	{
		user.history_.push_back(message_->MessageConstructor());
	}
	delete message_;
	AnswerChatBot();
}

//������� ��� ������� ��������� ��� �������� ������������.
void CommandModule::PrintHistory()
{
	system("cls");
	for (auto& user : users_[currentUser_].history_)
		std::cout << user << std::endl;
	if (autocompleteEnable_)
		std::cout << autoDict_->stream_;
}

//���������� ��������� ���������� ������������. ����� ������ ������� ����������
//������� ����������, ����� ������ ������ ���� ������������������ 
//�������������, ����� ����� ������ ������������. ����������� ��������� �����,
//����������� ��������� � ��������������� �������� �������. ��������� �������
//��� �������� ������������ � ��� ����������. ��������� ������������ �� �����
//����� ���������. ChatBot ����� ��������� � ��������� �� ����, ������ ����
//�������� �����������. ����� ��������� ������ ��������� ������ ����, ��� ����
//������� ����������� ������ ��� �������� ������������.
void CommandModule::MessageToUser()
{
	PrintHistory();
	PrintUsers();
	std::cout <<
		"������� ����� ������������, �������� �� ������ ��������� ���������: ";
	size_t command = 0;
	while (!(std::cin >> command) || (std::cin.peek() != '\n') || (command == 0)
		|| !(command < users_.size() + 1))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout 
			<< "�� ����� �������� ����� ��������. ����������, ��������� ����: "
			<< std::endl;
	}
	--command;
	PrintHistory();
	std::string text{ "[" + users_[currentUser_].login_ + "]->" 
		+ users_[command].login_ + " : " };
	std::cout << text;
	std::cin.ignore();
	if (autocompleteEnable_)
	{
		text = characterInput(text);
		text.erase(0, users_[currentUser_].login_.size() + 7 
			+ users_[command].login_.size());
		autoDict_->stream_.clear();
	}
	else std::getline(std::cin, text);
	message_ = new Message{ message_->TimeStamp(), users_[currentUser_].login_,
		users_[command].login_, text };
	users_[currentUser_].history_.push_back(message_->MessageConstructor());
	if (command != currentUser_)
	{
		users_[command].history_.push_back(message_->MessageConstructor());
	}
	delete message_;
	if (users_[command].login_ == "ChatBot") { AnswerChatBot(); }
}

//������� �� ����� ���� ������������������ ������������� � ����������� 
//����������� ������.
void CommandModule::PrintUsers()
{
	size_t counter = 0;
	for (auto& user : users_)
	{
		++counter;
		std::cout << counter << " - " << user.login_;
		std::cout << (user.online_ ? " (online) " : " (offline) ");
		std::cout << std::endl;
	}
}

//���������� ����������� ������� ���������� ������������ ����� ����� 
//����������� ������������ �� ����������� ������. ����������� ��������� �����,
//����������� ��������� � ��������������� �������� �������. ������� �����, ��� 
//� ������� ������� ������ ������������.
void CommandModule::UserInfo()
{
	PrintUsers();
	std::cout <<
		"������� ����� ������������, ������� �������� �� ������ ����������: ";
	size_t command = 0;
	while (!(std::cin >> command) || (std::cin.peek() != '\n') || (command == 0)
		|| !(command < users_.size() + 1))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << 
			"�� ����� �������� ����� ��������. ����������, ��������� ����: "
			<< std::endl;
	}
	std::cout << "�����: " << users_[--command].login_ << std::endl;
	std::cout << "���: " << users_[command].name_ << std::endl;
	std::cout << (users_[command].online_ == true ? "� ����: ��" : "� ����: ���")
		<< std::endl;
	std::cout << std::endl;
	system("pause");
}

//��������� ������� ChatBot'� �� ��������� ����� ���������. ChatBot ��������
//�� ����� ����� ��������� � ���� ��� ��������� ������ ���������� �����������.
//����� ��������� - ���������, �� ������ ���� ������� ������� ChatBot'�.
//�������� ��������� ����������, �� ������ ��������� ���������� ���� � �������
//��� ��������� ��������� ��������� �����. �������� ��������������, ����� 
//���������� ����������, �������� 
//size_t answer = rand() % chatBotAnswers_.size();
//� ������ ������ - ������������ ������� ������ � ������������.
//����� ChatBot'� ����������� � ���������� � �����������.
void CommandModule::AnswerChatBot()
{
	size_t answer = rand() % 9;
	std::string text;

	try
	{
		if (answer >= chatBotAnswers_.size()) { throw bad_range(); }
		else { text = chatBotAnswers_[answer]; }
	}
	catch (bad_range& bR)
	{
		std::cout << bR.what() << std::endl;
		system("pause");
	}
	message_ = new Message{ message_->TimeStamp(), users_[0].login_,
		users_[currentUser_].login_, text };
	users_[currentUser_].history_.push_back(message_->MessageConstructor());
	users_[0].history_.push_back(message_->MessageConstructor());
	delete message_;
}

//�������������� ������� ������� ����������� ������
void CommandModule::InitAutoDict()
{
	std::string const words[] =
	{
		{"�����������"},
		{"������"},
		{"����"},
		{"�����"},
		{"�����"},
		{"����"},
		{"����"},
		{"���"},
		{"������"},
		{"�����"}
	};
	for (auto& word : words)
		autoDict_->Insert(autoDict_, word);
}

auto CommandModule::characterInput(std::string const text)->std::string
{
	autoDict_->stream_ = text;
	do
	{
		//��������� ��� ������� �������.
		symbol_ = _getch();
		//��������� �� ������� ������������ ���� ������� �������, � ����� true - 
		//��������� ��������.
		if (_kbhit())
			symbol_ = _getch();
		//Switch �� ���� ������� �������.
		switch (symbol_)
		{
			//������. ��������� ����� �� ������� � ������. ������� ������� �������.
			//��������� ������ � stream. ��������� �����.
		case 32:
			autoDict_->Insert(autoDict_, prefix_);
			prefix_ = {};
			autoDict_->stream_.push_back(' ');
			PrintHistory();
			break;
			//Enter. ��������� ����� �� Enter � ������. 
			//������� ������� �������. ��������� �����.
		case 13:
			std::cout << std::endl;
			autoDict_->Insert(autoDict_, prefix_);
			prefix_ = {};
			PrintHistory();
			break;
			//������� �����. ��������� ������� �� ���������� �����, ���� ������� �� 
			//������. ���������� � stream. ������� ������� �������. ��������� �����.
		case 72:
			if (prefix_ != "")
				autoDict_->stream_ += autoDict_->prefixes_[position_] + " ";
			prefix_ = {};
			PrintHistory();
			break;
			//������� �����. ���� ���� ���������� ������� ���������� �������� - 
			//������� ���.
		case 75:
			if (position_ > 0 && autoDict_->prefCount != 0)
			{
				PrintHistory();
				--position_;
				autoDict_->PrintAutocomplete(autoDict_, position_);
			}
			break;
			//������� ������. ���� ���� ����������� ������� ���������� �������� - 
			//������� ���.
		case 77:
			if (position_ + 1 < autoDict_->prefCount)
			{
				PrintHistory();
				++position_;
				autoDict_->PrintAutocomplete(autoDict_, position_);
			}
			break;
			//��� ��������� �������� ���� ������� �������. ��������� � stream.
			//���� ������ �� ��������� - ��������� � �������� ��������.
			//����� - ��������� ������� ������� � ������ � ������� ������� �������.
			//���� ������� ������� �� ������ � ���������� � ������ - ��������� �����
			//���� ���� ��� �������� � ������. �� ��������� ������� ������ �� 
			//��������� � �������� �������/���������� ����������� ���������.
		default:
			autoDict_->stream_.push_back(symbol_);
			position_ = 0;
			PrintHistory();
			if (symbol_ - '�' >= -32 && symbol_ - '�' <= 31)
				prefix_.push_back(symbol_);
			else
			{
				autoDict_->Insert(autoDict_, prefix_);
				prefix_ = "";
			}
			if (autoDict_->Search(autoDict_, prefix_) && prefix_ != "")
			{
				autoDict_->FindAllPrefixes(autoDict_, wordConstructor_, 0, prefix_);
				autoDict_->PrintAutocomplete(autoDict_, position_);
			}
			break;
		}
		//Enter. ������� �� ������������ �����.
	} while (symbol_ != 13);
	return autoDict_->stream_;
}

