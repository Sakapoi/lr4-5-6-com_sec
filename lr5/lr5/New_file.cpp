#include "New_file.h"

void New_file::change_rights(User& new_user, bool access_rights[3])//{чтение, запись, исполнение}
{
	New_file::access_rights[new_user][0] = access_rights[0];
	New_file::access_rights[new_user][1] = access_rights[1];
	New_file::access_rights[new_user][2] = access_rights[2];
}
bool* New_file::get_access_rights(User& new_user)
{
	return New_file::access_rights[new_user];
}