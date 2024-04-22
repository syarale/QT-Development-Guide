#ifndef STRING_LIST_MODEL_STRING_LIST_MODEL_DEMO_H_
#define STRING_LIST_MODEL_STRING_LIST_MODEL_DEMO_H_

#include <QLabel>
#include <QStringListModel>
#include <QListView>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QSplitter>
#include <QWidget>

class StringListModelDemo : public QWidget {
  Q_OBJECT
 public:
  explicit StringListModelDemo(QWidget* parent = nullptr);
  ~StringListModelDemo();

 private:
  void InitUI();
  void InitModel();
  void InitUISlots();

  // Slot funtions
  void OnAddClicked();
  void OnInsertClicked();
  void OnDeleteClicked();
  void OnClearListClicked();
  void OnClearTextClicked();
  void OnShowModelClicked();
  void OnSelectRow(const QModelIndex& index);

  QStringListModel* list_model_;
  bool is_ui_inited = false;

  QPushButton* pbutton_add_;
  QPushButton* pbutton_insert_;
  QPushButton* pbutton_delete_;
  QPushButton* pbutton_clear_list_;
  QPushButton* pbutton_clear_text_;
  QPushButton* pbutton_show_model_;

  QListView* list_view_;
  QPlainTextEdit* text_edit_;
  QLabel* label_curr_index_;
};

#endif  // STRING_LIST_MODEL_STRING_LIST_MODEL_DEMO_H_