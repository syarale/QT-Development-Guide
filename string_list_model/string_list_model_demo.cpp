#include "string_list_model_demo.h"

#include <cassert>
#include <iostream>

#include <QGridLayout>
#include <QGroupBox>
#include <QStringList>
#include <QVBoxLayout>

StringListModelDemo::StringListModelDemo(QWidget* parent) {
  InitUI();
  InitModel();
  InitUISlots();

  setWindowTitle("String List Model");
}
StringListModelDemo::~StringListModelDemo() {}

void StringListModelDemo::InitUI() {
  QVBoxLayout* major_layout = new QVBoxLayout();

  QSplitter* splitter = new QSplitter(Qt::Horizontal);
  {
    QGroupBox* gbox_list_view = new QGroupBox("QListView");
    {
      QGridLayout* grid = new QGridLayout();
      pbutton_add_ = new QPushButton("Add Item");
      pbutton_insert_ = new QPushButton("Insert Item");
      pbutton_delete_ = new QPushButton("Delete Item");
      pbutton_clear_list_ = new QPushButton("Clear List");
      grid->addWidget(pbutton_add_, 0, 0);
      grid->addWidget(pbutton_insert_, 0, 1);
      grid->addWidget(pbutton_delete_, 1, 0);
      grid->addWidget(pbutton_clear_list_, 1, 1);

      list_view_ = new QListView();

      QVBoxLayout* vlayout = new QVBoxLayout();
      vlayout->addLayout(grid);
      vlayout->addWidget(list_view_);
      gbox_list_view->setLayout(vlayout);
    }

    QGroupBox* gbox_text_edit = new QGroupBox("QPlainTextEdit");
    {
      pbutton_clear_text_ = new QPushButton("Clear Text");
      pbutton_show_model_ = new QPushButton("Show Model");
      text_edit_ = new QPlainTextEdit();
      // text_edit_->setEnabled(false);

      QVBoxLayout* vlayout = new QVBoxLayout();
      vlayout->addWidget(pbutton_clear_text_);
      vlayout->addWidget(pbutton_show_model_);
      vlayout->addWidget(text_edit_);
      gbox_text_edit->setLayout(vlayout);
    }
    splitter->addWidget(gbox_list_view);
    splitter->addWidget(gbox_text_edit);
  }

  QGroupBox* group_box = new QGroupBox();
  {
    QVBoxLayout* layout = new QVBoxLayout();
    label_curr_index_ = new QLabel("Current Item Index: ");
    layout->addWidget(label_curr_index_);
    group_box->setLayout(layout);
  }

  major_layout->addWidget(splitter);
  major_layout->addWidget(group_box);
  setLayout(major_layout);

  is_ui_inited = true;
  std::cout << "[INFO] UI Init successed." << std::endl;
}

void StringListModelDemo::InitModel() {
  QStringList string_list;
  string_list << "BeiJing"
              << "ShangHai"
              << "TianJin"
              << "HeBei"
              << "ShanDong"
              << "SiChuan"
              << "ChongQing";

  list_model_ = new QStringListModel(this);
  list_model_->setStringList(string_list);
  list_view_->setModel(list_model_);
  list_view_->setEditTriggers(QAbstractItemView::DoubleClicked |
                              QAbstractItemView::SelectedClicked);
}

void StringListModelDemo::InitUISlots() {
  assert(is_ui_inited);
  connect(pbutton_add_, QPushButton::clicked, this, &OnAddClicked);
  connect(pbutton_insert_, QPushButton::clicked, this, &OnInsertClicked);
  connect(pbutton_delete_, QPushButton::clicked, this, &OnDeleteClicked);
  connect(pbutton_clear_list_, QPushButton::clicked, this, &OnClearListClicked);
  connect(pbutton_clear_text_, QPushButton::clicked, this, &OnClearTextClicked);
  connect(pbutton_show_model_, QPushButton::clicked, this, &OnShowModelClicked);

  connect(list_view_, &QListView::clicked, this, &OnSelectRow);
}

void StringListModelDemo::OnAddClicked() {
  list_model_->insertRow(list_model_->rowCount());
  QModelIndex new_index = list_model_->index(list_model_->rowCount() - 1, 0);
  list_model_->setData(new_index, "New Item", Qt::DisplayRole);
  list_view_->setCurrentIndex(new_index);
  std::cout << "[INFO] Click Add..." << std::endl;
}

void StringListModelDemo::OnInsertClicked() {
  QModelIndex curr_index = list_view_->currentIndex();
  list_model_->insertRow(curr_index.row());
  list_model_->setData(curr_index, "Inserted Item", Qt::DisplayRole);
  list_view_->setCurrentIndex(curr_index);
  std::cout << "[INFO] Click Insert..." << std::endl;
}

void StringListModelDemo::OnDeleteClicked() {
  QModelIndex curr_index = list_view_->currentIndex();
  list_model_->removeRow(curr_index.row());
  std::cout << "[INFO] Click Delete..." << std::endl;
}

void StringListModelDemo::OnClearListClicked() {
  list_model_->removeRows(0, list_model_->rowCount());
  std::cout << "[INFO] Click ClearList..." << std::endl;
}

void StringListModelDemo::OnClearTextClicked() {
  text_edit_->clear();
  std::cout << "[INFO] Click ClearText..." << std::endl;
}

void StringListModelDemo::OnShowModelClicked() {
  QStringList string_list = list_model_->stringList();
  text_edit_->clear();
  for (int i = 0; i < string_list.count(); i++) {
    text_edit_->appendPlainText(string_list.at(i));
  }
  std::cout << "[INFO] Click ShowModel..." << std::endl;
}

void StringListModelDemo::OnSelectRow(const QModelIndex& index) {
  label_curr_index_->setText(
      QString::asprintf("Current Item Index: row = %d, column = %d",
                        index.row(), index.column()));
}