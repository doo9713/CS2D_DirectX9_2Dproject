#pragma once

#include "MathF.h"

namespace UTILITY
{
	struct CDirectX
	{
	public :
		struct Vertex
		{
			VECTOR3 Pos;
			D3DXVECTOR2 UV;
			enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
		};
	private :
		LPDIRECT3D9 p3D;
		LPDIRECT3DDEVICE9 pDevice;
		LPDIRECT3DVERTEXBUFFER9 VB;
	public :
		// 카메라 이동
		void Camera(float x = 0, float y = 0)
		{
			MATRIX mat;
			pDevice->SetTransform(D3DTS_VIEW, &mat.Move(-x, -y));
		}
		// 벡터를 사용한 카메라 이동
		void Camera(const VECTOR3& Pos)
		{
			Camera(Pos.x, Pos.y);
		}
	public :
		operator LPDIRECT3DDEVICE9() { return pDevice; }
		LPDIRECT3DDEVICE9 operator ->() { return pDevice; }
	public :
		void Draw(LPD3DXEFFECT Shader, MATRIX& World, const char* Key, UINT Cnt = 0);
		void Draw(MATRIX& World, const char* Key, UINT Cnt = 0);
		void Init(HWND Window, BOOL Full = false);
		void Begin()
		{
			pDevice->Clear(0, nullptr,
				D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
				D3DCOLOR_ARGB(255, 255, 255, 0),
				1.0f, 0);
			pDevice->BeginScene();
		}
		void End(HWND hWnd = nullptr)
		{
			pDevice->EndScene();
			pDevice->Present(nullptr, nullptr, hWnd, nullptr);
		}
	public :
		~CDirectX()
		{
			if(VB) VB->Release();
			if(pDevice) pDevice->Release();
			if(p3D) p3D->Release();
		}
	};

	extern CDirectX DRX;

	struct CTexture
	{
	public:
		struct Image
		{
			LPDIRECT3DTEXTURE9 Tex;
			VECTOR3 Scale;
		};
	private:
		std::vector<Image*> ImageList;
	public:
		Image* operator[](int index)
		{
			return ImageList[index];
		}
		void LoadFromFile(const char* Path, const char* Elimit = "png");
	public:
		~CTexture()
		{
			for (auto img : ImageList)
			{
				img->Tex->Release();
				delete img;
			}
			ImageList.clear();
		}
	};

	struct CTextureList
	{
	private :
		std::map<std::string, CTexture*> Texture;
	public :
		void Load(const char* Key, const char* Path, const char* Elimit = "png");
		CTexture::Image* GetImage(const char* Key, UINT Cnt = 0);
		~CTextureList()
		{
			for (auto tex : Texture)
				delete tex.second;
			Texture.clear();
		}
	};

	extern CTextureList TEXTURE;

	struct CFont
	{
	private :
		struct FontValue
		{
			int Left;
			int Top;
			int Right;
			int Bottom;
		};
		struct FontData
		{
			int TextNumber;
			int SizeX;
			int SizeY;
			std::map<char, FontValue*> CharList;
			~FontData()
			{
				for (auto data : CharList)
					delete data.second;
				CharList.clear();
			}
		};
		std::map<std::string, FontData*> FontList;
		LPDIRECT3DVERTEXBUFFER9 VB;
	public :
		float WordSpace;
		float WordJump;
		float WordAngle;
		float WordLine;
		float LineJump;
		VECTOR3 WordScale;
	public :
		void FontLoad(const char* Key, int Number, const char* Path);
		void Draw(const char* Data, const char* Key, const VECTOR3& Pos);
		void Init()
		{
			WordSpace = 20;
			WordJump = 0;
			WordAngle = 0;
			WordLine = 0;
			LineJump = 0;
			WordScale = VECTOR3(1, 1);

			DRX->CreateVertexBuffer(sizeof(CDirectX::Vertex) * 6, 0, CDirectX::Vertex::FVF, D3DPOOL_MANAGED, &VB, nullptr);
			CDirectX::Vertex* PTR;
			VB->Lock(0, sizeof(CDirectX::Vertex) * 6, (void**)&PTR, 0);
			PTR[0].Pos = VECTOR3(-0.5, 0.5);
			PTR[1].Pos = VECTOR3(0.5, 0.5);
			PTR[2].Pos = VECTOR3(0.5, -0.5);
			PTR[3].Pos = VECTOR3(-0.5, 0.5);
			PTR[4].Pos = VECTOR3(0.5, -0.5);
			PTR[5].Pos = VECTOR3(-0.5, -0.5);
			VB->Unlock();
		}
		CFont()
			: WordSpace(20), WordJump(0), WordAngle(0), WordLine(0), LineJump(0), WordScale(1, 1)
		{}
		~CFont()
		{
			if(VB) VB->Release();
			for (auto data : FontList)
				delete data.second;
			FontList.clear();
		}
	};

	extern CFont FONT;

	struct CShader
	{
	private :
		struct CEffect
		{
		private :
			LPD3DXEFFECT Eff;
		public :
			LPD3DXEFFECT GetEffect() { return Eff; }
			void OnLoad(const char* Path)
			{
				D3DXCreateEffectFromFileA(DRX, Path, nullptr, nullptr, D3DXSHADER_DEBUG, nullptr, &Eff, nullptr);
			}
			~CEffect() { Eff->Release(); }
		};
		std::map<std::string, CEffect*> EffList;
	public :
		void OnLoad(const char* Key, const char* Path);
		LPD3DXEFFECT GetEffect(const char* Key);
		~CShader()
		{
			for (auto eff : EffList)
				delete eff.second;
			EffList.clear();
		}
	};

	extern CShader SHADER;
}