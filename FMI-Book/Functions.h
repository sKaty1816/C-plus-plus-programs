#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <iomanip>
using namespace std;

int char_to_int(char num[])
{
	int result = 0;
	for (int i = 0; i < strlen(num); i++)
	{
		if (num[i]>47 && num[i] < 58)
			result = result * 10 + num[i] - '0';
	}
	return result;
}

void Print(User arr[], int users_in_net)
{
	for (int i = 0; i < users_in_net; i++)
		arr[i].print();
}

void interface()
{
	Administrator Admin;
	System system;
	while (true)
	{
		char command[256];
		cin.getline(command, 256);
		
		char *next_token = NULL;
		char *actor = NULL;
		actor = strtok_s(command, " ", &next_token);
		if (system.checkUser(actor) == 1 ||
			system.checkUser(actor) == 2 ||
			strcmp(actor, Admin.getName()) == 0)
		{
			char* command2 = strtok_s(NULL, " ", &next_token);
			//the things only the Admin can do
			if (strcmp(actor, Admin.getName()) == 0)
			{
				if (strcmp(command2, "add_user") == 0)
				{
					char* name = strtok_s(NULL, " ", &next_token);
					char* age = strtok_s(NULL, "\n", &next_token);
					int a = char_to_int(age);
					Admin.addUser(name, a, system);
				}
				else if (strcmp(command2, "add_moderator") == 0)
				{
					char* name = strtok_s(NULL, " ", &next_token);
					char* age = strtok_s(NULL, "\n", &next_token);
					int a = char_to_int(age);
					Admin.addModerator(name, a, system);
				}
				else if (strcmp(command2, "remove_user") == 0)
				{
					char* name = strtok_s(NULL, "\n", &next_token);
					Admin.removeUser(name, system);
				}
			}
			//the things every user can do
			if (strcmp(command2, "rename") == 0)
			{
				char* name = strtok_s(NULL, "\n", &next_token);
				if (strcmp(actor, Admin.getName()) == 0)
				{
					if (system.checkUser(name) == 0)
					{
						system.renameAdminPosts(actor, name);
						cout << "User " << Admin.getName();
						Admin.setName(name);
						cout << " is now known as " << Admin.getName() << endl;
					}
					else
						cout << "Nickname already in use.\n";
				}
				else
				{
					if (system.checkUser(name) == 0)
						system.rename(actor, name);
					else
						cout << "Nickname already in use.\n";
				}
			}
			else if (strcmp(command2, "post") == 0)
			{
				char* type = strtok_s(NULL, " ", &next_token);
				char* text = strtok_s(NULL, "\n", &next_token);
				if (strcmp(type, "[text]") == 0)
				{
					if (strcmp(actor, Admin.getName()) == 0)
						Admin.addPost(text, system);
					else
						system.addText(actor, text);
				}
				else if (strcmp(type, "[image]") == 0)
				{
					if (strcmp(actor, Admin.getName()) == 0)
						Admin.addImage(text, system);
					else
						system.addText(actor, text);
				}
			}
			else if (strcmp(command2, "remove_post") == 0)
			{
				char* num = strtok_s(NULL, "\n", &next_token);
				int n = char_to_int(num);
				if (strcmp(actor, Admin.getName()) == 0)
					Admin.removePost(n, system);
				else
					system.removePost(actor, n);
			}
			else if (strcmp(command2, "view_post") == 0)
			{
				char* num = strtok_s(NULL, "\n", &next_token);
				system.view(num);
			}
			//the things only the admin and the moderators can do
			else if ((strcmp(command2, "block") == 0) &&
				((system.checkUser(actor) == 2) ||
				(strcmp(actor, Admin.getName()) == 0)))
			{
				char* name = strtok_s(NULL, "\n", &next_token);
				if (strcmp(actor, Admin.getName()) == 0)
					Admin.Block(system, name);
				else
					system.Block(name);
			}
			else if ((strcmp(command2, "unblock") == 0) &&
				((system.checkUser(actor) == 2) ||
				(strcmp(actor, Admin.getName()) == 0)))
			{
				char* name = strtok_s(NULL, "\n", &next_token);
				if (strcmp(actor, Admin.getName()) == 0)
					Admin.Unblock(system, name);
				else
					system.Unblock(name);
			}
		}
		else if (strcmp(command, "info") == 0)
		{
			Admin.print();
			system.info();
		}
		else if (strcmp(command, "quit") == 0)
			break;
		else
			cout << "Incorrect command!\n";
	}
}
#endif