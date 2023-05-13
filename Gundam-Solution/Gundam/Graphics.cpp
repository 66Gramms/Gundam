#include "Graphics.h"
#include "Model.h"
#include "Material.h"
#include "CubeMaterial.h"
#include "Camera.h"
#include <cmath>
#include <d3dcompiler.h>
#include <DirectXMath.h>

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

#pragma comment(lib, "D3DCompiler.lib")

Graphics::Graphics(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	// Create device and front/back buffers and swap chain and rendering context
	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		nullptr,
		&pContext
	);

	wrl::ComPtr<ID3D11Resource> pBackBuffer = nullptr;
	pSwap->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget);

	// Create depth stencil state
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	wrl::ComPtr<ID3D11DepthStencilState> pDSState;
	pDevice->CreateDepthStencilState(&dsDesc, &pDSState);

	// Bind depth state
	pContext->OMSetDepthStencilState(pDSState.Get(), 1);

	// Create depth stencil texture
	wrl::ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};

#if FULLSCREEN
	descDepth.Width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	descDepth.Height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
#else
	descDepth.Width = 800;
	descDepth.Height = 600;
#endif
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	pDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil);

	// Create view of depth stencil texture
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	pDevice->CreateDepthStencilView(pDepthStencil.Get(), &descDSV, &pDSV);

	// Bind depth stencil view to OM
	pContext->OMSetRenderTargets(1, pTarget.GetAddressOf(), pDSV.Get());

	// Configure viewport
	D3D11_VIEWPORT vp;
#if FULLSCREEN
	vp.Width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	vp.Height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
#else
	vp.Width = 800;
	vp.Height = 600;
#endif
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pContext->RSSetViewports(1, &vp);

	// Set primitive topology to triangle list (groups of 3 vertices)
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Graphics::EndFrame()
{
	pSwap->Present(1u, 0u);
}

void Graphics::ClearBuffer(float red, float green, float blue) noexcept
{
	const float color[] = { red, green, blue, 1.0f };
	pContext->ClearRenderTargetView(pTarget.Get(), color);
	pContext->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Graphics::DrawModel(Model* model, Camera* camera, float angleY, float angleX, float x, float y, float z)
{
	namespace wrl = Microsoft::WRL;

	// Bind vertex buffer
	const UINT stride = sizeof(Model::Vertex);
	const UINT offset = 0;
	pContext->IASetVertexBuffers(0, 1, model->mesh.pVertexBuffer.GetAddressOf(), &stride, &offset);

	// Bind index buffer
	pContext->IASetIndexBuffer(model->mesh.pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

	// Bind pixel shader
	pContext->PSSetShader(model->material->pPixelShader.Get(), nullptr, 0);

	// Bind vertex shader
	pContext->VSSetShader(model->material->pVertexShader.Get(), nullptr, 0);

	// Bind constant vector buffer
	pContext->VSSetConstantBuffers(0, 1, model->GetConstantBuffer().GetAddressOf());

	model->cb.world = DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationY(angleY) * DirectX::XMMatrixRotationX(angleX) * DirectX::XMMatrixTranslation(x, y, z));
	model->cb.view = DirectX::XMMatrixTranspose(camera->GetViewMatrix());
	model->cb.projection = DirectX::XMMatrixTranspose(camera->GetProjectionMatrix());

	model->CreateConstantBuffer(*pDevice.GetAddressOf());

	// Bind constant pixel buffer
	pContext->PSSetConstantBuffers(0, 1, model->material->pColorCB.GetAddressOf());

	CubeMaterial* cubeMaterial = dynamic_cast<CubeMaterial*>(model->material);
	if (cubeMaterial)
	{
		pContext->PSSetShaderResources(0, 1, cubeMaterial->CubesTexture.GetAddressOf());
		pContext->PSSetSamplers(0, 1, cubeMaterial->CubesTexSamplerState.GetAddressOf());
	}

	// Bind input layout
	pContext->IASetInputLayout(model->material->pInputLayout.Get());

	pContext->DrawIndexed((UINT)model->mesh.IndexCount, 0, 0);
}