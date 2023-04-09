#ifndef MESSAGE_H
#define MESSAGE_H
#pragma once

#include <set>
#include <string>

class Folder;

class Message
{
	friend Folder;
	friend void swap(Message&, Message&);
public:
	Message() :content_(nullptr) {  }
	explicit Message(std::string* msg);
	Message(const Message&);
	Message& operator=(const Message&);
	~Message();
	void save(Folder&);
	void remove(Folder&);

private:
	std::string* content_;
	std::set<Folder*> folders_;
	void add_to_folder(const Message&);
	void remove_from_folder();
};
void swap(Message& lhs, Message& rhs);

class Folder
{
	friend void swap(Message&, Message&);
public:
	Folder() = default;
	Folder(Folder&);
	Folder& operator=(Folder&);
	~Folder();
	void add_msg(Message*);
	void rem_msg(Message*);
private:
	std::set<Message*> messages;
	void add_to_messages(Folder&);
	void remove_from_messages();
};



#endif