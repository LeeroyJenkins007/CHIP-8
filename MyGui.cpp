#include "MyGui.h"

#include <iostream>

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

    ImGuiIO& io = ImGui::GetIO(); 
    //io = ImGui::GetIO();
    (void)io;
    //this->io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(platform.mainWindow, platform.renderer);
    //ImGui_ImplSDL3_InitForSDLRenderer(platform.emulatorWindow, platform.emuRenderer);
    ImGui_ImplSDLRenderer3_Init(platform.renderer);
    //ImGui_ImplSDLRenderer3_Init(platform.emuRenderer);
    
}

bool MyGui::ProcessEvent(uint8_t* keypad, uint16_t& prevKeys){
    bool quit = false;

    SDL_Event event;
    while(SDL_PollEvent(&event)){
        ImGui_ImplSDL3_ProcessEvent(&event);
        quit = platform.ProcessInput(keypad, prevKeys, event);
        if (quit)
            break;
    }

    return quit;
}

void MyGui::Update(const void* pixels, int pitch, uint8_t emuMem[], uint16_t memSize){
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

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }

    static MemoryEditor mem_edit;
    mem_edit.DrawWindow("Memory Editor", emuMem, memSize);

    ImGui::Begin("Emulator");

    SDL_UpdateTexture(platform.screenTexture, NULL, pixels, pitch);

    ImGui::Image(textureID, ImVec2(graphicsData.emuWidth, graphicsData.emuHeight));
    ImGui::End();


    //platform.Render(pixels, pitch);

    ImGui::Render();

    SDL_SetRenderDrawColorFloat(platform.renderer, clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    SDL_RenderClear(platform.renderer);

    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), platform.renderer);

    SDL_RenderPresent(platform.renderer);

    
}

void MyGui::destroy(){
    //Clearnup SDL3
    platform.destroy();

    //Cleanup ImGUI
    ImGui_ImplSDL3_Shutdown();
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui::DestroyContext();
}