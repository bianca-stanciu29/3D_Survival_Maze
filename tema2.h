#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema2/camera.h"
using namespace std;

struct coliziune {
    glm::vec3 position;
    glm::vec3 dimension;

    coliziune() {

    }

    coliziune(glm::vec3 position, glm::vec3 dimension) {
        this->position = position;
        this->dimension = dimension;
    }
};

struct glont2 {

    glm::vec3 position;
    glm::vec3 forward;
    float angular;
    int click;
    coliziune col;
    glont2() {
        position = glm::vec3(0, 2, 5);
        forward = glm::vec3(0, 0, -1);
        angular = 0;
        click = 0;
        col = coliziune();
    }
    glont2( glm::vec3 position,  glm::vec3 forward, float angular, int click, coliziune col) {
        this->position = position;
        this->forward = forward;
        this->angular = angular;
        this->click = click;
        this->col = col;
    }
};



struct inamic2 {
    coliziune inamic;
    
    inamic2( coliziune coliziune) {
        this->inamic = coliziune;
    }
};


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
        Tema2();
        ~Tema2();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void Labirint();
        void adous_border();
        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) override;
        void init_dim(int h, int w);
        vector<pair<int, int>> find_neighbors(int r, int c, int grid[][21], bool isWall = false);
        void generate(int h, int w);
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        bool Collision(coliziune a, coliziune b);
        void printText(char* text);
        Mesh* CreateCube(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);
     protected:
        implemented::Camera_Tema *camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        // TODO(student): If you need any other class variables, define them here.
        float fov;
        float inaltime;
        float latime;
        int H;
        int W;
        int grid[21][21];
        float pozX, pozY;
        float angularStep;
        int speed = 10000;
        float nr_glont;
        std::vector<glont2> gloante;
        std::vector<inamic2> inamici;
        std::vector<coliziune> obstacole;
        coliziune player_col;
        implemented::Camera_Tema* poz;
        float offsetX = 0, offsetZ = 0;
        int flagX = 1, flagZ = 1;
        int col = 0;
        int row = 1;
        int end_col = 0;
        int end_row = 19;
        float time_total = 100;
        float life = 20;
        coliziune end_coliziune;
        
    };
}   // namespace m1
