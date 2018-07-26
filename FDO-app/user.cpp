#include "user.h"

User::User(const QString& username,
           const QString name,
           const QString password,
           const QString question,
           const QString answer,
           const QVector roles,
           const QString avatar)
{
    this->setUsername(username);
    this->setName(name);
    this->setPassword(password);
    this->setHintQuestion(question);
    this->setHintAnswer(answer);
    this->setRoles(roles);
    this->setAvatar(avatar);
}

QString User::getUsername() const
{
    return this->username;
}

void User::setUsername(const QString& username)
{
    this->username = username;
}

QString User::getName() const
{
    return this->name;
}

void User::setName(const QString& name)
{
    this->name = name;
}

QString User::getPassword() const
{
    return this->password;
}

void User::setPassword(const QString& password)
{
    this->password = password;
}

QString User::getHintQuestion() const
{
    return this->hintQuestion;
}

void User::setHintQuestion(const QString& question)
{
    this->hintQuestion = question;
}

QString User::getHintAnswer() const
{
    return this->hintAnswer;
}

void User::setHintAnswer(const QString& answer)
{
    this->hintAnswer = answer;
}

QVector User::getRoles() const
{
    return this->roles;
}

void User::setName(const QVector& roles)
{
    this->roles = roles;
}

QString User::getAvatar() const
{
    return this->avatar;
}

void User::setAvatar(const QString& avatar)
{
    this->avatar = avatar;
}
