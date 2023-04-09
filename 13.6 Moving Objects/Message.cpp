#include "Message.h"

Message::Message(std::string* con) :content_(con)
{
	add_to_folder(*this);
}

Message::Message(const Message& msg) :content_(msg.content_)
{
	add_to_folder(msg);
}

Message& Message::operator=(const Message& msg)
{
	remove_from_folder();
	content_ = msg.content_;
	add_to_folder(msg);
	return *this;
}

void Message::save(Folder& f)
{
	folders_.emplace(&f);
	f.add_msg(this);
}

void Message::remove(Folder& f)
{
	folders_.erase(&f);
	f.rem_msg(this);
}

void Message::add_to_folder(const Message& msg)
{
	for (auto& folder : msg.folders_)
	{
		folder->add_msg(this);
	}
}

void Message::remove_from_folder()
{
	for (auto& folder : folders_)
	{
		folder->rem_msg(this);
	}
}

void swap(Message& lhs, Message& rhs)
{
	for (auto& folder : lhs.folders_)
	{
		folder->rem_msg(&lhs);
	}
	for (auto& folder : rhs.folders_)
	{
		folder->rem_msg(&rhs);
	}
	std::swap(lhs.content_, rhs.content_);
	std::swap(lhs.folders_, rhs.folders_);
	lhs.add_to_folder(lhs);
	rhs.add_to_folder(rhs);
}

Folder::Folder(Folder& f)
{
	add_to_messages(f);
}

Folder& Folder::operator=(Folder& f)
{
	remove_from_messages();
	messages = f.messages;
	add_to_messages(f);
	return *this;
}

Folder::~Folder()
{
	for (const auto& mess : messages)
	{
		rem_msg(mess);
	}
}

void Folder::add_msg(Message* m)
{
	messages.emplace(m);
	m->save(*this);
}

void Folder::rem_msg(Message* m)
{
	messages.erase(m);
	m->remove(*this);
}

void Folder::add_to_messages(Folder& f)
{
	for (const auto& msg : f.messages)
	{
		msg->save(f);
	}
}

void Folder::remove_from_messages()
{
	for (const auto& msg : messages)
	{
		msg->remove(*this);
	}
}
