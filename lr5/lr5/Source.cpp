#include <iostream>
#include "User.h"
#include "New_file.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	User* users [5];
	users[0] = new User("Peter");
	users[1] = new User("Oleg");
	users[2] = new User("Boris");
	users[3] = new User("Vasiliy");
	users[4] = new User("Guest");

	New_file* new_files[3];
	new_files[0] = new New_file("Books");
	new_files[1] = new New_file("Films");
	new_files[2] = new New_file("Games");

	bool full[] = { true,true,true };//полные права
	bool rw[] = { true,true,false };//чтение и запись
	bool empty[] = { false,false,false };//пустые права
	bool r[] = { true,false,false };//чтение
	bool e[] = { false,false,true };//исполнение
	//устанавливаем права доступа
	//для Петра
	new_files[0]->change_rights(*users[0], full);
	new_files[1]->change_rights(*users[0], full);
	new_files[2]->change_rights(*users[0], full);
	//для Олега
	new_files[0]->change_rights(*users[1], full);
	new_files[1]->change_rights(*users[1], rw);
	new_files[2]->change_rights(*users[1], empty);
	//для Бориса
	new_files[0]->change_rights(*users[2], empty);
	new_files[1]->change_rights(*users[2], r);
	new_files[2]->change_rights(*users[2], empty);
	//для Василия
	new_files[0]->change_rights(*users[3], full);
	new_files[1]->change_rights(*users[3], full);
	new_files[2]->change_rights(*users[3], full);
	//для Гостя
	new_files[0]->change_rights(*users[4], empty);
	new_files[1]->change_rights(*users[4], empty);
	new_files[2]->change_rights(*users[4], empty);

	std::string name;
	User* current_user=users[4];
	std::cout << "Здравствуйте, введите имя пользавателя:" << std::endl;
	std::cin >> name;
	for (User* i : users)
	{
		if (i->name == name)
		{
			current_user = i;
			break;
		}
	}
	std::cout << "Вы вошли как " << current_user->name<<std::endl;
	std::cout << "Ваши права: " <<  std::endl;

	

	for (New_file* i : new_files)
	{
		auto temporary_rights = i->get_access_rights(*current_user);
		std::cout << i->get_name() << ": " << (
			(temporary_rights[0] && temporary_rights[1] && temporary_rights[2]) ? "полные права" : (
				(!temporary_rights[0] && !temporary_rights[1] && !temporary_rights[2]) ? "нет прав" : (
					std::string(((temporary_rights[0]) ? "чтение" : "")) + " " +
					std::string(((temporary_rights[1]) ? "запись" : "")) + " " +
					std::string(((temporary_rights[2]) ? "исполнение" : "")) + " ")
				)
			) << std::endl;
	}
	
	std::string next_step = "выход";
	std::string object = " ";
	
	while (true)
	{
		std::cout << "Что Вы хотите сделать?" << std::endl;
		std::cin >> next_step;
		int counter = ((next_step == "read") ? 0 :( (next_step == "write") ? 1 :( (next_step == "execute") ? 2 :((next_step == "change")?3: 4))));

		if (counter == 4)
		{
			break;
		}
		std::cout << "Над каким объектом Вы хотите это сделать?" << std::endl;
		std::cin >> object;
		New_file* current_file=nullptr;
		for (New_file* i : new_files)
		{
			if (i->get_name() == object)
			{
				current_file = i;
				break;
			}
		}
		if (current_file == nullptr)
		{
			std::cout << "Невозможно найти данный файл" << std::endl;
			continue;
		}
		int a = 0;
		switch (counter)
		{
		case 0:
			if (current_file->get_access_rights(*current_user)[0])
				std::cout << "Операция прошла успешно" << std::endl;
			else
				std::cout << "У Вас нет прав для чтения" << std::endl;
			break;

		case 1:
			if (current_file->get_access_rights(*current_user)[1])
				std::cout << "Операция прошла успешно" << std::endl;
			else
				std::cout << "У Вас нет прав для записи" << std::endl;
			break;
		case 2:
			if (current_file->get_access_rights(*current_user)[2])
				std::cout << "Операция прошла успешно" << std::endl;
			else
				std::cout << "У Вас нет прав для исполнения" << std::endl;
			break;
		case 3:
			std::cout << "Какие будут новые права у данного файла?" << std::endl;
			
			std::cin >> a;
			if (a == 1)
				current_file->change_rights(*current_user, full);
			else
				current_file->change_rights(*current_user, empty);
			std::cout << "Новые права: " << std::endl;
			for (New_file* i : new_files)
			{
				auto temporary_rights = i->get_access_rights(*current_user);
				std::cout << i->get_name() << ": " << (
					(temporary_rights[0] && temporary_rights[1] && temporary_rights[2]) ? "полные права" : (
						(!temporary_rights[0] && !temporary_rights[1] && !temporary_rights[2]) ? "нет прав" : (
							std::string(((temporary_rights[0]) ? "чтение" : "")) + " " +
							std::string(((temporary_rights[1]) ? "запись" : "")) + " " +
							std::string(((temporary_rights[2]) ? "исполнение" : "")) + " ")
						)
					) << std::endl;
			}
			break;
		default:
			
			break;
		}
	}
	std::cout << "До свидания, " << current_user->name << ", нам будет Вас не хватать." << std::endl;

	

	system("pause");
	return 0;
}