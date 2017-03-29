/*
* PROJECT		: SETTrek
* FILE			: ModelClass.cpp
* PROGRAMMER	: Austin Che
* DATE			: 2017/01/25
* DESCRIPTION	: The CPP file containing the implementation for the ModelClass class.
* CREDIT        : http://www.rastertek.com/dx11s2tut04.html
*/
#include "ModelClass.h"



ModelClass::ModelClass()
{
    _vertexBuffer = nullptr;
    _indexBuffer = nullptr;
    _vertexCount = 0;
    _indexCount = 0;
}



ModelClass::~ModelClass()
{
    // Release the index buffer.
    if (_indexBuffer)
        _indexBuffer->Release();

    // Release the vertex buffer.
    if (_vertexBuffer)
        _vertexBuffer->Release();
}



bool ModelClass::Initialize(ID3D11Device* device)
{
    // Initialize the vertex and index buffers.
    bool result = InitializeBuffers(device);
    if (!result)
    {
        return false;
    }

    return true;
}


void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
    // Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
    RenderBuffers(deviceContext);
    return;
}


bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
    VertexType* vertices;
    unsigned long* indices;
    D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
    HRESULT result;


    // Set the number of vertices in the vertex array.
    _vertexCount = 3;

    // Set the number of indices in the index array.
    _indexCount = 3;

    // Create the vertex array.
    vertices = new VertexType[_vertexCount];
    if (!vertices)
    {
        return false;
    }

    // Create the index array.
    indices = new unsigned long[_indexCount];
    if (!indices)
    {
        return false;
    }

    // Load the vertex array with data.
    vertices[0].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left.
    vertices[0].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

    vertices[1].position = XMFLOAT3(0.0f, 1.0f, 0.0f);  // Top middle.
    vertices[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

    vertices[2].position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right.
    vertices[2].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

    // Load the index array with data.
    indices[0] = 0;  // Bottom left.
    indices[1] = 1;  // Top middle.
    indices[2] = 2;  // Bottom right.

                     // Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * _vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;
    vertexData.SysMemPitch = 0;
    vertexData.SysMemSlicePitch = 0;

    // Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &_vertexBuffer);
    if (FAILED(result))
    {
        return false;
    }

    // Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * _indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
    indexBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
    indexData.SysMemPitch = 0;
    indexData.SysMemSlicePitch = 0;

    // Create the index buffer.
    result = device->CreateBuffer(&indexBufferDesc, &indexData, &_indexBuffer);
    if (FAILED(result))
    {
        return false;
    }

    // Release the arrays now that the vertex and index buffers have been created and loaded.
    delete[] vertices;
    vertices = 0;

    delete[] indices;
    indices = 0;

    return true;
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
    unsigned int stride;
    unsigned int offset;


    // Set vertex buffer stride and offset.
    stride = sizeof(VertexType);
    offset = 0;

    // Set the vertex buffer to active in the input assembler so it can be rendered.
    deviceContext->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
    deviceContext->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    return;
}



int ModelClass::GetIndexCount()
{
    return _indexCount;
}