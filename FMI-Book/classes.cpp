#include "classes.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

int char_to_int(char num[]);

User::User(char* u_name, int u_age, int posts)
{
	setName(u_name);
	age = u_age;
	blocked = false;
	number_of_posts = posts;
}

User::User(const User& u)
{
	setName(u.nickname);
	age = u.age;
	blocked = u.blocked;
	number_of_posts = u.number_of_posts;
}

User& User::operator=(const User& u)
{
	if (&u != this)
	{
		setName(u.nickname);
		age = u.age;
		blocked = u.blocked;
		number_of_posts = u.number_of_posts;
	}
	return *this;
}

User::~User()
{
	if (nickname != NULL)
		delete nickname;
}

const char* User::getName() const
{
	return nickname;
}

void User::setName(char* name)
{
	if (nickname != NULL)
		delete nickname;
	nickname = new char[strlen(name) + 1];
	strcpy_s(nickname, strlen(name) + 1, name);
}

bool User::getStatus()
{
	return blocked;
}

void User::makeBlocked()
{
	blocked = true;
}

void User::makeUnblocked()
{
	blocked = false;
}

void User::addPost()
{
	number_of_posts++;
}

void User::removePost()
{
	number_of_posts--;
}

void User::print()
{
	cout << nickname
		<< " - Regular User, "<<
		number_of_posts<<" posts.\n";
}

Moderator::Moderator(char* m_name, int m_age) :
User(m_name, m_age)
{}

void Moderator::Block(System& s, char* name)
{
	if (s.checkUser(name) != 0)
		s.Block(name);
	else
		cout << "User doesn't exist.\n";
}

void Moderator::Unblock(System& s, char* name)
{
	if (s.checkUser(name) != 0)
		s.Unblock(name);
	else
		cout << "User doesn't exist.\n";
}

void Moderator::addPost()
{
	User::addPost();
}

void Moderator::removePost()
{
	User::removePost();
}

void Moderator::print()
{
	cout << nickname
		<< " - Moderator, " <<
		number_of_posts << " posts.\n";
}

Administrator::Administrator() : Moderator("Admin", 23)
{}

void Administrator::addUser(char* name, int age, System& s)
{
	User *u = new User(name, age);
	s.u_add(u);
	cout << name << " created.\n";
}

void Administrator::addModerator(char* name, int age, System& s)
{
	Moderator *m = new Moderator(name, age);
	s.m_add(m);
	cout << name << " created.\n";
}

void Administrator::removeUser(char* name, System& s)
{
	s.remove(name);
}

void Administrator::addPost(char* cont, System& s)
{
	number_of_posts++;
	s.Admin_addText(nickname, cont);
}

void Administrator::addImage(char* cont, System& s)
{
	number_of_posts++;
	s.Admin_addImage(nickname, cont);
}

void Administrator::removePost(int n, System& s)
{
	if (s.Admin_removeText(n, nickname))
		number_of_posts--;
}

void Administrator::print()
{
	cout << nickname
		<< " - Administrator, " <<
		number_of_posts << " posts.\n";
}

Post_Text::Post_Text(char* crtor, char* cont, int id)
{
	setContent(cont);
	setCreator(crtor);
	ID = id;
}

Post_Text::Post_Text(const Post_Text& t)
{
	setContent(t.content);
	setCreator(t.creator);
	ID = t.ID;
}

Post_Text& Post_Text::operator=(const Post_Text& t)
{
	if (&t != this)
	{
		setContent(t.content);
		setCreator(t.creator);
		ID = t.ID;
	}
	return *this;
}

Post_Text::~Post_Text()
{
	if (content != NULL)
		delete content;
	if (creator != NULL)
		delete creator;
}

void Post_Text::setContent(char* cont)
{
	if (content != NULL)
		delete content;
	content = new char[strlen(cont) + 1];
	strcpy_s(content, strlen(cont) + 1, cont);
}

void Post_Text::setCreator(char* crtor)
{
	if (creator != NULL)
		delete creator;
	creator = new char[strlen(crtor) + 1];
	strcpy_s(creator, strlen(crtor) + 1, crtor);
}

const char* Post_Text::getCreator() const
{
	return creator;
}

int Post_Text::getID() const
{
	return ID;
}

void Post_Text::createFile(char* num)
{
	string f_name = "post";
	f_name += num;
	f_name += ".htm";
	ofstream html(f_name, ios::out, ios::trunc);
	html << content;
	cout << "HTML view for post " << ID << " created.\n";
}

Post_Image::Post_Image(char* crtor, char* cont, int id) :
Post_Text(crtor, cont, id)
{}

void Post_Image::createFile(char* num)
{
	//this works with windows paths
	//haven't tried on linux :D
	string f_name = "post";
	f_name += num;
	f_name += ".htm";
	ofstream html(f_name, ios::out, ios::trunc);
	html << "<!DOCTYPE html>\n"
		<< "<html>\n"
		<< "<body>\n"
		<< "<h2>HTML Image "<<ID<<"</h2>\n"
		<< "<img src=\"/" << content << "\">\n"
		<< "</body>\n"
		<< "</html>\n";	
	cout << "HTML view for post " << ID << " created.\n";
}

bool System::u_resize()
{
	User ** newArr = new User*[u_capacity * 2];
	if (newArr == NULL)
		return false;
	for (int i = 0; i < u_capacity; i++)
		newArr[i] = users[i];
	users = newArr;
	u_capacity *= 2;
	return true;
}

bool System::m_resize()
{
	Moderator ** newArr = new Moderator*[m_capacity * 2];
	if (newArr == NULL)
		return false;
	for (int i = 0; i < m_capacity; i++)
		newArr[i] = mods[i];
	mods = newArr;
	m_capacity *= 2;
	return true;
}

bool System::t_resize()
{
	Post_Text ** newArr = new Post_Text*[t_capacity * 2];
	if (newArr == NULL)
		return false;
	for (int i = 0; i < t_capacity; i++)
		newArr[i] = texts[i];
	texts = newArr;
	t_capacity *= 2;
	return true;
}

bool System::i_resize()
{
	Post_Image ** newArr = new Post_Image*[i_capacity * 2];
	if (newArr == NULL)
		return false;
	for (int i = 0; i < i_capacity; i++)
		newArr[i] = pics[i];
	pics = newArr;
	i_capacity *= 2;
	return true;
}

System::System()
{
	u_capacity = 3;
	m_capacity = 3;
	t_capacity = 3;
	i_capacity = 3;
	u_size = 0;
	m_size = 0;
	t_size = 0;
	i_size = 0;
	users = new User*[u_capacity];
	mods = new Moderator*[m_capacity];
	texts = new Post_Text*[t_capacity];
	pics = new Post_Image*[i_capacity];
	post_id = -1;
}

System::~System()
{
	for (int i = 0; i < u_size; i++)
		delete users[i];
	delete[] users;

	for (int i = 0; i < m_size; i++)
		delete mods[i];
	delete[] mods;

	for (int i = 0; i < t_size; i++)
		delete texts[i];
	delete[] texts;

	for (int i = 0; i < i_size; i++)
		delete pics[i];
	delete[] pics;
}

void System::u_add(User* u)
{
	if (u_size == u_capacity && !u_resize())
		return;
	users[u_size++] = u;
}

void System::m_add(Moderator* m)
{
	if (m_size == m_capacity && !m_resize())
		return;
	mods[m_size++] = m;
}

void System::remove(char* name)
{
	if (checkUser(name) == 0)
	{
		cout << "User doesn't exist.\n";
		return;
	}
	else if (checkUser(name) == 1)
	{
		
		for (int i = 0; i < u_size; i++)
		{
			if (strcmp(users[i]->getName(), name) == 0)
			{
				User** newList;
				newList = new User*[u_size - 1];
				for (int j = 0; j <= i - 1; j++)
					newList[j] = users[j];
				for (int j = i; j <= u_size - 1; j++)
					newList[j] = users[j+1];
				delete[] users;
				u_size--;
				users = new User*[u_size];
				for (int j = 0; j < u_size; j++)
					users[j] = newList[j];
				newList = NULL;
				cout << name << " removed.\n";
				return;
			}
		}
	}
	else
	{
		for (int i = 0; i < m_size; i++)
		{
			if (strcmp(mods[i]->getName(), name) == 0)
			{
				Moderator** newList;
				newList = new Moderator*[m_size - 1];
				for (int j = 0; j <= i - 1; j++)
					newList[j] = mods[j];
				for (int j = i; j <= m_size - 1; j++)
					newList[j] = mods[j + 1];
				delete[] mods;
				m_size--;
				mods = new Moderator*[m_size];
				for (int j = 0; j < m_size; j++)
					mods[j] = newList[j];
				newList = NULL;
				cout << name << " removed.\n";
				return;
			}
		}
	}
	removeAll(name);
}

void System::renameAdminPosts(char* old_name, char* new_name)
{
	for (int i = 0; i < t_size; i++)
	{
		if (strcmp(texts[i]->getCreator(), old_name) == 0)
			texts[i]->setCreator(new_name);
	}
}
void System::rename(char* old_name, char* new_name)
{
	for (int i = 0; i < t_size; i++)
	{
		if (strcmp(texts[i]->getCreator(), old_name) == 0)
			texts[i]->setCreator(new_name);
	}
	if (checkUser(old_name) == 1)
	{
		for (int i = 0; i < u_size; i++)
		{
			if (strcmp(users[i]->getName(), old_name) == 0)
			{
				users[i]->setName(new_name);
				cout << "User " << old_name << " is now known as " << users[i]->getName() << endl;
				return;
			}
		}
	}
	else
	{
		for (int i = 0; i < m_size; i++)
		{
			if (strcmp(mods[i]->getName(), old_name) == 0)
			{
				mods[i]->setName(new_name);
				cout << "User " << old_name << " is now known as " << mods[i]->getName() << endl;
				return;
			}

		}
	}
}

void System::Block(char* name)
{
	if (checkUser(name) == 1)
	{
		for (int i = 0; i < u_size; i++)
		{
			if (strcmp(users[i]->getName(), name) == 0)
			{
				users[i]->makeBlocked();
				cout << name << " blocked.\n";
				return;
			}
		}
	}
	else
	{
		for (int i = 0; i < m_size; i++)
		{
			if (strcmp(mods[i]->getName(), name) == 0)
			{
				mods[i]->makeBlocked();
				cout << name << " blocked.\n";
				return;
			}
		}
	}
}

void System::Unblock(char* name)
{
	if (checkUser(name) == 1)
	{
		for (int i = 0; i < u_size; i++)
		{
			if (strcmp(users[i]->getName(), name) == 0)
			{
				users[i]->makeUnblocked();
				cout << name << " unblocked.\n";
				return;
			}
		}
	}
	else
	{
		for (int i = 0; i < m_size; i++)
		{
			if (strcmp(mods[i]->getName(), name) == 0)
			{
				mods[i]->makeUnblocked();
				cout << name << " unblocked.\n";
				return;
			}
		}
	}
}

void System::addText(char* name, char* txt)
{
	if (checkUser(name) == 0)
	{
		cout << "User doesn't exist.\n";
		return;
	}
	else if (checkUser(name) == 1)
	{
		for (int i = 0; i < u_size; i++)
		{
			if ((strcmp(users[i]->getName(), name) == 0) &&
				!users[i]->getStatus())
			{
				post_id++;
				Post_Text *t = new Post_Text(name, txt, post_id);
				if (t_size == t_capacity && !t_resize())
					return;
				texts[t_size++] = t;
				users[i]->addPost();
			}
			else if (users[i]->getStatus())
			{
				cout << "Post not created - user blocked!\n";
				return;
			}	
		}
	}
	else if (checkUser(name) == 2)
	{
		for (int i = 0; i < m_size; i++)
		{
			if ((strcmp(mods[i]->getName(), name) == 0) &&
				!mods[i]->getStatus())
			{
				post_id++;
				Post_Text *t = new Post_Text(name, txt, post_id);
				if (t_size == t_capacity && !t_resize())
					return;
				texts[t_size++] = t;
				mods[i]->addPost();
			}
			else if (mods[i]->getStatus())
			{
				cout << "Post not created - user blocked!\n";
				return;
			}
		}
	}
	cout << "Post " << post_id << " created.\n";
}

void System::Admin_addText(char* name, char* cont)
{
	post_id++;
	Post_Text *t = new Post_Text(name, cont, post_id);
	if (t_size == t_capacity && !t_resize())
		return;
	texts[t_size++] = t;
	cout << "Post " << post_id << " created.\n";
}

void System::Admin_addImage(char* name, char* cont)
{
	post_id++;
	Post_Image *im = new Post_Image(name, cont, post_id);
	if (i_size == i_capacity && !i_resize())
		return;
	pics[i_size++] = im;
	cout << "Post " << post_id << " created.\n";
}

bool System::Admin_removeText(int n, char* name)
{
	bool is_it_the_admin = false;
	for (int i = 0; i < t_size; i++)
	{
		if (texts[i]->getID() == n)
		{
			if (checkUser(name) != 0)
			{
				for (int j = 0; j < u_size; j++)
				{
					if (strcmp(users[j]->getName(), texts[i]->getCreator()) == 0)
						users[j]->removePost();
				}
				for (int j = 0; j < m_size; j++)
				{
					if (strcmp(mods[j]->getName(), texts[i]->getCreator()) == 0)
						mods[j]->removePost();
				}
			}
			else if (strcmp(texts[i]->getCreator(), name) == 0)
				is_it_the_admin = true;
			Post_Text** newT;
			newT = new Post_Text*[t_size - 1];
			for (int j = 0; j <= i - 1; j++)
				newT[j] = texts[j];
			for (int j = i; j <= t_size - 1; j++)
				newT[j] = texts[j + 1];
			delete[] texts;
			t_size--;
			texts = new Post_Text*[t_size];
			for (int j = 0; j < t_size; j++)
				texts[j] = newT[j];
			newT = NULL;
			cout << "Post " << n << " removed.\n";
		}
	}
	if (Admin_removePic(n, name))
		is_it_the_admin = true;
	return is_it_the_admin;
}

bool System::Admin_removePic(int n, char* name)
{
	bool flag = false;
	bool is_it_the_admin = false;
	for (int i = 0; i < i_size; i++)
	{
		if (pics[i]->getID() == n)
		{
			if (checkUser(name) != 0)
			{
				for (int j = 0; j < u_size; j++)
				{
					if (strcmp(users[j]->getName(), pics[i]->getCreator()) == 0)
						users[j]->removePost();
				}
				for (int j = 0; j < m_size; j++)
				{
					if (strcmp(mods[j]->getName(), pics[i]->getCreator()) == 0)
						mods[j]->removePost();
				}
			}
			else if (strcmp(pics[i]->getCreator(), name) == 0)
				is_it_the_admin = true;
			flag = true;
			Post_Image** newT;
			newT = new Post_Image*[i_size - 1];
			for (int j = 0; j <= i - 1; j++)
				newT[j] = pics[j];
			for (int j = i; j <= i_size - 1; j++)
				newT[j] = pics[j + 1];
			delete[] pics;
			i_size--;
			pics = new Post_Image*[i_size];
			for (int j = 0; j < i_size; j++)
				pics[j] = newT[j];
			newT = NULL;
			cout << "Post " << n << " removed.\n";
		}
	}
	if (!flag)
		cout << "No such post!\n";
	return is_it_the_admin;
}

void System::removePost(char* name, int n)
{
	for (int i = 0; i < t_size; i++)
	{
		if ((texts[i]->getID() == n) &&
			((checkUser(name) == 2) ||
			((checkUser(name) == 1) &&
			strcmp(texts[i]->getCreator(), name) == 0)))
		{
			for (int j = 0; j < u_size; j++)
			{
				if (strcmp(users[j]->getName(), texts[i]->getCreator()) == 0)
					users[j]->removePost();
			}
			for (int j = 0; j < m_size; j++)
			{
				if (strcmp(mods[j]->getName(), texts[i]->getCreator()) == 0)
					mods[j]->removePost();
			}
			Post_Text** newT;
			newT = new Post_Text*[t_size - 1];
			for (int j = 0; j <= i - 1; j++)
				newT[j] = texts[j];
			for (int j = i; j <= t_size - 1; j++)
				newT[j] = texts[j + 1];
			delete[] texts;
			t_size--;
			texts = new Post_Text*[t_size];
			for (int j = 0; j < t_size; j++)
				texts[j] = newT[j];
			newT = NULL;
			cout << "Post " << n << " removed.\n";
			return;
		}
		else if ((texts[i]->getID() == n) &&
			((checkUser(name) == 1) &&
			strcmp(texts[i]->getCreator(), name) != 0))
			cout << "Regular users can't do that.\n";
	}
	
	cout << "No such post!\n";
}

void System::removeAll(char* name)
{
	for (int i = 0; i < t_size; i++)
	{
		if (strcmp(texts[i]->getCreator(), name) == 0)
		{
			Post_Text** newT;
			newT = new Post_Text*[t_size - 1];
			for (int j = 0; j <= i - 1; j++)
				newT[j] = texts[j];
			for (int j = i; j <= t_size - 1; j++)
				newT[j] = texts[j + 1];
			delete[] texts;
			t_size--;
			texts = new Post_Text*[t_size];
			for (int j = 0; j < t_size; j++)
				texts[j] = newT[j];
			newT = NULL;
		}
	}
}

void System::view(char* num)
{
	int n = char_to_int(num);
	for (int i = 0; i < t_size; i++)
	{
		if (texts[i]->getID() == n)
		{
			texts[i]->createFile(num);
			return;
		}	
	}
	for (int i = 0; i < i_size; i++)
	{
		if (pics[i]->getID() == n)
		{
			pics[i]->createFile(num);
			return;
		}
	}
	cout << "No such post!\n";
}

void System::info()
{
	for (int i = 0; i < m_size; i++)
		mods[i]->print();
	for (int i = 0; i < u_size; i++)
		users[i]->print();
}

int System::checkUser(char* name)
{
	for (int i = 0; i < u_size; i++)
	{
		if(strcmp(users[i]->getName(), name) == 0)
			//returns 1 if there's a regular user with that name
			return 1; 
	}
	for (int i = 0; i < m_size; i++)
	{
		if (strcmp(mods[i]->getName(), name) == 0)
			//returns 2 if there's a moderator with that name
			return 2;
	}
	//returns 0 if there isn't a user with that name
	return 0;
}
