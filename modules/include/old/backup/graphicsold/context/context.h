#pragma once

// namespace RG {
// 	class PostProcess {

// 		GLuint framebuffer, textureColorbuffer;
// 		GLuint quadVAO, quadVBO;
// 		// GLuint postProcessingShader;
// 		RG_Shader_Raw postRawShaders;
// 		RG_Shader postShader;
// 	public:
// 		void init() {
// 			postRawShaders.init(RG_StandartPostProcessShader330, RG_StandartVertexShader330);
// 			postShader.init(postRawShaders);

// 			// postProcessingShader = 
// 			// Генерация framebuffer
// 			glGenFramebuffers(1, &framebuffer);
// 			glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

// 			// Создание текстуры для хранения результата рендеринга
// 			glGenTextures(1, &textureColorbuffer);
// 			glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
// 			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, RG_Window_Standart->set().resolution.x, RG_Window_Standart->set().resolution.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
// 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

// 			// Проверка framebuffer
// 			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
// 				RG_Debug::addl(RG_LOG_WARNING, "Framebuffer is not complete!");
// 			// std::rg_cout << "Framebuffer is not complete!" << std::endl;

// 			glBindFramebuffer(GL_FRAMEBUFFER, 0);

// 			// Создание полноэкранного квадрата
// 			float quadVertices[] = {
// 				// Координаты      // Текстурные координаты
// 				-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
// 				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
// 				 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,

// 				-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
// 				 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
// 				 1.0f,  1.0f, 0.0f, 1.0f, 1.0f
// 			};

// 			glGenVertexArrays(1, &quadVAO);
// 			glGenBuffers(1, &quadVBO);
// 			glBindVertexArray(quadVAO);
// 			glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
// 			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
// 			glEnableVertexAttribArray(0);
// 			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
// 			glEnableVertexAttribArray(1);
// 			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
// 		}
// 		void update() {
// 			// Первый проход: Рендеринг сцены в framebuffer
// 			glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
// 			// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// 			// Здесь происходит ваш текущий рендеринг (всё, что вы обычно выводите на экран)
// 			// Например, вызовы OpenGL для отрисовки объектов, текстур и т.д.

// 			glBindFramebuffer(GL_FRAMEBUFFER, 0); // Отвязываем framebuffer

// 			// Второй проход: Применение постобработки
// 			// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 			// glUseProgram(postProcessingShader); // Шейдер постобработки
// 			postShader.used();
// 			glBindVertexArray(quadVAO);
// 			glBindTexture(GL_TEXTURE_2D,  ); // Текстура сцены
// 			glDrawArrays(GL_TRIANGLES, 0, 6);
// 			RG_Shader_StandartPtr->used();
// 		}
// 	};
// }
// RG::PostProcess RG_TEST_POST_PROCESS;
namespace RG_Events {
	RG_Array<RG_Array<char>>DragNDropPaths;
	bool WindowWasChange = false;
	bool FileWasDropped = false;
	bool ClipboardUpdate = false;
	bool WinPosChanget = false;
	// bool postprocesison = false;
	// POINT2D<uint> WinPos = {0,0};

	string Clipboard;
	POINT2D<int> ScrollMouse;
	POINT2D <double> MPos;
	//int & (Keys[350]) = RG_KEYS;
	//int & (Keys_Tape[350]) = RG_KEYS_TAPE;
	// void Update(RG_Timer& timer = *RG_Timer_StandartPtr){

	// }
	// void PostProcessOn() {
	// 	postprocesison = true;
	// 	RG_TEST_POST_PROCESS.init();
	// }
	void Update(bool clear = true, RG_Timer& timer = *RG_Timer_StandartPtr) {
		/*if(!AlredyUpdate){
			glfwSwapBuffers(RG_Window_Standart->win());
			//sizeWindowChange = false;
			WindowWasChange = false;
			FileWasDropped = false;
			ClipboardUpdate = false;
			ScrollMouse.y = 0;
			ScrollMouse.x = 0;
		}*/

		/*POST */
		// Генерация framebuffer и текстуры

		/**/
		// if (postprocesison)
		// 	RG_TEST_POST_PROCESS.update();
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
	/*void Update(){
	 RG_Debug::addl(RG_LOG_WARNING,"RG_Events::Update() ")
	 glfwSwapBuffers(RG_Window_Standart->win());
	 //sizeWindowChange = false;
	 WindowWasChange = false;
	 FileWasDropped = false;
	 ClipboardUpdate = false;
	 AlredyUpdate = true;
	 ScrollMouse.y = 0;
	 ScrollMouse.x = 0;
	}*/

	namespace Callback {//Calback
		void GLFW_Error(int err, const char* description) {
			RG_Debug::addl(RG_LOG_ERROR, "GLFW_Error: " + to_string(err) + ", " + string(description));
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



















void RG_TestGLError() {
	int glError = 0;
	RG_Debug::addl(RG_LOG_INFO, "Start test GL error");
	while ((glError = glGetError()) != GL_NO_ERROR) {
		switch (glError) {
			case GL_NO_ERROR:						RG_Debug::addl(RG_LOG_ERROR, "GL_NO_ERROR");break;
			case GL_INVALID_ENUM:				RG_Debug::addl(RG_LOG_ERROR, "GL_INVALID_ENUM");break;
			case GL_INVALID_VALUE:			RG_Debug::addl(RG_LOG_ERROR, "GL_INVALID_VALUE");break;
			case GL_INVALID_OPERATION:	RG_Debug::addl(RG_LOG_ERROR, "GL_INVALID_OPERATION");break;
			case GL_STACK_OVERFLOW:			RG_Debug::addl(RG_LOG_ERROR, "GL_STACK_OVERFLOW");break;
			case GL_STACK_UNDERFLOW:		RG_Debug::addl(RG_LOG_ERROR, "GL_STACK_UNDERFLOW");break;
			case GL_OUT_OF_MEMORY:			RG_Debug::addl(RG_LOG_ERROR, "GL_OUT_OF_MEMORY");break;
			default:										RG_Debug::addl(RG_LOG_ERROR, "Unknown error");break;
		};
	}
	RG_Debug::addl(RG_LOG_INFO, "Stop test GL error");
}

void RG_GL_Get_Error() {
	int glError = 0;
	RG_Debug::addl(RG_LOG_INFO, "Start test GL error");
	while ((glError = glGetError()) != GL_NO_ERROR) {
		switch (glError) {
			case GL_NO_ERROR:						RG_Debug::addl(RG_LOG_ERROR, "GL_NO_ERROR");break;
			case GL_INVALID_ENUM:				RG_Debug::addl(RG_LOG_ERROR, "GL_INVALID_ENUM");break;
			case GL_INVALID_VALUE:			RG_Debug::addl(RG_LOG_ERROR, "GL_INVALID_VALUE");break;
			case GL_INVALID_OPERATION:	RG_Debug::addl(RG_LOG_ERROR, "GL_INVALID_OPERATION");break;
			case GL_STACK_OVERFLOW:			RG_Debug::addl(RG_LOG_ERROR, "GL_STACK_OVERFLOW");break;
			case GL_STACK_UNDERFLOW:		RG_Debug::addl(RG_LOG_ERROR, "GL_STACK_UNDERFLOW");break;
			case GL_OUT_OF_MEMORY:			RG_Debug::addl(RG_LOG_ERROR, "GL_OUT_OF_MEMORY");break;
			default:										RG_Debug::addl(RG_LOG_ERROR, "Unknown error");break;
		};
	}
	RG_Debug::addl(RG_LOG_INFO, "Stop test GL error");
}





string& Clipboard = RG_Events::Clipboard;
POINT2D<int>& ScrollMouse = RG_Events::ScrollMouse;
POINT2D <double>& MPos = RG_Events::MPos;
