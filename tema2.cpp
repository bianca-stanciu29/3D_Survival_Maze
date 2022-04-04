#include "lab_m1/tema2/tema2.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}

Mesh* Tema2::CreateCube(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color) {

    std::vector<VertexFormat> vertices
    {
        VertexFormat(leftBottomCorner + glm::vec3(0.0f, 0.0f, length), color),
        VertexFormat(leftBottomCorner + glm::vec3(length, 0.0f, length), color),
        VertexFormat(leftBottomCorner + glm::vec3(0.0f, length, length), color),
        VertexFormat(leftBottomCorner + glm::vec3(length, length, length), color),
        VertexFormat(leftBottomCorner + glm::vec3(0.0f, 0.0f, 0.0f), color),
        VertexFormat(leftBottomCorner + glm::vec3(length, 0.0f, 0.0f), color),
        VertexFormat(leftBottomCorner + glm::vec3(0.0f, length, 0.0f), color),
        VertexFormat(leftBottomCorner + glm::vec3(length, length, 0.0f), color)
    };

    Mesh* cube = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        1, 3, 2,
        2, 3, 7,
        2, 7, 6,
        1, 7, 3,
        1, 5, 7,
        6, 7, 4,
        7, 5, 4,
        0, 4, 1,
        1, 4, 5,
        2, 6, 4,
        0, 2, 4
    };

    cube->InitFromData(vertices, indices);
    return cube;
}

void Tema2::Init()
{
    renderCameraTarget = true;
    fov = RADIANS(6);
    inaltime = 5;
    latime = 0;
    nr_glont = 0;
    camera = new implemented::Camera_Tema();
    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    poz = new implemented::Camera_Tema();
   
    
    {
        Mesh* foot = CreateCube("foot", glm::vec3(0), 0.5f, glm::vec3(0.0f, 0.0f, 0.8f));
        AddMeshToList(foot);

        Mesh* body = CreateCube("body", glm::vec3(0), 0.5f, glm::vec3(0.37f, 0.61f, 0.62f));
        AddMeshToList(body);

        Mesh* skin = CreateCube("skin", glm::vec3(0), 0.5f, glm::vec3(1.0f, 0.85f, 0.67f));
        AddMeshToList(skin);

        Mesh* inamic = CreateCube("inamic", glm::vec3(0), 0.5f, glm::vec3(1, 0, 0));
        AddMeshToList(inamic);

        Mesh* glont = CreateCube("glont", glm::vec3(0), 0.1f, glm::vec3(0, 0, 1));
        for (int i = 0; i < 5; i++) {
            gloante.push_back(glont2());
        }
        AddMeshToList(glont);

        Mesh* cube = CreateCube("cube", glm::vec3(0), 0.5f, glm::vec3(0, 0.39f, 0));
        AddMeshToList(cube);

        Mesh* start = CreateCube("start", glm::vec3(0), 0.5f, glm::vec3(0, 1, 0));
        AddMeshToList(start);

        Mesh* end = CreateCube("end", glm::vec3(0), 0.5f, glm::vec3(0, 0, 1));
        AddMeshToList(end);

        Mesh* time = CreateCube("time", glm::vec3(0), 0.5f, glm::vec3(0, 0, 1));
        AddMeshToList(time);
    }

    //  After you implement the changing of the projection
    // parameters, remove hardcodings of these parameters
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

    player_col.dimension.x = 1.25f;
    player_col.dimension.y = 1.25f;
    player_col.dimension.z = 1.25f;

    init_dim(10, 10);
    generate(10, 10);
    
   
    
}

void Tema2::init_dim(int h, int w) {
    H = 2 * h + 1;
    W = 2 * w + 1;
}

vector<pair<int, int>> Tema2::find_neighbors(int r, int c, int grid[][21], bool isWall) {
    vector<pair<int, int>> ns;
    if (r > 1 && grid[r - 2][c] == isWall) {
        ns.push_back(make_pair(r - 2, c));
    }
    if (r < H - 2 && grid[r + 2][c] == isWall) {
        ns.push_back(make_pair(r + 2, c));
    }
    if (c > 1 && grid[r][c - 2] == isWall) {
        ns.push_back(make_pair(r, c - 2));
    }
    if (c < W - 2 && grid[r][c + 2] == isWall) {
        ns.push_back(make_pair(r, c + 2));
    }
    random_shuffle(ns.begin(), ns.end());

    for (auto p : ns) {
        
    }
    return ns;
}

void Tema2::generate(int h, int w) {
    //int grid[11][11];
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++) {
            grid[i][j] = 1;
        }
    }
    srand(time(NULL));
    int r_aux = rand() % (H / 2);
    int crow = 1;
    int c_aux = rand() % (H / 2);
    int ccol = 2 * c_aux + 1;
    grid[crow][ccol] = 0;


    int num_visited = 1;
    vector<pair<int, int>> neighbors;

    while (num_visited < h * w) {
        neighbors.clear();
        neighbors = find_neighbors(crow, ccol, grid, true);
        if (neighbors.size() == 0) {


            auto aux = find_neighbors(crow, ccol, grid);
            int r = rand() % aux.size();

            auto e = aux[r];


            crow = e.first;
            ccol = e.second;

            continue;
        }
        for (int i = 0; i < neighbors.size(); i++) {
            if (grid[neighbors[i].first][neighbors[i].second] > 0) {
                grid[(neighbors[i].first + crow) / 2][(neighbors[i].second + ccol) / 2] = 0;
                grid[neighbors[i].first][neighbors[i].second] = 0;
                num_visited += 1;
                crow = neighbors[i].first;
                ccol = neighbors[i].second;
                break;
            }
        }
    }

    
    int nr_inamc = 14;
   
    while (nr_inamc > 0) {
        int x = rand() % 21;
        int y = rand() % 21;
        if (grid[x][y] == 0) {
            grid[x][y] = 2;
            inamic2 inamic(coliziune(glm::vec3(2*x - 20, 0, 2*y - 20), glm::vec3(0.5f, 1.0f, 0.5f)));
            inamici.push_back(inamic);
            nr_inamc--;
        }
    }

    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++) {
            if (grid[i][j] == 1) {
                coliziune perete(glm::vec3(2*i - 20, 0, 2*j - 20), glm::vec3(2, 2, 2));
                obstacole.push_back(perete);
          }
        }
    }
 
    bool ok = false;

    while (true) {
       
        if (grid[row][col] == 0) {
            //setare punct de start
            camera->Set(glm::vec3(2 * row - 20 + 1, 1, 2 * col - 20 + 1), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
            player_col.position.x = camera->GetTargetPosition().x - 0.6;
            player_col.position.y = camera->GetTargetPosition().y;
            player_col.position.z = camera->GetTargetPosition().z - 0.6;

            ok = true;
            for (int i = 0; i < obstacole.size(); i++) {
                if (Collision(player_col, obstacole[i])) {
                    ok = false;
                }
            }
        }
        if (ok == true) {
            break;
        }
        col++;
    }
     
    bool fnl = false;
    while (fnl == false) {
        if (grid[end_row][end_col] != 1) {
            fnl = true;
        }
        end_col++;
    }

    //coordonata punctului de finish
    end_coliziune = coliziune(glm::vec3(2 * end_row - 20, 0, 2 * end_col - 20), glm::vec3(2, 2, 2));
    

}
void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
    

}


void Tema2::Labirint() {

}



void Tema2::Update(float deltaTimeSeconds)
{
    float angular = atan2(camera->forward.x, camera->forward.z);
    time_total -= deltaTimeSeconds;
    offsetX += flagX * deltaTimeSeconds;
    if (offsetX >= 0.75) {
        flagX = -1;
    }
    if (offsetX <= 0.5) {
        flagX = 1;
    }
    offsetZ += flagZ * deltaTimeSeconds;
    if (offsetZ >= 1) {
        flagZ = -1;
    }
    if (offsetZ <= 0) {
        flagZ = 1;
    }
    glm::mat4 modelMatrix = glm::mat4(1);

    //randare inamici si miscarea lor
    for (int i = 0; i < inamici.size(); i++) {
        modelMatrix = glm::mat4(1);

        modelMatrix = glm::translate(modelMatrix, glm::vec3( inamici[i].inamic.position.x + offsetX, inamici[i].inamic.position.y,  inamici[i].inamic.position.z + offsetZ));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 1));

        RenderMesh(meshes["inamic"], shaders["VertexColor"], modelMatrix);
    }

    //randare peretii labirintului
    for (int i = 0; i < obstacole.size(); i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3( obstacole[i].position.x, obstacole[i].position.y,  obstacole[i].position.z));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(4, 2, 4));

        RenderMesh(meshes["cube"], shaders["VertexColor"], modelMatrix);
    }

    //randare punct de start
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(2 * row - 20 + 2, -2.0f, 2 * col - 20));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(4, 2, 4));
    RenderMesh(meshes["start"], shaders["VertexColor"], modelMatrix);

    //randare punct de final
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(2 * end_row - 20, -1, 2 * end_col - 20));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(4, 2, 4));
    RenderMesh(meshes["end"], shaders["VertexColor"], modelMatrix);

    //randare glont
    for (int i = 0; i < 5; i++) {
        if (gloante[i].click == 1) {
            gloante[i].position += glm::normalize(gloante[i].forward) * deltaTimeSeconds * 13.0f;
            gloante[i].col.position += glm::normalize(gloante[i].forward) * deltaTimeSeconds * 13.0f;
            modelMatrix = glm::mat3(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(gloante[i].position));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 1));
            RenderMesh(meshes["glont"], shaders["VertexColor"], modelMatrix);
        }
    }

    for (int i = 0; i < gloante.size(); i++) {
        //glont-perete
        for (int j = 0; j < obstacole.size(); j++) {
            if (gloante[i].click == 1 && Collision(gloante[i].col, obstacole[j])) {
                gloante[i].click = 0;
            }
        }

        //glont-inamic
        for (int k = 0; k < inamici.size(); k++) {
            coliziune inamicOffset = inamici[k].inamic;
            inamicOffset.position.x += offsetX;
            inamicOffset.position.z += offsetZ;
            if (gloante[i].click == 1 && Collision(gloante[i].col, inamicOffset)) {
                inamici.erase(inamici.begin() + k);
                gloante[i].click = 0;
                
                break;
            }
        }
    }
  
    // Render the camera target. This is useful for understanding where
    // the rotation point is, when moving in third-person camera mode.
    if (renderCameraTarget)
    {

        //foot 1
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition()));
        modelMatrix = glm::rotate(modelMatrix, angular, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0) - glm::vec3(0.2875f, 1.8f , 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 1.5f, 0.5f));
       
        RenderMesh(meshes["foot"], shaders["VertexColor"], modelMatrix);

        //foot2
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition()));
        modelMatrix = glm::rotate(modelMatrix, angular, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.4, 0, 0) - glm::vec3(0.2875f, 1.8f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 1.5f, 0.5f));
        RenderMesh(meshes["foot"], shaders["VertexColor"], modelMatrix);

        //body
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition()));
        modelMatrix = glm::rotate(modelMatrix, angular, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.75f, 0) - glm::vec3(0.2875f, 1.8f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1.3f, 1.5f, 0.5f));
        RenderMesh(meshes["body"], shaders["VertexColor"], modelMatrix);

        //hand 1
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition()));
        modelMatrix = glm::rotate(modelMatrix, angular, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.25, 1.0f, 0) - glm::vec3(0.2875f, 1.8f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 1.0f, 0.5f));
        RenderMesh(meshes["body"], shaders["VertexColor"], modelMatrix);

        //hand 2
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition()));
        modelMatrix = glm::rotate(modelMatrix, angular, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.65f, 1.0f, 0) - glm::vec3(0.2875f, 1.8f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 1.0f, 0.5f));
        RenderMesh(meshes["body"], shaders["VertexColor"], modelMatrix);

        //skin hand 1
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition()));
        modelMatrix = glm::rotate(modelMatrix, angular, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.25f, 0.75f, 0) - glm::vec3(0.2875f, 1.8f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
        RenderMesh(meshes["skin"], shaders["VertexColor"], modelMatrix);

        //skin hand 2
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition()));
        modelMatrix = glm::rotate(modelMatrix, angular, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.65f, 0.75f, 0) - glm::vec3(0.2875f, 1.8f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
        RenderMesh(meshes["skin"], shaders["VertexColor"], modelMatrix);

        //head
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition()));
        modelMatrix = glm::rotate(modelMatrix, angular, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.2f, 1.5f, 0) - glm::vec3(0.2875f, 1.8f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
        RenderMesh(meshes["skin"], shaders["VertexColor"], modelMatrix);

        //time
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition()));
        modelMatrix = glm::rotate(modelMatrix, angular, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.2f, 1.9f, 0) - glm::vec3(0.5f, 1.8f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1.5f*time_total / 100, 0.2f, 0.1f));
        RenderMesh(meshes["time"], shaders["VertexColor"], modelMatrix);

        //life
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition()));
        modelMatrix = glm::rotate(modelMatrix, angular, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.2f, 2.0f, 0) - glm::vec3(0.5f, 1.8f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1.5f * life / 20, 0.2f, 0.1f));
        RenderMesh(meshes["inamic"], shaders["VertexColor"], modelMatrix);
       
        if (life <= 0) {
            cout << "Ai ramas fara viata! \n Game over!!!!" << endl;
            exit(0);
        }
        
        if (time_total <= 0) {
            cout << "Ai ramas fara timp! \n Game over!!!!" << endl;
            exit(0);
         }
        
    }
}

void Tema2::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{

  
    // move the camera only if MOUSE_RIGHT button is pressed
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 4.0f;
        *poz = *camera;

        if (window->KeyHold(GLFW_KEY_W)) {
            //Translate the camera forward
            camera->MoveForward(deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            // Translate the camera to the left
            camera->TranslateRight(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            // ): Translate the camera backward
            camera->MoveForward(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            // : Translate the camera to the right
            camera->TranslateRight(deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            //  Translate the camera downward
            camera->TranslateUpward(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_E)) {
            // Translate the camera upward
            camera->TranslateUpward(deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_O)) {
             inaltime = 5;
             latime = inaltime * window->props.aspectRatio;
            projectionMatrix = glm::ortho(-latime / 2, latime / 2, -inaltime / 2, inaltime / 2, 0.0f, 200.0f);
        }

        if (window->KeyHold(GLFW_KEY_P)) {
            
            projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
        }

        // inversare FOV
        if (window->KeyHold(GLFW_KEY_1)) {
            fov += deltaTime;
            projectionMatrix = glm::perspective(fov, window->props.aspectRatio, 0.01f, 200.0f);
        }
        // FOV normal
        if (window->KeyHold(GLFW_KEY_2))
        {
            fov -= deltaTime;
            projectionMatrix = glm::perspective(fov, window->props.aspectRatio, 0.01f, 200.0f);
        }

        if (window->KeyHold(GLFW_KEY_Z)) {
            inaltime += deltaTime;
             latime = inaltime * window->props.aspectRatio;
            projectionMatrix = glm::ortho(-latime / 2, latime / 2, -inaltime / 2, inaltime / 2, 0.0f, 200.0f);
        }

        if (window->KeyHold(GLFW_KEY_X)) {
             inaltime -= deltaTime;
             latime = inaltime * window->props.aspectRatio;
            projectionMatrix = glm::ortho(-latime / 2, latime / 2, -inaltime / 2, inaltime / 2, 0.0f, 200.0f);
        }
        //pozitia playerului schimbata
        player_col.position.x = camera->GetTargetPosition().x - 0.6;
        player_col.position.y = camera->GetTargetPosition().y;
        player_col.position.z = camera->GetTargetPosition().z - 0.6;

        //player-obastacole
        for (int i = 0; i < obstacole.size(); i++) {
            //daca este coliziune in perete se va reveni la vechea pozitie
            if (Collision(player_col, obstacole[i])) {
                *camera = *poz;
                break;
            }
        }
        // player-inamic
        for (int i = 0; i < inamici.size(); i++) {
            coliziune inamicOffset = inamici[i].inamic;
            inamicOffset.position.x += offsetX;
            inamicOffset.position.z += offsetZ;
            if (Collision(player_col, inamicOffset)) {
                //eliminare inamic
                inamici.erase(inamici.begin() + i);
                //scadere viata
                life -= 3;
                break;
            }
        }

        if (Collision(player_col, end_coliziune)) {
            cout << "Felicitari!!\n Game over!!!" << endl;
            exit(0);
        }
      
    }

}

    // TODO(student): Change projection parameters. Declare any extra
    // variables you might need in the class header. Inspect this file
    // for any hardcoded projection arguments (can you find any?) and
    // replace them with those extra variables.
   


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }
    // TODO(student): Switch projections

}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            
            // TODO(student): Rotate the camera in first-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateThirdPerson_OX(-sensivityOX * deltaY);
            camera->RotateThirdPerson_OY(-sensivityOY * deltaX);
            renderCameraTarget = true;
        }

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
           
            // TODO(student): Rotate the camera in third-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            

            camera->RotateFirstPerson_OX(-sensivityOX * deltaY);
            camera->RotateFirstPerson_OY(-sensivityOY * deltaX);
            renderCameraTarget = false;
        }
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && renderCameraTarget == false) {
        if (nr_glont < 5) {
            gloante[nr_glont].click = 1;
            gloante[nr_glont].position = camera->GetTargetPosition();
            gloante[nr_glont].forward = camera->forward;
            gloante[nr_glont].angular = angularStep;
            gloante[nr_glont].col.position = gloante[nr_glont].position;
            gloante[nr_glont].col.dimension = glm::vec3(0.5, 0.5, 0.5);
            

            nr_glont++;
        }
        else {
            nr_glont = 0;
        }
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}

bool Tema2::Collision(coliziune a, coliziune b) {

    return (a.position.x <= (b.position.x + b.dimension.x) && (a.position.x + a.dimension.x) >= b.position.x &&
        a.position.y <= (b.position.y + b.dimension.y) && (a.position.y + a.dimension.y) >= b.position.y
        && a.position.z <= (b.position.z + b.dimension.z) && (a.dimension.z + a.position.z) >= b.position.z);
}