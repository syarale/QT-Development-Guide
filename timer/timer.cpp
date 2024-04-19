#include "timer.h"

#include <cassert>
#include <iostream>

#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

constexpr int INIT_COUNT = 60;
constexpr int MIN_COUNT = 1;
constexpr int MAX_COUNT = 1000;
constexpr int TIMER_INTERVAL = 1000;  // ms

Timer::Timer() : current_count_(INIT_COUNT) {
  InitUI();
  InitUISlots();
  InitTimer();
  setWindowTitle("Timer");
}

Timer::~Timer() {}

void Timer::InitUI() {
  label_count_ = new QLabel("Set Counter: ");
  spinbox_count_ = new QSpinBox();
  spinbox_count_->setValue(INIT_COUNT);
  spinbox_count_->setSuffix(" s");
  spinbox_count_->setRange(MIN_COUNT, MAX_COUNT);

  QHBoxLayout* hlayout1_ = new QHBoxLayout();
  hlayout1_->addWidget(label_count_);
  hlayout1_->addWidget(spinbox_count_);

  pbutton_start_ = new QPushButton();
  pbutton_stop_ = new QPushButton();
  pbutton_start_->setText("Start");
  pbutton_stop_->setText("Stop");

  QHBoxLayout* hlayout2_ = new QHBoxLayout();
  hlayout2_->addWidget(pbutton_start_);
  hlayout2_->addWidget(pbutton_stop_);

  QVBoxLayout* vlayout1_ = new QVBoxLayout();
  vlayout1_->addLayout(hlayout1_);
  vlayout1_->addLayout(hlayout2_);

  QGroupBox* button_group_ = new QGroupBox();
  button_group_->setLayout(vlayout1_);

  lcd_numer_ = new QLCDNumber();
  lcd_numer_->setSegmentStyle(QLCDNumber::Flat);
  lcd_numer_->display(INIT_COUNT);

  QHBoxLayout* hlayout3_ = new QHBoxLayout();
  hlayout3_->addWidget(button_group_);
  hlayout3_->addWidget(lcd_numer_);

  pgbar_progress_ = new QProgressBar();
  pgbar_progress_->setRange(0, INIT_COUNT);
  pgbar_progress_->setValue(INIT_COUNT);
  pgbar_progress_->setInvertedAppearance(true);

  QVBoxLayout* major_layout_ = new QVBoxLayout(this);
  major_layout_->addLayout(hlayout3_);
  major_layout_->addWidget(pgbar_progress_);
  setLayout(major_layout_);

  is_ui_inited = true;
}

void Timer::InitUISlots() {
  assert(is_ui_inited);

  connect(spinbox_count_, QOverload<int>::of(&QSpinBox::valueChanged), this,
          OnValueChanged);
  connect(pbutton_start_, &QPushButton::clicked, this, OnStartClick);
  connect(pbutton_stop_, &QPushButton::clicked, this, OnStopClick);

  std::cout << "[INFO] Init slot functions completed." << std::endl;
}

void Timer::OnValueChanged(int value) {
  StopTimer();

  int count = spinbox_count_->value();
  lcd_numer_->display(count);
  pgbar_progress_->setRange(0, count);
  pgbar_progress_->setValue(count);

  std::cout << "[INFO] SpinBox's value changed." << std::endl;
}

void Timer::OnStartClick() {
  StartTimer();
  std::cout << "[INFO] Timer start successed." << std::endl;
}

void Timer::OnStopClick() {
  StopTimer();
  std::cout << "[INFO] Timer stop successed." << std::endl;
}

void Timer::OnTimerout() {
  --current_count_;
  lcd_numer_->display(current_count_);
  pgbar_progress_->setValue(current_count_);
  std::cout << "[INFO] Trigger timeout, current count: " << current_count_
            << std::endl;

  if (current_count_ <= 0) {
    StopTimer();
    std::cout << "[INFO] Count down to 0, timer finished." << std::endl;
  }
}

void Timer::InitTimer() {
  timer_ = new QTimer(this);
  timer_->setInterval(TIMER_INTERVAL);
  connect(timer_, &QTimer::timeout, this, OnTimerout);
  std::cout << "[INFO] Init Timer completed.";
}

void Timer::StartTimer() {
  is_timer_running = true;
  current_count_ = lcd_numer_->value();
  pbutton_start_->setEnabled(false);
  timer_->start();
}

void Timer::StopTimer() {
  if (is_timer_running) {
    timer_->stop();
    pbutton_start_->setEnabled(true);
    is_timer_running = false;
  }
}