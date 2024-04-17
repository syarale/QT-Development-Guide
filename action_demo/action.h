#ifndef ACTION_DEMO_ACTION_H_
#define ACTION_DEMO_ACTION_H_

#include <QAction>
#include <QHBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>
#include <QObject>
#include "person.h"

class ActionDemo : public QWidget {
  Q_OBJECT
 public:
  explicit ActionDemo(QWidget* parent = nullptr);
  ~ActionDemo();

 private:
  void InitUI();
  void InitUISlots();
  void InitPersonSlots();

  // slot functions
  void OnBoyIncButtonClick();
  void OnGirlIncButtonClick();
  void OnMetaInfoButtonClick();
  void OnClearEditButtonClick();
  void OnSpinValueChanged(int value);
  void OnAgeChangedSlot(int value); // on QPerson's signal

  QPerson* boy_;
  QPerson* girl_;

  QLabel* label_boy_;
  QLabel* label_girl_;

  QSpinBox* spin_boy_age_;
  QSpinBox* spin_girl_age_;

  QPushButton* pbutton_boy_inc_;
  QPushButton* pbutton_girl_inc_;
  QPushButton* pbutton_meta_info_;
  QPushButton* pbutton_clear_edit_;

  QHBoxLayout* hlayout_;
  QVBoxLayout* label_vlayout_;
  QVBoxLayout* spinbox_vlayout_;
  QVBoxLayout* pbutton_vlayout1_;
  QVBoxLayout* pbutton_vlayout2_;
  QVBoxLayout* major_layout_;

  QPlainTextEdit* text_edit_;
};

#endif  // ACTION_DEMO_ACTION_H_