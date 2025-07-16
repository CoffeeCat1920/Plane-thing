#include "./include/raylib.h"

void DrawCustomGrid(int slices, float spacing, Color color)
{
  float half = (slices * spacing) / 2.0f;

  for (int i = 0; i <= slices; i++)
  {
    float offset = -half + i * spacing;

    // Lines parallel to X-axis
    DrawLine3D(
      (Vector3){ -half, 0.0f, offset },
      (Vector3){  half, 0.0f, offset },
      color
    );

    // Lines parallel to Z-axis
    DrawLine3D(
      (Vector3){ offset, 0.0f, -half },
      (Vector3){ offset, 0.0f,  half },
      color
    );
  }
}

// Generate a simple triangle mesh from code
static Mesh GenMeshCustom(void) {
    Mesh mesh = { 0 };
    mesh.triangleCount = 1;
    mesh.vertexCount = mesh.triangleCount*3;
    mesh.vertices = (float *)MemAlloc(mesh.vertexCount*3*sizeof(float));    // 3 vertices, 3 coordinates each (x, y, z)
    mesh.texcoords = (float *)MemAlloc(mesh.vertexCount*2*sizeof(float));   // 3 vertices, 2 coordinates each (x, y)
    mesh.normals = (float *)MemAlloc(mesh.vertexCount*3*sizeof(float));     // 3 vertices, 3 coordinates each (x, y, z)

    // Vertex at (0, 0, 0)
    mesh.vertices[0] = 0;
    mesh.vertices[1] = 0;
    mesh.vertices[2] = 0;
    mesh.normals[0] = 0;
    mesh.normals[1] = 1;
    mesh.normals[2] = 0;
    mesh.texcoords[0] = 0;
    mesh.texcoords[1] = 0;

    // Vertex at (1, 0, 2)
    mesh.vertices[3] = 1;
    mesh.vertices[4] = 0;
    mesh.vertices[5] = 2;
    mesh.normals[3] = 0;
    mesh.normals[4] = 1;
    mesh.normals[5] = 0;
    mesh.texcoords[2] = 0.5f;
    mesh.texcoords[3] = 1.0f;

    // Vertex at (2, 0, 0)
    mesh.vertices[6] = 2;
    mesh.vertices[7] = 0;
    mesh.vertices[8] = 0;
    mesh.normals[6] = 0;
    mesh.normals[7] = 1;
    mesh.normals[8] = 0;
    mesh.texcoords[4] = 1;
    mesh.texcoords[5] =0;

    // Upload mesh data from CPU (RAM) to GPU (VRAM) memory
    UploadMesh(&mesh, false);

    return mesh;
}


int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 650;

    InitWindow(screenWidth, screenHeight, "Fuselarge thing");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 50.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 position = (Vector3){0, 2.5, 0};

    Model mesh = LoadModelFromMesh(GenMeshCustom());

    // Gruvbox colors
    Color gruvbox_bg = (Color){29, 32, 33, 255};         // bg0
    Color gruvbox_fg = (Color){235, 219, 178, 255};      // fg
    Color gruvbox_grid = (Color){184, 187, 38, 255};     // yellow-greenish
    Color gruvbox_model = (Color){251, 73, 52, 255};     // red
    Color gruvbox_wire = (Color){131, 165, 152, 255};    // blueish

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(gruvbox_bg);

        BeginMode3D(camera);

        UpdateCamera(&camera, CAMERA_ORBITAL);

        // DrawCube(position, 5, 5, 5, gruvbox_wire);
        // DrawCubeWires(position, 5, 5, 5, gruvbox_bg);

        DrawSphereWires(position, 20, 10, 10, gruvbox_fg);
        DrawSphereWires(position, 15, 10, 10, RED);
        DrawSphere(position, 10, gruvbox_wire);


        DrawGrid(10, 1.0f);  // Optional: built-in grid
        DrawCustomGrid(10, 1.0f, gruvbox_grid);  // Gruvbox custom grid

        EndMode3D();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
