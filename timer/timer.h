#ifndef TIMER_TIMER_H_
#define TIMER_TIMER_H_

#include <QLabel>
#include <QLCDNumber>
#include <QProgressBar>
#include <QPushButton>
#include <QSpinBox>
#include <QTimer>
#include <QWidget>

class Timer : public QWidget {
  Q_OBJECT
 public:
  explicit Timer();
  ~Timer();

 private:
  void InitUI();
  void InitUISlots();

  void InitTimer();
  void StartTimer();
  void StopTimer();

  // Slot functions
  void OnValueChanged(int value);  // sender: spinbox_count_
  void OnStartClick();             // sender: pbutton_start_
  void OnStopClick();              // sender: pbutton_stop_
  void OnTimerout();               // sender: timer_

  bool is_timer_running = false;  // Assert InitUI before InitSlots
  bool is_ui_inited = false;
  int current_count_ = 0;
  QTimer* timer_;

  QLabel* label_count_;
  QSpinBox* spinbox_count_;
  QPushButton* pbutton_start_;
  QPushButton* pbutton_stop_;
  QLCDNumber* lcd_numer_;
  QProgressBar* pgbar_progress_;
};

#endif  // TIMER_TIMER_H_