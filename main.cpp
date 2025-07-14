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

  Vector3 position = (Vector3){0, 3, 0};

  Model mesh = LoadModelFromMesh(GenMeshCustom());

  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    BeginMode3D(camera);

    UpdateCamera(&camera, CAMERA_ORBITAL);

    // DrawCube(position, 5, 5, 5, BLUE);
    DrawModel(mesh, position, 1.0f, RED);
    DrawCubeWires(position, 5, 5, 5, BLACK);

    DrawGrid(10, 1.0);
    DrawCustomGrid(10, 1.0, WHITE); 

    EndMode3D();

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
