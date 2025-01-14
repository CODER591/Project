#include "guimanager.h"

GUIManager::GUIManager(QObject* parent)
    : QObject(parent),
      logger_(ClientLogger::Instance()),
      unread_requests_(0),
      friend_to_delete_("") {  // for testing
  controller_ = new ClientController(this);
  logger_->set_log_level(LogLevel::HIGH);

  connect(this, SIGNAL(SelectedFriendIdChanged(unsigned)), this,
          SLOT(ShowMessages(unsigned)));
  connect(controller_, SIGNAL(MessageRecieved(Message*)), this,
          SLOT(LoadMessage(Message*)));
  connect(controller_, SIGNAL(LoginResult(bool)), this,
          SLOT(OnLoginResult(bool)));
  connect(controller_, SIGNAL(RegisterResult(quint32)), this,
          SLOT(OnRegisterResult(quint32)));
  connect(controller_, SIGNAL(StatusChanged(unsigned, bool)), this,
          SLOT(OnStatusChanged(unsigned, bool)));
  connect(controller_, SIGNAL(FriendRequestResult(bool)), this,
          SLOT(OnFriendRequestResult(bool)));
  connect(controller_, SIGNAL(AddFriendRequestInfo(QString)), this,
          SLOT(OnAddFriendRequest(QString)));
  connect(controller_, SIGNAL(NewFriendRequestResult(QString, quint32)), this,
          SLOT(OnNewFriendInfo(QString, quint32)));
  connect(controller_, SIGNAL(DeleteRequestResult(quint32)), this,
          SLOT(OnDeleteFriend(quint32)));
  connect(controller_, SIGNAL(MessagesSent(unsigned)), this,
          SLOT(OnMessagesSent(unsigned)));
}

int GUIManager::my_id() const { return controller_->app_info_.my_id; }

FriendModel* GUIManager::friend_model() { return &friend_model_; }

MessageModel* GUIManager::message_model() { return &message_model_; }

FriendRequestModel* GUIManager::friend_request_model() {
  return &friend_request_model_;
}

unsigned GUIManager::selected_friend_id() const { return selected_friend_id_; }

void GUIManager::set_selected_friend_id(unsigned selected_id) {
  if (selected_friend_id_ == selected_id) return;

  selected_friend_id_ = selected_id;
  emit SelectedFriendIdChanged(selected_id);
}

unsigned GUIManager::unread_requests() const { return unread_requests_; }

void GUIManager::set_unread_requests(unsigned unread_requests) {
  if (unread_requests_ == unread_requests) return;

  unread_requests_ = unread_requests;
  emit UnreadRequestsChanged(unread_requests);
}

QString GUIManager::friend_to_delete() const { return friend_to_delete_; }

void GUIManager::set_friend_to_delete(QString friend_login) {
  if (friend_to_delete_ == friend_login) return;

  friend_to_delete_ = friend_login;
  emit FriendToDeleteChanged(friend_login);
}

void GUIManager::newFriend(QString new_friend_login, quint32 id) {
  FriendItem* new_friend = new FriendItem(new_friend_login, false, id);
  friend_model_.AddFriendToList(new_friend);
}

void GUIManager::deleteFriend(quint32 friend_to_delete) {
  if (!friend_to_delete) return;
  FriendItem* to_delete = friend_model_.FindFriendItem(friend_to_delete);
  friend_model_.RemoveFriendFromList(to_delete);
  message_model_.RemoveAllMessagesFromList();  //
  emit showHighlighter(false);
}

void GUIManager::newMessage(QString message) {
  Message* temp =
      new Message{0,       selected_friend_id_,  controller_->app_info_.my_id,
                  message, QDate::currentDate(), QTime::currentTime(),
                  false};
  messages_cache_[selected_friend_id_].push_back(temp);
  MessageItem* new_message = new MessageItem(temp);
  message_model_.AddMessageToList(new_message);
}

void GUIManager::ShowMessages(unsigned friend_id) {
  if (friend_id) {
    message_model_.RemoveAllMessagesFromList();

    MessageItem* new_message;

    if (messages_cache_.find(friend_id) == messages_cache_.end()) {
      LoadAllMessages(friend_id);
    }

    for (Message* msg : messages_cache_[friend_id]) {
      new_message = new MessageItem(msg);
      message_model_.AddMessageToList(new_message);
    }
    friend_model_.DeleteUnreadMesgs(friend_id);
    emit showHighlighter(true);
  }
}

void GUIManager::LoadAllMessages(unsigned friend_id) {
  Message* temp;
  QList<Message*> messages;
  QVector<Message> history = controller_->LoadMessages(friend_id);  // use controller's func
  for (auto msg : history) {
    msg.status = true;
    temp = new Message(msg);
    messages.push_back(temp);
  }
  messages_cache_[friend_id] = messages;  // make masgs cache in client controller
}

void GUIManager::LoadMessage(Message* msg) {
  MessageItem* new_message;
  msg->status = true;

  if (messages_cache_.find(msg->owner_id) == messages_cache_.end()) {
    LoadAllMessages(msg->owner_id);
  }

  messages_cache_[msg->chat_id].push_back(msg);
  if (selected_friend_id_ == msg->chat_id) {
    new_message = new MessageItem(msg);
    message_model_.AddMessageToList(new_message);
  } else {
    friend_model_.AddUnreadMesg(msg->chat_id);
    emit messageRing();
  }
}

void GUIManager::OnMessagesSent(unsigned friend_id) {
  if (selected_friend_id_ == friend_id) {
    message_model_.SetMessagesAsSent();
  } else {
    for (auto it = messages_cache_[friend_id].rbegin();
         it < messages_cache_[friend_id].rend(); it++) {
      if ((*it)->status) {
        break;
      } else {
        (*it)->status = true;
      }
    }
  }
}

void GUIManager::deleteFriendRiequest(
    FriendRequestItem* friend_request_to_delete) {
  if (!friend_request_to_delete) return;
  friend_request_model_.RemoveRequestFromList(friend_request_to_delete);
}

void GUIManager::newFriendRiequest(QString login) {
  FriendRequestItem* new_friend_request = new FriendRequestItem(login);
  friend_request_model_.AddRequestToList(new_friend_request);
  set_unread_requests(unread_requests() + 1);  // unread_requests_++
  emit requestRing();
}

void GUIManager::LogIn(QString user_login, QString user_password) {
  logger_->WriteLog(LogType::SUCCESS, user_login);
  controller_->LogIn(user_login, user_password);
  //OnLoginResult(true);
}

void GUIManager::LogOut() {
  friend_model_.RemoveAllFriendsFromList();
  controller_->Stop();
}

void GUIManager::Register(QString user_login, QString user_password) {
  controller_->Register(user_login, user_password);
}

void GUIManager::OnLoginResult(bool logged_in) {
  if (logged_in) {
    LoadFriends();

    ShowMessages(friend_model_.GetFirstFriendId());
    selected_friend_id_ = friend_model_.GetFirstFriendId();

    for (QString login : controller_->LoadFriendRequests()) {
      newFriendRiequest(login);
    }

    logger_->WriteLog(LogType::SUCCESS, controller_->app_info_.my_login);
    emit openMainPage();
  } else {
    emit openFailed("Log In");
  }
}

void GUIManager::OnRegisterResult(quint32 new_id) {
  if (new_id) {
    controller_->OnLogin(true);
    controller_->app_info_.my_id = new_id;
    controller_->AddMeToDB();
    selected_friend_id_ = friend_model_.GetFirstFriendId();
    emit openMainPage();
  } else {
    emit openFailed("Register");
  }
}

void GUIManager::OnStatusChanged(unsigned id, bool status) {
  friend_model_.SetStatus(id, status);
}

void GUIManager::AddFriendRequest(QString new_friend_login) {
  if (new_friend_login != controller_->app_info_.my_login) {
    controller_->AddFriend(new_friend_login);
  }
}

void GUIManager::OnFriendRequestResult(bool request_result) {
  if (request_result) {
    emit showInfo("Friend request sent");
    logger_->WriteLog(LogType::SUCCESS, "Good requst");
  } else {
    emit showInfo("Bad friend request");
    logger_->WriteLog(LogType::ERROR, "Bad requst");
  }
}

void GUIManager::OnAddFriendRequest(QString login) {
  emit showInfo(login + " want to add you to friends");
  newFriendRiequest(login);
}

void GUIManager::AcceptFriend(QString login) {
  controller_->FriendRequestAccepted(login);
  set_unread_requests(unread_requests() - 1);
}

void GUIManager::RejectFriend(QString login) {
  controller_->FriendRequestRejected(login);
  set_unread_requests(unread_requests() - 1);
}

void GUIManager::OnNewFriendInfo(QString login, quint32 id) {
  logger_->WriteLog(LogType::SUCCESS, "User with login '" + login + "' added");
  emit showInfo("User " + login + " added to your friend list");
  newFriend(login, id);
  if (!selected_friend_id_) {
    selected_friend_id_ = id;
  }
}

void GUIManager::DeleteFriend(QString login) {
  controller_->DeleteFriend(login);
}

void GUIManager::OnDeleteFriend(quint32 id) {
  if (id) {
    deleteFriend(id);
    emit showInfo("User with id" + QString::number(id) +
                  " deleted from your friend list");  // temporary
  } else {
    emit showInfo("Failed friend deleting");
  }
}

void GUIManager::SendMessage(QString message) {
  if (selected_friend_id_) {
    newMessage(message);
    controller_->SendMessage(selected_friend_id_, message);
  }
}

void GUIManager::LoadFriends() {  // don't forget to load id
  for (const Friend& i : controller_->LoadFriends()) {
    if (i.id == controller_->app_info_.my_id) continue;
    FriendItem* friend_item = new FriendItem(i.login, false, i.id);
    friend_model_.AddFriendToList(friend_item);
  }
}
