#include "MyGui.h"


bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

MyGui::MyGui(GraphicalInterface* graphicsData){

    this->graphicsData = *graphicsData;

    //Initialize the SDL Platform
    platform = Platform(graphicsData->windowName, graphicsData->windowWidth, graphicsData->windowHeight, graphicsData->pxlWidth, graphicsData->pxlHeight);

    textureID = (ImTextureID)platform.screenTexture;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(platform.window, platform.renderer);
    ImGui_ImplSDLRenderer3_Init(platform.renderer);
    
}

bool MyGui::ProcessEvent(uint8_t* keypad){
    bool quit = false;

    SDL_Event event;
    while(SDL_PollEvent(&event)){
        ImGui_ImplSDL3_ProcessEvent(&event);
        quit = platform.ProcessInput(keypad, event);
        if (quit)
            break;
    }

    return quit;
}

void MyGui::Update(const void* pixels, int pitch){
    //platform.Render(pixels, pitch);

    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    if(show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }




    if (show_another_window){
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }


    ImGui::Begin("Emulator");

    SDL_UpdateTexture(platform.screenTexture, NULL, pixels, pitch);

    ImGui::Image(textureID, ImVec2(graphicsData.windowWidth, graphicsData.windowHeight));
    ImGui::End();


    //platform.Render(pixels, pitch);

    ImGui::Render();

    SDL_SetRenderDrawColorFloat(platform.renderer, clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    SDL_RenderClear(platform.renderer);

    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), platform.renderer);

    SDL_RenderPresent(platform.renderer);

    
}

void MyGui::destroy(){
    platform.destroy();

    ImGui_ImplSDL3_Shutdown();
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui::DestroyContext();
}