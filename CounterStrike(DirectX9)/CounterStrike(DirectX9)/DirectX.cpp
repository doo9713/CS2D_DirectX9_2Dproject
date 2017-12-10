#include "DirectX.h"
#include "FileIO.h"
#include "Constant.h"

UTILITY::CDirectX UTILITY::DRX;
UTILITY::CTextureList UTILITY::TEXTURE;
UTILITY::CFont UTILITY::FONT;
UTILITY::CShader UTILITY::SHADER;

// 쉐이더를 사용해서 그리기
void UTILITY::CDirectX::Draw(LPD3DXEFFECT Shader, MATRIX& World, const char* Key, UINT Cnt)
{
	auto Texture = TEXTURE.GetImage(Key, Cnt);
	if (Texture == nullptr)
		return;
	MATRIX Final, View, Proj;
	Final.Scale(Texture->Scale);
	pDevice->GetTransform(D3DTS_VIEW, &View);
	pDevice->GetTransform(D3DTS_PROJECTION, &Proj);
	Final = Final * World * View * Proj;
	Shader->SetMatrix("WVP", &Final);
	Shader->SetTexture("Image", Texture->Tex);

	UINT PassCnt;
	Shader->Begin(&PassCnt, 0);
	for (UINT i = 0; i < PassCnt; ++i)
	{
		Shader->BeginPass(i);
		pDevice->SetStreamSource(0, VB, 0, sizeof(Vertex));
		pDevice->SetFVF(Vertex::FVF);
		pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
		Shader->EndPass();
	}
	Shader->End();
	pDevice->SetVertexShader(nullptr);
	pDevice->SetPixelShader(nullptr);
}

// 그리기
void UTILITY::CDirectX::Draw(MATRIX& World, const char* Key, UINT Cnt)
{
	auto Texture = TEXTURE.GetImage(Key, Cnt);
	if (Texture == nullptr)
		return;
	pDevice->SetTexture(0, Texture->Tex);
	MATRIX Final;
	Final.Scale(Texture->Scale);
	Final = Final * World;
	pDevice->SetTransform(D3DTS_WORLD, &Final);
	pDevice->SetStreamSource(0, VB, 0, sizeof(Vertex));
	pDevice->SetFVF(Vertex::FVF);
	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}

// 다이렉트X 초기화
void UTILITY::CDirectX::Init(HWND Window, BOOL Full)
{
	p3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DCAPS9 caps;
	ZeroMemory(&caps, sizeof(caps));
	p3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	DWORD Flag = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		Flag = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		Flag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	D3DPRESENT_PARAMETERS param;
	ZeroMemory(&param, sizeof(param));
	param.BackBufferCount = 1;
	param.BackBufferFormat = D3DFMT_A8R8G8B8;
	param.BackBufferWidth = ScreenWidth;
	param.BackBufferHeight = ScreenHeight;

	param.AutoDepthStencilFormat = D3DFMT_D24S8;
	param.EnableAutoDepthStencil = true;

	param.hDeviceWindow = Window;
	param.Windowed = !Full;

	param.SwapEffect = D3DSWAPEFFECT_DISCARD;
	param.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	param.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	p3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window, Flag, &param, &pDevice);

	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	pDevice->CreateVertexBuffer(sizeof(Vertex) * 6, 0, Vertex::FVF, D3DPOOL_MANAGED, &VB, nullptr);

	Vertex Data[6] =
	{
		{ { -0.5, 0.5, 0 },{ 0,0 } },
		{ { 0.5, 0.5, 0 },{ 1,0 } },
		{ { 0.5,-0.5, 0 },{ 1,1 } },
		{ { -0.5, 0.5, 0 },{ 0,0 } },
		{ { 0.5,-0.5, 0 },{ 1,1 } },
		{ { -0.5,-0.5, 0 },{ 0,1 } }
	};
	Vertex* ptr;
	VB->Lock(0, sizeof(Vertex) * 6, (void**)&ptr, 0);
	memcpy(ptr, Data, sizeof(Vertex) * 6);
	VB->Unlock();
}

// 파일에서 텍스쳐 읽어오기(기본 확장자 : png)
void UTILITY::CTexture::LoadFromFile(const char* Path, const char* Elimit)
{
	FileFinder FF(Path, Elimit);
	FF.Find(false,
		[this](const std::string& _path,
			const std::string& _elimit,
			const std::string& _name,
			UINT _attribute)
	{
		std::string FullPath = _path + "/" + _name + "." + _elimit;
		D3DXIMAGE_INFO Info;
		D3DXGetImageInfoFromFileA(FullPath.data(), &Info);
		Image* ptr = new Image;
		ptr->Scale = VECTOR3(Info.Width, Info.Height);
		D3DXCreateTextureFromFileA(DRX, FullPath.data(), &ptr->Tex);
		ImageList.emplace_back(ptr);
	});
}

// 이미지 로드(기본 확장자 : png)
void UTILITY::CTextureList::Load(const char* Key, const char* Path, const char* Elimit)
{
	auto finder_name = Texture.find(Key);
	if (finder_name != Texture.end())
		return;
	CTexture* tex = new CTexture;
	tex->LoadFromFile(Path, Elimit);
	Texture.insert(std::make_pair(Key, tex));
}

void UTILITY::CTextureList::Clear()
{
	for (auto tex = Texture.begin(); tex != Texture.end(); ++tex)
	{
		delete tex->second;
		tex->second = nullptr;
	}
	Texture.clear();
}

// 이미지 가져오기
UTILITY::CTexture::Image* UTILITY::CTextureList::GetImage(const char* Key, UINT Cnt)
{
	auto finder_name = Texture.find(Key);
	if (finder_name == Texture.end())
		return nullptr;
	return (*finder_name->second)[Cnt];
}

// 폰트 로드
void UTILITY::CFont::FontLoad(const char* Key, int Number, const char* Path)
{
	auto finder_name = FontList.find(Key);
	if (finder_name != FontList.end())
		return;
	FontData* FD = new FontData;
	FD->TextNumber = Number;
	auto Size = TEXTURE.GetImage("Text", Number)->Scale;
	FD->SizeX = Size.x;
	FD->SizeY = Size.y;

	FILE* fp = fopen(Path, "rt");

	FontValue* FV = new FontValue;
	char Data;

	while (fscanf(fp, "%c %d %d %d %d\n", &Data, &FV->Left, &FV->Top, &FV->Right, &FV->Bottom) > 0)
	{
		FD->CharList.insert(std::make_pair(Data, FV));
		FV = new FontValue;
	}
	delete FV;

	fclose(fp);

	FontList.insert(std::make_pair(Key, FD));
}

// 폰트 그리기
void UTILITY::CFont::Draw(const char* Data, const char* Key, const VECTOR3& Pos)
{
	auto font = FontList.find(Key);
	if (font == FontList.end())
		return;
	int Jump = 0;
	CDirectX::Vertex* PTR;
	MATRIX Final, Trans, Scale, CharScale;

	auto Tex = TEXTURE.GetImage("Text", font->second->TextNumber)->Tex;
	DRX->SetTexture(0, Tex);
	CharScale.Scale(WordScale);

	MATRIX Rot;
	Rot.Rotation(WordAngle);

	float JumpY = 0;
	while (*Data != '\0')
	{
		auto CharData = font->second->CharList.find(*Data);
		if (CharData == font->second->CharList.end())
		{
			Jump += (WordSpace)* WordScale.x;
			++Data;
			continue;
		}
		VB->Lock(0, sizeof(CDirectX::Vertex) * 6, (void**)&PTR, 0);

		PTR[0].UV = D3DXVECTOR2(CharData->second->Left / (float)font->second->SizeX, CharData->second->Top / (float)font->second->SizeY);
		PTR[1].UV = D3DXVECTOR2(CharData->second->Right / (float)font->second->SizeX, CharData->second->Top / (float)font->second->SizeY);
		PTR[2].UV = D3DXVECTOR2(CharData->second->Right / (float)font->second->SizeX, CharData->second->Bottom / (float)font->second->SizeY);
		PTR[3].UV = D3DXVECTOR2(CharData->second->Left / (float)font->second->SizeX, CharData->second->Top / (float)font->second->SizeY);
		PTR[4].UV = D3DXVECTOR2(CharData->second->Right / (float)font->second->SizeX, CharData->second->Bottom / (float)font->second->SizeY);
		PTR[5].UV = D3DXVECTOR2(CharData->second->Left / (float)font->second->SizeX, CharData->second->Bottom / (float)font->second->SizeY);

		VB->Unlock();

		Final = CharScale * Scale.Scale
			(CharData->second->Right - CharData->second->Left,
			CharData->second->Bottom - CharData->second->Top) *
			Trans.Move(Pos.x + Jump, Pos.y + JumpY, Pos.z) *
			Rot;
		Jump += (CharData->second->Right - CharData->second->Left) * WordScale.x;
		Jump -= WordJump * WordScale.x;
		if (WordLine != 0)
		{
			if (Jump >= WordLine)
			{
				Jump = 0;
				JumpY -= (CharData->second->Bottom - CharData->second->Top) * WordScale.y;
				JumpY += LineJump * WordScale.y;
			}
		}
		DRX->SetTransform(D3DTS_WORLD, &Final);
		DRX->SetStreamSource(0, VB, 0, sizeof(CDirectX::Vertex));
		DRX->SetFVF(CDirectX::Vertex::FVF);
		DRX->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

		++Data;
	}
}

// 쉐이더 로드
void UTILITY::CShader::OnLoad(const char* Key, const char* Path)
{
	auto finder_name = EffList.find(Key);
	if (finder_name != EffList.end())
		return;
	auto Eff = new CEffect;
	Eff->OnLoad(Path);
	EffList.insert(std::make_pair(Key, Eff));
}

// 이펙트 가져오기
LPD3DXEFFECT UTILITY::CShader::GetEffect(const char* Key)
{
	auto finder_name = EffList.find(Key);
	if (finder_name == EffList.end())
		return nullptr;
	return finder_name->second->GetEffect();
}