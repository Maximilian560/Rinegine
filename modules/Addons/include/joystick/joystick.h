#pragma once

#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "add/joystick"
class RG_Joystick {
  int _id = -1;
  bool _init = 0;
  const float* _axes = nullptr;
  const unsigned char* _buttons = nullptr;
  const unsigned char* _hats = nullptr;
  const char* _name;
  int countaxes = 0, countbuttons = 0, counthats = 0;
public:
  RG_Joystick() {}
  RG_Joystick(int id) { init(id); }
  void init(int id) {
    _id = id;
    _axes = glfwGetJoystickAxes(id, &countaxes);
    _buttons = glfwGetJoystickButtons(id, &countbuttons);
    _hats = glfwGetJoystickHats(id, &counthats);
    _name = glfwGetJoystickName(id);
    if (_name != nullptr)_init = 1;
  }
  void update() {
    _axes = glfwGetJoystickAxes(_id, &countaxes);
    _buttons = glfwGetJoystickButtons(_id, &countbuttons);
    _hats = glfwGetJoystickHats(_id, &counthats);
    if (countaxes != 0 || countbuttons != 0 || counthats != 0)_init = 1;else _init = 0;
  }
  void update_axes() {
    _axes = glfwGetJoystickAxes(_id, &countaxes);
    if (countaxes == 0)_init = 0;else _init = 1;
  }
  void update_buttons() {
    _buttons = glfwGetJoystickButtons(_id, &countbuttons);
    if (countbuttons == 0)_init = 0;else _init = 1;
  }
  void update_hats() {
    _hats = glfwGetJoystickHats(_id, &counthats);
    if (counthats == 0)_init = 0;else _init = 1;
  }
  int get_count_axes() { return countaxes; }
  int get_count_buttons() { return countbuttons; }
  int get_count_hats() { return counthats; }

  const bool& is_init() {
    return _init;
  }
  const float get_axes(int i) {
    if (!_init)return 0;
    int out = i < countaxes ? i : countaxes - 1;
    return _axes[out];
  }

  const unsigned char get_buttons(int i) {
    if (!_init)return 0;
    int out = i < countbuttons ? i : countbuttons - 1;
    return _buttons[out];
  }
  const unsigned char get_hats(int i) {
    if (!_init)return 0;
    int out = i < counthats ? i : counthats - 1;
    return _hats[out];
  }
  const char* get_name() { return _name; }

  int get_id() { return _id; }
  void print() {
    rg_cout << "Joystick name: " << _name << endl;
    rg_cout << "Number of axes: " << countaxes << endl;
    rg_cout << "Number of buttons: " << countbuttons << endl;
    rg_cout << "Number of hats: " << counthats << endl;
    rg_cout << "Axes: " << endl;
    for (int i = 0; i < countaxes; i++) {
      rg_cout << "  " << i << " = " << _axes[i] << endl;
    }
    rg_cout << "Buttons: " << endl;
    for (int i = 0; i < countbuttons; i++) {
      rg_cout << "  " << i << " = " << _buttons[i] << endl;
    }
    rg_cout << "Hats: " << endl;
    for (int i = 0; i < counthats; i++) {
      rg_cout << "  " << i << " = " << _hats[i] << endl;
    }
    rg_cout << endl;
  }
};