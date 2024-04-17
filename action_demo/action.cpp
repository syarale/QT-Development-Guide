#include "action.h"

#include <iostream>
#include <QMetaProperty>

ActionDemo::ActionDemo(QWidget* parent) : QWidget(parent) {
  InitUI();
  InitPersonSlots();
  InitUISlots();
  setWindowTitle("MetaObject");
}

ActionDemo::~ActionDemo() {

}

void ActionDemo::InitUI() {
  label_boy_ = new QLabel();
  label_girl_ = new QLabel();
  label_boy_->setText("设置男生年龄");
  label_girl_->setText("设置女生年龄");
  label_boy_->setAlignment(Qt::AlignCenter);
  label_girl_->setAlignment(Qt::AlignCenter);

  label_vlayout_ = new QVBoxLayout();
  label_vlayout_->addWidget(label_boy_);
  label_vlayout_->addWidget(label_girl_);

  spin_boy_age_ = new QSpinBox();
  spin_girl_age_ = new QSpinBox();
  spin_boy_age_->setRange(0, 100);
  spin_girl_age_->setRange(0, 100);
  spin_boy_age_->setValue(12);
  spin_girl_age_->setValue(20);

  spinbox_vlayout_ = new QVBoxLayout();
  spinbox_vlayout_->addWidget(spin_boy_age_);
  spinbox_vlayout_->addWidget(spin_girl_age_);

  pbutton_boy_inc_ = new QPushButton("boy长大一岁");
  pbutton_girl_inc_ = new QPushButton("girl长大一岁");
  
  pbutton_vlayout1_ = new QVBoxLayout();
  pbutton_vlayout1_->addWidget(pbutton_boy_inc_);
  pbutton_vlayout1_->addWidget(pbutton_girl_inc_);

  pbutton_meta_info_ = new QPushButton("类的元对象信息");
  pbutton_clear_edit_ = new QPushButton("清空文本框");

  pbutton_vlayout2_ = new QVBoxLayout();
  pbutton_vlayout2_->addWidget(pbutton_meta_info_);
  pbutton_vlayout2_->addWidget(pbutton_clear_edit_);

  hlayout_ = new QHBoxLayout();
  hlayout_->addLayout(label_vlayout_);
  hlayout_->addLayout(spinbox_vlayout_);
  hlayout_->addLayout(pbutton_vlayout1_);
  hlayout_->addLayout(pbutton_vlayout2_);

  text_edit_ = new QPlainTextEdit();
  text_edit_->setReadOnly(true);

  major_layout_ = new QVBoxLayout(this); 
  major_layout_->addLayout(hlayout_);
  major_layout_->addWidget(text_edit_);

  std::cout << "[INFO] InitUI Completed." << std::endl;
}


// Before InitSlots, InitUI should completed.
void ActionDemo::InitUISlots() {
  connect(pbutton_boy_inc_, &QPushButton::clicked, this, OnBoyIncButtonClick);
  connect(pbutton_girl_inc_, &QPushButton::clicked, this, OnGirlIncButtonClick);
  connect(pbutton_meta_info_, &QPushButton::clicked, this, OnMetaInfoButtonClick);
  connect(pbutton_clear_edit_, &QPushButton::clicked, this, OnClearEditButtonClick);

  spin_boy_age_->setProperty("is_boy", true);
  spin_girl_age_->setProperty("is_boy", false);
  connect(spin_boy_age_, QOverload<int>::of(&QSpinBox::valueChanged), this, OnSpinValueChanged);
  connect(spin_girl_age_, QOverload<int>::of(&QSpinBox::valueChanged), this, OnSpinValueChanged);
}

void ActionDemo::InitPersonSlots() {
  boy_ = new QPerson("Joh");
  boy_->setProperty("score", 95);
  boy_->setProperty("age", 10);
  boy_->setProperty("sex", "Boy");

  girl_ = new QPerson("Lucy");
  girl_->setProperty("score", 81);
  girl_->setProperty("age", 20);
  girl_->setProperty("sex", "Girl");

  connect(boy_, &QPerson::ageChanged, this, OnAgeChangedSlot);
  connect(girl_, &QPerson::ageChanged, this, OnAgeChangedSlot);
}

void ActionDemo::OnBoyIncButtonClick() {
  boy_->IncreaseAge();
  // spin_boy_age_->setValue(boy_->age());
}

void ActionDemo::OnGirlIncButtonClick() {
  girl_->IncreaseAge();
  // spin_girl_age_->setValue(girl_->age());
}


void ActionDemo::OnMetaInfoButtonClick() {
  const QMetaObject* meta = boy_->metaObject();
  text_edit_->clear();
  text_edit_->appendPlainText(" -------- Meta Information ------- \n");
  text_edit_->appendPlainText(
      QString("class name: %1 \n").arg(meta->className()));
  text_edit_->appendPlainText("property");

  for (int i = meta->propertyOffset(); i < meta->propertyCount(); i ++) {
    QMetaProperty prop = meta->property(i);
    const char* prop_name = prop.name();
    QString prop_value = boy_->property(prop_name).toString();
    text_edit_->appendPlainText(
        QString("Attribute: %1, Value: %2").arg(prop_name).arg(prop_value));
  }

  text_edit_->appendPlainText("------------------- \n");
  text_edit_->appendPlainText("Class Information");
  for (int i = meta->classInfoOffset(); i < meta->classInfoCount(); i ++ ) {
    QMetaClassInfo class_info = meta->classInfo(i);
    text_edit_->appendPlainText(QString("Name: %1, Value: %2")
                                    .arg(class_info.name())
                                    .arg(class_info.value()));
  }
  
  std::cout << "[INFO] Print Meta Information" << std::endl;
}

void ActionDemo::OnClearEditButtonClick() {
  text_edit_->clear();
  std::cout << "[INFO] Clear text edit" << std::endl;
}

void ActionDemo::OnSpinValueChanged(int value) {
  QSpinBox* spinbox = qobject_cast<QSpinBox*>(sender());
  bool is_boy = spinbox->property("is_boy").toBool();
  if (is_boy) {
    boy_->set_age(spinbox->value());
  } else {
    girl_->set_age(spinbox->value());
  }
  std::cout << "[INFO] SpinBox value changed to: " << spinbox->value() << std::endl;
}


void ActionDemo::OnAgeChangedSlot(int value) {
  Q_UNUSED(value);
  QPerson* person = qobject_cast<QPerson*>(sender());
  QString name = person->property("name").toString();
  QString sex = person->property("sex").toString();
  int age = person->age();

  text_edit_->appendPlainText(name + ", " + sex + QString::asprintf(", age = %d", age));
  std::cout << "[INFO] Age changed: " << name.toStdString() << ", " << age << std::endl;
}  