#pragma once
#include <string>
#include <map>
#include"User.h"


class New_file
{
private:
	std::string name;
	std::map<std::string, bool[3]> access_rights;//{чтение, запись, исполнение}
public:
	New_file(std::string name) :name(name) {};
	void change_rights(User& new_user, bool access_rights[3]);//{чтение, запись, исполнение}
	bool* get_access_rights(User& new_user);
	std::string get_name() { return name; }
};

