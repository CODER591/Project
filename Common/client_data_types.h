#ifndef CLIENT_DATA_TYPES_H
#define CLIENT_DATA_TYPES_H

#include <QString>
#include <QDate>
#include <QTime>
#include <QVector>
#include <qbytearray.h>

//
//// This is our entity from database
struct Friend {
  quint32 id;
  QString login;
  QString ip;
  unsigned int port;
  QString name;
  QString surname;
  bool status;
  QByteArray photo; //in progress
};
//
struct Message {
  unsigned int id;
  unsigned int chat_id;
  unsigned int owner_id;
  QString data;
  QDate date;
  QTime time;
  bool status;
};
//
struct UsersID {
	unsigned int first_user_id;
	unsigned int second_user_id;
};
//
struct User {
	unsigned int id;
	QString	login;
	QString	password;
	QString	ip;
	unsigned int port;

	QVector<UsersID> friends;
	QVector<UsersID> requests;
	QVector<UsersID> notification;
	QVector<UsersID> deletenotificatoin;
};
//
enum  RequestType
{
	MyRequest,
	RequestForMe
};
//
struct FriendRequest {
	QString	login;
	bool type;
};
//
#endif  // !1CLIENT_DATA_TYPES_H
