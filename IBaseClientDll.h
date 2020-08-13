#pragma once
#include "CClientClass.h"
#include "CViewSetup.h"


class IBaseClientDll
{
public:
	virtual int						Init(void* appSystemFactory, void* physicsFactory, void* pGlobals) = 0;
	
	virtual void					PostInit() = 0;
	virtual void					Shutdown(void) = 0;

	virtual bool					ReplayInit(void* fnReplayFactory) = 0;
	virtual bool					ReplayPostInit() = 0;

	virtual void					LevelInitPreEntity(const char *pMapName) = 0;
	virtual void					LevelInitPostEntity() = 0;
	virtual void					LevelShutdown(void) = 0;

	virtual ClientClass*			GetAllClasses(void) = 0;

	virtual int						HudVidInit(void) = 0;
	virtual void					HudProcessInput(bool bActive) = 0;
	virtual void					HudUpdate(bool bActive) = 0;
	virtual void					HudReset(void) = 0;
	virtual void					HudText(const char * message) = 0;

	// Mouse Input Interfaces
	virtual void					IN_ActivateMouse(void) = 0;
	virtual void					IN_DeactivateMouse(void) = 0;
	virtual void					IN_Accumulate(void) = 0;
	virtual void					IN_ClearStates(void) = 0;
	virtual bool					IN_IsKeyDown(const char *name, bool& isdown) = 0;
	virtual void					IN_OnMouseWheeled(int nDelta) = 0;
	// Raw signal
	virtual int						IN_KeyEvent(int eventcode, int keynum, const char *pszCurrentBinding) = 0;
	// Create movement command
	virtual void					CreateMove(int sequence_number, float input_sample_frametime, bool active) = 0;
	virtual void					ExtraMouseSample(float frametime, bool active) = 0;
	virtual bool					WriteUsercmdDeltaToBuffer(void* buf, int from, int to, bool isnewcommand) = 0;
	virtual void					EncodeUserCmdToBuffer(void* buf, int slot) = 0;
	virtual void					DecodeUserCmdFromBuffer(void* buf, int slot) = 0;


	virtual void					View_Render(void *rect) = 0;
	virtual void					RenderView(const CViewSetup &view, int nClearFlags, int whatToDraw) = 0;
	virtual void					View_Fade(void *pSF) = 0;

	virtual void					SetCrosshairAngle(const Math::QAngle& angle) = 0;

	virtual void					InitSprite(void *pSprite, const char *loadname);
	virtual void					ShutdownSprite(void *pSprite);

	virtual int						GetSpriteSize(void) const;

	virtual void					VoiceStatus(int entindex, void* bTalking);

	virtual void					InstallStringTableCallback(const char *tableName);

	virtual void					FrameStageNotify(void* curStage);

	virtual bool					DispatchUserMessage(int msg_type, void* &msg_data);

	// Save/restore system hooks
	virtual void  			*SaveInit(int size);
	virtual void			SaveWriteFields(void*, const char *, void *, void*, void*, int);
	virtual void			SaveReadFields(void*, const char *, void *, void*, void*, int);
	virtual void			PreSave(void*);
	virtual void			Save(void*);
	virtual void			WriteSaveHeaders(void*);
	virtual void			ReadRestoreHeaders(void*);
	virtual void			Restore(void*, bool);
	virtual void			DispatchOnRestore();
	virtual void* GetStandardRecvProxies();
	virtual void			WriteSaveGameScreenshot(const char *pFilename);
	// Given a list of "S(wavname) S(wavname2)" tokens, look up the localized text and emit
	//  the appropriate close caption if running with closecaption = 1
	virtual void			EmitSentenceCloseCaption(char const *tokenstream);
	virtual void			EmitCloseCaption(char const *captionname, float duration);
	virtual bool			CanRecordDemo(char *errorMsg, int length) const;

	virtual void			OnDemoRecordStart(char const* pDemoBaseName);
	virtual void			OnDemoRecordStop();
	virtual void			OnDemoPlaybackStart(char const* pDemoBaseName);
	virtual void			OnDemoPlaybackStop();

	virtual bool			ShouldDrawDropdownConsole();

	// Get client screen dimensions
	virtual int				GetScreenWidth();
	virtual int				GetScreenHeight();

	// save game screenshot writing
	virtual void			WriteSaveGameScreenshotOfSize(const char *pFilename, int width, int height, bool bCreatePowerOf2Padded/*=false*/, bool bWriteVTF/*=false*/);

	// Gets the location of the player viewpoint
	virtual bool			GetPlayerView(CViewSetup &playerView);

	// Matchmaking
	virtual void			SetupGameProperties(void* contexts, void* properties);
	virtual int			    GetPresenceID(const char *pIDName);
	virtual const char*		GetPropertyIdString(const UINT id);
	virtual void			GetPropertyDisplayString(UINT id, UINT value, char *pOutput, int nBytes);
	virtual void			InvalidateMdlCache();
	virtual void			IN_SetSampleTime(float frametime);
	virtual void			ReloadFilesInList(void*pFilesToReload);
	virtual void			StartStatsReporting(HANDLE handle, bool bArbitrated);
	// Let the client handle UI toggle - if this function returns false, the UI will toggle, otherwise it will not.
	virtual bool			HandleUiToggle();

	// Allow the console to be shown?
	virtual bool			ShouldAllowConsole();
	// Get renamed recv tables
	virtual void* *GetRenamedRecvTableInfos();
	// Get the mouthinfo for the sound being played inside UI panels
	virtual void*		GetClientUIMouthInfo();

	// Notify the client that a file has been received from the game server
	virtual void	FileReceived(const char * fileName, unsigned int transferID);

	virtual const char* TranslateEffectForVisionFilter(const char *pchEffectType, const char *pchEffectName);


	// there's more shit below 
};