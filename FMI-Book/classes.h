#ifndef CLASSES_H
#define CLASSES_H

class System; //because there is circular dependency

class User
{
protected:
	char* nickname;
	int age;
	bool blocked = false;
	int number_of_posts;
public:
	User(char* = "", int = 0, int = 0);
	User(const User&);
	User& operator=(const User&);
	virtual ~User();
	const char *getName() const;
	void setName(char*);
	bool getStatus();
	void makeBlocked();
	void makeUnblocked();
	virtual void addPost();
	virtual void removePost();
	virtual void print();
};

class Moderator : public User
{
public:
	Moderator(char*, int);
	void Block(System&, char*);
	void Unblock(System&, char*);
	virtual void addPost();
	virtual void removePost();
	virtual void print();
};

class Administrator : public Moderator
{
public:
	Administrator();
	void addUser(char*, int, System&);
	void addModerator(char*, int, System&);
	void removeUser(char*, System&);
	void addPost(char*, System&);
	void removePost(int, System&);
	void addImage(char*, System&);
	virtual void print();
};

class Post_Text
{
protected:
	char* content;
	int ID;
	char* creator;
public:
	Post_Text(char* = "", char* = "", int = -1);
	Post_Text(const Post_Text&);
	Post_Text& operator=(const Post_Text&);
	virtual ~Post_Text();

	void setContent(char*);
	void setCreator(char*);
	int getID() const;
	const char *getCreator() const;
	virtual void createFile(char*);
};

class Post_Image: public Post_Text
{
public:
	Post_Image(char*, char*, int);
	virtual void createFile(char*);
};

class System
{
private:
	User **users;
	int u_size;
	int u_capacity;
	bool u_resize();
	Moderator **mods;
	int m_size;
	int m_capacity;
	bool m_resize();
	Post_Text** texts;
	int t_size;
	int t_capacity;
	bool t_resize();
	Post_Image** pics;
	int i_size;
	int i_capacity;
	bool i_resize();
	int post_id;
public:
	System();
	~System();
	void u_add(User*);
	void m_add(Moderator*);
	void remove(char*);
	void renameAdminPosts(char*, char*);
	void rename(char*, char*);
	void Block(char*);
	void Unblock(char*);
	void Admin_addText(char*, char*);
	void addText(char*, char*);
	void Admin_addImage(char*, char*);
	bool Admin_removeText(int, char*);
	bool Admin_removePic(int, char*);
	void removePost(char*, int);
	void removeAll(char*);
	void view(char*);
	void info();
	int checkUser(char*);
};

#endif