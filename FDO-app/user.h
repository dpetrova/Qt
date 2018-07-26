#ifndef USER_H
#define USER_H

#include <QString>

enum class UserRole
{
     Admin,
     Trainer
};


class User
{
public:
    User();

public:
    explicit Album(const QString& username,
                   const QString name,
                   const QString password,
                   const QString question,
                   const QString answer,
                   const QVector roles,
                   const QString avatar = "avatar.png");
    //getters & settes
    QString getUsername() const;
    void setUsername(const QString& username);
    QString getName() const;
    void setName(const QString& name);
    QString getPassword() const;
    void setPassword(const QString& pass);
    QString getHintQuestion() const;
    void setHintQuestion(const QString& question);
    QString getHintAnswer() const;
    void setHintAnswer(const QString& answer);
    QString getAvatar() const;
    void setAvatar(const QString& avatarFilename);
    QVector getRoles() const;
    void setRoles(const QVector roles);

private:
    int id;
    QString username;
    QString name;
    QString avatar;
    QString password;
    QString hintQuestion;
    QString hintAnswer;
    QVector roles;
};

#endif // USER_H
