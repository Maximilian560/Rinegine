#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/med/events"

namespace RG_Events {
	RG_Array<RG_Array<char>>DragNDropPaths;
	bool WindowWasChange = false;
	bool FileWasDropped = false;
	bool ClipboardUpdate = false;
	bool WinPosChanget = false;

	string Clipboard;
	POINT2D<int> ScrollMouse;
	POINT2D <double> MPos;

	void Update(bool clear = true, RG_Timer& timer = *RG_Timer_StandartPtr) {
		glfwSwapBuffers(RG_Window_Standart->win());
		if (clear)
			RG_ClearContext();
		//sizeWindowChange = false;
		WindowWasChange = false;
		FileWasDropped = false;
		ClipboardUpdate = false;
		WinPosChanget = false;
		ScrollMouse.y = 0;
		ScrollMouse.x = 0;

		RG_Camera_StandartPtr->update();
		glfwPollEvents();
		glfwGetCursorPos(RG_Window_Standart->win(), &MPos.x, &MPos.y);
		timer.update();
	}
	namespace Context {
		void Update(RG_Timer& timer = *RG_Timer_StandartPtr) {
			glfwSwapBuffers(RG_Window_Standart->win());
			RG_ClearContext();
			WindowWasChange = false;
			FileWasDropped = false;
			ClipboardUpdate = false;
			WinPosChanget = false;
			ScrollMouse.y = 0;
			ScrollMouse.x = 0;
			glfwPollEvents();
			glfwGetCursorPos(RG_Window_Standart->win(), &MPos.x, &MPos.y);
			timer.update();
		}
	}
	namespace Other {
		static bool run = 1;
		void Start() {
			thread test([]() {
				while (run) {
					RG_Camera_StandartPtr->update();
				}
				return;
			});
		}
		void Stop() {
			run = 0;
		}
	}
	namespace Callback {//Calback
		void GLFW_Error(int err, const char* description) {
			RG_LOG_LOCK_ERROR("GLFW_Error: " + to_string(err) + ", " + string(description));
		}

		void Keys(GLFWwindow* win, int key, int scancode, int action, int mods) {
			if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
				RG_Window_Standart->Active_Fullscreen();
				glfwSetCursorPos(RG_Window_Standart->win(), RG_Window_Standart->set().resolution.x / 2., RG_Window_Standart->set().resolution.y / 2.);
				//if(RG_CursorFix)glfwSetCursorPos(window,WindowSize.x/2.,WindowSize.y/2.);

			}
			if (RG_KEYS[GLFW_KEY_LEFT_CONTROL] && key == GLFW_KEY_V) {
				const char* tempa = glfwGetClipboardString(RG_Window_Standart->win());
				if (tempa != nullptr) {
					Clipboard = tempa;
					ClipboardUpdate = true;
				}
			}
			RG_KEYS[key] = action;
			if(action == 1){
				RG_KEYS_TEST[key]++;
			}elif(action == 0&&RG_KEYS_TEST[key]>0){	
				RG_KEYS_TEST[key]--;
			}
			/*if(action <= 1){
				RG_KEYS[key] = action;
			}*/
		}

		void DragNDrop(GLFWwindow* window, int path_count, const char* paths[]) {
			if (!DragNDropPaths.empty()) {
				DragNDropPaths.clear();
			}
			int temp_size = 0;
			//rg_cout<<path_count<<"\n"<<paths[0]<<endl<<endl;
			DragNDropPaths.resize(path_count);
			for (int i = 0; i < path_count; i++) {
				//RG_DragNDropPaths[i].resize();
				temp_size = 0;
				for (int j = 0;paths[i][j] != '\0';j++) {
					temp_size++;
					//rg_cout<<paths[i][j]<<endl;
				}
				DragNDropPaths[i].resize(temp_size + 1);
				for (int j = 0;j < temp_size;j++) {
					DragNDropPaths[i][j] = paths[i][j];
				}
				DragNDropPaths[i][temp_size] = '\0';
				//RG_DragNDropPaths[i]=
			}
			//rg_cout<<"end\n";
			FileWasDropped = true;
		}
		void WindowPos(GLFWwindow* window, int xpos, int ypos) {
			WinPosChanget = true;
			WinPos.x = xpos;
			WinPos.y = ypos;
		}
		//void (*MainKey)(GLFWwindow* , int , int , int , int ) = &KeyEvent;
		void ViewPort(GLFWwindow* window, int x, int y) {
			RG_Window_Standart->set().resolution.x = x;
			RG_Window_Standart->set().resolution.y = y;
			RG_Window_Standart->set().winedit.quotx = RG_Window_Standart->set().resolution.x / RG_Window_Size_Standart;
			RG_Window_Standart->set().winedit.quoty = RG_Window_Standart->set().resolution.y / RG_Window_Size_Standart;
			RG_Window_Standart->set().winedit.difx = RG_Window_Standart->set().resolution.x - RG_Window_Size_Standart;
			RG_Window_Standart->set().winedit.dify = RG_Window_Standart->set().resolution.y - RG_Window_Size_Standart;
			glViewport(0, 0, x, y);
			WindowWasChange = true;
		}
		void Mouse(GLFWwindow* window, int button, int action, int mods) {
			RG_MOUSE[button] = action;
		}
		void Scroll(GLFWwindow* window, double x, double y) {
			ScrollMouse.y = y;
			ScrollMouse.x = x;
		}


		namespace Set {//Set
			void Standart(GLFWwindow*& win) {
				glfwSetKeyCallback(win, RG_Events::Callback::Keys);
				glfwSetFramebufferSizeCallback(win, RG_Events::Callback::ViewPort);
				glfwSetMouseButtonCallback(win, RG_Events::Callback::Mouse);
				glfwSetScrollCallback(win, RG_Events::Callback::Scroll);
				glfwSetDropCallback(win, RG_Events::Callback::DragNDrop);
				glfwSetWindowPosCallback(win, RG_Events::Callback::WindowPos);
				glfwSetErrorCallback(RG_Events::Callback::GLFW_Error);
			}
			void Standart(RG_Window& win) {
				Standart(win.win());
			}
			void Keys(void(&Event)(GLFWwindow*, int, int, int, int)) {
				glfwSetKeyCallback(RG_Window_Standart->win(), Event);
			}
			void ViewPort(void(&Event)(GLFWwindow*, int, int)) {
				glfwSetFramebufferSizeCallback(RG_Window_Standart->win(), Event);
			}
			void Mouse(void(&Event)(GLFWwindow*, int, int, int)) {
				glfwSetMouseButtonCallback(RG_Window_Standart->win(), Event);
			}
			void Scroll(void(&Event)(GLFWwindow*, double, double)) {
				glfwSetScrollCallback(RG_Window_Standart->win(), Event);
			}
			void DragNDrop(void(&Event)(GLFWwindow*, int, const char**)) {
				glfwSetDropCallback(RG_Window_Standart->win(), Event);
			}
			void WindowPos(void(&Event)(GLFWwindow*, int, int)) {
				glfwSetWindowPosCallback(RG_Window_Standart->win(), Event);
			}
			void GLFW_Error(void(&Event)(int, const char*)) { //int err, const char *description) {
				glfwSetErrorCallback(Event);
			}
		};

	};
};


string& Clipboard = RG_Events::Clipboard;
POINT2D<int>& ScrollMouse = RG_Events::ScrollMouse;
POINT2D <double>& MPos = RG_Events::MPos;
