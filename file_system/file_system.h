#ifndef FILE_SYSTEM_FILE_SYSTEM_H_
#define FILE_SYSTEM_FILE_SYSTEM_H_

#include <QCheckBox>
#include <QFileSystemModel>
#include <QLabel>
#include <QListView>
#include <QMainWindow>
#include <QTableView>
#include <QTreeView>

class FileSystem : public QMainWindow {
  Q_OBJECT
 public:
  explicit FileSystem();
  ~FileSystem();

 private:
  void InitUI();
  void InitUISlots();

  // Slot function
  void OnTreeViewClick(const QModelIndex& index);

  bool is_ui_inited = false;

  QFileSystemModel* file_system_model_;

  QTreeView* tree_view_;
  QListView* list_view_;
  QTableView* table_view_;

  QCheckBox* chbox_is_folder_;
  QLabel* label_file_name_;
  QLabel* label_file_size_;
  QLabel* label_file_type_;
  QLabel* label_file_path_;
};

#endif  // FILE_SYSTEM_FILE_SYSTEM_H_