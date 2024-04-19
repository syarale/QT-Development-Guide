#ifndef ACTION_DEMO_PERSON_H_
#define ACTION_DEMO_PERSON_H_

#include <QObject>

class QPerson : public QObject {
  Q_OBJECT
  Q_CLASSINFO("author", "Wang")
  Q_CLASSINFO("company", "UPC")
  Q_CLASSINFO("version", "1.0.0")
  Q_PROPERTY(int age READ age WRITE set_age NOTIFY ageChanged)
  Q_PROPERTY(QString name MEMBER name_)
  Q_PROPERTY(int score MEMBER score_)
 public:
  explicit QPerson(QString name, QObject* parent = nullptr) : name_(name) {}
  ~QPerson() {}
  
  int age() { return age_;} 
  
  void set_age(int value) {
    age_ = value;
    emit ageChanged(age_);
  }

  void IncreaseAge() {
    ++ age_;
    emit ageChanged(age_);
  }

 private:
  int age_ = 10;
  QString name_;
  int score_ = 79;
 
 signals:
  void ageChanged(int value);
};

#endif  // ACTION_DEMO_PERSON_H_