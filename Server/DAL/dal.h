#pragma once
#include <iostream>
#include <map>
#include <string>
#include "../Exceptions/user_not_found.h"

#include "Client.h"
#include "sqldal.h"
// using namespace std;

class DAL {
 public:
  DAL();
  ~DAL();
  // interface associated with database access will be placed here
  void CreateNew(User);
  // call this each time some changes to client are performed
  void UpdateClient(User);
  User getClient(QString);
  User getClient(quint32);
  bool CheckIfClientExistsInDb(User);
  bool CheckIfClientExistsInDb(QString);
  bool CheckIfFriends(User user1, User user2);
  int GetClientId(User);
  

 private:

  dal::UnitOfWork database_;
  std::shared_ptr<dal::Users> users;
};
