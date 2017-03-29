/*
* PROJECT		: SETTrek
* FILE			: ModelClass.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/01/25
* DESCRIPTION	: The header file containing the class definition for the ModelClass class.
* CREDIT        : http://www.rastertek.com/dx11s2tut04.html
*/
#pragma once
#include <d3d11.h>
#include <directxmath.h>
using namespace DirectX;




//=============================
// ModelClass CONSTANTS
//=============================



//=============================
// ModelClass CLASS DEFINITION
//=============================
class ModelClass
{
private:

    struct VertexType
    {
        XMFLOAT3 position;
        XMFLOAT4 color;
    };

    ID3D11Buffer*   _vertexBuffer; 
    ID3D11Buffer*   _indexBuffer;
    int _vertexCount;
    int _indexCount;

    bool InitializeBuffers(ID3D11Device* device);
    void RenderBuffers(ID3D11DeviceContext* deviceContext);


public:

    ModelClass();
    ~ModelClass();

    bool Initialize(ID3D11Device* device);
    void Render(ID3D11DeviceContext* deviceContext);

    int GetIndexCount(void);
};