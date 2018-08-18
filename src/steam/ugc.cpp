#include <SpecialK/steam_api.h>
#include <SpecialK/config.h>
#include <SpecialK/utility.h>

#include <Windows.h>
#include <cstdint>

#include <unordered_map>

class IWrapSteamUGC;

#include <concurrent_unordered_map.h>
concurrency::concurrent_unordered_map <ISteamUGC*, IWrapSteamUGC*>   SK_SteamWrapper_remap_ugc;

class IWrapSteamUGC010 : public ISteamUGC
{
public:
  IWrapSteamUGC010 (ISteamUGC* pUGC) :
                               pRealUGC (pUGC) {
  };


	// Query UGC associated with a user. Creator app id or consumer app id must be valid and be set to the current running app. unPage should start at 1.
	virtual UGCQueryHandle_t CreateQueryUserUGCRequest( AccountID_t unAccountID, EUserUGCList eListType, EUGCMatchingUGCType eMatchingUGCType, EUserUGCListSortOrder eSortOrder, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage ) override {
    steam_log.Log (L"ISteamUGC::CreateQueryUserUGCRequest (unAccountID=%x, type=%x)", unAccountID, eListType);

    return pRealUGC->CreateQueryUserUGCRequest (unAccountID, eListType, eMatchingUGCType, eSortOrder, nCreatorAppID, nConsumerAppID, unPage);
  }

	// Query for all matching UGC. Creator app id or consumer app id must be valid and be set to the current running app. unPage should start at 1.
	virtual UGCQueryHandle_t CreateQueryAllUGCRequest( EUGCQuery eQueryType, EUGCMatchingUGCType eMatchingeMatchingUGCTypeFileType, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage ) override {
    steam_log.Log (L"ISteamUGC::CreateQueryAllUGCRequest (type=%x)", eQueryType);

    return pRealUGC->CreateQueryAllUGCRequest (eQueryType, eMatchingeMatchingUGCTypeFileType, nCreatorAppID, nConsumerAppID, unPage);
  }

	// Query for the details of the given published file ids (the RequestUGCDetails call is deprecated and replaced with this)
	virtual UGCQueryHandle_t CreateQueryUGCDetailsRequest( PublishedFileId_t *pvecPublishedFileID, uint32 unNumPublishedFileIDs ) override {
    steam_log.Log (L"ISteamUGC::CreateQueryUGCDetailsRequest (..., %lu)", unNumPublishedFileIDs);

    return pRealUGC->CreateQueryUGCDetailsRequest (pvecPublishedFileID, unNumPublishedFileIDs);
  }

	// Send the query to Steam
	virtual SteamAPICall_t SendQueryUGCRequest( UGCQueryHandle_t handle ) override {
    steam_log.Log (L"ISteamUGC::SendQueryUGCResult (%x)", handle);

    return pRealUGC->SendQueryUGCRequest (handle);
  }

	// Retrieve an individual result after receiving the callback for querying UGC
	virtual bool GetQueryUGCResult( UGCQueryHandle_t handle, uint32 index, SteamUGCDetails_t *pDetails ) override {
    steam_log.Log (L"ISteamUGC::GetQueryUGCResult (%x)", handle);

    return pRealUGC->GetQueryUGCResult (handle, index, pDetails);
  }
	virtual bool GetQueryUGCPreviewURL( UGCQueryHandle_t handle, uint32 index, char *pchURL, uint32 cchURLSize ) override {
    return pRealUGC->GetQueryUGCPreviewURL (handle, index, pchURL, cchURLSize);
  }
	virtual bool GetQueryUGCMetadata( UGCQueryHandle_t handle, uint32 index, char *pchMetadata, uint32 cchMetadatasize ) override {
    return pRealUGC->GetQueryUGCMetadata (handle, index, pchMetadata, cchMetadatasize);
  }
	virtual bool GetQueryUGCChildren( UGCQueryHandle_t handle, uint32 index, PublishedFileId_t* pvecPublishedFileID, uint32 cMaxEntries ) override {
    return pRealUGC->GetQueryUGCChildren (handle, index, pvecPublishedFileID, cMaxEntries);
  }
	virtual bool GetQueryUGCStatistic( UGCQueryHandle_t handle, uint32 index, EItemStatistic eStatType, uint32 *pStatValue ) override {
    return pRealUGC->GetQueryUGCStatistic (handle, index, eStatType, pStatValue);
  }
	virtual uint32 GetQueryUGCNumAdditionalPreviews( UGCQueryHandle_t handle, uint32 index ) override {
    return pRealUGC->GetQueryUGCNumAdditionalPreviews (handle, index);
  }
	virtual bool GetQueryUGCAdditionalPreview( UGCQueryHandle_t handle, uint32 index, uint32 previewIndex, char *pchURLOrVideoID, uint32 cchURLSize, bool *pbIsImage ) override {
    return pRealUGC->GetQueryUGCAdditionalPreview (handle, index, previewIndex, pchURLOrVideoID, cchURLSize, pbIsImage);
  }
  virtual uint32 GetQueryUGCNumKeyValueTags (UGCQueryHandle_t handle, uint32 index) override {
    return pRealUGC->GetQueryUGCNumKeyValueTags (handle, index);
  }
	virtual bool GetQueryUGCKeyValueTag( UGCQueryHandle_t handle, uint32 index, uint32 keyValueTagIndex, char *pchKey, uint32 cchKeySize, char *pchValue, uint32 cchValueSize ) override {
    return pRealUGC->GetQueryUGCKeyValueTag (handle, index, keyValueTagIndex, pchKey, cchKeySize, pchValue, cchValueSize);
  }

	// Release the request to free up memory, after retrieving results
	virtual bool ReleaseQueryUGCRequest( UGCQueryHandle_t handle ) override {
    return pRealUGC->ReleaseQueryUGCRequest (handle);
  }

	// Options to set for querying UGC
	virtual bool AddRequiredTag( UGCQueryHandle_t handle, const char *pTagName ) override {
    return pRealUGC->AddRequiredTag (handle, pTagName);
  }
  virtual bool AddExcludedTag (UGCQueryHandle_t handle, const char *pTagName) override {
    return pRealUGC->AddExcludedTag (handle, pTagName);
  }
	virtual bool SetReturnKeyValueTags( UGCQueryHandle_t handle, bool bReturnKeyValueTags ) override {
    return pRealUGC->SetReturnKeyValueTags (handle, bReturnKeyValueTags);
  }
	virtual bool SetReturnLongDescription( UGCQueryHandle_t handle, bool bReturnLongDescription ) override {
    return pRealUGC->SetReturnLongDescription (handle, bReturnLongDescription);
  }
	virtual bool SetReturnMetadata( UGCQueryHandle_t handle, bool bReturnMetadata ) override {
    return pRealUGC->SetReturnMetadata (handle, bReturnMetadata);
  }
	virtual bool SetReturnChildren( UGCQueryHandle_t handle, bool bReturnChildren ) override {
    return pRealUGC->SetReturnChildren (handle, bReturnChildren);
  }
	virtual bool SetReturnAdditionalPreviews( UGCQueryHandle_t handle, bool bReturnAdditionalPreviews ) override {
    return pRealUGC->SetReturnChildren (handle, bReturnAdditionalPreviews);
  }
	virtual bool SetReturnTotalOnly( UGCQueryHandle_t handle, bool bReturnTotalOnly ) override {
    return pRealUGC->SetReturnTotalOnly (handle, bReturnTotalOnly);
  }
  virtual bool SetLanguage (UGCQueryHandle_t handle, const char *pchLanguage) override
  {
    return pRealUGC->SetLanguage (handle, pchLanguage);
  }
	virtual bool SetAllowCachedResponse( UGCQueryHandle_t handle, uint32 unMaxAgeSeconds ) override {
    return pRealUGC->SetAllowCachedResponse (handle, unMaxAgeSeconds);
  }

	// Options only for querying user UGC
	virtual bool SetCloudFileNameFilter( UGCQueryHandle_t handle, const char *pMatchCloudFileName ) override {
    return pRealUGC->SetCloudFileNameFilter (handle, pMatchCloudFileName);
  }

	// Options only for querying all UGC
	virtual bool SetMatchAnyTag( UGCQueryHandle_t handle, bool bMatchAnyTag ) override {
    return pRealUGC->SetMatchAnyTag (handle, bMatchAnyTag);
  }
  virtual bool SetSearchText (UGCQueryHandle_t handle, const char *pSearchText) override {
    return pRealUGC->SetSearchText (handle, pSearchText);
  }
  virtual bool SetRankedByTrendDays (UGCQueryHandle_t handle, uint32 unDays) override {
    return pRealUGC->SetRankedByTrendDays (handle, unDays);
  }
	virtual bool AddRequiredKeyValueTag( UGCQueryHandle_t handle, const char *pKey, const char *pValue ) override {
    return pRealUGC->AddRequiredKeyValueTag (handle, pKey, pValue);
  }

	// DEPRECATED - Use CreateQueryUGCDetailsRequest call above instead!
  virtual SteamAPICall_t RequestUGCDetails (PublishedFileId_t nPublishedFileID, uint32 unMaxAgeSeconds) override {
    return pRealUGC->RequestUGCDetails (nPublishedFileID, unMaxAgeSeconds);
  }

	// Steam Workshop Creator API
	virtual SteamAPICall_t CreateItem( AppId_t nConsumerAppId, EWorkshopFileType eFileType ) override {
    return pRealUGC->CreateItem (nConsumerAppId, eFileType);
  }; // create new item for this app with no content attached yet

	virtual UGCUpdateHandle_t StartItemUpdate( AppId_t nConsumerAppId, PublishedFileId_t nPublishedFileID ) override {
    return pRealUGC->StartItemUpdate (nConsumerAppId, nPublishedFileID);
  }; // start an UGC item update. Set changed properties before commiting update with CommitItemUpdate()

	virtual bool SetItemTitle( UGCUpdateHandle_t handle, const char *pchTitle ) override { // change the title of an UGC item
    return pRealUGC->SetItemTitle (handle, pchTitle);
  }
	virtual bool SetItemDescription( UGCUpdateHandle_t handle, const char *pchDescription ) override {
    return pRealUGC->SetItemDescription (handle, pchDescription);
  }; // change the description of an UGC item
	virtual bool SetItemUpdateLanguage( UGCUpdateHandle_t handle, const char *pchLanguage ) override {
    return pRealUGC->SetItemUpdateLanguage (handle, pchLanguage);
  } // specify the language of the title or description that will be set
	virtual bool SetItemMetadata( UGCUpdateHandle_t handle, const char *pchMetaData ) override {
    return pRealUGC->SetItemMetadata (handle, pchMetaData);
  } // change the metadata of an UGC item (max = k_cchDeveloperMetadataMax)
	virtual bool SetItemVisibility( UGCUpdateHandle_t handle, ERemoteStoragePublishedFileVisibility eVisibility ) override {
    return pRealUGC->SetItemVisibility (handle, eVisibility);
  } // change the visibility of an UGC item
	virtual bool SetItemTags( UGCUpdateHandle_t updateHandle, const SteamParamStringArray_t *pTags ) override { // change the tags of an UGC item 
    return pRealUGC->SetItemTags (updateHandle, pTags);
  }
	virtual bool SetItemContent( UGCUpdateHandle_t handle, const char *pszContentFolder ) override { // update item content from this local folder
    return pRealUGC->SetItemContent (handle, pszContentFolder);
  }
	virtual bool SetItemPreview( UGCUpdateHandle_t handle, const char *pszPreviewFile ) override { //  change preview image file for this item. pszPreviewFile points to local image file, which must be under 1MB in size
    return pRealUGC->SetItemPreview (handle, pszPreviewFile);
  }
	virtual bool RemoveItemKeyValueTags( UGCUpdateHandle_t handle, const char *pchKey ) override { // remove any existing key-value tags with the specified key
    return pRealUGC->RemoveItemKeyValueTags (handle, pchKey);
  }
	virtual bool AddItemKeyValueTag( UGCUpdateHandle_t handle, const char *pchKey, const char *pchValue ) override { // add new key-value tags for the item. Note that there can be multiple values for a tag.
    return pRealUGC->AddItemKeyValueTag (handle, pchKey, pchValue);
  }

	virtual SteamAPICall_t SubmitItemUpdate( UGCUpdateHandle_t handle, const char *pchChangeNote ) override { // commit update process started with StartItemUpdate()
    return pRealUGC->SubmitItemUpdate (handle, pchChangeNote);
  }
  virtual EItemUpdateStatus GetItemUpdateProgress (UGCUpdateHandle_t handle, uint64 *punBytesProcessed, uint64* punBytesTotal) override {
    return pRealUGC->GetItemUpdateProgress (handle, punBytesProcessed, punBytesTotal);
  }

	// Steam Workshop Consumer API
  virtual SteamAPICall_t SetUserItemVote (PublishedFileId_t nPublishedFileID, bool bVoteUp) override {
    return pRealUGC->SetUserItemVote (nPublishedFileID, bVoteUp);
  }
  virtual SteamAPICall_t GetUserItemVote (PublishedFileId_t nPublishedFileID) override {
    return pRealUGC->GetUserItemVote (nPublishedFileID);
  }
  virtual SteamAPICall_t AddItemToFavorites (AppId_t nAppId, PublishedFileId_t nPublishedFileID) override {
    return pRealUGC->AddItemToFavorites (nAppId, nPublishedFileID);
  }
  virtual SteamAPICall_t RemoveItemFromFavorites (AppId_t nAppId, PublishedFileId_t nPublishedFileID) override {
    return pRealUGC->RemoveItemFromFavorites (nAppId, nPublishedFileID);
  }
	virtual SteamAPICall_t SubscribeItem( PublishedFileId_t nPublishedFileID ) override {
    return pRealUGC->SubscribeItem (nPublishedFileID);
  }; // subscribe to this item, will be installed ASAP
	virtual SteamAPICall_t UnsubscribeItem( PublishedFileId_t nPublishedFileID ) override { // unsubscribe from this item, will be uninstalled after game quits
    return pRealUGC->UnsubscribeItem (nPublishedFileID);
  }
	virtual uint32 GetNumSubscribedItems() override { // number of subscribed items 
    steam_log.Log (L"ISteamUGC::GetNumSubscribedItems (...)");

    if ((int)SK_SteamUser_BLoggedOn () & (int)SK_SteamUser_LoggedOn_e::Online)
      return pRealUGC->GetNumSubscribedItems ();
    else
      return 0;
  }
	virtual uint32 GetSubscribedItems( PublishedFileId_t* pvecPublishedFileID, uint32 cMaxEntries ) override { // all subscribed item PublishFileIDs
    steam_log.Log (L"ISteamUGC::GetSubscribedItems (...)");

    return pRealUGC->GetSubscribedItems (pvecPublishedFileID, cMaxEntries);
  }

	// get EItemState flags about item on this client
  virtual uint32 GetItemState (PublishedFileId_t nPublishedFileID) override {
    steam_log.Log (L"ISteamUGC::GetItemState (%x)", nPublishedFileID);

    if ((int)SK_SteamUser_BLoggedOn () & (int)SK_SteamUser_LoggedOn_e::Online)
      return pRealUGC->GetItemState (nPublishedFileID);
    else
      return EItemState::k_EItemStateNone;
  }

	// get info about currently installed content on disc for items that have k_EItemStateInstalled set
	// if k_EItemStateLegacyItem is set, pchFolder contains the path to the legacy file itself (not a folder)
  virtual bool GetItemInstallInfo (PublishedFileId_t nPublishedFileID, uint64 *punSizeOnDisk, char *pchFolder, uint32 cchFolderSize, uint32 *punTimeStamp) override {
    steam_log.Log (L"ISteamUGC::GetItemInstallInfo (%x)", nPublishedFileID);

    return pRealUGC->GetItemInstallInfo (nPublishedFileID, punSizeOnDisk, pchFolder, cchFolderSize, punTimeStamp);
  }

	// get info about pending update for items that have k_EItemStateNeedsUpdate set. punBytesTotal will be valid after download started once
  virtual bool GetItemDownloadInfo (PublishedFileId_t nPublishedFileID, uint64 *punBytesDownloaded, uint64 *punBytesTotal) override {
    steam_log.Log (L"ISteamUGC::GetItemDownloadlInfo (%x)", nPublishedFileID);

    return pRealUGC->GetItemDownloadInfo (nPublishedFileID, punBytesDownloaded, punBytesTotal);
  }
		
	// download new or update already installed item. If function returns true, wait for DownloadItemResult_t. If the item is already installed,
	// then files on disk should not be used until callback received. If item is not subscribed to, it will be cached for some time.
	// If bHighPriority is set, any other item download will be suspended and this item downloaded ASAP.
  virtual bool DownloadItem (PublishedFileId_t nPublishedFileID, bool bHighPriority) override {
    steam_log.Log (L"ISteamUGC::DownloadItem (%x, { bHighPriorty = %s })", nPublishedFileID, bHighPriority ? L"true" : L"false");

    return pRealUGC->DownloadItem (nPublishedFileID, bHighPriority);
  }

  //
  // END VERSION 007
  //

  virtual bool BInitWorkshopForGameServer (DepotId_t unWorkshopDepotID, const char *pszFolder) override {
    steam_log.Log (L"ISteamUGC::BInitWorkshopForGameServer (...)");

    return pRealUGC->BInitWorkshopForGameServer (unWorkshopDepotID, pszFolder);
  }

  virtual void SuspendDownloads (bool bSuspend) override {
    return pRealUGC->SuspendDownloads (bSuspend);
  }

  virtual SteamAPICall_t StartPlaytimeTracking (PublishedFileId_t *pvecPublishedFileID, uint32 unNumPublishedFileIDs) override {
    return pRealUGC->StartPlaytimeTracking (pvecPublishedFileID, unNumPublishedFileIDs);
  }

  virtual SteamAPICall_t StopPlaytimeTracking (PublishedFileId_t *pvecPublishedFileID, uint32 unNumPublishedFileIDs) override {
    return pRealUGC->StopPlaytimeTracking (pvecPublishedFileID, unNumPublishedFileIDs);
  }

  virtual SteamAPICall_t StopPlaytimeTrackingForAllItems (void) override {
    return pRealUGC->StopPlaytimeTrackingForAllItems ();
  }

  virtual SteamAPICall_t AddDependency (PublishedFileId_t nParentPublishedFileID, PublishedFileId_t nChildPublishedFileID) override {
    return pRealUGC->AddDependency (nParentPublishedFileID, nChildPublishedFileID);
  }

  virtual SteamAPICall_t RemoveDependency (PublishedFileId_t nParentPublishedFileID, PublishedFileId_t nChildPublishedFileID) override {
    return pRealUGC->RemoveDependency (nParentPublishedFileID, nChildPublishedFileID);
  }

private:
  ISteamUGC* pRealUGC;
};

using SteamAPI_ISteamClient_GetISteamUGC_pfn = ISteamUGC* (S_CALLTYPE *)(
  ISteamClient *This,
  HSteamUser    hSteamuser,
  HSteamPipe    hSteamPipe,
  const char   *pchVersion
  );
SteamAPI_ISteamClient_GetISteamUGC_pfn   SteamAPI_ISteamClient_GetISteamUGC_Original = nullptr;

#define STEAMUGC_INTERFACE_VERSION "STEAMUGC_INTERFACE_VERSION010"

ISteamUGC*
S_CALLTYPE
SteamAPI_ISteamClient_GetISteamUGC_Detour ( ISteamClient *This,
                                            HSteamUser    hSteamuser,
                                            HSteamPipe    hSteamPipe,
                                            const char   *pchVersion )
{
  SK_RunOnce (
    steam_log.Log ( L"[!] %hs (..., %hs)",
                      __FUNCTION__, pchVersion )
  );

  ISteamUGC* pUGC =
    SteamAPI_ISteamClient_GetISteamUGC_Original ( This,
                                                    hSteamuser,
                                                      hSteamPipe,
                                                        pchVersion );

  if (pUGC != nullptr)
  {
    if ((! lstrcmpA (pchVersion, STEAMUGC_INTERFACE_VERSION)))
    {
      if (SK_SteamWrapper_remap_ugc.count (pUGC))
         return reinterpret_cast <ISteamUGC *> (SK_SteamWrapper_remap_ugc [pUGC]);

      else
      {
        SK_SteamWrapper_remap_ugc [pUGC] =
          reinterpret_cast <IWrapSteamUGC *> (
                new IWrapSteamUGC010 (pUGC)
          );

        return reinterpret_cast <ISteamUGC *> (SK_SteamWrapper_remap_ugc [pUGC]);
      }
    }

    else
    {
      SK_RunOnce (
        steam_log.Log ( L"Game requested unexpected interface version (%hs)!",
                          pchVersion )
      );

      return pUGC;
    }
  }

  return nullptr;
}

ISteamUGC*
SK_SteamWrapper_WrappedClient_GetISteamUGC ( ISteamClient *This,
                                             HSteamUser    hSteamuser,
                                             HSteamPipe    hSteamPipe,
                                             const char   *pchVersion )
{
  SK_RunOnce (
    steam_log.Log ( L"[!] %hs (..., %hs)",
                      __FUNCTION__, pchVersion )
  );

  ISteamUGC* pUGC =
    This->GetISteamUGC ( hSteamuser,
                           hSteamPipe,
                             pchVersion );

  if (pUGC != nullptr)
  {
    if ((! lstrcmpA (pchVersion, STEAMUGC_INTERFACE_VERSION)))
    {
      if (SK_SteamWrapper_remap_ugc.count (pUGC))
         return reinterpret_cast <ISteamUGC *> (SK_SteamWrapper_remap_ugc [pUGC]);

      else
      {
        SK_SteamWrapper_remap_ugc [pUGC] =
          reinterpret_cast <IWrapSteamUGC *> (
                new IWrapSteamUGC010 (pUGC)
          );

        return reinterpret_cast <ISteamUGC *> (SK_SteamWrapper_remap_ugc [pUGC]);
      }
    }

    else
    {
      SK_RunOnce (
        steam_log.Log ( L"Game requested unexpected interface version (%hs)!",
                          pchVersion )
      );

      return pUGC;
    }
  }

  return nullptr;
}

using SteamUGC_pfn = ISteamUGC* (S_CALLTYPE *)(
        void
      );
SteamUGC_pfn SteamUGC_Original = nullptr;

ISteamUGC*
S_CALLTYPE
SteamUGC_Detour (void)
{
  SK_RunOnce (
    steam_log.Log ( L"[!] %hs ()",
                      __FUNCTION__ )
  );

#ifndef DANGEROUS_INTERFACE_ALIASING
  return SteamUGC_Original ( );
#else
  if (steam_ctx.UGCVersion () == 10)
  {
    ISteamUGC* pUGC =
      static_cast <ISteamUGC *> ( SteamUGC_Original () );
    
    if (SK_SteamWrapper_remap_ugc.count (pUGC))
       return reinterpret_cast <ISteamUGC *> (SK_SteamWrapper_remap_ugc [pUGC]);

    else
    {
      SK_SteamWrapper_remap_ugc [pUGC] =
        reinterpret_cast <IWrapSteamUGC *> (
              new IWrapSteamUGC010 (pUGC)
        );

      return reinterpret_cast <ISteamUGC *> (SK_SteamWrapper_remap_ugc [pUGC]);
    }
  }

  return SteamUGC_Original ();
#endif
}