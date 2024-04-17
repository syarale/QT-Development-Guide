#include "Dialog.h"

#include <iostream>
#include <functional>

#include <QFont>
#include <QHBoxLayout>
#include <QVBoxLayout>

Dialog::Dialog(QWidget* parent) : QDialog(parent) {
  InitUI();
  InitSignalSlots();
  setWindowTitle("Hello QT");
}

Dialog::~Dialog() {

}

void Dialog::InitUI() {
  // Create CheckBox and set horizontal layout
  checkbox_under_ = new QCheckBox(tr("Underline")); 
  checkbox_italic_ = new QCheckBox(tr("Italic")); 
  checkbox_bold_ = new QCheckBox(tr("Bold"));

  QHBoxLayout* hlayout1 = new QHBoxLayout();
  hlayout1->addWidget(checkbox_under_);
  hlayout1->addWidget(checkbox_italic_);
  hlayout1->addWidget(checkbox_bold_);

  // Create RadioButton set horizontal layout
  rbutton_black_ = new QRadioButton(tr("Black")); 
  rbutton_red_ = new QRadioButton(tr("Red")); 
  rbutton_blue_ = new QRadioButton(tr("Blue"));

  QHBoxLayout* hlayout2 = new QHBoxLayout();
  hlayout2->addWidget(rbutton_black_);
  hlayout2->addWidget(rbutton_red_);
  hlayout2->addWidget(rbutton_blue_);

  // Create PushButton set horizontal layout
  pbutton_ok_ = new QPushButton(tr("OK"));
  pbutton_cancel_ = new QPushButton(tr("Cancel"));
  pbutton_close_ = new QPushButton(tr("Close"));

  QHBoxLayout* hlayout3 = new QHBoxLayout();
  hlayout3->addStretch();
  hlayout3->addWidget(pbutton_ok_);
  hlayout3->addStretch();
  hlayout3->addWidget(pbutton_cancel_);
  hlayout3->addStretch();
  hlayout3->addWidget(pbutton_close_);

  // Create plain text edit
  text_edit_ = new QPlainTextEdit();
  text_edit_->setPlainText("Hello World\nIt's my demo");
  QFont font = text_edit_->font();
  font.setPointSize(20);
  text_edit_->setFont(font);

  QVBoxLayout* major_layout = new QVBoxLayout();
  major_layout->addLayout(hlayout1);
  major_layout->addLayout(hlayout2);
  major_layout->addWidget(text_edit_);
  major_layout->addLayout(hlayout3);
  setLayout(major_layout);
}

void Dialog::InitSignalSlots() {
  connect(rbutton_black_, &QRadioButton::clicked, this,
          std::bind(&Dialog::SetTextFontColor, this, Qt::black));
  connect(rbutton_red_, &QRadioButton::clicked, this,
          std::bind(&Dialog::SetTextFontColor, this, Qt::red));
  connect(rbutton_blue_, &QRadioButton::clicked, this,
          std::bind(&Dialog::SetTextFontColor, this, Qt::blue));

  connect(checkbox_under_, &QCheckBox::clicked, this,
          std::bind(&Dialog::UpdateTextFontStyle, this, FontStyle::UNDERLINE));
  connect(checkbox_italic_, &QCheckBox::clicked, this,
          std::bind(&Dialog::UpdateTextFontStyle, this, FontStyle::ITALIC));
  connect(checkbox_bold_, &QCheckBox::clicked, this,
          std::bind(&Dialog::UpdateTextFontStyle, this, FontStyle::BOLD));
}


void Dialog::UpdateTextFontStyle(FontStyle style) {
  QFont font = text_edit_->font();
  switch (style) {
    case FontStyle::UNDERLINE:
      font.setUnderline(checkbox_under_->isChecked());
      break;
    case FontStyle::ITALIC:
      font.setItalic(checkbox_italic_->isChecked());
      break;
    case FontStyle::BOLD:
      font.setBold(checkbox_bold_->isChecked());
      break;
    default:
      std::cerr << "Invalid FontStyle to set..." << std::endl;
  }
  text_edit_->setFont(font);
}


void Dialog::SetTextFontColor(const QColor& color) {
  QPalette plet = text_edit_->palette();
  plet.setColor(QPalette::Text, color);
  text_edit_->setPalette(plet);
}