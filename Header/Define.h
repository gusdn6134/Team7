#pragma once

extern HWND		g_hWnd;

#define		WINCX		800
#define		WINCY		600

#define		OBJ_NOEVENT		0
#define		OBJ_DEAD		1

#define		VK_MAX			0xff

#define		TILECX			30
#define		TILECY			30

#define		TILEX			20
#define		TILEY			30

#define		MIN_STR			64
#define		MAX_STR			256

#define		RUBY			0x01		// -> 0001
#define		DIAMOND			0x02		// -> 0010
#define		SAPPHIRE		0x04		// -> 0100

#define GET_TOOLVIEW									                              \
CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();								  \
CToolView* pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 0));  \

#define GET_ScrollView																		   \
CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();										   \
CScrollView* pScrollView = dynamic_cast<CScrollView*>(pMainFrm->m_MainSplitter.GetPane(0, 0)); \

#define GET_MyFoem																	  \
CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();								  \
CMyForm* pMyForm = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));  \




#define ERR_MSG(message)								\
::MessageBox(nullptr, message, L"error", MB_OK)

#define NO_COPY(ClassName)								\
ClassName(const ClassName&) = delete;					\
ClassName& operator=(const ClassName&) = delete;

#define DECLARE_SINGLETON(ClassName)					\
		NO_COPY(ClassName)								\
public :												\
	static ClassName* Get_Instance();					\
	static void		  Destroy_Instance();				\
private:												\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)					\
ClassName* ClassName::m_pInstance = nullptr;			\
ClassName* ClassName::Get_Instance()					\
{														\
	if (nullptr == m_pInstance)							\
		m_pInstance = new ClassName;					\
	return m_pInstance;									\
}														\
void ClassName::Destroy_Instance()						\
{														\
	if(nullptr != m_pInstance)							\
	{													\
		delete m_pInstance;								\
		m_pInstance = nullptr;							\
	}													\
}

#define INSERT_TEXTURE(path, type, category, name, count) \
    if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(path, type, category, name, count))) { \
        AfxMessageBox(L"Terrain Texture Insert Failed"); \
        return E_FAIL; \
    }


// 선언과 동시에 초기화 불가능, 먼저 선언된 전역변수와 자료형, 변수명까지 일치하는 상태에서만 사용 가능