#include <cassert>
#include <iostream>

#include <QGroupBox>
#include <QHBoxLayout>
#include <QSplitter>
#include <QWidget>

#include "file_system.h"

FileSystem::FileSystem() {
  InitUI();

  assert(is_ui_inited);
  file_system_model_ = new QFileSystemModel(this);
  file_system_model_->setRootPath(QDir::currentPath());
  tree_view_->setModel(file_system_model_);
  list_view_->setModel(file_system_model_);
  table_view_->setModel(file_system_model_);

  InitUISlots();
}

FileSystem::~FileSystem() {}

void FileSystem::InitUI() {
  setWindowTitle("File System");
  QWidget* central_widget = new QWidget();
  QVBoxLayout* major_layout = new QVBoxLayout();
  {
    QSplitter* hsplitter = new QSplitter(Qt::Horizontal);
    {
      QGroupBox* gbox_tree = new QGroupBox();
      {
        QVBoxLayout* vlayout_tree = new QVBoxLayout();
        tree_view_ = new QTreeView();
        vlayout_tree->addWidget(tree_view_);

        gbox_tree->setTitle("TreeView");
        gbox_tree->setLayout(vlayout_tree);
      }

      QSplitter* vsplitter = new QSplitter(Qt::Vertical);
      {
        QGroupBox* gbox_list = new QGroupBox();
        {
          QVBoxLayout* vlayout_list = new QVBoxLayout();
          list_view_ = new QListView();
          vlayout_list->addWidget(list_view_);

          gbox_list->setTitle("ListView");
          gbox_list->setLayout(vlayout_list);
        }

        QGroupBox* gbox_table = new QGroupBox();
        {
          QVBoxLayout* vlayout_table = new QVBoxLayout();
          table_view_ = new QTableView();
          vlayout_table->addWidget(table_view_);

          gbox_table->setTitle("TableView");
          gbox_table->setLayout(vlayout_table);
        }

        vsplitter->addWidget(gbox_list);
        vsplitter->addWidget(gbox_table);
      }
      hsplitter->addWidget(gbox_tree);
      hsplitter->addWidget(vsplitter);
    }

    QGroupBox* gbox_labels = new QGroupBox();
    {
      QVBoxLayout* vlayout = new QVBoxLayout();
      {
        QHBoxLayout* hlayout = new QHBoxLayout();
        {
          label_file_name_ = new QLabel("File name: ");
          label_file_size_ = new QLabel("File size: ");
          label_file_type_ = new QLabel("File type: ");
          chbox_is_folder_ = new QCheckBox("Is folder");

          hlayout->addWidget(label_file_name_);
          hlayout->addWidget(label_file_size_);
          hlayout->addWidget(label_file_type_);
          hlayout->addWidget(chbox_is_folder_);
        }
        label_file_path_ = new QLabel("File Path: ");

        vlayout->addLayout(hlayout);
        vlayout->addWidget(label_file_path_);
      }
      gbox_labels->setLayout(vlayout);
    }

    major_layout->addWidget(hsplitter);
    major_layout->addWidget(gbox_labels);
    central_widget->setLayout(major_layout);
  }
  setCentralWidget(central_widget);
  is_ui_inited = true;
  std::cout << "[INFO] UI Init successed." << std::endl;
}

void FileSystem::InitUISlots() {
  assert(is_ui_inited);

  connect(tree_view_, &QTreeView::clicked, list_view_,
          &QListView::setRootIndex);
  connect(tree_view_, &QTreeView::clicked, table_view_,
          &QTableView::setRootIndex);
  connect(tree_view_, &QTreeView::clicked, this, OnTreeViewClick);
}

void FileSystem::OnTreeViewClick(const QModelIndex& index) {
  label_file_name_->setText(file_system_model_->fileName(index));
  label_file_path_->setText(file_system_model_->filePath(index));
  label_file_type_->setText(file_system_model_->type(index));
  chbox_is_folder_->setChecked(file_system_model_->isDir(index));

  int file_size = file_system_model_->size(index);
  if (file_size < 1024) {
    label_file_size_->setText(QString("%1 KB").arg(file_size));
  } else {
    label_file_size_->setText(QString::asprintf("%.1f MB", file_size / 1024.0));
  }

  std::cout << "[INFO] TreeView Clicked." << std::endl;
}