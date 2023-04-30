#include "autocomplete_dictionary.h"
#include <iostream>

//������� ����� ���� � ������� ������.
AutocompleteDictionary::AutocompleteDictionary()
{
  //������������� ���� ����� ����� � false.
  endOfWord_ = false;

  //�������������� ����� ������� ���������.
  for (size_t i = 0; i < ALPHABET_SIZE; i++)
    child_[i] = nullptr;
}

AutocompleteDictionary::~AutocompleteDictionary() {}

void AutocompleteDictionary::Remove(AutocompleteDictionary* &root)
{
  for (size_t i = 0; i < ALPHABET_SIZE; ++i)
    if (root->child_[i] != nullptr)
    {
      Remove(root->child_[i]);
      delete root->child_[i];
    }
}

//��������� ���� � ������, ���� ��� ���.
//�����, ���� ���� ������� ��������� ���� ������, 
//�������� � �������� ��������� �.�. ����� �����.
void AutocompleteDictionary::Insert(AutocompleteDictionary* &root,
  std::string const& word)
{
  AutocompleteDictionary* node = root;
  for (size_t i = 0; i < word.length(); i++)
  {
    //��������� ������ � �������� ����� �������� ������������ ������ �����.
    int index = word[i] - '�';

    //���� ����� ���������, �� ��������� � ��������.
    if (index < 0)
      index += 32;

    //���� ��������� �������, �.�. ����� � ����� ��������� ���, 
    //�� ������� ����� ����
    if (!node->child_[index])
      node->child_[index] = new AutocompleteDictionary;
    node = node->child_[index];
  }
  //�������� ��������� ���� ��� ����, �.�. ����� �����.
  node->endOfWord_ = true;
}

//���������� true, ���� ������� ���������� � ������, ����� false. 
auto AutocompleteDictionary::Search(AutocompleteDictionary* &root,
  std::string const& word)->bool
{
  AutocompleteDictionary* node = root;
  for (size_t i = 0; i < word.length(); i++)
  {
    int index = word[i] - '�';
    if (index < 0)
      index += 32;
    if (!node->child_[index])
      return false;
    node = node->child_[index];
  }
  return true;
}

//���� ��� ����� � ������ ��������������� ��������.
void AutocompleteDictionary::FindAllPrefixes(AutocompleteDictionary* &root,
  char* wordConstructor, int index, std::string const& prefix)
{
  if (!root)
    return;

  //������� ��������� ����, ���������� ������� ��� ������ ��������� � �������.
  if (index == 0)
  {
    prefCount = 0;
    std::vector<std::string>().swap(prefixes_);
  }

  //���������� �������� ���� ������ �������� �������� (�������� ���������� 
  //��������). ����� ���������� ��� ������������ ������� � ��������� ����������
  //����� � ���������� ���������� ��� ������� ����. ��������� ����� ����������
  //� �������� � ��� ����������� �� �������� ����� ����������� ����������.
  if (prefix.length() > index)
  {
    wordConstructor[index] = prefix[index];
    int i = wordConstructor[index] - '�';
    if (i < 0)
      i += 32;
    FindAllPrefixes(root->child_[i], wordConstructor, index + 1, prefix);
  }
  else
  {
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
      if (root->child_[i] != nullptr)
      {
        wordConstructor[index - prefix.length()] = i + '�';
        if (root->child_[i]->endOfWord_)
        {
          wordConstructor[static_cast<unsigned long long>(index) + 1 -
            prefix.length()] = '\0';
          prefixes_.push_back(std::string(wordConstructor));
          ++prefCount;
        }
        FindAllPrefixes(root->child_[i], wordConstructor, index + 1, prefix);
      }
    }
  }
  //���� ������� = ����� � ������ � ��������, ������� 1 ������ ������� 
  //���������� ����, ���������� �������, ��� ��������� ������ ��������� 
  //� ��������������� �������� ����������
  if (root->endOfWord_ && prefCount == 0)
  {
    prefixes_.push_back("");
    ++prefCount;
  }
}

//������� �� ����� ������� �������������� ����� �� ��������, ������� 
//������������ ����� �������������� ������ ����. ��������� ������� 
//�������������� ��������� � ���������� ����, ���������� ������� �������.
//������� ��������� �������������� �������� ���������� "<-", 
//����������� - "->'.
void AutocompleteDictionary::PrintAutocomplete(AutocompleteDictionary* &root,
  size_t position)
{
  printf_s("\033[46m");
  std::cout << root->prefixes_[position];
  printf_s("\033[0m");
  if (position > 0)
    std::cout << "<-";
  if (root->prefCount > position + 1)
    std::cout << "->";
}
