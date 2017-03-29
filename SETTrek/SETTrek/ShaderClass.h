/*
* PROJECT		: SETTrek
* FILE			: ShaderClass.h
* PROGRAMMER	: Austin Che
* DATE			: 2017/01/25
* DESCRIPTION	: The header file containing the class definition for the Direct3D class.
* CREDIT        : http://www.rastertek.com/dx11s2tut04.html
*/
#pragma once
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <fstream>

using namespace DirectX;
using namespace std;


//=============================
// ShaderClass CONSTANTS
//=============================




//=============================
// ShaderClass CLASS DEFINITION
//=============================
class ShaderClass
{
private:

    struct MatrixBufferType
    {
        XMMATRIX world;
        XMMATRIX view;
        XMMATRIX projection;
    };

    ID3D11VertexShader*         _vertexShader;
    ID3D11PixelShader*          _pixelShader;
    ID3D11InputLayout*          _layout;
    ID3D11Buffer*               _matrixBuffer;

    bool InitializeShader(ID3D11Device* device, HWND hwnd, LPCWSTR vsFile, LPCWSTR psFile);
    void OutputShaderErrorMessage(ID3D10Blob* error, HWND hwnd, LPCWSTR shaderFileName);

    bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX);
    void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

public:

    /*-Constructors-*/
    //------------------
    ShaderClass();

    /*-Deconstructors-*/
    //------------------
    ~ShaderClass();


    /*-General Methods-*/
    //------------------
    bool Init(ID3D11Device* d3device, HWND windowHandle);
    bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX);
};