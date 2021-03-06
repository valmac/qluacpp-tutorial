#pragma once

#include <atomic>

#include "model.hpp"

struct gui {
  static gui& instance();
  void create(const std::string& title, model* m);
  void repaint();
  void terminate();

  model* model_;

  std::string title_;
  std::string wnd_class_{"qluacpp_draw_candles"};
  void* hwnd_{nullptr};
  int wnd_height_{400};
  int wnd_width_{900};
  int chart_width_{0};
  int chart_height_{0};
  int candle_width_{0};
  std::atomic<bool> done_{false};

private:
  gui() {};
};
