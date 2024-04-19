#ifndef DIALOG_DEMO_DIALOG_H_
#define DIALOG_DEMO_DIALOG_H_

#include <QMainWindow>
#include <QCheckBox>
#include <QDialog>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QRadioButton>

enum class FontStyle { UNDERLINE = 0, ITALIC, BOLD };

class Dialog : public QDialog {
  Q_OBJECT

 public:
  Dialog(QWidget *parent = nullptr);
  ~Dialog();
 
 private:
  void InitUI();
  void InitSignalSlots();

  // slot functions
  void UpdateTextFontStyle(FontStyle style);
  void SetTextFontColor(const QColor& color);
  
  QCheckBox* checkbox_under_; 
  QCheckBox* checkbox_italic_; 
  QCheckBox* checkbox_bold_;

  QRadioButton* rbutton_black_; 
  QRadioButton* rbutton_red_; 
  QRadioButton* rbutton_blue_;

  QPlainTextEdit* text_edit_;
  QPushButton* pbutton_ok_;
  QPushButton* pbutton_cancel_;
  QPushButton* pbutton_close_;
};

#endif  //DIALOG_DEMO_DIALOG_H_