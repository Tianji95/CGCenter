#include "uiframework.h"
#include <iostream>
// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;
    switch (key) {
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GL_TRUE);
        break;
    case GLFW_KEY_W:
        UIFramework::Instance().camera->MoveForward(1);
        break;
    case GLFW_KEY_S:
        UIFramework::Instance().camera->MoveBack(1);
        break;

    case GLFW_KEY_A:
        UIFramework::Instance().camera->MoveLeft(1);
        break;

    case GLFW_KEY_D:
        UIFramework::Instance().camera->MoveRight(1);
        break;

    default:
        break;
    }
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    //if (action == GLFW_PRESS) switch (button) {
    //case GLFW_MOUSE_BUTTON_LEFT:
    //    strcpy(msg, "Mosue left button clicked!");
    //    break;
    //case GLFW_MOUSE_BUTTON_MIDDLE:
    //    strcpy(msg, "Mosue middle button clicked!");
    //    break;
    //case GLFW_MOUSE_BUTTON_RIGHT:
    //    strcpy(msg, "Mosue right button clicked!");
    //    break;
    //default:
    //    return;
    //}
    //return;
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
    //if (height == 0)  									// Prevent A Divide By Zero By
    //{
    //    height = 1;										// Making Height Equal One
    //}
    //if (h > 0)
    //    ratio = (float)w / (float)h;
    //glViewport(0, 0, w, h); // Setup viewport
    //width = w;
    //height = h;
    //glViewport(0, 0, width, height);						// Reset The Current Viewport
    //glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    //glLoadIdentity();									// Reset The Projection Matrix
    //// Calculate The Aspect Ratio Of The Window
    //gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    //glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
    //glLoadIdentity();
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    std::cout << "xpos:" << xpos << "   ypos:" << ypos << std::endl;
    //if (firstMouse) // 这个bool变量初始时是设定为true的
    //{
    //    lastX = xpos;
    //    lastY = ypos;
    //    firstMouse = false;
    //    //        return;
    //}
    //float xoffset = xpos - lastX;
    //float yoffset = lastY - ypos;
    //lastX = xpos;
    //lastY = ypos;


    //float sensitivity = 0.05f;//灵敏度
    //xoffset *= sensitivity;
    //yoffset *= sensitivity;

    //yaw += xoffset;
    //pitch += yoffset;

    //pitch = pitch > 89.0f ? 89.0f : pitch;
    //pitch = pitch < -89.0f ? -89.0f : pitch;

    //glm::vec3 front;
    ////根据俯仰和偏航角度来算出此向量，也就是速度在三个维度的数值
    //front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    //front.y = sin(glm::radians(pitch));
    //front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch)) - 1;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    std::cout << "xoffset:" << xoffset << "   yoffset:" << yoffset << std::endl;

    //if (fov >= 1.0f && fov <= 45.0f) {
    //    fov -= yoffset;
    //}

    //fov = fov <= 1.0f ? 1.0f : fov;
    //fov = fov >= 45.0f ? 45.0f : fov;
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

bool UIFramework::Init()
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return false;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create window with graphics context
    window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL)
        return false;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    bool err = glewInit() != GLEW_OK;
    if (err) {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return false;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, scroll_callback);
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    render = new Render();
    camera = new Camera();

    return true;
}

bool UIFramework::Draw()
{
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    // Rendering
    ImGui::Render(); 
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    render->DrawScene();

    glfwSwapBuffers(window);
    return true;
}
bool UIFramework::WindowShouldClose()
{
    return glfwWindowShouldClose(window);
}

bool UIFramework::Destroy()
{
    delete render;
    delete camera;
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return true;
}
