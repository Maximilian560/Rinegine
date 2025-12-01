#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "add/fpscam"

struct RG_FPS_CAM_Set;

void RG_Camera_Update(RG_Camera& cam, RG_FPS_CAM_Set& set);

struct RG_FPS_CAM_Set {
  POINT3D<double>AngleCam;
  double accelSpeed = 7;
  double constSpeed = 2;
private:
  double speed = 0;
  bool mouseHide = 1;
  friend void RG_Camera_Update(RG_Camera& cam, RG_FPS_CAM_Set& set);
}RG_FPS_CAM_Set_Standart;

static RG::vec2<double> MouseMove = { 0,0 };
static bool fast_update = false,
FastUpdateClear = false;
static RG_Timer FastTimer;
static double FPSUpdate = 0;
static uint FastIterate = 0;
class FastUpdate {
  friend void FastUpdateMouseEventOn(RG_Window&);
  friend void FastUpdateMouseEventOff();
  static thread FastThread;
  inline static bool run = false;
  static void Start(RG_Window& win = *RG_Window_Standart) {
    if (run)return;
    run = 1;
    FastThread = thread([&]() {
      while (run) {
        FastTimer.update();
        POINT2D<double> temp;
        FPSUpdate += FastTimer.getBias();
        FastIterate++;
        /*if (FastUpdateClear) {
          MouseMove.x = 0;
          MouseMove.y = 0;
          FastUpdateClear = false;
        }*/
        glfwGetCursorPos(win.win(), &temp.x, &temp.y);
        MouseMove.x += ((temp.x - RG_Window_Standart->set().resolution.x / 2.) / 3.);
        MouseMove.y += ((temp.y - RG_Window_Standart->set().resolution.y / 2.) / 3.);
      }
      return;
    });
  }
  static void Stop() {
    run = 0;
    if (FastThread.joinable())
      FastThread.join();
  }
};
std::thread FastUpdate::FastThread;
void FastUpdateMouseEventOn(RG_Window& win = *RG_Window_Standart) {
  if (fast_update)return;
  fast_update = true;
  FastUpdate::Start(win);

}

void FastUpdateMouseEventOff() {
  fast_update = false;
  FastUpdate::Stop();
}

void RG_Camera_Update(RG_Camera& cam = RG_Camera_Standart, RG_FPS_CAM_Set& set = RG_FPS_CAM_Set_Standart) {

  set.speed = set.constSpeed * RG_Timer_Standart.getBias();

  if (RG_KEYS[GLFW_KEY_EQUAL] || RG_KEYS[GLFW_KEY_KP_ADD]) {
    cam.zoom(cam.getZoom() * RG_Timer_Standart.getBias());
  }
  if (RG_KEYS[GLFW_KEY_MINUS] || RG_KEYS[GLFW_KEY_KP_SUBTRACT]) {
    cam.zoom(-cam.getZoom() * RG_Timer_Standart.getBias());
  }


  if ((RG_KEYS[GLFW_KEY_LEFT_ALT] || RG_KEYS[GLFW_KEY_RIGHT_ALT]) && set.mouseHide) {
    set.mouseHide = 0;
    glfwSetInputMode(RG_Window_Standart->win(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }
  elif(!RG_KEYS[GLFW_KEY_LEFT_ALT] && !RG_KEYS[GLFW_KEY_RIGHT_ALT]) {
    if (!set.mouseHide) {
      set.mouseHide = 1;
      glfwSetCursorPos(RG_Window_Standart->win(), RG_Window_Standart->set().resolution.x / 2., RG_Window_Standart->set().resolution.y / 2.);
      glfwSetInputMode(RG_Window_Standart->win(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }elif(glfwGetWindowAttrib(RG_Window_Standart->win(), GLFW_HOVERED)) {
      if (fast_update) {
        //set.AngleCam.x += ((MPos.x - RG_Window_Standart->set().resolution.x / 2.) / 3.) / (cam.getZoom() >= 1 ? cam.getZoom() : 1);
        //set.AngleCam.y += ((MPos.y - RG_Window_Standart->set().resolution.y / 2.) / 3.) / (cam.getZoom() >= 1 ? cam.getZoom() : 1);
        set.AngleCam.x += (MouseMove.x*(FPSUpdate/(double)FastIterate)*50.) / (cam.getZoom() >= 1 ? cam.getZoom() : 1);
        set.AngleCam.y += (MouseMove.y*(FPSUpdate/(double)FastIterate)*50.) / (cam.getZoom() >= 1 ? cam.getZoom() : 1);
        FPSUpdate = 0;
        FastIterate = 0;
        glfwSetCursorPos(RG_Window_Standart->win(), RG_Window_Standart->set().resolution.x / 2., RG_Window_Standart->set().resolution.y / 2.);
        MouseMove.x = 0;
        MouseMove.y = 0;
        FastUpdateClear = true;
      }
      else {
        set.AngleCam.x += ((MPos.x - RG_Window_Standart->set().resolution.x / 2.) / 3.) / (cam.getZoom() >= 1 ? cam.getZoom() : 1);
        set.AngleCam.y += ((MPos.y - RG_Window_Standart->set().resolution.y / 2.) / 3.) / (cam.getZoom() >= 1 ? cam.getZoom() : 1);
        glfwSetCursorPos(RG_Window_Standart->win(), RG_Window_Standart->set().resolution.x / 2., RG_Window_Standart->set().resolution.y / 2.);
      }
    }
  }


  if (set.AngleCam.y > 90)set.AngleCam.y = 90;
  if (set.AngleCam.y < -90)set.AngleCam.y = -90;
  if (set.AngleCam.x > 180)set.AngleCam.x -= 360;
  if (set.AngleCam.x < -180)set.AngleCam.x += 360;
  cam.setRotate(set.AngleCam);

  if (RG_KEYS[GLFW_KEY_LEFT_SHIFT] || RG_KEYS[GLFW_KEY_RIGHT_SHIFT]) {
    set.speed *= set.accelSpeed;
  }
  if (RG_KEYS[GLFW_KEY_SPACE]) {
    cam.move({ 0, -set.speed * (1. / cam.getZoom()), 0 });
  }
  if (RG_KEYS[GLFW_KEY_LEFT_CONTROL] || RG_KEYS[GLFW_KEY_RIGHT_CONTROL]) {
    cam.move({ 0, set.speed * (1. / cam.getZoom()), 0 });
  }

  if (RG_KEYS[GLFW_KEY_W] || RG_KEYS[GLFW_KEY_UP] || RG_KEYS[GLFW_KEY_KP_8]) {
    cam.move({
      -sin(set.AngleCam.x / 180. * M_PI) * set.speed * ((set.AngleCam.x > 180) ? -1 : 1) * (1. / cam.getZoom()),                                                                    /*X*/
      0,                                                                    /*Y*/
      cos(set.AngleCam.x / 180. * M_PI) * set.speed * ((set.AngleCam.x > 180) ? -1 : 1) * (1. / cam.getZoom()) /*Z*/
      });
  }
  if (RG_KEYS[GLFW_KEY_S] || RG_KEYS[GLFW_KEY_DOWN] || RG_KEYS[GLFW_KEY_KP_2]) {
    cam.move({
      sin(set.AngleCam.x / 180. * M_PI) * set.speed * ((set.AngleCam.x > 180) ? -1 : 1) * (1. / cam.getZoom()),                                                                    /*X*/
      0,                                                                    /*Y*/
      -cos(set.AngleCam.x / 180. * M_PI) * set.speed * ((set.AngleCam.x > 180) ? -1 : 1) * (1. / cam.getZoom()) /*Z*/
      });
  }

  if (RG_KEYS[GLFW_KEY_A] || RG_KEYS[GLFW_KEY_LEFT] || RG_KEYS[GLFW_KEY_KP_4]) {
    cam.move({
      cos(set.AngleCam.x / 180. * M_PI) * set.speed * ((set.AngleCam.x > 180) ? -1 : 1) * (1. / cam.getZoom()),                                                                    /*X*/
      0,                                                                    /*Y*/
      sin(set.AngleCam.x / 180. * M_PI) * set.speed * ((set.AngleCam.x > 180) ? -1 : 1) * (1. / cam.getZoom()) /*Z*/
      });
  }
  if (RG_KEYS[GLFW_KEY_D] || RG_KEYS[GLFW_KEY_RIGHT] || RG_KEYS[GLFW_KEY_KP_6]) {
    cam.move({
      -cos(set.AngleCam.x / 180. * M_PI) * set.speed * ((set.AngleCam.x > 180) ? -1 : 1) * (1. / cam.getZoom()),                                                                    /*X*/
      0,                                                                    /*Y*/
      -sin(set.AngleCam.x / 180. * M_PI) * set.speed * ((set.AngleCam.x > 180) ? -1 : 1) * (1. / cam.getZoom()) /*Z*/
      });
  }

}